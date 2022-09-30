
cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)


project(pico_spi)

pico_sdk_init()


add_executable(spi
        spi.c
)

target_link_libraries(spi
        pico_stdlib
        hardware_spi
)

pico_enable_stdio_usb(spi 1)
pico_enable_stdio_uart(spi 0)

pico_add_extra_outputs(spi)
