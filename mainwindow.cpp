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
    if (serialRTU->Init(this))
    {
        for (auto i= 0; i< serialRTU->AvailablePorts().length(); i++){
            ui->cmboPorts->addItem(serialRTU->AvailablePorts()[i].portName());
        }

    }

    // mbRTUServer = new QModbusRtuSerialServer();
    // mbRTUServer->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::Parity::NoParity);
    // mbRTUServer->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    // mbRTUServer->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::StopBits::OneStop);
    // mbRTUServer->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);

    // if (mbRTUServer->open()) {
    //     bool passt = true;
    // }




    //mbClient = new QModbusClient(this);
    // rs485 = new Rs485();
    // auto ports = QSerialPortInfo::availablePorts();
    // for (int i=0;i<ports.length();i++){
    //     ui->cmboPorts->addItem(ports[i].portName());
    //     Protokoll protokoll;

    //     QList<qint32> baudrates = ports[i].standardBaudRates();
    //     QSerialPort* serialport = rs485->GetSerialPort();
    //     serialport->setPort(ports[i]);
    //     serialport->setBaudRate(baudrates[0]);
    //     serialport->setStopBits(QSerialPort::StopBits::OneStop);
    //     serialport->setParity(QSerialPort::Parity::NoParity);
    //     serialport->setDataBits(QSerialPort::Data8);

    //     ui->lblStartbit->setText("1");
    //     ui->lblBaudrate->setText("9600");

    //    // ui->lblStopbits = QSerialPort::StopBits::OneStop;
    // }
}



MainWindow::~MainWindow()
{
    delete ui;
   // delete rs485;
}
