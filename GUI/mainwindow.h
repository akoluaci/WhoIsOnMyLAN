#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backend_handler.hpp"
<<<<<<< HEAD
#include "TimerWorker.h"
#include <QThread>
=======
>>>>>>> f80e74b (Backend can connec information to UI)

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();
    void handleDataReady(const std::vector<const Device*>& data);
<<<<<<< HEAD
    void onTimeUpdated(int second);
    void onBackendThreadFinished();
    // void handleHostDeviceInfo(const QString& ipAddress, const QString& macAddress);
    // void handleNetworkDeviceInfo();

protected:
    void closeEvent(QCloseEvent *event) override;
=======
    // void handleHostDeviceInfo(const QString& ipAddress, const QString& macAddress);
    // void handleNetworkDeviceInfo();
>>>>>>> f80e74b (Backend can connec information to UI)

private:
    Ui::MainWindow *ui;
    BackendHandler *backendHandler;
    void fillTable(const std::vector<const Device*>& vec);
<<<<<<< HEAD
    QThread* m_backendThread;
    QThread* m_timerThread;
    TimerWorker *timerWorker;
    bool isTimerRunning = false;
    bool isUIClosed = false;
=======
>>>>>>> f80e74b (Backend can connec information to UI)
};
#endif // MAINWINDOW_H
