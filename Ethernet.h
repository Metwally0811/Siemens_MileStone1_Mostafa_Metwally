#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


class Ethernet {
    double LineRate;
    int CaptureSizeMs;
    int MinNumOfIFGsPerPacket;
    uint64_t DestAddress;
    uint64_t SourceAddress;
    double MaxPacketSize;
    int BurstSize;
    int BurstPeriodicity_us;

public:
	Ethernet() : LineRate(0), CaptureSizeMs(0), MinNumOfIFGsPerPacket(0), DestAddress(0), SourceAddress(0), MaxPacketSize(0), BurstSize(0), BurstPeriodicity_us(0) {}
	void setLineRate(double LineRate);
	void setCaptureSizeMs(int CaptureSizeMs);
	void setMinNumOfIFGsPerPacket(int MinNumOfIFGsPerPacket);
	void setDestAddress(uint64_t DestAddress);
	void setSourceAddress(uint64_t SourceAddress);
	void setMaxPacketSize(double MaxPacketSize);
	void setBurstSize(int BurstSize);
	void setBurstPeriodicity_us(int BurstPeriodicity_us);
	double getLineRate();
	int getCaptureSizeMs();
	int getMinNumOfIFGsPerPacket();
	uint64_t getDestAddress();
	uint64_t getSourceAddress();
	double getMaxPacketSize();
	int getBurstSize();
	int getBurstPeriodicity_us();

    void print();
};