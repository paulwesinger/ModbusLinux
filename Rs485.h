#ifndef RS485_H
#define RS485_H

#include <QObject>
#include <QSerialPort>
#include <QList>


typedef enum{
    BD4800 = 0,
    BD9600,
    BD19200,
    BD38400,
    BD57600,
    BD115200,
    BD128000,
    BD250000,
    BD256000
} BaudRates;

typedef struct
{
    int Startbits;
    QList<quint32> StatndardBaudrates;
    int Stopbits;
} Protokoll;



class Rs485 : public QObject
{
    Q_OBJECT
public:
    explicit Rs485(QObject *parent = nullptr);
    QList<Protokoll> Ports;

    QSerialPort* GetSerialPort();

protected:
    QSerialPort* serialport = nullptr;
signals:
};

#endif // RS485_H
