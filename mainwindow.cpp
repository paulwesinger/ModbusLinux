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

    serialRTU = new SerialRTu(this);

    if (serialRTU->Init(this)){
        for (auto i= 0; i< serialRTU->AvailablePorts().length(); i++){
            ui->cmboPorts->addItem(serialRTU->AvailablePorts()[i].portName());
        }

        connect(serialRTU->ModbusServer(),&QModbusServer::stateChanged,this,&MainWindow::onStateChanged);
        connect(serialRTU->ModbusServer(),&QModbusServer::dataWritten,this,&MainWindow::onDataWritten);

        if (serialRTU->Connected())
            ui->lblBaudrate->setText("Connected");
        else
                ui->lblBaudrate->setText("Disconnected");


    }
}


void MainWindow::onStateChanged(QModbusDevice::State state) {
    bool wurscht = true;
}

void MainWindow::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size){
    bool wurscht = true;
}


MainWindow::~MainWindow()
{
    delete serialRTU;
    delete ui;
   // delete rs485;
}
