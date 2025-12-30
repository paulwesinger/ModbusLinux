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

        // ********************************************
        // Erstmal alle verfügbaren einstellungen laden
        // ********************************************
        ui->leSartbit->setText("1");

        int baudindex = 0;


        for (auto j= 0; j<mbRTUModel->Ports().length();j++) {
            for (auto i = 0; i<mbRTUModel->BaudRates().length(); i++){
                ui->cmbBaudRate->addItem(mbRTUModel->BaudRates()[i].text, mbRTUModel->BaudRates()[i].value);
                if (mbRTUModel->BaudRates()[i].value == mbRTUModel->Ports()[j]->baudRate())
                    baudindex = i;
            }

            ui->cmbBaudRate->setCurrentIndex(baudindex);

            // for (auto i = 0; i<mbRTUModel->StopBits().length(); i++){/8
            //     ui->cmbStopBits->addItem(mbRTUModel->StopBits()[i].text, mbRTUModel->StopBits()[i].value);
            // }

            // for (auto i = 0; i<mbRTUModel->Paritys().length(); i++){
            //     ui->cmbParity->addItem(mbRTUModel->Paritys()[i].text, mbRTUModel->Paritys()[i].value);
            // }
            // for (auto i = 0; i<mbRTUModel->DataBits().length(); i++){
            //     ui->cmbDataBits->addItem(mbRTUModel->DataBits()[i].text, mbRTUModel->DataBits()[i].value);
            // }

            // *********************************************
            // Checken was auf dem Seriellen Port
            // eingestellt ist, und in den Combos anzeigen
            // *********************************************

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
