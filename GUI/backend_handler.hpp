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
<<<<<<< HEAD
    int second;
    // std::atomic<bool> stopRequest;
=======
>>>>>>> f80e74b (Backend can connec information to UI)
=======
    int second;
    // std::atomic<bool> stopRequest;
>>>>>>> c3eb0db (backend and timer start/stop issue fixed)
public:
    BackendHandler(QObject *parent = nullptr);
    ~BackendHandler() = default;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c02e6f3 (project name changed, make compatible to build with and without ui program)
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
    void setStopRequest(std::atomic<bool> _value);
// public slots:
//     void setElapsedTimer();
// private slots:
//     void  incrementTimer();
signals:
    void dataReady(const std::vector<const Device*>& data);
<<<<<<< HEAD
    
>>>>>>> f80e74b (Backend can connec information to UI)
=======
    // void timeUpdated(int second);
>>>>>>> c3eb0db (backend and timer start/stop issue fixed)
};


#endif