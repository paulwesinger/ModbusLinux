#ifndef MODBUS_H
#define MODBUS_H

#include <QSerialPortInfo>
#include <QSerialPort>
#include "Rs485.h"


class ModbusRS485
{
public:
    ModbusRS485();
protected:
   //Protokoll * CurrentProtokoll;
private:
    void Init();
};

#endif // ModbusRS485
