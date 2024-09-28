#include "ORAN.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


void ORAN::setSCS(int SCS)
{
	if (SCS % 15 == 0)
		this->SCS = SCS;
	else
	{
		cout << "SCS must be multiple of 15" << endl;
		exit(EXIT_FAILURE);// terminate with error
	}
}
void ORAN::setMaxNrb(int MaxNrb)
{
	if (MaxNrb < 0 || MaxNrb > 255)
	{
		cout << "MaxNrb must be between 0 and 255" << endl;
		exit(EXIT_FAILURE);// terminate with error
	}
	if (MaxNrb == 0)
	{
		this->MaxNrb = 273;
	}
	else
	{
		this->MaxNrb = MaxNrb;
	}
}
void ORAN::setNrbPerPacket(int NrbPerPacket)
{
	if (NrbPerPacket < 0 || NrbPerPacket > 255)
	{
		cout << "NrbPerPacket must be between 0 and 255" << endl;
		exit(EXIT_FAILURE);// terminate with error
	}
	if (NrbPerPacket == 0)
	{
		this->NrbPerPacket = 273;
	}
	else
	{
		this->NrbPerPacket = NrbPerPacket;
	}
}
void ORAN::setPayloadType(string PayloadType)
{
	this->PayloadType = PayloadType;
}
void ORAN::setPayload(string Payload)
{
	this->Payload = Payload;
}

char ORAN::getSCS()
{
	return SCS;
}
int ORAN::getMaxNrb()
{
	return MaxNrb;
}
int ORAN::getNrbPerPacket()
{
	return NrbPerPacket;
}
string ORAN::getPayloadType()
{
	return PayloadType;
}
string ORAN::getPayload()
{
	return Payload;
}
void ORAN::print()
{
	cout << "Oran.SCS: " << SCS << endl;
	cout << "Oran.MaxNrb: " << MaxNrb << endl;
	cout << "Oran.NrbPerPacket: " << NrbPerPacket << endl;
	cout << "Oran.PayloadType: " << PayloadType << endl;
	cout << "Oran.Payload: " << Payload << endl;
}
