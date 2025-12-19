#include "Rs485.h"
#include <QSerialPortInfo>

Rs485::Rs485(QObject *parent)
    : QObject{parent}
{
    serialport = new QSerialPort();
}

QSerialPort* Rs485::GetSerialPort(){
    return serialport;
}




