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
    ~ModbusRTUModel();

    QModbusDevice::State CurrentState();
    QSerialPort::BaudRate CurrentBaudRate();
    QSerialPort::DataBits CurrentDataBits();
    QSerialPort::Parity CurrentParity();
    QString CurrentPortName();

    /// ****************************************
    /// Die PortInfos anhand des Comboboxindexes
    /// ermitteln mit Bereichscheck
    /// ****************************************
    QSerialPortInfo *(GetPort(int index));

    /// *****************************************
    /// Hilfsfunktion, Current gewählten Port
    /// ohne Argument zurück geben ohne
    /// Bereichscheck
    /// *****************************************
    QSerialPortInfo* CurrentPort();

    /// *****************************************
    /// Den aktuellen Port anhand des Comboindex
    /// setzen -> checken ob gültig!
    /// false -> index out of range,
    /// true -> index ok
    /// *****************************************
    bool SetCurrentPort(int index);

    QList<stCombostruct> BaudRates();
    QList<stCombostruct> DataBits();
    QList<stCombostruct> Paritys();
    QList<stCombostruct> StopBits();


    QList<QSerialPortInfo> AvailablePorts();
    QList<QSerialPort*> Ports();

    void setPortName(QString protname);
    void setBaudRate(QSerialPort::BaudRate baudrate);
    void setDataBits(QSerialPort::DataBits databits);
    void setParity(QSerialPort::Parity);
    void setCurrentState(QModbusDevice::State state);
    void addPort(QSerialPort* port);

private:
    QList<QSerialPortInfo> _AvailablePorts;

    QSerialPort::BaudRate _CurrentBaudRate;
    QSerialPort::DataBits _CurrentDataBits;
    QSerialPort::Parity   _CurrentParity;
    QString _CurrentPortName;
    QModbusDevice::State _CurrentState;
    QSerialPortInfo _CurrentPort;

    QList<stCombostruct> _BaudRates;
    QList<stCombostruct> _DataBits;
    QList<stCombostruct> _Paritys;
    QList<stCombostruct> _StopBits;

    QList<QSerialPort*> _Ports;

    void InitBaudRates();
    void InitDataBits();
    void InitParitys();
    void InitStopBits();
    void GetAvailablePorts();

};

#endif // SERIALRTUMODEL_H
