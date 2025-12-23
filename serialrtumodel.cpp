#include "serialrtumodel.h"


ModbusRTUModel::ModbusRTUModel() {
    InitBaudRates();
    InitDataBits();
    InitParitys();
    InitStopBits();
}

void ModbusRTUModel::InitBaudRates(){
    _BaudRates.append(stCombostruct("Baud1200",1200));
    _BaudRates.append(stCombostruct("Baud2400",2400));
    _BaudRates.append(stCombostruct("Baud4800",4800));
    _BaudRates.append(stCombostruct("Baud9600",9600));
    _BaudRates.append(stCombostruct("Baud19200",19200));
    _BaudRates.append(stCombostruct("Baud38400",38400));
    _BaudRates.append(stCombostruct("Baud57600",57600));
    _BaudRates.append(stCombostruct("Baud115200",115200));
}

void ModbusRTUModel::InitDataBits(){
    _DataBits.append(stCombostruct("Data 5", 5));
    _DataBits.append(stCombostruct("Data 6", 6));
    _DataBits.append(stCombostruct("Data 7", 7));
    _DataBits.append(stCombostruct("Data 8", 8));
}

void ModbusRTUModel::InitParitys(){
    _Paritys.append(stCombostruct("Keine Parität",0));
    _Paritys.append(stCombostruct("Gerade Parität",2));
    _Paritys.append(stCombostruct("Ungerade Parität",3));
    _Paritys.append(stCombostruct("Space Parität",4));
    _Paritys.append(stCombostruct("Mark Parität",5));
}

void ModbusRTUModel::InitStopBits(){
    _StopBits.append(stCombostruct("Ein Stop Bit",0));
    _StopBits.append(stCombostruct("Ein einhalb Stopbit(Windows only)",3));
    _StopBits.append(stCombostruct("Zwei Stop Bit",2));
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
QModbusDevice::State ModbusRTUModel::CurrentState(){
    return _CurrentState;
}

QList<stCombostruct> ModbusRTUModel::BaudRates(){
    return _BaudRates;
}
QList<stCombostruct> ModbusRTUModel::StopBits(){
    return _StopBits;
}
QList<stCombostruct> ModbusRTUModel::Paritys(){
    return _Paritys;
}
QList<stCombostruct> ModbusRTUModel::DataBits(){
    return _DataBits;
}


void ModbusRTUModel::setCurrentState(QModbusDevice::State state){
    _CurrentState = state;
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
