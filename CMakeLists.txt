# CMake'in minimum versiyonunu ve proje adını belirtir
cmake_minimum_required(VERSION 3.10)
project(NetworkScanner)

# C++17 standardını kullanacağımızı belirtir
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Başlık dosyalarının (.h, .hpp) bulunduğu 'include' klasörünü tanıtır
include_directories(include)

# CMake tüm çalıştırılabilir dosyaları ve DLL'leri build/bin klasörüne yerleştirecek
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Çalıştırılabilir programı (netscan) ve onu oluşturacak kaynak dosyalarını listeler
# Bu en standart ve hatasız yöntemdir
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

# Gerekli kütüphaneleri programa bağlar
# Bu blok, programın Windows üzerinde derlenirken ağ fonksiyonları için
# gerekli olan kütüphaneleri bulmasını sağlar.
if (WIN32)
    target_link_libraries(netls PRIVATE ws2_32 iphlpapi)
endif()