#include "Bus.h"

Bus::Bus() {

}

Bus::~Bus() {

}

uint8_t Bus::read(uint16_t a) {
	return ram[a];
}

void Bus::write(uint16_t a, uint8_t d) {
	ram[a] = d;
}