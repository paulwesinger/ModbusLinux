#include "Rs485.h"
#include <QSerialPortInfo>


Rs485::Rs485(QObject *parent)
    : QObject{parent}
{
    serialport = new QSerialPort();
}

QList<QString>Rs485::Portnames()
{
    QSerialPortInfo* info = new QSerialPortInfo();

    QList<QString> names;

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        QString  port = portInfo.portName();
    }

    return names;

}


