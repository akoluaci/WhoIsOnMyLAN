# cmake_minimum_required(VERSION 3.19)
# project(LoginForm LANGUAGES CXX)

# # No need to find_package here if the main project already does
# # find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# qt_standard_project_setup()

# # Create a library instead of an executable
# qt_add_library(LoginForm
#     mainwindow.cpp
#     mainwindow.h
#     mainwindow.ui
#     backend_handler.hpp
#     backend_handler.cpp
# )

# target_link_libraries(LoginForm
#     PRIVATE
#         Qt6::Core
#         Qt6::Widgets
#         BackendCore
# )

<<<<<<< HEAD
qt_wrap_ui(NETLS_UI_HEADERS mainwindow.ui)

qt_wrap_cpp(NETLS_MOC_SRCS 
    mainwindow.h
    backend_handler.hpp
    TimerWorker.h
)


add_library(ui STATIC
    mainwindow.cpp
    backend_handler.cpp
    TimerWorker.cpp
    ${NETLS_UI_HEADERS}
    ${NETLS_MOC_SRCS}
)

target_include_directories(ui
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# 5. Linkleme (aynı kalır)
target_link_libraries(ui
    PRIVATE
=======
# GUI/CMakeLists.txt (Manuel Yapılandırma)

# 1. UI dosyasını işleyen (uic) komutunu tanımla.
# uic çıktısını her zaman derleme dizinindeki bir alt klasörde oluşturur.
# Bu dosya (ui_mainwindow.h) artık bir kaynak (source) dosyası gibi işlenecek.
qt_wrap_ui(LOGINFORM_UI_HEADERS mainwindow.ui)

# 2. Q_OBJECT macro'larını işleyen (moc) komutunu tanımla.
# Hem mainwindow.h hem de backend_handler.hpp Q_OBJECT içeriyor.
qt_wrap_cpp(LOGINFORM_MOC_SRCS 
    mainwindow.h
    backend_handler.hpp
    TimerWorker.h
)

# 3. Kütüphaneyi oluştur.
add_library(LoginForm STATIC
    mainwindow.cpp
    backend_handler.cpp
    TimerWorker.cpp
    ${LOGINFORM_UI_HEADERS}
    ${LOGINFORM_MOC_SRCS}
)

# 4. KRİTİK INCLUDE AYARI: ui_mainwindow.h'nin bulunduğu dizini ekle.
# qt_wrap_ui çıktıyı doğrudan ${CMAKE_CURRENT_BINARY_DIR}'da oluşturur.
target_include_directories(LoginForm
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# 5. Linkleme (aynı kalır)
target_link_libraries(LoginForm
    PRIVATE
>>>>>>> f80e74b (Backend can connec information to UI)
        BackendCore 
        Qt6::Widgets
        Qt6::Core    
)