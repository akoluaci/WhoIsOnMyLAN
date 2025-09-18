#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_4->setPixmap(QPixmap("D:\\codes\\c++\\qt\\crashcourse\\icons8-settings-20-g.png"));
    ui->label_5->setPixmap(QPixmap("D:\\codes\\c++\\qt\\crashcourse\\icons8-help-20-glyph.png"));
    ui->label_14->setPixmap(QPixmap("D:\\codes\\c++\\qt\\crashcourse\\icons8-search-25.png"));
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString("13 Eyl 2025")));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString("F7:15:AA:26")));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString("80 / HTTP")));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString("Apple")));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString("John's iPhone")));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Tara") {
        ui->pushButton->setText("Durdur");
        ui->label_14->setVisible(false);
    } else {
        ui->pushButton->setText("Tara");
        ui->label_14->setVisible(true);
    }
}

