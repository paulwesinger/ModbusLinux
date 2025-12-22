#include "serialrtu.h"
#include <QSerialPort>
#include <QModbusRtuSerialServer>

SerialRTu::SerialRTu(QObject *parent)
{

}
SerialRTu::~SerialRTu(){
    modbusDevice->disconnectDevice();
    availableports.clear();
}
bool SerialRTu::Init(ModbusRTUModel *model,QObject *parent)
{
    mbRTUModel = model;

    connected = false;
    modbusDevice = new QModbusRtuSerialServer(parent);
    availableports = QSerialPortInfo::availablePorts();
    if (modbusDevice->state() == QModbusDevice::UnconnectedState){
        if (availableports.length() > 0){

            mbRTUModel->setPortName(availableports[0].portName());

    //         if (connected) {
    //             QVariant va = modbusDevice-> connectionParameter(QModbusDevice::SerialBaudRateParameter);
    //             QString st = va.toString();
    //        //     _Databits =  modbusDevice->connectionParameter(QModbusDevice::SerialDataBitsParameter);

            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::Parity::NoParity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::StopBits::OneStop);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,availableports[0].portName());
            connected = modbusDevice->connectDevice();
        }
    }
    return connected;
}

int SerialRTu::Baudrate(){
    return _Baudrate;
}
int SerialRTu::Databits(){
    return _Databits;
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





