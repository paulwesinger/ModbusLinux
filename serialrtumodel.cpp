#include "serialrtumodel.h"


ModbusRTUModel::ModbusRTUModel() {

}

QList<QSerialPortInfo> ModbusRTUModel::AvailablePorts(){
    return _AvailablePorts;
}

QSerialPort::BaudRate ModbusRTUModel::CurrentBaudRate(){
    return _CurrentBaudRate;
}
QSerialPort::DataBits ModbusRTUModel::CurrentDataBits(){
    return _CurrentDataBits;
}
QString ModbusRTUModel::CurrentPortName() {
    return _CurrentPortName;
}
QSerialPort::Parity ModbusRTUModel::CurrentParity(){
    return  _CurrentParity;
}


void ModbusRTUModel::setPortName(QString portname){
    _CurrentPortName = portname;
}
void ModbusRTUModel::setDataBits(QSerialPort::DataBits databits){
    _CurrentDataBits = databits;
}
void ModbusRTUModel::setBaudRate(QSerialPort::BaudRate baudrate){
    _CurrentBaudRate = baudrate;
}
void ModbusRTUModel::setParity(QSerialPort::Parity parity){
    _CurrentParity = parity;
}
