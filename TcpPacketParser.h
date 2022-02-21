//Dennis Audu
//148463193
//daudu@myseneca
#ifndef _TCPPACKETPARSER_H_
#define _TCPPACKETPARSER_H_ 
#include"PacketParser.h"

class TcpPacketParser : public PacketParser {
	unsigned int sourcePort;
	unsigned int destPort;
	unsigned int sequence_num;
	unsigned int ack_num;
	unsigned int ignore;
	unsigned int ignore2;
	unsigned int length;
	unsigned int checksum;
	unsigned char* data;
	
public:
	 bool parse(const char* packet);
	 void display(std::ostream& os)const;
	 ~TcpPacketParser();
};

#endif