#include "serialrtu.h"
#include <QSerialPort>
#include <QModbusRtuSerialServer>

SerialRTu::SerialRTu(QObject *parent)
{
    Init(parent);
}

bool SerialRTu::Init(QObject *parent)
{
    modbusDevice = new QModbusRtuSerialServer(parent);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::Parity::NoParity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::StopBits::OneStop);

    connect(modbusDevice,SIGNAL(QModbusServer::stateChanged(QModbusDevice::State)),
            this, SLOT(onStateChanged(QModbusDevice::State)));

    availableports = QSerialPortInfo::availablePorts();
    return true;
}

QList<QSerialPortInfo> SerialRTu::AvailablePorts(){
    return availableports;
}

bool SerialRTu::Connected(){
    return connected;
}
void SerialRTu:: onStateChanged(QModbusDevice::State state){

    if (state == QModbusDevice::ConnectedState)
        connected = true;
    else
        connected = false;
}

