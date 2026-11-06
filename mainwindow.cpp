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
    //connect(serialRTU->ModbusClient(),&QModbusClient::stateChanged,this,&MainWindow::onStateChanged);
    //connect(serialRTU->ModbusClient(),&QModbusClient::dataWritten,this,&MainWindow::onDataWritten);
    connect(ui->cmbDataBits,&QComboBox::currentIndexChanged,this,&MainWindow::onComboDataBitsIndexChanged);
    connect(ui->pbTakeSettings,&QPushButton::clicked,this,&MainWindow::onTakeSettings);
    connect(ui->pbTelegram,&QPushButton::clicked,this,&MainWindow::SendTelegrammclicked);
    connect(ui->pbReadRelayState,&QPushButton::clicked,this,&MainWindow::ReadRelaystate);
    connect(ui->pbRequest,&QPushButton::clicked,this,&MainWindow::sendRequestClicked);
    connect(ui->pbFirmware,&QPushButton::clicked,this,&MainWindow::ReadVersionClicked);

    // Relais mit slot verbinden
    connect(ui->rbRelay_1,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_2,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_3,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_4,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_5,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_6,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_7,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);
    connect(ui->rbRelay_8,&QCheckBox::checkStateChanged,this,&MainWindow::SetCheckState);

}



void MainWindow::Init(){

    model = new QStringListModel();

    ui->lvResponse->setModel(model);

    mbRTUModel = new ModbusRTUModel();
    modbusClient = new QModbusRtuSerialClient();

    for (QSerialPortInfo info: mbRTUModel->AvailablePorts()){
         ui->cmboPorts->addItem(info.portName());
    }





    //     if (serialRTU->Connected()) {
    //         msg = tr("Verbunden mit: ");
    //         msg.append(mbRTUModel->Ports()[0]->portName());
    //     }
    //     else{
    //         msg = tr("Disconnected: ");
    //         msg.append(mbRTUModel->Ports()[0]->portName());
    //     }
    //     this->statusBar()->showMessage(msg);

    //     /// ********************************************
    //     /// Erstmal alle verfügbaren einstellungen laden
    //     /// anhand der werte die indexes für die
    //     /// comboboxen holen und anzeigen
    //     /// ********************************************
    ui->leSartbit->setText("1");

    for(auto info: mbRTUModel->BaudRates()){
        ui->cmbBaudRate->addItem(info.text, QVariant(info.value));
    }

    for( auto info:mbRTUModel->StopBits()){
         ui->cmbStopBits->addItem(info.text,QVariant(info.value));
    }

    for( auto info:mbRTUModel->Paritys()){
        ui->cmbParity->addItem(info.text,QVariant(info.value));
    }
    for( auto info:mbRTUModel->DataBits()){
        ui->cmbDataBits->addItem(info.text,QVariant(info.value));

    }

    //     for (auto i = 0; i<mbRTUModel->BaudRates().length(); i++){
    //         ui->cmbBaudRate->addItem(mbRTUModel->BaudRates()[i].text, mbRTUModel->BaudRates()[i].value);
    //         if (mbRTUModel->BaudRates()[i].value == mbRTUModel->Ports()[0]->baudRate())
    //             ui->cmbBaudRate->setCurrentIndex(i);
    //     }

    //      for (auto i = 0; i<mbRTUModel->StopBits().length(); i++){
    //          ui->cmbStopBits->addItem(mbRTUModel->StopBits()[i].text, mbRTUModel->StopBits()[i].value);
    //          if (mbRTUModel->StopBits()[i].value == mbRTUModel->Ports()[0]->stopBits())
    //              ui->cmbStopBits->setCurrentIndex(i);+++++++++++++++++++++++
    //      }

    //      for (auto i = 0; i<mbRTUModel->Paritys().length(); i++){
    //          ui->cmbParity->addItem(mbRTUModel->Paritys()[i].text, mbRTUModel->Paritys()[i].value);
    //          if (mbRTUModel->Paritys()[i].value == mbRTUModel->Ports()[0]->parity())
    //              ui->cmbParity->setCurrentIndex(i);
    //      }

    //      for (auto i = 0; i<mbRTUModel->DataBits().length(); i++){
    //          ui->cmbDataBits->addItem(mbRTUModel->DataBits()[i].text, mbRTUModel->DataBits()[i].value);
    //          if (mbRTUModel->DataBits()[i].value == mbRTUModel->Ports()[0]->dataBits())
    //              ui->cmbDataBits->setCurrentIndex(i);
    //     }


    // }
}


void MainWindow::onComboDataBitsIndexChanged(int index){
    QVariant selected = ui->cmbDataBits->itemData(index);
    int bits = selected.toInt();
}

void MainWindow::SetCheckState(Qt::CheckState state){

    QCheckBox *cb = qobject_cast<QCheckBox*>(sender());
    if ( ! cb )
        return;

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils);


    quint16 comand = 0x01 <<  8;   // adresse
    comand |= 0x05;

    QList<quint16> values{0x1,0x5};

    // die adresse zum einfügen
    QList<quint16> relais;

    //Relais nummer extrahieren

    QString relaisname = cb->objectName();


    if (relaisname.length() > 0)
    {
        bool ok;
        QString relaynameasstring = relaisname;

        QString relaisnumber =  relaisname[relaisname.length()-1];


        quint16 number = relaisnumber.toUInt(&ok,16);
        number --;
        qDebug()<<relaynameasstring;

         statusBar()->showMessage(relaisname);

         if (ok) {

            relais.append(0x0);
            relais.append(number);
         }
         else
             return;

    }
    else
        return;

    if (cb->isChecked()){
        relais.append(0xFF );
        relais.append(0x0);
    }
    else{
        relais.append(0x0);
        relais.append(0x0);
    }
    values.append(relais);



    // values.clear();
    // values.append(0x01);
    // values.append(0x05);
    // values.append(0x00);
    // values.append(0x08);
    // values.append(0xFF);
    // values.append(0x00);




    QList<quint16> crc = CheckSum::CRCModbus(values);
    values.append(crc);
    writeUnit.setValues(values);

    // ----------------------------
    // Ausgabe in ie Konsole
    // ----------------------------
    QString st = "Request: ";
    foreach (quint16 val, values) {
        st += QString::number(val,16) + "- ";
    }

    qDebug() << st;


    // if (auto * reply = serialRTU->modbusDevice->sendWriteRequest(writeUnit,1)){
    //     if (! reply->isFinished()){
    //         connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
    //     }
    //     else{
    //         delete reply;
    //     }
    // }



}

void MainWindow::onStateChanged(QModbusDevice::State state) {


    switch (state){
    case QModbusDevice::ConnectedState:  break;
    case QModbusDevice::ClosingState:
        // if(serialRTU->Connected()) {
        //     serialRTU->DisConnect();
        // }
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

            // if (auto * reply = serialRTU->modbusDevice->sendReadRequest(readunit,1))
            // {
            //     if (! reply->isFinished()){
            //         connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
            //     }
            //     else{
            //         delete reply;
            //     }
            // }
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
            // if (auto * reply = serialRTU->modbusDevice->sendWriteRequest(writeUnit,1)){
            //     if (! reply->isFinished()){
            //         connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
            //     }
            //     else{
            //         delete reply;
            //     }
            // }
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

    // if (auto * reply = serialRTU->modbusDevice->sendWriteRequest(writeUnit,1)){
    //     if (! reply->isFinished()){
    //         connect(reply,&QModbusReply::finished,this,&MainWindow::replyFinished);
    //     }
    //     else{
    //         delete reply;
    //     }
    // }
}
void MainWindow::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size){

}
void MainWindow::onTakeSettings(){

    QString t = ui->cmboPorts->currentText();

    modbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, ui->cmboPorts->currentText()); //mbRTUModel->CurrentPort()); // Z.B. COM2 (über Nullmodem-Kabel mit COM1 verbunden)
    modbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, ui->cmbBaudRate->currentData().toInt());
    modbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, ui->cmbDataBits->currentData().toInt());
    modbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, ui->cmbParity->currentData().toInt());
    modbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, ui->cmbStopBits->currentData().toInt());


    // Timeout und Wiederholungen einstellen
    modbusClient->setTimeout(1000); // 1 Sekunde
    modbusClient->setNumberOfRetries(3);



    // Den aktuell ausgewählten Port(info) als Port öffnen:
    // Erstmal den Port  init.
    mbRTUModel->setCurrentPort(mbRTUModel->AvailablePorts()[ui->cmboPorts->currentIndex()]);
    if (mbRTUModel->CurrentPort()->open(QIODeviceBase::ReadWrite) ){
        qDebug() << "Port "<< mbRTUModel->CurrentPortName() << " offen";
        _PortOpen = true;


    }
    else{
         qDebug() << "Port "<< mbRTUModel->CurrentPortName() << " NICHT offen  " << mbRTUModel->CurrentPort()->errorString() ;
        _PortOpen = false;

    }





    // 3. Client verbinden
    if (!modbusClient->connectDevice()) {
        qDebug() << "Fehler beim Verbinden des Modbus-Clients:" << modbusClient->errorString();
        if (_PortOpen)
            mbRTUModel->CurrentPort()->close();
    }

    else{
        qDebug() << "Ok";
    }
}


MainWindow::~MainWindow()
{

    if (_PortOpen)
        mbRTUModel->CurrentPort()->close();
    delete serialRTU;
    delete ui;
   // delete rs485;
}
