#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <numeric>
#include <QCloseEvent>

static std::string vector2String(std::vector<int> portsVector) {
    std::string ports = "";
    for (size_t i = 0; i < portsVector.size(); i++)
    {
        ports += std::to_string(portsVector[i]);
        if (i != portsVector.size() - 1)
            ports += ",";
    }
    return ports;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hostInterfacesTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->hostInterfacesTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->networkDevsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->networkDevsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    QThread *timerThread = new QThread(this);
    timerWorker = new TimerWorker();
    timerWorker->moveToThread(timerThread);
    connect(timerWorker, &TimerWorker::elapsedTimeUpdated, this, &MainWindow::onTimeUpdated);
    connect(timerThread, &QThread::finished, timerWorker, &QObject::deleteLater);
    timerThread->start();
    m_timerThread = timerThread;

    QThread* backendThread = new QThread(this);
    backendHandler = new BackendHandler();
    backendHandler->moveToThread(backendThread);
    connect(backendThread, &QThread::finished, backendHandler, &QObject::deleteLater);

    connect(backendHandler, &BackendHandler::dataReady,
            this, &MainWindow::handleDataReady);
    connect(ui->pushButton, &QPushButton::clicked,
            backendHandler, &BackendHandler::triggerDataGeneration);
    connect(backendThread, &QThread::finished, this, &MainWindow::onBackendThreadFinished);
    qDebug() << "Signal/Slot connection is done!\n";
    backendThread->start();
    m_backendThread = backendThread;
}

MainWindow::~MainWindow()
{
    delete ui;
    m_backendThread->quit();
    m_backendThread->wait();
    m_timerThread->quit();
    m_timerThread->wait();
    
}

void MainWindow::on_pushButton_clicked()
{
    if (isTimerRunning) {
        QMetaObject::invokeMethod(timerWorker, "stopTimer", Qt::QueuedConnection);
        isTimerRunning = false;
    } else {
        QMetaObject::invokeMethod(timerWorker, "startTimer", Qt::QueuedConnection);
        // backendHandler->setStopRequest();
        // m_backendThread->start();
        isTimerRunning = true;
    }

    if (ui->pushButton->text() == "Tara") {
        ui->pushButton->setText("Durdur");
        backendHandler->setStopRequest(false);
    } else {
        ui->pushButton->setText("Tara");
        m_backendThread->quit();
        ui->hostInterfacesTable->clearContents();
        ui->networkDevsTable->clearContents();
        ui->elapsedTimeLabel->setText("Elapsed Time:");
        ui->foundDevicesLabel->setText("Found Devices: ");
        timerWorker->resetSecond();
        m_backendThread->start();
        backendHandler->setStopRequest(true);
    }
}

// void MainWindow::handleHostDeviceInfo(const QString& ipAddress, const QString& macAddress) {
//     qDebug() << "Host Device Info\n";
//     QString itemText = QString("IP: %1  -  MAC: %2").arg(ipAddress, macAddress);
//     ui->tableWidget->setItem(1, 0, new QTableWidgetItem(ipAddress));
//     ui->tableWidget->setItem(1, 1, new QTableWidgetItem(macAddress));

// }
// void MainWindow::handleNetworkDeviceInfo() {
//     qDebug() << "Host Device Info\n";
// }

void MainWindow::handleDataReady(const std::vector<const Device*>& data) {
    qDebug() << "Sinyal MainWindow'a ulasti. Slot calisiyor...";
    fillTable(data);
}

void MainWindow::fillTable(const std::vector<const Device*>& data) {
    // std::cout << "fillTable\n";
    // std::cout << data.at(0)->getIpv4Address() << "\n";
    // std::cout << "device type: " << typeid(*data.at(0)).name() << "\n";
    // std::cout << "Device count: " << data.size() << "\n";
    ui->networkDevsTable->setRowCount(data.size() - 1);
    ui->hostInterfacesTable->setRowCount(1);
    ui->foundDevicesLabel->setText("Device Found: " + QString::number(data.size()));
    int hostDevCnt = 0;
    int networkDevCnt = 0;
    for (auto &ptr : data) {
        // std::cout << "ip in fillTable:" << ptr->getIpv4Address() << "\n";
        if (const HostDevice* host = dynamic_cast<const HostDevice*>(ptr)) {
            // std::cout <<"in if\n";
            ui->hostInterfacesTable->setItem(hostDevCnt, 0, new QTableWidgetItem(QString::fromStdString(host->getIpv4Address())));
            ui->hostInterfacesTable->item(hostDevCnt, 0)->setTextAlignment(Qt::AlignCenter);
            ui->hostInterfacesTable->setItem(hostDevCnt, 1, new QTableWidgetItem(QString::fromStdString(host->getMacAddress())));
            ui->hostInterfacesTable->item(hostDevCnt, 1)->setTextAlignment(Qt::AlignCenter);
            ui->hostInterfacesTable->setItem(hostDevCnt, 2, new QTableWidgetItem(QString::fromStdString(host->getVendor())));
            ui->hostInterfacesTable->item(hostDevCnt, 2)->setTextAlignment(Qt::AlignCenter);
            ui->hostInterfacesTable->setItem(hostDevCnt, 3, new QTableWidgetItem(QString::fromStdString(host->getAdapterName())));
            ui->hostInterfacesTable->item(hostDevCnt, 3)->setTextAlignment(Qt::AlignCenter);
            hostDevCnt++;
        } else if (const NetworkDevice* devicee = dynamic_cast<const NetworkDevice*>(ptr)){
            // std::cout << "in else\n";
            ui->networkDevsTable->setItem(networkDevCnt, 0, new QTableWidgetItem(QString::fromStdString(devicee->getIpv4Address())));
            ui->networkDevsTable->item(networkDevCnt, 0)->setTextAlignment(Qt::AlignCenter);
            ui->networkDevsTable->setItem(networkDevCnt, 1, new QTableWidgetItem(QString::fromStdString(devicee->getMacAddress())));
            ui->networkDevsTable->item(networkDevCnt, 1)->setTextAlignment(Qt::AlignCenter);
            ui->networkDevsTable->setItem(networkDevCnt, 2, new QTableWidgetItem(QString::fromStdString(devicee->getVendor())));
            ui->networkDevsTable->item(networkDevCnt, 2)->setTextAlignment(Qt::AlignCenter);
            std::string openPorts = vector2String(devicee->getOpenPorts());
            ui->networkDevsTable->setItem(networkDevCnt, 3, new QTableWidgetItem(QString::fromStdString(openPorts)));
            ui->networkDevsTable->item(networkDevCnt, 3)->setTextAlignment(Qt::AlignCenter);
            networkDevCnt++;
        }
    }
    // std::cout << "end of fillTable\n";
    QMetaObject::invokeMethod(timerWorker, "stopTimer", Qt::QueuedConnection);
}

void MainWindow::onTimeUpdated(int second) {
    QString elapsedTimeStr = QString("Elapsed Time: ") + QString::number(second) + QString("s");
    ui->elapsedTimeLabel->setText(elapsedTimeStr);
}

void MainWindow::onBackendThreadFinished() {
    qDebug() << "Backend is about to finish!\n";
    m_backendThread->wait();
    if (isUIClosed) {
        this->close();
        isUIClosed = false;
    }
    isUIClosed = false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_backendThread && m_backendThread->isRunning()) {
        
        m_backendThread->quit(); 
        isUIClosed = true;

        event->ignore(); 
        backendHandler->setStopRequest(true);
        
    } else {
        event->accept();
        isUIClosed = false;
    }
