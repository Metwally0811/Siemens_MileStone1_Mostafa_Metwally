#include "ORAN_Packet.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;




ORAN_Packet::ORAN_Packet(unsigned char frame_id, unsigned char subframe_id, unsigned char slot_id, unsigned char symbol_id, unsigned char rb_size, unsigned char rb, unsigned char startPrbu, unsigned char num_Prbu)
{
	this->frame_id = frame_id;
	this->subframe_id = subframe_id;
	this->slot_id = slot_id;
	this->symbol_id = symbol_id;
	this->rb_size = rb_size;
	this->startPrbu = startPrbu;
	this->num_Prbu = num_Prbu;
	this->rb_arr = new int16_t * [rb_size];
	for (int i = 0; i < rb_size; i++)
	{
		rb_arr[i] = new int16_t[24];
	}
	this->rb = rb;
	this->symInc = 0;
	this->section_id = 0;
}

void ORAN_Packet::setFrame_id(unsigned char frame_id)
{
	this->frame_id = frame_id;
}
void ORAN_Packet::setSubframe_id(unsigned char subframe_id)
{
	this->subframe_id = subframe_id;
}
void ORAN_Packet::setSlot_id(unsigned char slot_id)
{
	this->slot_id = slot_id;
}
void ORAN_Packet::setSymbol_id(unsigned char symbol_id)
{
	this->symbol_id = symbol_id;
}
void ORAN_Packet::setSection_id(unsigned char section_id)
{
	this->section_id = section_id;
}
void ORAN_Packet::setrb_arr(int16_t** rb_arr)
{
	this->rb_arr = rb_arr;
}
void ORAN_Packet::set_rbsize(unsigned char rb_size)
{
	this->rb_size = rb_size;
}
void ORAN_Packet::setrb(unsigned char rb)
{
	this->rb = rb;
}
void ORAN_Packet::setSymInc(unsigned char symInc)
{
	this->symInc = symInc;
}
void ORAN_Packet::setStartPrbu(unsigned char startPrbu)
{
	this->startPrbu = startPrbu;
}
void ORAN_Packet::setNum_Prbu(unsigned char num_Prbu)
{
	this->num_Prbu = num_Prbu;
}

void ORAN_Packet::addIQsamples(int16_t IQsamples[24],unsigned char rb)
{
	rb_arr[rb] = IQsamples;
}

const unsigned char ORAN_Packet::getData_Dir_Version_filter()
{
	return Data_Dir_Version_filter;
}

unsigned char ORAN_Packet::getFrame_id()
{
	return frame_id;
}
unsigned char ORAN_Packet::getSubframe()
{
	return subframe_id;
}
unsigned char ORAN_Packet::getSlot_id()
{
	return slot_id;
}
unsigned char ORAN_Packet::getSymbol_id()
{
	return symbol_id;
}
unsigned char ORAN_Packet::getSection_id()
{
	return section_id;
}
int16_t** ORAN_Packet::getrb_arr()
{
	return rb_arr;
}
unsigned char ORAN_Packet::get_rbsize()
{
	return rb_size;
}
unsigned char ORAN_Packet::getrb()
{
	return rb;
}
unsigned char ORAN_Packet::getSymInc()
{
	return symInc;
}
unsigned char ORAN_Packet::getStartPrbu()
{
	return startPrbu;
}
unsigned char ORAN_Packet::getNum_Prbu()
{
	return num_Prbu;
}



void ORAN_Packet::print()
{
	cout << "Data_Dir_Version_filter: " << (int)Data_Dir_Version_filter << endl;
	cout << "frame_id: " << (int)frame_id << endl;
	cout << "subframe_id: " << (int)subframe_id << endl;
	cout << "slot_id: " << (int)slot_id << endl;
	cout << "symbol_id: " << (int)symbol_id << endl;
	//cout << "rb: " << (int)rb_arr << endl;
	cout << "symInc: " << (int)symInc << endl;
	cout << "section_id: " << (int)section_id << endl;
	cout << "startPrbu: " << (int)startPrbu << endl;
	cout << "num_Prbu: " << (int)num_Prbu << endl;
}

//
//ORAN_Packet::~ORAN_Packet()
//{
//	for (int i = 0; i < rb_size; i++)
//	{
//		delete[] rb_arr[i];
//	}
//	delete[] rb_arr;
//}
