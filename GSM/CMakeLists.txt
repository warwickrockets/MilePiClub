cmake_minimum_required(VERSION 2.8.3)
project(GSM)

include_directories(lib/serial/include)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(serial_SRCS lib/serial/src/serial.cc lib/serial/include/serial/serial.h lib/serial/include/serial/v8stdint.h)
if(UNIX)
    list(APPEND serial_SRCS lib/serial/src/impl/unix.cc)
    if(NOT APPLE)
        list(APPEND serial_SRCS lib/serial/src/impl/list_ports/list_ports_linux.cc)
    else()
        list(APPEND serial_SRCS lib/serial/src/impl/list_ports/list_ports_osx.cc)
    endif()
else()
    list(APPEND serial_SRCS lib/serial/src/impl/win.cc)
    list(APPEND serial_SRCS lib/serial/src/impl/list_ports/list_ports_win.cc)
endif()

## Add serial library
add_library(serial ${serial_SRCS})
if(UNIX AND NOT APPLE)
    target_link_libraries(serial rt)
endif()

## Build your executable
add_executable(GSM src/main.cpp src/sim900.cpp)
## Link your executable against the library
target_link_libraries(GSM serial)
