<<<<<<< HEAD
cmake_minimum_required(VERSION 3.10)
project(NetworkScanner)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

=======
# # CMake'in minimum versiyonunu ve proje adını belirtir
# cmake_minimum_required(VERSION 3.10)
# project(NetworkScanner)

# # C++17 standardını kullanacağımızı belirtir
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Find Qt6 here so all targets know about it
# find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)


# # Başlık dosyalarının (.h, .hpp) bulunduğu 'include' klasörünü tanıtır
# include_directories(include)

# # CMake tüm çalıştırılabilir dosyaları ve DLL'leri build/bin klasörüne yerleştirecek
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# add_subdirectory(source)

# # Add the GUI subdirectory. This will build the 'LoginForm' target as a library.
# add_subdirectory(GUI)

# # Çalıştırılabilir programı (netscan) ve onu oluşturacak kaynak dosyalarını listeler
# # Bu en standart ve hatasız yöntemdir
# add_executable(netscan
#     main.cpp
# )

# # Link netscan to the GUI library and Qt
# target_link_libraries(netscan PRIVATE LoginForm BackendCore Qt6::Widgets)

# # Gerekli kütüphaneleri programa bağlar
# # Bu blok, programın Windows üzerinde derlenirken ağ fonksiyonları için
# # gerekli olan kütüphaneleri bulmasını sağlar.
# # if (WIN32)
# #     target_link_libraries(netscan PRIVATE ws2_32 iphlpapi)
# # endif()

# # windeployqt aracını bulma
# # find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS
# #     "${Qt6_DIR}/../../bin"
# # )

# # # netscan.exe derlendikten sonra windeployqt'yi çalıştır
# # add_custom_command(
# #     TARGET netscan
# #     POST_BUILD
# #     COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:netscan>"
# #     COMMENT "Deploying Qt dependencies with windeployqt..."
# # )

# Kök/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NetworkScanner VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# include dizinini genel olarak tanımla, böylece diğerleri random_generator.hpp'yi bulur.
>>>>>>> f80e74b (Backend can connec information to UI)
include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

<<<<<<< HEAD

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

=======
add_subdirectory(source)
add_subdirectory(GUI)

add_executable(netscan main.cpp)

# main.cpp'nin mainwindow.h'yi bulabilmesi için GUI yolunu eklemeye devam ediyoruz.
target_include_directories(netscan
    PRIVATE
        ${CMAKE_SOURCE_DIR}/GUI     # mainwindow.h ve backend_handler.hpp için
        ${CMAKE_SOURCE_DIR}/include # random_generator.hpp için
)

# netscan'i GUI ve Backend kütüphanelerine ve gerekli Qt modüllerine bağla.
target_link_libraries(netscan 
    PRIVATE 
        LoginForm      
        BackendCore    # RandomGenerator'ı içeren kütüphane
        Qt6::Widgets   
)
>>>>>>> f80e74b (Backend can connec information to UI)
