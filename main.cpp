#include <iostream>
#include "Cpu6502.h"
#include "Bus.h"

int main()
{
	
	Bus* bus = new Bus;
	Cpu6502 Cpu;

	//Very simple program to add 2 and 3 together.
	bus->write(0x40, 0xA9); //Into 0x40 load instruction 0xA0 (In this case, Load A using immidiate addressing)
	bus->write(0x41, 0b10); //Into 0x41 load the binary value 10
	bus->write(0x42, 0x69); //Into 0x42 load instruction 0x69 (In this case, ADC using immidiate addressing)
	bus->write(0x43, 0b11); //Into 0x43 load the binary value 11

	Cpu.Connect(bus);
	Cpu.PC = 0x40; //Set the program counter to 0x40

	bool RUNNING = true;
	while (RUNNING) {
		Cpu.clock();

		//Debug to show result
		int result = (int)Cpu.acc;
		std::cout << result << std::endl;
		if (result == 5) {
			RUNNING = false;
		}
	}

	delete bus;
	return 0;
}