#ifndef SERIALRTU_H
#define SERIALRTU_H

#include <QModbusServer>
#include <QSerialPortInfo>

class SerialRTu :QObject
{
    Q_OBJECT
public:
    explicit SerialRTu(QObject * parent= nullptr);
    ~SerialRTu();

    bool Init(QObject * parent = nullptr);   
    QModbusServer * ModbusServer();

    bool Connected();
    QList<QSerialPortInfo> AvailablePorts();
protected:
    bool connected = false;
    QList<QSerialPortInfo> availableports;

private slots:

private :

    QModbusServer *modbusDevice = nullptr;

signals:
};

#endif // SERIALRTU_H
