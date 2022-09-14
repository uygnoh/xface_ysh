
cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)


project(pico_i2c)

pico_sdk_init()


add_executable(i2c
        i2c.c
)

target_link_libraries(i2c
        pico_stdlib
        hardware_i2c
)

pico_enable_stdio_usb(i2c 1)
pico_enable_stdio_uart(i2c 0)

pico_add_extra_outputs(i2c)
