#ifndef SERIALRTUMODEL_H
#define SERIALRTUMODEL_H

#include <QSerialPortInfo>
#include <QModbusServer>
#include <QList>
#include <QSerialPort>
#include <QComboBox>

struct stCombostruct {
    QString text;
    QVariant value;
    stCombostruct(QString t,QVariant val):
        text(t),
        value(val)
        {}
} ;

class ModbusRTUModel
{
public:
    ModbusRTUModel();

    QModbusDevice::State CurrentState();
    QList<QSerialPortInfo> AvailablePorts();
    QSerialPort::BaudRate CurrentBaudRate();
    QSerialPort::DataBits CurrentDataBits();
    QSerialPort::Parity CurrentParity();
    QString CurrentPortName();

    QList<stCombostruct> BaudRates();
    QList<stCombostruct> DataBits();
    QList<stCombostruct> Paritys();
    QList<stCombostruct> StopBits();

    void setPortName(QString protname);
    void setBaudRate(QSerialPort::BaudRate baudrate);
    void setDataBits(QSerialPort::DataBits databits);
    void setParity(QSerialPort::Parity);
    void setCurrentState(QModbusDevice::State state);

private:
    QList<QSerialPortInfo> _AvailablePorts;
    QSerialPort::BaudRate _CurrentBaudRate;
    QSerialPort::DataBits _CurrentDataBits;
    QSerialPort::Parity   _CurrentParity;
    QString _CurrentPortName;
    QModbusDevice::State _CurrentState;

    QList<stCombostruct> _BaudRates;
    QList<stCombostruct> _DataBits;
    QList<stCombostruct> _Paritys;
    QList<stCombostruct> _StopBits;

    void InitBaudRates();
    void InitDataBits();
    void InitParitys();
    void InitStopBits();


};

#endif // SERIALRTUMODEL_H
