#include "packet.h"

using namespace std;

quint16 packet_checksum(struct Packet* pkt)
{
    quint32 sum = 0x0;
    quint16 *pkt_ptr = (quint16*)(pkt);
    quint16 *ptr = (quint16*)&(pkt->data);
    for(unsigned int i=2; i<sizeof(struct Packet);i+=2)
    {
        if(i<8)
            sum += *(++pkt_ptr);
        else
            sum += *(ptr++);
        if(sum > 0xffff)
            sum -= 0xffff;
    }
    return ~(sum);
}

uint16_t ack_packet_checksum(struct AckPacket* pkt)
{
    quint32 sum = 0x0;
    quint16 *pkt_ptr = (quint16*)(pkt);
    for(unsigned int i=2; i<sizeof(struct AckPacket);i+=2)
    {
        sum += *(++pkt_ptr);
        if(sum > 0xffff)
            sum -= 0xffff;
    }
    return ~(sum);
}
