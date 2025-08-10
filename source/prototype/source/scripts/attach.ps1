# attach_bootsel.ps1
# Wait for RPI-RP2 (BOOTSEL) device to appear and attach it to WSL

param(
    [int]$TimeoutSeconds = 10
)

$endTime = (Get-Date).AddSeconds($TimeoutSeconds)

while ((Get-Date) -lt $endTime) {
    $devices = usbipd list

    $bootDeviceLine = $devices | Where-Object { $_ -match 'RP2' }
    if ($bootDeviceLine) {
        $busid = ($bootDeviceLine -split '\s+')[0]
        Write-Host "Found BOOTSEL device with busid: $busid"
        usbipd attach --wsl --busid $busid
        exit 0
    }
    Start-Sleep -Seconds 1
}

Write-Host "Timeout waiting for BOOTSEL device"
exit 1
