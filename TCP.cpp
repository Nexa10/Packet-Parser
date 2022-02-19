#include <iostream>
#include<iomanip>
#include"TcpPacketParser.h"
using namespace std;

const int MAX_LEN = 1500;//The maximum length of a TCP packet could be up to 65535 bytes
const int HEADER_LEN = 22;//The length of the packet header

bool TcpPacketParser::parse(const char* packet) {
	bool retval;
	if (packet == nullptr) return false;

	//source port
	this->sourcePort = (*packet) * 0x0100;
	++packet;
	this->sourcePort += *packet;

	//destination port
	++packet;
	this->destPort = (*packet) * 0x0100;//0x00 * 0x0100
	++packet;
	this->destPort += *packet;

	//sequence Number
	++packet;
	this->sequence_num = (*packet) * 0x1000000;
	packet;
	 this->sequence_num = (*packet) * 0x10000;
	 ++packet;
	this->sequence_num = (*packet) * 0x100;
	 ++packet;
	 this->sequence_num += *packet;
	
	//acknolegement number;
	 ++packet;
	 this->ack_num = (*packet) * 0x1000000;
	 packet;
	 this->ack_num = (*packet) * 0x10000;
	 ++packet;
	 this->ack_num = (*packet) * 0x100;
	 ++packet;
	 this->ack_num += *packet;

	 //ignore
	++packet;
	this->ignore = (*packet) * 0x01000000;
	++packet;
	this->ignore = (*packet) * 0x010000;
	++packet;
	this->ignore = (*packet) * 0x0100;
	++packet;
	this->ignore = *packet;

	//check sum
	++packet;
	this->checksum = (*packet) * 0x0100;
	++packet;
	this->checksum += *packet;

	//ignore2
	++packet;
	this->ignore2 = (*packet) * 0x0100;
	++packet;
	this->ignore2 = *packet;

	//length
	++packet;
	this->length = (*packet) * 0x0100;
	++packet;
	this->length += *packet;

	unsigned int Mychecksum;//for comparison
	Mychecksum = sourcePort + destPort + sequence_num + ack_num + length + ignore + ignore2;
	if (Mychecksum == this->checksum) retval = true;

	//data
	if (retval = true) {
		this->data = new unsigned char[length + 1];
		memcpy(this->data, packet + HEADER_LEN, length + 1);
		this->data[length] = '\0';
	}

	return retval;
}

void TcpPacketParser::display(std::ostream& os)const {
	os << "Report for UDP Packet Parser" << endl;
	os << setw(13) << left << "Source port: " << this->sourcePort << endl;
	os << setw(13) << left << "Dest port: " << this->destPort << endl;
	os << setw(13) << left << "Seq number: " << this->sequence_num << endl;
	os << setw(13) << left << "Ack number: " << this->ack_num << endl;
	os << setw(13) << left << "Data length: " << this->length << endl;
	os << setw(13) << left << "Data: " << this->data << endl;
}

TcpPacketParser::~TcpPacketParser() {
	sourcePort = 0;
	destPort = 0;
	sequence_num = 0;
	ack_num = 0;
	ignore = 0;
	ignore2 = 0;
	length = 0;
	checksum = 0;
	data = nullptr;
}