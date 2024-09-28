#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


class ORAN_Packet
{
	const unsigned char Data_Dir_Version_filter = 0x00; 
	unsigned char frame_id; 
	unsigned char subframe_id;
    unsigned char slot_id;
	unsigned char symbol_id;
	unsigned char section_id;
	int16_t** rb_arr;
	unsigned char rb_size;
	unsigned char rb;
	unsigned char symInc;
	unsigned char startPrbu;
	unsigned char num_Prbu;
	

public:
	ORAN_Packet() : frame_id(0), subframe_id(0), slot_id(0), symbol_id(0), section_id(0), rb_arr(nullptr), rb(0), symInc(0), rb_size(0), startPrbu(0), num_Prbu(0)
	{
	}
	ORAN_Packet(unsigned char frame_id, unsigned char subframe_id, unsigned char slot_id, unsigned char symbol_id,unsigned char rb_size, unsigned char rb, unsigned char startPrbu, unsigned char num_Prbu);
	ORAN_Packet& operator=(const ORAN_Packet& other)
	{
		if (this != &other)
		{
			frame_id = other.frame_id;
			subframe_id = other.subframe_id;
			slot_id = other.slot_id;
			symbol_id = other.symbol_id;
			section_id = other.section_id;
			rb_arr = other.rb_arr;
			symInc = other.symInc;
			startPrbu = other.startPrbu;
			num_Prbu = other.num_Prbu;
			rb = other.rb;
		}
		return *this;
	}

	void setFrame_id(unsigned char frame_id);
	void setSubframe_id(unsigned char subframe);
	void setSlot_id(unsigned char slot_id);
	void setSymbol_id(unsigned char symbol_id);
	void setSection_id(unsigned char section_id);
	void setrb_arr(int16_t** rb_arr);
	void set_rbsize(unsigned char rb_size);
	void setrb(unsigned char rb);
	void setSymInc(unsigned char symInc);
	void setStartPrbu(unsigned char startPrbu);
	void setNum_Prbu(unsigned char num_Prbu);
	void addIQsamples(int16_t IQsamples[24],unsigned char rb);

	const unsigned char getData_Dir_Version_filter();
	unsigned char getFrame_id();
	unsigned char getSubframe();
	unsigned char getSlot_id();
	unsigned char getSymbol_id();
	unsigned char getSection_id();
	int16_t** getrb_arr();
	unsigned char get_rbsize();
	unsigned char getrb();
	unsigned char getSymInc();
	unsigned char getStartPrbu();
	unsigned char getNum_Prbu();



	//~ORAN_Packet();

	void print();


};

