#ifndef BACKEND_HANDLER_H
#define BACKEND_HANDLER_H

#include "network_scanner.hpp"
#include <QObject>
#include <QVector>
#include "device.hpp"
#include "host_device.hpp"
#include "network_device.hpp"
#include <QVariant>

class BackendHandler : public QObject
{
    Q_OBJECT
private:
    /* data */
    NetworkScanner networkScanner;
    int second;
    // std::atomic<bool> stopRequest;
public:
    BackendHandler(QObject *parent = nullptr);
    ~BackendHandler() = default;

    void triggerDataGeneration(); 
    void setStopRequest(std::atomic<bool> _value);
// public slots:
//     void setElapsedTimer();
// private slots:
//     void  incrementTimer();
signals:
    void dataReady(const std::vector<const Device*>& data);
    // void timeUpdated(int second);
};


#endif