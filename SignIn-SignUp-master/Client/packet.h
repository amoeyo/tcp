#ifndef PACKET_H
#define PACKET_H

#include <fstream>
#include <stdint.h>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <QTimer>
#include <QString>

struct Packet{
    uint16_t checksum;
    uint16_t len;
    uint32_t seq;
    char data[504];
};

struct AckPacket{
    uint16_t checksum;
    uint16_t len;
    uint32_t ack;
};

uint16_t packet_checksum(struct Packet* pkt);

uint16_t ack_packet_checksum(struct AckPacket* pkt);

#endif // PACKET_H
