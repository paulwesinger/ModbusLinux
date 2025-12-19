#ifndef SERIALRTU_H
#define SERIALRTU_H

#include <QModbusServer>
#include <QSerialPortInfo>

class SerialRTu :QObject
{
    Q_OBJECT
public:
    explicit SerialRTu(QObject * parent= nullptr);
    bool Init(QObject * parent = nullptr);

    bool Connected();
    QList<QSerialPortInfo> AvailablePorts();
protected:

    bool connected = false;
    QList<QSerialPortInfo> availableports;

private slots:
      void onStateChanged(QModbusDevice::State state);
private :

    QModbusServer *modbusDevice = nullptr;
signals:
};

#endif // SERIALRTU_H
