cmake_minimum_required (VERSION 3.22.0)
project (WebPageMaker)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wpedantic")
file(GLOB SOURCE "src/*.c")
file(GLOB HEADERS "include/*.h")
include_directories("${CMAKE_SOURCE_DIR}/include/")
add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS} ${APP_ICON_RESOURCE_WINDOWS})