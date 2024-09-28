#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class ORAN
{
	int SCS;
	int MaxNrb;
	int NrbPerPacket;
	string PayloadType;
	string Payload;
public:
	ORAN() : SCS(0), MaxNrb(0), NrbPerPacket(0), PayloadType(" "), Payload(" ") {}
	// setters
	void setSCS(int SCS);
	void setMaxNrb(int MaxNrb);
	void setNrbPerPacket(int NrbPerPacket);
	void setPayloadType(string PayloadType);
	void setPayload(string Payload);
	char getSCS();
	//getters
	int getMaxNrb();
	int getNrbPerPacket();
	string getPayloadType();
	string getPayload();
	void print();

};

