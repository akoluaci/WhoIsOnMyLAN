#ifndef TIMER_WORKER_H
#define TIMER_WORKER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>

class TimerWorker : public QObject
{
    Q_OBJECT
    
public:
    explicit TimerWorker(QObject *parent = nullptr) : QObject(parent), second(0) , timer(nullptr){}
    ~TimerWorker();
    void resetSecond();
public slots:
    void startTimer();
    void stopTimer();
private slots:
    void incrementSecond();

signals:
    void elapsedTimeUpdated(int elapsedSeconds); 
    
private:
    int second;
    QTimer *timer;
};

#endif