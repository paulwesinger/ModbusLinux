#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>
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
    connect(serialRTU->ModbusServer(),&QModbusServer::stateChanged,this,&MainWindow::onStateChanged);
    connect(serialRTU->ModbusServer(),&QModbusServer::dataWritten,this,&MainWindow::onDataWritten);
    connect(ui->cmbDataBits,&QComboBox::currentIndexChanged,this,&MainWindow::onComboDataBitsIndexChanged);
    connect(ui->pbTakeSettings,&QPushButton::clicked,this,&MainWindow::onTakeSettings);
}

void MainWindow::Init(){
    QString msg;
    mbRTUModel = new ModbusRTUModel();
    serialRTU = new SerialRTu(this);

    if (serialRTU->Init(mbRTUModel,this)){
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
         if (serialRTU->modbusDevice->open()){

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
    case QModbusDevice::ClosingState: break;
    default:

        break;
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
    std::vector<ubyte> protokoll {0x01,0x01,0x00,0x00,0x00,0x08};

    /// funktioniert
    /// !!!
    std::vector<ubyte> crc = CheckSum::CRCModbus(protokoll);

    // vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    protokoll.insert(protokoll.end(),crc.begin(),crc.end());
    QByteArray img (reinterpret_cast<const char*>(protokoll.data()), protokoll.size());

    QModbusResponse request(QModbusResponse::ReadCoils,img);
    QModbusResponse res = serialRTU->modbusDevice->processRequest(request);



}




MainWindow::~MainWindow()
{
    delete serialRTU;
    delete ui;
   // delete rs485;
}
