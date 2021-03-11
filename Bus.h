#pragma once
#include <cstdint>
#include "Cpu6502.h"
#include <array>

class Bus
{
public:

	//Constructor/Destructor
	Bus();
	~Bus();

	//Units connected to Bus
	Cpu6502 cpu;

	//Fake ram for example purposes
	std::array<uint8_t, 64 * 1024> ram;

	//Read and write to ram
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);

};