#include "serialrtu.h"
#include <QSerialPort>
#include <QModbusRtuSerialServer>

SerialRTu::SerialRTu(QObject *parent)
{

}
SerialRTu::~SerialRTu(){
    modbusDevice->disconnectDevice();
    delete mbRTUModel;
}
bool SerialRTu::Init(ModbusRTUModel *model,QObject *parent)
{
    mbRTUModel = model;

    connected = false;
    modbusDevice = new QModbusRtuSerialServer(parent);

    if (modbusDevice->state() == QModbusDevice::UnconnectedState){
        if (mbRTUModel->AvailablePorts().length() > 0){

            for (auto i = 0; i < mbRTUModel->AvailablePorts().length(); i++){
                QSerialPort * port = new QSerialPort(mbRTUModel->AvailablePorts()[i]);

                qint32 databits = port->dataBits();
                QSerialPort::Parity parity = port->parity();
                qint32 baudrate = port->baudRate();
                qint32 stopbits = port->stopBits();
                QString portname = port->portName();

                mbRTUModel->addPort(port);

        //         if (connected) {
        //             QVariant va = modbusDevice-> connectionParameter(QModbusDevice::SerialBaudRateParameter);
        //             QString st = va.toString();
        //        //     _Databits =  modbusDevice->connectionParameter(QModbusDevice::SerialDataBitsParameter);

                /// ******************************************************************
                /// Nur für den ersten port standardmässig übernhemen
                /// ******************************************************************
                if (i == 0) {

                    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,baudrate);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,databits);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,parity);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,stopbits);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portname);

                    connected = modbusDevice->connectDevice();
                }
            }

        }
    }
    return connected;
}

// QList<QSerialPort*>SerialRTu::Ports(){
//     return _Ports;
// }
int SerialRTu::Baudrate(){
    return _Baudrate;
}
int SerialRTu::Databits(){
    return _Databits;
}

QModbusServer* SerialRTu::ModbusServer(){
    return modbusDevice;
}

// QList<QSerialPortInfo> SerialRTu::AvailablePorts(){
//     return availableportsinfo;
// }

bool SerialRTu::Connected(){
    return connected;
}





