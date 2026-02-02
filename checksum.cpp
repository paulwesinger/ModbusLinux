#include "checksum.h"
#include <QList>
CheckSum::CheckSum() {}

std::vector<ubyte> CheckSum::CRCModbus(std::vector<ubyte>data)
{
    ushort currentcrc = 0xFFFF;
    //ushort mask = 0x0001;
    try
    {
        for (int j = 0; j < data.size(); j++)
        {
            currentcrc ^= data[j];

            for (int i = 8; i != 0; i--)
            {
                if ((currentcrc & 0x0001) != 0)
                {
                    currentcrc >>= 1;
                    currentcrc ^= 0xA001;
                }
                else
                {
                    currentcrc = currentcrc >>= 1;
                }
            }
        }

        std::vector<ubyte> ret;
        for(int i = 0; i != sizeof(currentcrc); ++i)
        {
            ret.push_back((char)((currentcrc & (0xFF << (i*8))) >> (i*8)));
        }
        return ret;
    }
    catch(...)
    {
        return std::vector<ubyte>();
    }
}


QList<quint16> CheckSum::CRCModbus(QList<quint16> data){
    quint16 currentcrc = 0xFFFF;
    //ushort mask = 0x0001;
    try
    {
        for (int j = 0; j < data.size(); j++)
        {
            currentcrc ^= data[j];

            for (int i = 8; i != 0; i--)
            {
                if ((currentcrc & 0x0001) != 0)
                {
                    currentcrc >>= 1;
                    currentcrc ^= 0xA001;
                }
                else
                {
                    currentcrc = currentcrc >>= 1;
                }
            }
        }

        QList<quint16> ret;
        for(int i = 0; i != sizeof(currentcrc); ++i)
        {
            ret.append((currentcrc & (0xFF << (i*8))) >> (i*8));
        }
        return ret;
    }
    catch(...)
    {
        return QList<quint16>();
    }
}

