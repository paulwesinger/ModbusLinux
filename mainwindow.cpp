#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

void MainWindow::Init(){
    rs485 = new Rs485();
    QList<QString> list = rs485->Portnames();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rs485;
}
