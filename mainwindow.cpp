#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>



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
    connect(ui->pbOk,&QPushButton::clicked,this,&MainWindow::onTakeSettings);
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

}


MainWindow::~MainWindow()
{
    delete serialRTU;
    delete ui;
   // delete rs485;
}
