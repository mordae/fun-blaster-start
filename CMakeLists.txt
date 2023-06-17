cmake_minimum_required(VERSION 3.12)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

set(PICO_BOARD fun_blaster_10)
set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/src/boards)

add_definitions(-I${CMAKE_CURRENT_LIST_DIR}/src)
add_definitions(-I${CMAKE_CURRENT_LIST_DIR}/vendor/pico-task/include)
list(APPEND PICO_CONFIG_HEADER_FILES task_hooks.h)

project(fun_blaster)
pico_sdk_init()

add_subdirectory(vendor/pico-switch)
add_subdirectory(vendor/pico-task)
add_subdirectory(src)


# vim:set sw=2 ts=2 et:
