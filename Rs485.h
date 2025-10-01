#ifndef RS485_H
#define RS485_H

#include <QObject>
#include <QSerialPort>
#include <QList>

class Rs485 : public QObject
{
    Q_OBJECT
public:
    explicit Rs485(QObject *parent = nullptr);
    QList<QString> Portnames();

protected:
    QSerialPort* serialport = nullptr;

signals:
};

#endif // RS485_H
