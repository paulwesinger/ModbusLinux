#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QModbusRequest>
#include <QThread>
#include "checksum.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    Init();
    Initconnections();

}

void MainWindow::Initconnections(){
    connect(serialRTU->ModbusClient(),&QModbusClient::stateChanged,this,&MainWindow::onStateChanged);
    //connect(serialRTU->ModbusClient(),&QModbusClient::dataWritten,this,&MainWindow::onDataWritten);
    connect(ui->cmbDataBits,&QComboBox::currentIndexChanged,this,&MainWindow::onComboDataBitsIndexChanged);
    connect(ui->pbTakeSettings,&QPushButton::clicked,this,&MainWindow::onTakeSettings);
    connect(ui->pbTelegram,&QPushButton::clicked,this,&MainWindow::SendTelegrammclicked);
    connect(ui->pbReadRelayState,&QPushButton::clicked,this,&MainWindow::ReadRelaystate);
    connect(ui->pbRequest,&QPushButton::clicked,this,&MainWindow::sendRequestClicked);
    connect(ui->pbFirmware,&QPushButton::clicked,this,&MainWindow::ReadVersionClicked);
}

void MainWindow::Init(){
    QString msg;

    model = new QStringListModel();

    ui->lvResponse->setModel(model);

    mbRTUModel = new ModbusRTUModel();
    serialRTU = new SerialRTu(this);

    if ( serialRTU->Init(mbRTUModel,this)){
        for (auto i= 0; i< mbRTUModel->Ports().length(); i++){
            ui->cmboPorts->addItem(mbRTUModel->Ports()[i]->portName());
        }


        if (serialRTU->Connected()) {            
            msg = tr("Verbunden mit: ");
            msg.append(mbRTUModel->Ports()[0]->portName());
        }
        else{
            msg = tr("Disconnected: ");
            msg.append(mbRTUModel->Ports()[0]->portName());
        }
        this->statusBar()->showMessage(msg);

        /// ********************************************
        /// Erstmal alle verfügbaren einstellungen laden
        /// anhand der werte die indexes für die
        /// comboboxen holen und anzeigen
        /// ********************************************
        ui->leSartbit->setText("1");

        for (auto i = 0; i<mbRTUModel->BaudRates().length(); i++){
            ui->cmbBaudRate->addItem(mbRTUModel->BaudRates()[i].text, mbRTUModel->BaudRates()[i].value);
            if (mbRTUModel->BaudRates()[i].value == mbRTUModel->Ports()[0]->baudRate())
                ui->cmbBaudRate->setCurrentIndex(i);
        }

         for (auto i = 0; i<mbRTUModel->StopBits().length(); i++){
             ui->cmbStopBits->addItem(mbRTUModel->StopBits()[i].text, mbRTUModel->StopBits()[i].value);
             if (mbRTUModel->StopBits()[i].value == mbRTUModel->Ports()[0]->stopBits())
                 ui->cmbStopBits->setCurrentIndex(i);
         }

         for (auto i = 0; i<mbRTUModel->Paritys().length(); i++){
             ui->cmbParity->addItem(mbRTUModel->Paritys()[i].text, mbRTUModel->Paritys()[i].value);
             if (mbRTUModel->Paritys()[i].value == mbRTUModel->Ports()[0]->parity())
                 ui->cmbParity->setCurrentIndex(i);
         }

         for (auto i = 0; i<mbRTUModel->DataBits().length(); i++){
             ui->cmbDataBits->addItem(mbRTUModel->DataBits()[i].text, mbRTUModel->DataBits()[i].value);
             if (mbRTUModel->DataBits()[i].value == mbRTUModel->Ports()[0]->dataBits())
                 ui->cmbDataBits->setCurrentIndex(i);
        }


    }
}


void MainWindow::onComboDataBitsIndexChanged(int index){
    QVariant selected = ui->cmbDataBits->itemData(index);
    int bits = selected.toInt();
}

void MainWindow::onStateChanged(QModbusDevice::State state) {

    switch (state){
    case QModbusDevice::ConnectedState:  break;
    case QModbusDevice::ClosingState:
        if(serialRTU->Connected()) {
            serialRTU->DisConnect();
        }
        break ;
    default:

        break;
    }
}



void MainWindow::SendTelegrammclicked(){

}

void MainWindow::ReadVersionClicked(){
    QString tmp = ui->leRequest->text();
    // eingabe: hex hex hex ...
    QList<quint16> requestValues;
    if ( ! tmp.isEmpty()){
        QStringList list = tmp.split(' ');
        if (! list.empty() ){
            requestValues = ConvertStringToNumber(list);
            QList<quint16> crc = CheckSum::CRCModbus(requestValues);
            requestValues.append(crc);

            QString item = "Request: ";
            foreach(QString elem,list){
                item.append("0x");
                item.append( elem);
                item.append("-");
            }
            QStringList strlist = model->stringList();
            strlist.append(item);
            model->setStringList(strlist);

            // send request

            QModbusDataUnit readunit(QModbusDataUnit::Coils);
            readunit.setValues(requestValues);

            if (auto * reply = serialRTU->modbusDevice->sendReadRequest(readunit,1))
            {
                if (! reply->isFinished()){
                    connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
                }
                else{
                    delete reply;
                }
            }
        }
    }
}


QList<quint16> MainWindow::ConvertStringToNumber(QStringList values){
    QList<quint16> tmplist;
    if ( ! values.isEmpty()){
        foreach (QString elem,values) {
            bool ok;
            quint16 tmp = elem.toUShort(&ok,16);
            if (ok){
                tmplist.append(tmp);
            }
        }
        return tmplist;
    }
}


void MainWindow::sendRequestClicked(){
    QString tmp = ui->leRequest->text();

    // eingabe: hex hex hex ...

    QList<quint16> requestValues;
    if ( ! tmp.isEmpty()){
        QStringList list = tmp.split(' ');
         if (! list.empty() ){
            requestValues = ConvertStringToNumber(list);
            QList<quint16> crc = CheckSum::CRCModbus(requestValues);
            requestValues.append(crc);

            QString item = "Request: ";
            foreach(QString elem,list){
                item.append("0x");
                item.append( elem);
                item.append("-");
            }
            QStringList strlist = model->stringList();
            strlist.append(item);
            model->setStringList(strlist);

            // send request
            QModbusDataUnit writeUnit(QModbusDataUnit::Coils);
            writeUnit.setValues(requestValues);
            if (auto * reply = serialRTU->modbusDevice->sendWriteRequest(writeUnit,1)){
                if (! reply->isFinished()){
                    connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
                }
                else{
                    delete reply;
                }
            }
        }
    }
}

void MainWindow::replyFinished(){
    QModbusReply * reply = qobject_cast<QModbusReply*>(sender());
    const QModbusDataUnit result = reply->result();

    QString item = "Response: ";
    for(auto i = 0; i< result.values().count();i++){

        QString tmp = QString::number(result.value(i),16);
        item.append(tmp);
        item.append("-");
    }

    QStringList strlist = model->stringList();
    strlist.append(item);
    model->setStringList(strlist);
}


void MainWindow::ReadRelaystate(){
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils);

    QList<quint16> values({0x01,0x05,0x0,0x6,0x0,0x0});

    QList<quint16> crc = CheckSum::CRCModbus(values);

    values.append(crc);


/*
    values.append((qint16) 1);
    values.append((qint16) 5);
    values.append((qint16) 0);
    values.append((qint16) 1);
    values.append((qint16) 255);
    values.append((qint16) 0);
    values.append((qint16) 0xDD);
*/
    writeUnit.setValues(values);
/*

    writeUnit.setValueCount(8);
    writeUnit.setValue(0,(qint16) 1);
    writeUnit.setValue(1,(qint16) 5);
    writeUnit.setValue(2,(qint16) 0);
    writeUnit.setValue(3,(qint16) 1);
    writeUnit.setValue(4,(qint16) 255);
    writeUnit.setValue(5,(qint16) 0);
    writeUnit.setValue(6,(qint16) 0xDD);
*/

//01 05 00 00 FF 00 8C 3A

    QString st = "";
    foreach (quint16 val, values) {
        st += QString::number(val,16) + "- ";
    }


    model->stringList().append(st);

    if (auto * reply = serialRTU->modbusDevice->sendWriteRequest(writeUnit,1)){
        if (! reply->isFinished()){
            connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
        }
        else{
            delete reply;
        }
    }
}
void MainWindow::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size){
    bool wurscht = true;
}
void MainWindow::onTakeSettings(){

    /// ******************************************
    /// test Checksum 01 01 00 00 00 08    3D CC
    /// Data von Waveshare relais
    /// ******************************************
    //std::vector<ubyte> protokoll {0x00,0x03,0x40,0x00,0x00,0x01};


    /// *******************************************
    /// Protokoll fertig basteln:
    /// *******************************************
   // std::vector<ubyte> crc = CheckSum::CRCModbus(protokoll);

   // vec1.insert(vec1.end(), vec2.begin(), vec2.end());
   // protokoll.insert(protokoll.end(),crc.begin(),crc.end());



    // Test Waveshare Relay Relay 1 on
/*
    QList<qint16> protokoll;
    protokoll.append(1);
    protokoll.append(5);
    protokoll.append(0);
    protokoll.append(0);
    protokoll.append(0xFF);
    protokoll.append(0);
    protokoll.append(0x8C);
    protokoll.append(0x3A);
*/
  //  QModbusDataUnit du(QModbusPdu::ReadCoils,0,protokoll);
  //  QModbusReply* repley = serialRTU->modbusDevice->sendWriteRequest(du,1);


    QModbusRequest request(QModbusPdu::WriteSingleCoil,QByteArray::fromHex("01050001ff00DDFA"));

    QModbusReply* repley = serialRTU->modbusDevice->sendRawRequest(request,1);
   // QModbusRequest request(QModbusPdu::ReadSingleCoil,QByteArray::fromHex("0101000000083dcc"));
   // QByteArray img (reinterpret_cast<const char*>(protokoll.data()), protokoll.size());

    //bool isvalid = request.isValid();
    //QModbusReply* repley = serialRTU->modbusDevice->sendReadRequest(request,1);//   sendRawRequest(request,1);

    //QModbusResponse response(QModbusResponse::ReadCoils,QByteArray::fromHex("010580000001ADCA"));
    //QModbusResponse res = serialRTU->modbusDevice->processRequest(response);
   // serialRTU->modbusDevice->readData()

  //  QByteArray retdata = res.data();
}


MainWindow::~MainWindow()
{
    delete serialRTU;
    delete ui;
   // delete rs485;
}
