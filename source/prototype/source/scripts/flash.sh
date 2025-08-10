#!/bin/bash

UF2FILE=$1
MOUNTPOINT=/mnt/pico

if [ -z "$UF2FILE" ]; then
    echo "Usage: $0 path/to/firmware.uf2"
    exit 1
fi

echo "Rebooting Pico into BOOTSEL mode..."
sudo picotool reboot -u -f

echo "Waiting 3 seconds for device to disconnect/reconnect..."
sleep 3

echo "Calling Windows script to attach BOOTSEL device to WSL..."
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "$(wslpath -w ./attach.ps1)"
if [ $? -ne 0 ]; then
    echo "Failed to attach BOOTSEL device to WSL."
    exit 1
fi

echo "Mounting BOOTSEL mass storage device..."
sudo mkdir -p $MOUNTPOINT
sudo mount -t vfat /dev/sdX1 $MOUNTPOINT  # Replace /dev/sdX1 with actual device node

echo "Copying UF2 file to Pico..."
sudo cp "$UF2FILE" "$MOUNTPOINT/"

echo "Sync and unmounting..."
sync
sudo umount $MOUNTPOINT

echo "Done. Pico is flashed and will reboot automatically."
