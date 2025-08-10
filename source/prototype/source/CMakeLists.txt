cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(picture_frame)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()




# rest of your project

add_executable(picture_frame
    picture_frame.c
    )

# pull in common dependencies
target_link_libraries(picture_frame 
    pico_stdlib
    hardware_i2c
    hardware_gpio
)
pico_enable_stdio_usb(picture_frame 1)
pico_enable_stdio_uart(picture_frame 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(picture_frame)



