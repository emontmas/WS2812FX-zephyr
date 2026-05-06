cmake_minimum_required(VERSION 3.20.0)

project(Adafruit_NeoPixel_zephyr)

if (NOT ${Zephyr_FOUND})
    message(FATAL_ERROR "Build must be done in a Zephyr application")
endif()

FILE(GLOB sources *.cpp)

add_library(${PROJECT_NAME} STATIC ${sources})

target_sources(${PROJECT_NAME} INTERFACE
    FILE_SET HEADERS
    BASE_DIRS .
    FILES Adafruit_NeoPixel.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC zephyr_interface)
