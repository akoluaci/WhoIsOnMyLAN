#include "backend_handler.hpp"
#include <iostream>
#include <QTimer>
#include <QThread>
// #include <QVariant>

BackendHandler::BackendHandler(QObject* parent)
    : QObject(parent),
      second(0)
{
    
}

void BackendHandler::triggerDataGeneration() {
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
//     std::cout << "Host info ready now!\n";
// }

// void BackendHandler::fullListReady() {
//     std::cout << "Network devices are found now!\n";
// }
