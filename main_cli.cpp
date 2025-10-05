#include <iostream>
// #include "network_scanner.hpp"
// #include "host_device.hpp"
#include "network_device.hpp"
<<<<<<< HEAD:main_cli.cpp
=======
#include "GUI/mainwindow.h"
#include "GUI/backend_handler.hpp"
#include <QApplication>
>>>>>>> f80e74b (Backend can connec information to UI):main.cpp


int main(int argc, char const *argv[])
{
    // HostDevice hostDevice;
    
<<<<<<< HEAD:main_cli.cpp
    NetworkScanner networkScanner;
    networkScanner.getHostDevice();
    Device& dev = networkScanner.getDevice(0);
    try
    {
        HostDevice& hostDevice = dynamic_cast<HostDevice&>(dev);
        std::cout << "Host Device Information:\n";
        hostDevice.printDeviceInformation();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
=======
    // NetworkScanner networkScanner;
    // Device& dev = networkScanner.getDevice(0);

    // try
    // {
    //     HostDevice& hostDevice = dynamic_cast<HostDevice&>(dev);
    //     hostDevice.printDeviceInformation();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
>>>>>>> f80e74b (Backend can connec information to UI):main.cpp
    
    // networkScanner.scan();
    
<<<<<<< HEAD:main_cli.cpp
    int deviceCount = networkScanner.getDeviceCount();
    std::cout << "\n----------------\nDevices in the network:\n";
    for (int i = 1; i < deviceCount; ++i) {
        Device& dev1 = networkScanner.getDevice(i);
        try
        {
            NetworkDevice& networkDevice = dynamic_cast<NetworkDevice&>(dev1);
            networkDevice.printDeviceInformation();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }    
    std::cout << "\n " << deviceCount << " device(s) found in the network.\n";
    return 0;
=======
    // int deviceCount = networkScanner.getDeviceCount();
    // // std::cout << "Device Count: " << deviceCount << "\n";
    
    // for (int i = 1; i < deviceCount; ++i) {
    //     Device& dev1 = networkScanner.getDevice(i);
    //     try
    //     {
    //         NetworkDevice& networkDevice = dynamic_cast<NetworkDevice&>(dev1);
    //         networkDevice.printDeviceInformation();
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << '\n';
    //     }
    // }    
    // return 0;

    QApplication a(argc, argv);
    BackendHandler backendHandler;
    MainWindow w;

    // QObject::connect(&backendHandler, &BackendHandler::hostInfoReady,
    //              &w,              &MainWindow::handleHostDeviceInfo);

    // QObject::connect(&backendHandler, &BackendHandler::fullListReady,
    //             &w,              &MainWindow::handleNetworkDeviceInfo);
    


    w.show();
    return a.exec();
>>>>>>> f80e74b (Backend can connec information to UI):main.cpp
}
