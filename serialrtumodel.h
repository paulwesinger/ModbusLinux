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
    /// ****************************************
    /// Die PortInfos anhand des Comboboxindexes
    /// ermitteln mit Bereichscheck
    /// ****************************************
    QSerialPortInfo *GetPort(int index);

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

    void addPort(QSerialPort* port);

private:
    QList<QSerialPortInfo> _AvailablePorts;
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
