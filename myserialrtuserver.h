#ifndef MYSERIALRTUSERVER_H
#define MYSERIALRTUSERVER_H

//#include <QModbusRtuSerialServer>
#include <QModbusRtuSerialClient>
#include <QModbusResponse>


class MySerialRTUClient :public QModbusRtuSerialClient
{
public:
    MySerialRTUClient(QObject * parent);
//    virtual QModbusResponse processResponse(QModbusResponse response,QDataUnit &du);
    virtual bool open() override;
    virtual void close() override;

};

#endif // MYSERIALRTUSERVER_H
