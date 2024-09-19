#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread> 
#include <chrono> 
#include <iomanip> 
#include <vector>
#include <algorithm>
#include "Ethernet.h"
#include "Ethernet_Packet.h"

using namespace std;



void parseEthConfig(const string& fileName, Ethernet& eth) {
	ifstream file(fileName);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string key;
		string value;

		// Split the line at '='
		if (getline(ss, key, '=') && getline(ss, value)) {
			// Remove any comments after '//'
			size_t commentPos = value.find("//");
			if (commentPos != string::npos) {
				value = value.substr(0, commentPos);
			}
			// Remove whitespace
			key.erase(key.find_last_not_of(" \n\r\t") + 1);
			value.erase(0, value.find_first_not_of(" \n\r\t"));
			// Parse values based on the key

			if (key == "Eth.LineRate") {
				eth.setLineRate(stod(value));
			}
			else if (key == "Eth.CaptureSizeMs") {
				eth.setCaptureSizeMs(stoi(value));
			}
			else if (key == "Eth.MinNumOfIFGsPerPacket") {
				eth.setMinNumOfIFGsPerPacket(stoi(value));
			}
			else if (key == "Eth.DestAddress") {
				eth.setDestAddress(stoull(value, nullptr, 16)); // Hexadecimal
			}
			else if (key == "Eth.SourceAddress") {
				eth.setSourceAddress(stoull(value, nullptr, 16)); // Hexadecimal
			}
			else if (key == "Eth.MaxPacketSize") {
				eth.setMaxPacketSize(stod(value));
			}
			else if (key == "Eth.BurstSize") {
				eth.setBurstSize(stoi(value));
			}
			else if (key == "Eth.BurstPeriodicity_us") {
				eth.setBurstPeriodicity_us(stoi(value));
			}
		}
	}

}



int Burst_printer(int key, Ethernet_Packet* P) {
	int Counter = key;
	const unsigned char* const_burst_print_temp;
	unsigned char* burst_print_temp;
	ofstream outfile("Milestone_1_output6.txt");
	for (int i = 0; i < 7; i++) {
		if (Counter >= 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		const_burst_print_temp = P->getPreamble();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_burst_print_temp[i];
		Counter++;
	}
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}

	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)P->getSFD() << dec;
	Counter++;
	for (int i = 0; i < 6; ++i) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		burst_print_temp = P->getDestAddress();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)burst_print_temp[i];
		Counter++;
	}
	for (int i = 0; i < 6; ++i) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		burst_print_temp = P->getSourceAddress();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)burst_print_temp[i];
		Counter++;

	}


	for (int i = 0; i < 2; i++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		const_burst_print_temp = P->getEtherType();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_burst_print_temp[i];
		Counter++;
	}

	for (int i = 0; i < P->getPayloadSize(); i++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		burst_print_temp = P->getPayload();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)burst_print_temp[i];
		Counter++;

	}

	for (int i = 0; i < 4; i++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		burst_print_temp = P->getFCS();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)burst_print_temp[i];
		Counter++;


	}

	for (int i = 0; i < P->getIFGSize(); i++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		burst_print_temp = P->getIFG();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)burst_print_temp[i];
		Counter++;
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
	}
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	return Counter;
}
int Calculate_Number_of_Bursts(Ethernet eth) {
	float Num_of_Bursts = (eth.getCaptureSizeMs() * 1000) / eth.getBurstPeriodicity_us();
	return Num_of_Bursts;
}
int Calculate_Number_of_Packets(Ethernet eth) {
	float Num_of_Packets = Calculate_Number_of_Bursts(eth) * eth.getBurstSize();
	return Num_of_Packets;
}
int Calculate_Packet_Duration(Ethernet eth) {
	double Packet_Duration = eth.getMaxPacketSize() * 8 * 1000000 / (eth.getLineRate() * (1024) * (1024) * (1024));
	return Packet_Duration;
}
int Calculate_Burst_Duration(Ethernet eth) {
	double Burst_Duration = eth.getBurstSize() * Calculate_Packet_Duration(eth);
	return Burst_Duration;
}

int main() {
	Ethernet eth;

	string fileName = "first_milestone.txt"; // Replace with your file path
	parseEthConfig(fileName, eth);

	int NUM_IFG = eth.getMinNumOfIFGsPerPacket();
	int Max_Size_Packet = eth.getMaxPacketSize();
	const int Size_of_Header = 26;
	int Size_With_Min_IFGS = Size_of_Header + NUM_IFG;
	int Size_of_Payload = 46;
	int Size_of_Packet = Size_With_Min_IFGS + Size_of_Payload;
	int Remainder = Size_of_Packet % 4;
	switch (Remainder)
	{
	case 0:
		break;
	case 1:
		NUM_IFG = NUM_IFG + 3;
		break;
	case 2:
		NUM_IFG = NUM_IFG + 2;
		break;
	case 3:
		NUM_IFG = NUM_IFG + 1;
		break;

	default:
		break;
	}
	Size_With_Min_IFGS = Size_of_Header + NUM_IFG;
	Size_of_Packet = Size_With_Min_IFGS + Size_of_Payload;

	// Calculate the number of bursts and packets and duration of each burst and packet
	float Num_of_Bursts = Calculate_Number_of_Bursts(eth);
	float Num_of_Packets = Calculate_Number_of_Packets(eth);
	double Packet_Duration = Calculate_Packet_Duration(eth);
	double Burst_Duration = Calculate_Burst_Duration(eth);

	// Dynamically allocate the Burst array
	Ethernet_Packet* Burst = new Ethernet_Packet[eth.getBurstSize()];
	int counter = 0;
	int counter_2 = 0;
	int Counter;
	ofstream outfile("Milestone_1_output.txt");


	unsigned char* set_dest_temp;
	unsigned char* set_src_temp;
	unsigned char* print_temp;
	const unsigned char* const_print_temp;


	for (int i = 0; i < Num_of_Bursts; ++i) {
		for (int burst = 0; burst < eth.getBurstSize(); ++burst) {
			Burst = new Ethernet_Packet(NUM_IFG, Size_of_Payload);
			for (int j = 0; j < 6; ++j) {
				set_dest_temp = Burst->getDestAddress();
				set_src_temp = Burst->getSourceAddress();

				set_dest_temp[j] = eth.getDestAddress();
				set_src_temp[j] = eth.getSourceAddress();
			}
			Burst->calculateFCS();
			std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(Packet_Duration)));

			counter = counter_2;
			counter_2 = Burst->Burst_print(counter);


			Counter = counter;
			for (int j = 0; j < 7; j++) {
				if (Counter >= 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				const_print_temp = Burst->getPreamble();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_print_temp[j];
				Counter++;
			}
			if (Counter == 4)
			{
				outfile << dec << "\n";
				Counter = 0;
			}

			outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Burst->getSFD() << dec;
			Counter++;
			for (int j = 0; j < 6; ++j) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				print_temp = Burst->getDestAddress();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
				Counter++;
			}
			for (int j = 0; j < 6; ++j) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				print_temp = Burst->getSourceAddress();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
				Counter++;

			}

			for (int j = 0; j < 2; j++) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				const_print_temp = Burst->getEtherType();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_print_temp[j];
				Counter++;
			}

			for (int j = 0; j < Burst->getPayloadSize(); j++) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				print_temp = Burst->getPayload();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
				Counter++;

			}

			for (int j = 0; j < 4; j++) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				print_temp = Burst->getFCS();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
				Counter++;


			}

			for (int j = 0; j < Burst->getIFGSize(); j++) {
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
				print_temp = Burst->getIFG();
				outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
				Counter++;
				if (Counter == 4)
				{
					outfile << dec << "\n";
					Counter = 0;
				}
			}
			if (Counter == 4)
			{
				outfile << dec << "\n";
				Counter = 0;
			}

		}

		delete[] Burst;
		std::this_thread::sleep_for(std::chrono::microseconds(eth.getBurstPeriodicity_us()));

	}

	outfile.close();
	return 0;
}
