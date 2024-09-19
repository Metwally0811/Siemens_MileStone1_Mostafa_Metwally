#include "Ethernet_Packet.h"
#pragma once
#include <iomanip> 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Ethernet_Packet::Ethernet_Packet(int ifg_size, int payload_size) {
	IFGSize = ifg_size;
	Payload_Size = payload_size;
	IFG = new unsigned char[IFGSize];  

	Payload = new unsigned char[Payload_Size]; 


	for (int i = 0; i < IFGSize; i++) {
		IFG[i] = 0xff;
	}
	for (int i = 0; i < Payload_Size; i++) {
		Payload[i] = 0x00;
	}
	for (int i = 0; i < 6; ++i) {
		DestAddress[i] = 0;
	}
	for (int i = 0; i < 6; ++i) {
		SourceAddress[i] = 0;
	}

	
}

void Ethernet_Packet::setDestAddress(unsigned char* DestAddress)
{
	for (int i = 0; i < 6; i++) {
		this->DestAddress[i] = DestAddress[i];
	}

}

void Ethernet_Packet::setSourceAddress(unsigned char* SourceAddress)
{
	for (int i = 0; i < 6; i++) {
		this->SourceAddress[i] = SourceAddress[i];
	}
}

void Ethernet_Packet::setPayload(unsigned char* Payload)
{
	for (int i = 0; i < Payload_Size; i++) {
		this->Payload[i] = Payload[i];
	}
}

void Ethernet_Packet::setIFG(unsigned char* IFG)
{
	for (int i = 0; i < IFGSize; i++) {
		this->IFG[i] = IFG[i];
	}
}

void Ethernet_Packet::setIFGSize(int IFGSize)
{
	this->IFGSize = IFGSize;
}

void Ethernet_Packet::setPayloadSize(int Payload_Size)
{
	this->Payload_Size = Payload_Size;
}

unsigned char* Ethernet_Packet::getDestAddress()
{

	return DestAddress;
	
}

unsigned char* Ethernet_Packet::getSourceAddress()
{
	return SourceAddress;
	
}

unsigned char* Ethernet_Packet::getPayload()
{
	return Payload;
	
}

unsigned char* Ethernet_Packet::getIFG()
{
	return IFG;
	
}

int Ethernet_Packet::getIFGSize()
{
	return IFGSize;
}

int Ethernet_Packet::getPayloadSize()
{
	return Payload_Size;
	
}
const unsigned char* Ethernet_Packet::getPreamble()
{
	return preamble;
}

const unsigned char Ethernet_Packet::getSFD()
{
	return SFD;
}

const unsigned char* Ethernet_Packet::getEtherType()
{
	return EtherType;
}

 unsigned char* Ethernet_Packet::getFCS()
{
	return FCS;
	
}


void Ethernet_Packet::print() {
	cout << "Ethernet_Packet.Preamble = ";
	for (int i = 0; i < 7; i++) {
		cout << hex << (int)preamble[i] << " ";
	}
	cout << dec << "\n";
	cout << "Ethernet_Packet.SFD = " << hex << (int)SFD << dec << "\n";
	cout << "Ethernet_Packet.DestAddress = 0x";

	cout << "" << hex << (int)DestAddress << " ";

	cout << dec << "\n";
	cout << "Ethernet_Packet.SourceAddress = 0x";

	cout << hex << (int)SourceAddress << " ";

	cout << dec << "\n";
	cout << "Ethernet_Packet.EtherType = ";
	for (int i = 0; i < 2; i++) {
		cout << hex << (int)EtherType[i] << " ";
	}
	cout << dec << "\n";
	cout << "Ethernet_Packet.Payload = ";
	for (int i = 0; i < 46; i++) {
		cout << hex << (int)Payload[i] << " ";
	}
	cout << dec << "\n";
	cout << "Ethernet_Packet.FCS = ";
	for (int i = 0; i < 4; i++) {
		cout << hex << (int)FCS[i] << " ";
	}
	cout << dec << "\n";
	cout << "Ethernet_Packet.IFG = ";
	for (int i = 0; i < IFGSize; i++) {
		cout << hex << (int)IFG[i] << " ";
	}
	cout << dec << "\n";
	cout << "IFGSize = " << IFGSize << "\n";
}



int Ethernet_Packet::Burst_print(int key) {
	int Counter=key;
	for (int i = 0; i < 7; i++) {
		if (Counter >= 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)preamble[i];
		Counter++;
	}
	if (Counter == 4)
	{
		cout << dec << "\n";
		Counter = 0;
	}
	std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)SFD << dec;
	Counter++;
	for (int i = 0; i < 6; ++i) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)DestAddress[i];
		Counter++;
	}
	for (int i = 0; i < 6; ++i) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)SourceAddress[i];
		Counter++;

	}


	for (int i = 0; i < 2; i++) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)EtherType[i];
		Counter++;
	}

	for (int i = 0; i < Payload_Size; i++) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)Payload[i];
		Counter++;

	}

	for (int i = 0; i < 4; i++) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)FCS[i];
		Counter++;


	}

	for (int i = 0; i < IFGSize; i++) {
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)IFG[i];
		Counter++;
		if (Counter == 4)
		{
			cout << dec << "\n";
			Counter = 0;
		}
	}
	if (Counter == 4)
	{
		cout << dec << "\n";
		Counter = 0;
	}
	return Counter;
}

void Ethernet_Packet::calculateFCS()
{
	std::vector<int> data;
	data.insert(data.end(), begin(preamble), end(preamble));
	data.insert(data.end(), &SFD, &SFD + 1);
	data.insert(data.end(), begin(DestAddress), end(DestAddress));
	data.insert(data.end(), begin(SourceAddress), end(SourceAddress));
	data.insert(data.end(), begin(EtherType), end(EtherType));
	data.insert(data.end(), Payload, Payload + Payload_Size);

	uint32_t crc = 0xEDB88320;
	for (int byte : data) {
		crc ^= byte;
		for (int i = 0; i < 8; ++i) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else {
				crc >>= 1;
			}
		}
	}
	FCS[0] = (crc >> 24) & 0xFF;
	FCS[1] = (crc >> 16) & 0xFF;
	FCS[2] = (crc >> 8) & 0xFF;
	FCS[3] = crc & 0xFF;
}
