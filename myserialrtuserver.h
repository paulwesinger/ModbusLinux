#ifndef MYSERIALRTUSERVER_H
#define MYSERIALRTUSERVER_H

#include <QModbusRtuSerialServer>
#include <QModbusResponse>

class MySerialRTUServer :public QModbusRtuSerialServer
{
public:
    MySerialRTUServer(QObject * parent);
    virtual QModbusResponse processRequest(const QModbusPdu &request) override;
    virtual bool open() override;
    virtual void close() override;

};

#endif // MYSERIALRTUSERVER_H
