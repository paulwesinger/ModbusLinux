#include "myserialrtuserver.h"

MySerialRTUServer::MySerialRTUServer(QObject* parent)
    :QModbusRtuSerialServer(parent)
{

}

QModbusResponse MySerialRTUServer::processRequest(const QModbusPdu &request){
    return QModbusRtuSerialServer::processRequest(request);
}

bool MySerialRTUServer::open(){
    QModbusRtuSerialServer::open();
}

void MySerialRTUServer::close(){
    QModbusRtuSerialServer::close();
}
