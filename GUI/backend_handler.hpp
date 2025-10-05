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
<<<<<<< HEAD
    int second;
    // std::atomic<bool> stopRequest;
=======
>>>>>>> f80e74b (Backend can connec information to UI)
public:
    BackendHandler(QObject *parent = nullptr);
    ~BackendHandler() = default;

<<<<<<< HEAD
    void triggerDataGeneration(); 
    void setStopRequest(std::atomic<bool> _value);
// public slots:
//     void setElapsedTimer();
// private slots:
//     void  incrementTimer();
signals:
    void dataReady(const std::vector<const Device*>& data);
    // void timeUpdated(int second);
=======
    void triggerDataGeneration(); // Butondan çağrılacak yeni metot

signals:
    void dataReady(const std::vector<const Device*>& data);
    
>>>>>>> f80e74b (Backend can connec information to UI)
};


#endif