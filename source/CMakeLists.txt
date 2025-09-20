# source/CMakeLists.txt
add_library(BackendCore STATIC
    network_scanner.cpp
    device.cpp
    host_device.cpp
    network_device.cpp
    arp.c
    icmp.c
    utils.c
)

target_include_directories(BackendCore 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

if (WIN32)
    target_link_libraries(BackendCore PRIVATE ws2_32 iphlpapi)
endif()