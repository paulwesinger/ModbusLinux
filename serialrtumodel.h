#ifndef SERIALRTUMODEL_H
#define SERIALRTUMODEL_H

#include <QSerialPortInfo>
#include <QModbusServer>
#include <QList>
#include <QSerialPort>

class ModbusRTUModel
{
public:
    ModbusRTUModel();

    QList<QSerialPortInfo> AvailablePorts();
    QSerialPort::BaudRate CurrentBaudRate();
    QSerialPort::DataBits CurrentDataBits();
    QSerialPort::Parity CurrentParity();
    QString CurrentPortName();

    void setPortName(QString protname);
    void setBaudRate(QSerialPort::BaudRate baudrate);
    void setDataBits(QSerialPort::DataBits databits);
    void setParity(QSerialPort::Parity);

private:
    QList<QSerialPortInfo> _AvailablePorts;
    QSerialPort::BaudRate _CurrentBaudRate;
    QSerialPort::DataBits _CurrentDataBits;
    QSerialPort::Parity   _CurrentParity;
    QString _CurrentPortName;

};

#endif // SERIALRTUMODEL_H
