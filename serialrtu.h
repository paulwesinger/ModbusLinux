#ifndef SERIALRTU_H
#define SERIALRTU_H

#include <QModbusServer>
#include <QSerialPortInfo>
#include <serialrtumodel.h>

class SerialRTu :QObject
{
    Q_OBJECT
public:
    explicit SerialRTu(QObject * parent= nullptr);
    ~SerialRTu();

    bool Init(ModbusRTUModel *model,QObject * parent = nullptr);
    QModbusServer * ModbusServer();
    bool Connected();    

    QList<QSerialPortInfo> AvailablePorts();
    int Baudrate();
    int Databits();

protected:
    bool connected = false;
    QList<QSerialPortInfo> availableports;

    ModbusRTUModel * mbRTUModel = nullptr;

private slots:

private :

    QModbusServer *modbusDevice = nullptr;

    int _Baudrate;
    int _Databits;

signals:
};

#endif // SERIALRTU_H
