
cmake_minimum_required(VERSION 3.10)
project(NetworkScanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


add_executable(netls
    main_cli.cpp
    source/network_scanner.cpp
    source/device.cpp
    source/host_device.cpp
    source/network_device.cpp
    source/arp.c
    source/icmp.c
    source/utils.c
)

if (WIN32)
    target_link_libraries(netls PRIVATE ws2_32 iphlpapi)
endif()