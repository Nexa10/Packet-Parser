#include <iostream>
#include"UdpPacketParser.h"
#include<iomanip>
using namespace std;
const int MAX_LEN = 65535;//The maximum length of a UDP packet could be up to 65535 bytes
const int HEADER_LEN = 8;//The length of the packet header

bool UdpPacketParser::parse(const char* packet) {
	bool retval;
	if (packet == nullptr) return false;

	this->sourcePort = (*packet) * 0x0100;
	++packet;
	this->sourcePort += *packet;

	++packet;
	this->destPort = (*packet) * 0x0100;
	++packet;
	this->destPort += *packet;

	++packet;
	this->length = (*packet) * 0x0100;
	++packet;
	length += *packet;

	++packet;
	this->checksum = (*packet) * 0x0100;
	++packet;
	this->checksum += *packet;

	unsigned int Mychecksum;//for comparing
	Mychecksum = sourcePort + destPort + length;
	if (Mychecksum == checksum) retval = true;

	if (retval = true) {
		this->data = new unsigned char[length + 1];
		memcpy(this->data, packet + HEADER_LEN, length + 1);
		this->data[length] = '\0';
	}

	return retval;
}

void UdpPacketParser::display(std::ostream& os)const {
	os << "Report for UDP Packet Parser" << endl;
	os << setw(13) << left << "Source port: " << this->sourcePort << endl;
	os << setw(13) << left << "Dest port: " << this->destPort << endl;
	os << setw(13) << left << "Data length: " << this->length << endl;
	os << setw(13) << left << "Data: " << this->data << endl;
}

UdpPacketParser::~UdpPacketParser() {
	sourcePort = 0;
	destPort = 0;
	length = 0;
	checksum = 0;
	data = nullptr;
}