#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusRtuSerialServer>
#include "serialrtu.h"
#include "serialrtumodel.h"

#include "Rs485.h"
//#include "modbusrs485.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//typedef unsigned char byt;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void Init();
    //QModbusClient * mbClient;
    //QModbusDevice * mbDevice;
    //QModbusServer * mbServer;
    SerialRTu * serialRTU = nullptr;
    ModbusRTUModel * mbRTUModel = nullptr;

    QModbusReply * reply = nullptr;

private slots:
    void onStateChanged(QModbusDevice::State state);
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);
    void onComboDataBitsIndexChanged(int index);
    void onTakeSettings();
    void SendTelegrammclicked();
    void ReadRelaystate();

    void replyFinished();

private:
    void Initconnections();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
