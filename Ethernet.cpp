#pragma once
#include "Ethernet.h"
#include <iomanip> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void Ethernet::setLineRate(double LineRate)
{
	this->LineRate = LineRate;
}
void Ethernet::setCaptureSizeMs(int CaptureSizeMs)
{
	this->CaptureSizeMs = CaptureSizeMs;
}
void Ethernet::setMinNumOfIFGsPerPacket(int MinNumOfIFGsPerPacket)
{
	this->MinNumOfIFGsPerPacket = MinNumOfIFGsPerPacket;
}
void Ethernet::setDestAddress(uint64_t DestAddress)
{
	this->DestAddress = DestAddress;
}
void Ethernet::setSourceAddress(uint64_t SourceAddress)
{
	this->SourceAddress = SourceAddress;
}
void Ethernet::setMaxPacketSize(double MaxPacketSize)
{
	this->MaxPacketSize = MaxPacketSize;
}
void Ethernet::setBurstSize(int BurstSize)
{
	this->BurstSize = BurstSize;
}
void Ethernet::setBurstPeriodicity_us(int BurstPeriodicity_us)
{
	this->BurstPeriodicity_us = BurstPeriodicity_us;
}
double Ethernet::getLineRate()
{
	return LineRate;
}
int Ethernet::getCaptureSizeMs()
{
	return CaptureSizeMs;
}
int Ethernet::getMinNumOfIFGsPerPacket()
{
	return MinNumOfIFGsPerPacket;
}
uint64_t Ethernet::getDestAddress()
{
	return DestAddress;
}
uint64_t Ethernet::getSourceAddress()
{
	return SourceAddress;
}
double Ethernet::getMaxPacketSize()
{
	return MaxPacketSize;
}
int Ethernet::getBurstSize()
{
	return BurstSize;
}
int Ethernet::getBurstPeriodicity_us()
{
	return BurstPeriodicity_us;
}

void Ethernet::print()
{
	cout << "Eth.LineRate = " << LineRate << "\n";
	cout << "Eth.CaptureSizeMs = " << CaptureSizeMs << "\n";
	cout << "Eth.MinNumOfIFGsPerPacket = " << MinNumOfIFGsPerPacket << "\n";
	std::cout << "Eth.DestAddress = 0x" << std::hex << std::setw(12) << std::setfill('0') << DestAddress << dec << "\n";
	std::cout << "Eth.SourceAddress = 0x" << std::hex << std::setw(12) << std::setfill('0') << SourceAddress << dec << "\n";
	cout << "Eth.MaxPacketSize = " << MaxPacketSize << "\n";
	cout << "Eth.BurstSize = " << BurstSize << "\n";
	cout << "Eth.BurstPeriodicity_us = " << BurstPeriodicity_us << " us" << "\n";
}