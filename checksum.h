#ifndef CHECKSUM_H
#define CHECKSUM_H
#include <QList>

typedef unsigned char ubyte;

class CheckSum
{
public:
    CheckSum();

    static std::vector<ubyte> CRCModbus(std::vector<ubyte> data);
    static QList<quint16> CRCModbus(QList<quint16> data);

};

#endif // CHECKSUM_H
