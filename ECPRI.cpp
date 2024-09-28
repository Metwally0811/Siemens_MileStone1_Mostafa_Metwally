#include "ECPRI.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ORAN_Packet.h"

using namespace std;
//constructor
//ECPRI::ECPRI() :  Message(0)
//{
//	for (int i = 0; i < 2; i++) {
//		Payload[i] = 0;
//		Seqid = 0;
//	}
//}

ECPRI::ECPRI(ORAN_Packet ORAN_Payload, unsigned char Seqid)
{
	this->ORAN_Payload = ORAN_Payload;
	this->Seqid = Seqid;
	this->Message = 0;
}

void ECPRI::setMessage(unsigned char Message)
{
	this->Message = Message;
}

void ECPRI::setPayload(ORAN_Packet ORAN_Payload)
{
	this->ORAN_Payload = ORAN_Payload;
}

void ECPRI::setSeqid(unsigned char Seqid)
{
	
		this->Seqid = Seqid;
	
}

unsigned char ECPRI::getVersion_Reserved_Concatenation()
{
	return Version_Reserved_Concatenation;
}

unsigned char ECPRI::getMessage()
{
	return Message;
	
}

ORAN_Packet ECPRI::getPayload()
{
	return ORAN_Payload;
}

const unsigned char* ECPRI::getPC_RTC()
{
	return PC_RTC;
}

unsigned char ECPRI::getSeqid()
{
	return Seqid;
}
