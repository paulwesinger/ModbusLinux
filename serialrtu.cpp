#include "serialrtu.h"
#include <QSerialPort>
#include <QModbusRtuSerialServer>

SerialRTu::SerialRTu(QObject *parent)
{  
}
SerialRTu::~SerialRTu(){
    availableports.clear();
}
bool SerialRTu::Init(QObject *parent)
{
    modbusDevice = new QModbusRtuSerialServer(parent);
    // connect(modbusDevice,&QModbusDevice::dataWritten,   //(QModbusDataUnit::RegisterType,int,int)),
    //          this,&SerialRTu::onDataWritten);    //SLOT(onDataWritten(QModbusDataUnit,int,int)));

    availableports = QSerialPortInfo::availablePorts();
    if (availableports.length() > 0){


        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::Parity::NoParity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::StopBits::OneStop);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,availableports[0].portName());

        if (modbusDevice->state() == QModbusDevice::UnconnectedState){
            connected = modbusDevice->connectDevice();
        }
    }

    return true;
}



QModbusServer* SerialRTu::ModbusServer(){
    return modbusDevice;
}

QList<QSerialPortInfo> SerialRTu::AvailablePorts(){
    return availableports;
}

bool SerialRTu::Connected(){
    return connected;
}
// void SerialRTu:: onStateChanged(QModbusDevice::State state){

//     if (state == QModbusDevice::ConnectedState)
//         connected = true;
//     else
//         connected = false;
// }

