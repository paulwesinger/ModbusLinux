#include "myserialrtuserver.h"

MySerialRTUClient::MySerialRTUClient(QObject* parent)
    :QModbusRtuSerialClient(parent)
{

}

/*
QModbusResponse MySerialRTUClient::processResponse(const QModbusPdu &request,QDataUnit& du){
    return QModbusRtuSerialClient::processResponse(request,du);
}
*/

bool MySerialRTUClient::open(){
    QModbusRtuSerialClient::open();
}

void MySerialRTUClient::close(){
    QModbusRtuSerialClient::close();
}
