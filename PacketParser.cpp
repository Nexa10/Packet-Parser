//Dennis Audu
//148463193
//daudu@myseneca
#include<iostream>
#include"PacketParser.h"

std::ostream& operator<<(std::ostream& os, PacketParser& parser) {
	parser.display(os);
	return os;
}