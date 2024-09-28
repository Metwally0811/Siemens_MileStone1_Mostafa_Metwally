#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ECPRI.h"

using namespace std;
class Ethernet_Packet
{
	/*
Preamble: 0xfb555555555555
• Start - of - Frame Delimiter(SFD) : (0xD5)
• Destination and Source MAC addresses : 6 byte Dest Address + 6 byte Src Add octets
• EtherType : 2 octets to define the payload type
• Payload : 46..1500 octets of Ethernet payload
(can be up to 9000 byte for jumbo frames and 16000 byte for super jumpo extra cheese frames)
• Frame Check Sequence(FCS) : 4 octets of CRC for error correction and detection
*/

	const unsigned char preamble[7] = { 0xfb, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 };
	const unsigned char SFD = 0xD5;
	unsigned char DestAddress[6]; //6 bytes
	unsigned char SourceAddress[6];// 6 bytes
	const unsigned char EtherType[2] = { 0xAA, 0xAA };
	ECPRI ECPRI_Packet;
	unsigned char FCS[4] = { 0x77, 0x77, 0x77, 0x77 };
	unsigned char* IFG ;
	int IFGSize; 

public:


	Ethernet_Packet() : DestAddress{ 0 }, SourceAddress{ 0 }, IFGSize(0) {}
	Ethernet_Packet(int ifgSize,  ECPRI ECPRI_Payload);
	void setDestAddress(unsigned char* DestAddress);
	void setSourceAddress(unsigned char* SourceAddress);
	void setPayload( ECPRI ECPRI_Packet);
	void setIFG(unsigned char* IFG);
	void setIFGSize(int IFGSize);
	unsigned char* getDestAddress();
	unsigned char* getSourceAddress();
	ECPRI getPayload();
	unsigned char* getIFG();
	int getIFGSize();
	const unsigned char* getPreamble();
	const unsigned char getSFD();
	const unsigned char* getEtherType();
	 unsigned char* getFCS();
	
	void print();
	int Burst_print(int key);
	void calculateFCS();
};
