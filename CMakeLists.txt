cmake_minimum_required(VERSION 3.20.0)

project(WS2812FX-zephyr)

if (NOT ${Zephyr_FOUND})
    message(FATAL_ERROR "Build must be done in a Zephyr application")
endif()

add_subdirectory(src/Adafruit_NeoPixel_zephyr)

FILE(GLOB sources src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${sources})

target_sources(${PROJECT_NAME} INTERFACE
    FILE_SET HEADERS
    BASE_DIRS src
    FILES src/WS2812FX.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC Adafruit_NeoPixel_zephyr)
target_link_libraries(${PROJECT_NAME} PUBLIC zephyr_interface)
