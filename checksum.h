#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <QByteArray>

typedef unsigned char ubyte;

class CheckSum
{
public:
    CheckSum();

    static std::vector<ubyte> CRCModbus(std::vector<ubyte> data);

};

#endif // CHECKSUM_H
