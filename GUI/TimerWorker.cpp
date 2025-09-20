#include "TimerWorker.h"

TimerWorker::~TimerWorker() {
    delete timer;
}

void TimerWorker::startTimer()
{
    if (timer == nullptr) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &TimerWorker::incrementSecond);
    }
    
    if (!timer->isActive()) {
        timer->start(1000);
    } else {
        // when timer is already active
    }
    
}


void TimerWorker::incrementSecond()
{
    second++;
    emit elapsedTimeUpdated(second);
}

void TimerWorker::stopTimer() {
    if (timer && timer->isActive()) {
        timer->stop();
    } else {
        // when timer is already stopper
    }
}

void TimerWorker::resetSecond() {
    second = 0;
}