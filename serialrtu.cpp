#include "serialrtu.h"
#include <QSerialPort>
#include <QModbusRtuSerialServer>

SerialRTu::SerialRTu(QObject *parent)
{

}
SerialRTu::~SerialRTu(){
    modbusDevice->disconnectDevice();
    availableportsinfo.clear();
}
bool SerialRTu::Init(ModbusRTUModel *model,QObject *parent)
{
    mbRTUModel = model;

    connected = false;
    modbusDevice = new QModbusRtuSerialServer(parent);
    availableportsinfo = QSerialPortInfo::availablePorts();


    if (modbusDevice->state() == QModbusDevice::UnconnectedState){
        if (availableportsinfo.length() > 0){

            for (auto i = 0; i <  availableportsinfo.length(); i++){
                QSerialPort * port = new QSerialPort(availableportsinfo[0]);

                qint32 databits = port->dataBits();
                QSerialPort::Parity parity = port->parity();
                qint32 baudrate = port->baudRate();
                qint32 stopbits = port->stopBits();
                QString portname = port->portName();

                _Ports.append(port);


               // mbRTUModel->SetCurrentPort(0);
               // mbRTUModel->setPortName(availableportsinfo[0].portName());

        //         if (connected) {
        //             QVariant va = modbusDevice-> connectionParameter(QModbusDevice::SerialBaudRateParameter);
        //             QString st = va.toString();
        //        //     _Databits =  modbusDevice->connectionParameter(QModbusDevice::SerialDataBitsParameter);

                modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,baudrate);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,databits);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,parity);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,stopbits);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portname);
            }
            connected = modbusDevice->connectDevice();
        }
    }
    return connected;
}

QList<QSerialPort*>SerialRTu::Ports(){
    return _Ports;
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
    return availableportsinfo;
}

bool SerialRTu::Connected(){
    return connected;
}





