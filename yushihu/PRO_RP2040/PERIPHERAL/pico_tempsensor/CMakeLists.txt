
cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)


project(pico_tempsensor)

pico_sdk_init()


add_executable(tempsensor
        tempsensor.c
)

target_link_libraries(tempsensor
        pico_stdlib
        hardware_adc
)

pico_enable_stdio_usb(tempsensor 1)
pico_enable_stdio_uart(tempsensor 0)

pico_add_extra_outputs(tempsensor)
