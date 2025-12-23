#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    Init();

}

void MainWindow::Init(){

    mbRTUModel = new ModbusRTUModel();
    serialRTU = new SerialRTu(this);

    if (serialRTU->Init(mbRTUModel,this)){
        for (auto i= 0; i< serialRTU->AvailablePorts().length(); i++){
            ui->cmboPorts->addItem(serialRTU->AvailablePorts()[i].portName());
        }

        connect(serialRTU->ModbusServer(),&QModbusServer::stateChanged,this,&MainWindow::onStateChanged);
        connect(serialRTU->ModbusServer(),&QModbusServer::dataWritten,this,&MainWindow::onDataWritten);

        QString msg;
        if (serialRTU->Connected()) {            
            msg = tr("Verbunden mit: ");
            msg.append(mbRTUModel->CurrentPortName());
        }
        else{
            msg = tr("Disconnected: ");
            msg.append(mbRTUModel->CurrentPortName());
        }
        this->statusBar()->showMessage(msg);
        ui->leSartbit->setText("1");

        for (auto i = 0; i<mbRTUModel->BaudRates().length(); i++){
            ui->cmbBaudRate->addItem(mbRTUModel->BaudRates()[i].text, mbRTUModel->BaudRates()[i].value);
        }

        for (auto i = 0; i<mbRTUModel->StopBits().length(); i++){
            ui->cmbStopBits->addItem(mbRTUModel->StopBits()[i].text, mbRTUModel->StopBits()[i].value);
        }

        for (auto i = 0; i<mbRTUModel->Paritys().length(); i++){
            ui->cmbParity->addItem(mbRTUModel->Paritys()[i].text, mbRTUModel->Paritys()[i].value);
        }
        for (auto i = 0; i<mbRTUModel->DataBits().length(); i++){
            ui->cmbDataBits->addItem(mbRTUModel->DataBits()[i].text, mbRTUModel->DataBits()[i].value);
        }


    }
}

void MainWindow::onStateChanged(QModbusDevice::State state) {

    switch (state){
    case QModbusDevice::ConnectedState:  break;
    case QModbusDevice::ClosingState: break;
    default:

        break;
    }
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
