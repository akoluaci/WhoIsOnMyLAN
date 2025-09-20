cmake_minimum_required(VERSION 3.10)
project(NetworkScanner)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


add_executable(netls_cli
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
    target_link_libraries(netls_cli PRIVATE ws2_32 iphlpapi)
endif()

add_subdirectory(source)
add_subdirectory(GUI)

add_executable(netls_ui main_ui.cpp)


target_include_directories(netls_ui
    PRIVATE
        ${CMAKE_SOURCE_DIR}/GUI     
        ${CMAKE_SOURCE_DIR}/include 
)


target_link_libraries(netls_ui 
    PRIVATE 
        ui      
        BackendCore   
        Qt6::Widgets   
)

