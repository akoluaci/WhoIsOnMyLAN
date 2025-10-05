#include "backend_handler.hpp"
#include <iostream>
<<<<<<< HEAD
#include <QTimer>
#include <QThread>
// #include <QVariant>

BackendHandler::BackendHandler(QObject* parent)
    : QObject(parent),
      second(0)
=======
// #include <QVariant>

BackendHandler::BackendHandler(QObject* parent)
    : QObject(parent)
>>>>>>> f80e74b (Backend can connec information to UI)
{
    
}

void BackendHandler::triggerDataGeneration() {
<<<<<<< HEAD
    // qDebug() << "BackendHandler: Rastgele veri uretimi tetiklendi.";
    networkScanner.getHostDevice();
    // emit hostInfoReady(devices);
    networkScanner.scan();
    // QVariant dataVariant = QVariant::fromValue(devices);
    auto devices = networkScanner.getDevicePointers();
    emit dataReady(devices);
}

void BackendHandler::setStopRequest(std::atomic<bool> _value) {
    networkScanner.setStopRequest(_value.load());
}

// void BackendHandler::setElapsedTimer() {
//     QTimer *timer = new QTimer(this);
//     connect(timer, &QTimer::timeout, this, &BackendHandler::incrementTimer);
//     std::cout << "timer is set\n";
//     timer->start(1000);
// }

// void BackendHandler::incrementTimer() {
//     ++second;
//     emit timeUpdated(second);
// }

// void BackendHandler::hostInfoReady(const std::vector<const Device *>& data) {
=======
    qDebug() << "BackendHandler: Rastgele veri uretimi tetiklendi.";
    networkScanner.getHostDevice();
    networkScanner.scan();
    auto devices = networkScanner.getDevicePointers();
    // QVariant dataVariant = QVariant::fromValue(devices);
    emit dataReady(devices);
}
// void BackendHandler::hostInfoReady() {
>>>>>>> f80e74b (Backend can connec information to UI)
//     std::cout << "Host info ready now!\n";
// }

// void BackendHandler::fullListReady() {
//     std::cout << "Network devices are found now!\n";
// }
<<<<<<< HEAD
=======

/*
I dont think you understand me again.

My backend files are in include and source folder. There is nothing about Qt inside them.

I wanna do everyting about GUI under my GUI folder. So please think this like there is even no inclusion of Qt libraries in the files under include and source folders.

I cannot understand TodoItem structure since I have already a class to hold my Todos. I can handle it with that class, I think.

I am now trying to add my backendhandler class under GUI folder.

Please me guide me considering this information.
*/
>>>>>>> f80e74b (Backend can connec information to UI)
