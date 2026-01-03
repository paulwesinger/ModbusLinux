#ifndef SERIALRTU_H
#define SERIALRTU_H

#include <QModbusServer>
#include <QSerialPortInfo>
#include <serialrtumodel.h>
#include "myserialrtuserver.h"

class SerialRTu :QObject
{
    Q_OBJECT
public:
    explicit SerialRTu(QObject * parent= nullptr);
    ~SerialRTu();

    bool Init(ModbusRTUModel *model,QObject * parent = nullptr);
    QModbusServer * ModbusServer();
    bool Connected();
    MySerialRTUServer *modbusDevice = nullptr;

protected:
    bool connected = false;
    ModbusRTUModel * mbRTUModel = nullptr;


private slots:

private :
    //QModbusServer *modbusDevice = nullptr;

signals:
};

#endif // SERIALRTU_H
