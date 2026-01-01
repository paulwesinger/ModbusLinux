#include "serialrtumodel.h"


ModbusRTUModel::ModbusRTUModel() {
    GetAvailablePorts();
    InitBaudRates();
    InitDataBits();
    InitParitys();
    InitStopBits();
}

ModbusRTUModel::~ModbusRTUModel(){
    _BaudRates.clear();
    _DataBits.clear();
    _StopBits.clear();
    _Paritys.clear();
    _AvailablePorts.clear();
}

void ModbusRTUModel::GetAvailablePorts(){
    _AvailablePorts = QSerialPortInfo::availablePorts();
}

void ModbusRTUModel::addPort(QSerialPort* port){
    _Ports.append(port);
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

///**************************************
/// Portinfo Methoden
/// *************************************
QSerialPortInfo * ModbusRTUModel::GetPort(int index){
    // Area check
    if (index > _AvailablePorts.length() - 1)
        return nullptr;
    return &_AvailablePorts[index];
}


QList<QSerialPort*>ModbusRTUModel::Ports(){
    return _Ports;
}

QList<QSerialPortInfo> ModbusRTUModel::AvailablePorts(){
    return _AvailablePorts;
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
