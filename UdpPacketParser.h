//Dennis Audu
//148463193
//daudu@myseneca
#ifndef _UDPPACKETPARSER_H_
#define _UDPPACKETPARSER_H_ 
#include "PacketParser.h"

class UdpPacketParser : public PacketParser {
	unsigned int sourcePort;
	unsigned int destPort;
	unsigned int length;
	unsigned int checksum;
	unsigned char* data;
public:
	 bool parse(const char* packet);
	 void display(std::ostream& os)const;
	 ~UdpPacketParser();
};

#endif