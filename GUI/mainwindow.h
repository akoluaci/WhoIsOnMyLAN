#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backend_handler.hpp"
#include "TimerWorker.h"
#include <QThread>

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
    void onTimeUpdated(int second);
    void onBackendThreadFinished();
    // void handleHostDeviceInfo(const QString& ipAddress, const QString& macAddress);
    // void handleNetworkDeviceInfo();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    BackendHandler *backendHandler;
    void fillTable(const std::vector<const Device*>& vec);
    QThread* m_backendThread;
    QThread* m_timerThread;
    TimerWorker *timerWorker;
    bool isTimerRunning = false;
    bool isUIClosed = false;
};
#endif // MAINWINDOW_H
