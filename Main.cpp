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
#include "ORAN_Packet.h"
#include "ORAN.h"
#include "ECPRI.h"

using namespace std;



void parseEthConfig(const string& fileName, Ethernet& eth, ORAN& ORAN_Obj) {
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
			else if (key == "Oran.SCS") {
				ORAN_Obj.setSCS(stoi(value));
			}
			else if (key == "Oran.MaxNrb") {
				ORAN_Obj.setMaxNrb(stoi(value));
			}
			else if (key == "Oran.NrbPerPacket") {
				ORAN_Obj.setNrbPerPacket(stoi(value));
			}
			else if (key == "Oran.PayloadType") {
				ORAN_Obj.setPayloadType(value);
			}
			else if (key == "Oran.Payload") {
				ORAN_Obj.setPayload(value);
			}
		}
	}
}

bool readNext24HexNumbers(const string& filename, int16_t numbers[24], int counter) {

	static ifstream file(filename);  // Keeps the file open between function calls
	static streampos lastPosition = 0;  // Keeps track of where we left off
	if (counter == 1)
	{
		lastPosition = 0;
		counter = 0;
	}
	// Ensure the file is open
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file." << std::endl;
		return false;
	}

	// Move to the last position where we stopped reading
	file.seekg(lastPosition);

	// Read 24 hexadecimal numbers from the file
	int count = 0;
	for (int i = 0; i < 24 && file >> std::hex >> numbers[i]; ++i) {
		++count;
	}

	// Save the position where we stopped reading
	lastPosition = file.tellg();

	// Return true if we read 24 numbers, false if less (end of file reached)
	return count == 24;
}
void emptyFile() {
	std::ofstream outfile("Milestone_2.txt");  // Open in default mode (which overwrites)
	outfile.close();  // Close immediately to empty the file
}
void Packet_printer(Ethernet_Packet Packet, int rb_size) {
	static int Counter = 0;
	const unsigned char* const_print_temp;
	unsigned char* print_temp;
	ofstream outfile("Milestone_2.txt",std::ios_base::app);
	static streampos lastPosition = 0;  // Keeps track of where we left off

	for (int j = 0; j < 7; j++) {
		if (Counter >= 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		const_print_temp = Packet.getPreamble();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_print_temp[j];
		Counter++;
	}
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}

	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getSFD() << dec;
	Counter++;
	for (int j = 0; j < 6; ++j) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		print_temp = Packet.getDestAddress();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
		Counter++;
	}
	for (int j = 0; j < 6; ++j) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		print_temp = Packet.getSourceAddress();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
		Counter++;

	}

	for (int j = 0; j < 2; j++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		const_print_temp = Packet.getEtherType();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)const_print_temp[j];
		Counter++;
	}


	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}

	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getVersion_Reserved_Concatenation();
	Counter++;

	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getMessage();
	Counter++;

	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getData_Dir_Version_filter();
	Counter++;

	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getFrame_id();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getSubframe();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getSlot_id();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getSymbol_id();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getSection_id();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}



	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getrb();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getSymInc();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getStartPrbu();
	Counter++;
	if (Counter == 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPayload().getNum_Prbu();
	Counter++;

	if (Counter >= 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	for (int rb = 0; rb < rb_size; rb++)
	{
		for (int l = 0; l < 24; l++) {
			if (Counter >= 4)
			{
				outfile << dec << "\n";
				Counter = 0;
			}
			else if ((Counter % 4 == 3))
			{
				if (Packet.getPayload().getPayload().getrb_arr()[rb][l] == (-145))
				{
					outfile << std::hex << std::setw(2) << std::setfill('0') << 0x6f;

					Counter += 2;
				}
				else
				{
					outfile << std::hex << std::setw(2) << std::setfill('0') << (int16_t)Packet.getPayload().getPayload().getrb_arr()[rb][l];
					Counter += 2;
				}
			}
			else
			{

				outfile << std::hex << std::setw(4) << std::setfill('0') << (int16_t)Packet.getPayload().getPayload().getrb_arr()[rb][l];
				Counter += 2;
			}
			if (Counter >= 4)
			{
				outfile << dec << "\n";
				Counter = 0;
			}
		}
	}
	if (Counter >= 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPC_RTC()[0];
	Counter++;
	if (Counter >= 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getPC_RTC()[1];

	Counter++;
	if (Counter >= 4)
	{
		outfile << dec << "\n";
		Counter = 0;
	}
	outfile << std::hex << std::setw(2) << std::setfill('0') << (int)Packet.getPayload().getSeqid();
	Counter++;

	for (int j = 0; j < 4; j++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		print_temp = Packet.getFCS();
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)print_temp[j];
		Counter++;


	}

	for (int j = 0; j < Packet.getIFGSize(); j++) {
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		print_temp = Packet.getIFG();
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
	return;
}
void End_Ifg_Printer(int End_IFGs)
{
	int Counter = 0;
	ofstream outfile("Milestone_2.txt", std::ios_base::app);
	for (int i = 0; i < End_IFGs; i++)
	{
		if (Counter == 4)
		{
			outfile << dec << "\n";
			Counter = 0;
		}
		outfile << std::hex << std::setw(2) << std::setfill('0') << (int)0xff;
		Counter++;
	}
	outfile.close();
	return;
}

double Calculate_Packet_Duration(Ethernet eth) {
	double Packet_Duration = (float)eth.getMaxPacketSize() * 8 * 1000 / (float)(eth.getLineRate() * (1024) * (1024) * (1024));
	return Packet_Duration;
}

int Calculate_Packet_Per_Symbol(ORAN ORAN_Object) {
	int Packet_Per_Symbol = ceil((float)ORAN_Object.getMaxNrb() / ORAN_Object.getNrbPerPacket());
	return Packet_Per_Symbol;
}








int main() {
	Ethernet eth;
	ORAN ORAN_Object;
	ECPRI ECPRI_Object;

	string fileName = "second_milstone.txt"; // Replace with your file path
	parseEthConfig(fileName, eth, ORAN_Object);

	string filename_IQ = ORAN_Object.getPayload();
	int16_t numbers[24];


	int NUM_IFG = eth.getMinNumOfIFGsPerPacket();
	int Max_Size_Packet = eth.getMaxPacketSize();
	const int Size_of_Header = 26;
	

	//Milestone 2
	float Packet_Per_Symbol = Calculate_Packet_Per_Symbol(ORAN_Object);
	int Normal_CP = 14;
	int Packets_Per_Slot = Normal_CP * Packet_Per_Symbol;
	int Slots_Per_Subframe = ORAN_Object.getSCS() / 15;
	int Packets_Per_Subframe = Slots_Per_Subframe * Packets_Per_Slot;
	int Packets_Per_Frame = Packets_Per_Subframe * 10;
	int Packets_Per_Second = Packets_Per_Frame * 100;
	int Number_Of_Packets = Packets_Per_Second * eth.getCaptureSizeMs() / 1000;
	int Number_Of_Bytes = Max_Size_Packet * Number_Of_Packets;
	double Packet_Duration = Calculate_Packet_Duration(eth);
	double Total_Packet_Duration = Packet_Duration * Number_Of_Packets;
	int Total_Packets = ceil((float)eth.getCaptureSizeMs() * Number_Of_Packets / Total_Packet_Duration);
	int Total_Bytes = Total_Packets * Max_Size_Packet;
	int END_IFGS = Total_Packets - Number_Of_Packets;
	int END_IFGS_Bytes = END_IFGS * Max_Size_Packet;


	


	unsigned char* set_dest_temp;
	unsigned char* set_src_temp;
	

	char frame_id = 0;
	char subframe_id = 0;
	char slot_id = 0;
	char symbol_id = 0;
	char rb = 0;
	char startPrbu = 0;
	char num_Prbu = ORAN_Object.getMaxNrb();
	char seq_id = 0;
	char rb_size = ORAN_Object.getNrbPerPacket();
	int valid = 0;
	int MaxIQ_Size = eth.getMaxPacketSize()-15;




	int Size_With_Min_IFGS = Size_of_Header + NUM_IFG;
	int rem = (Max_Size_Packet-15)%48;

	int Size_of_Payload = Max_Size_Packet-rem;
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
	emptyFile();
	for (int i = 0; i < Number_Of_Packets; ++i) {

		ORAN_Packet ORAN_Packet_Object(frame_id, subframe_id, slot_id, symbol_id, rb_size, rb, startPrbu, num_Prbu);
		for (int rb = 0; rb < rb_size; rb++)
		{
			if (MaxIQ_Size > 48)
			{
				if (readNext24HexNumbers(filename_IQ, numbers, valid)) {

					ORAN_Packet_Object.addIQsamples(numbers, rb);
				}
				else {
					valid = 1;
					readNext24HexNumbers(filename_IQ, numbers, valid);

					ORAN_Packet_Object.addIQsamples(numbers, rb);
					valid = 0;

				}
			}
			else
			{
				break;
			}
		}

		ECPRI ECPRI_Object(ORAN_Packet_Object, seq_id);
		Ethernet_Packet Packet(NUM_IFG, ECPRI_Object);
		for (int j = 0; j < 6; ++j) {
			set_dest_temp = Packet.getDestAddress();
			set_src_temp = Packet.getSourceAddress();

			set_dest_temp[j] = eth.getDestAddress();
			set_src_temp[j] = eth.getSourceAddress();
		}
		Packet.calculateFCS();


		Packet_printer(Packet, rb_size);
		if (symbol_id == 13)
		{
			symbol_id = 0;
			if (slot_id == (Slots_Per_Subframe - 1))
			{
				slot_id = 0;
				if (subframe_id == 9)
				{
					subframe_id = 0;
					if (frame_id == 255)
					{
						frame_id = 0;
					}
					else
					{
						frame_id++;
					}
				}
				else
				{
					subframe_id++;
				}
			}
			else
			{
				slot_id++;
			}
		}
		else
		{
			symbol_id++;
		}
		if (seq_id == 255)
		{
			seq_id = 0;
		}
		else
		{
			seq_id++;
		}
		startPrbu += num_Prbu;
	}

	End_Ifg_Printer(END_IFGS);

	return 0;
}
