#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QSerialPortInfo>
//#include <QModbusClient>
//#include <QModbusDevice>
//#include <QModbusServer>
#include <QModbusRtuSerialServer>
#include "serialrtu.h"

#include "Rs485.h"
//#include "modbusrs485.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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

private slots:
    void onStateChanged(QModbusDevice::State state);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
