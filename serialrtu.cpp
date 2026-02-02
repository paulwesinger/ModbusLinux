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
    modbusDevice = new MySerialRTUClient(parent);   //QModbusRtuSerialServer(parent);
    modbusDevice->setTimeout(300);
    modbusDevice->setNumberOfRetries(3);

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

                /// ******************************************************************
                /// Nur für den ersten(aktuellen) port Einstellungen übernhemen
                /// und anzeigen
                /// ******************************************************************
                if (i == 0) {

                    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,baudrate);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,databits);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,parity);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,stopbits);
                    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portname);
                    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter,502);

                    connected = modbusDevice->connectDevice();
                }
            }
        }
    }
    return connected;
}
void SerialRTu::DisConnect(){
    try{
        modbusDevice->disconnectDevice();
        connected = false;
    }
    catch(const std::exception& e){}

}

QModbusClient* SerialRTu::ModbusClient(){
    return modbusDevice;
}

bool SerialRTu::Connected(){
    return connected;
}





