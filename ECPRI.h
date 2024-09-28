#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ORAN_Packet.h"
class ECPRI
{
	const unsigned char Version_Reserved_Concatenation=0;
	unsigned char Message;
	ORAN_Packet ORAN_Payload;
	const unsigned char PC_RTC[2] = {0x00,0x00};
	unsigned char Seqid;
private:
public:
	
	ECPRI() : Message(0), ORAN_Payload(), Seqid{0}
	{
	}
	ECPRI(ORAN_Packet ORAN_Payload, unsigned char Seqid);
	ECPRI& operator=(const ECPRI& other) {
		if (this != &other) {
			Message = other.Message;
			ORAN_Payload = other.ORAN_Payload;
			Seqid = other.Seqid;
		}
		return *this;
	}
	void setMessage(unsigned char Message);
	void setPayload(ORAN_Packet ORAN_Payload);
	void setSeqid(unsigned char Seqid);
	unsigned char getVersion_Reserved_Concatenation();
	unsigned char getMessage();
	ORAN_Packet getPayload();
	unsigned const char* getPC_RTC();
	unsigned char getSeqid();
	void print();
};

