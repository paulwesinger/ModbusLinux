#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
//#include <QModbusRtuSerialServer>
#include "serialrtu.h"
#include "serialrtumodel.h"
#include <QStringListModel>

#include <QSerialPort>
#include <QModbusDataUnit>
#include <QModbusRtuSerialClient>
#include <QModbusReply>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

#include <QDebug>


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
    QList<QSerialPortInfo> AvailablePorts();


protected:
    void Init();
    SerialRTu * serialRTU = nullptr;
    ModbusRTUModel * mbRTUModel = nullptr;

    QStringListModel *model = nullptr;
    QModbusReply * reply = nullptr;

    QList<quint16> ConvertStringToNumber(QStringList values);
    QModbusRtuSerialClient * modbusClient;

private slots:
    void onStateChanged(QModbusDevice::State state);
    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);
    void onComboDataBitsIndexChanged(int index);
    void onTakeSettings();
    void SendTelegrammclicked();
    void ReadRelaystate();
    void ReadVersionClicked();
    void SetCheckState(Qt::CheckState state);

    void replyFinished();
    void sendRequestClicked();

private:
    void Initconnections();

    bool _PortOpen ;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
