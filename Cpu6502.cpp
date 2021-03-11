#include "Cpu6502.h"
#include "Bus.h"

Cpu6502::Cpu6502() {

	using c = Cpu6502;
	instructions =
	{
		{"BRK", &c::BRK, &c::IMP, 7}, {"ORA", &c::ORA, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"ORA", &c::ORA, &c::ZPG, 3}, {"ASL", &c::ASL, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"PHP", &c::PHP, &c::IMP, 3}, {"ORA", &c::ORA, &c::IMM, 2}, {"ASL", &c::ASL, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABS, 4}, {"ASL", &c::ASL, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BPL", &c::BPL, &c::REL, 2}, {"ORA", &c::ORA, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"ORA", &c::ORA, &c::ZPX, 4}, {"ASL", &c::ASL, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"CLC", &c::CLC, &c::IMP, 2}, {"ORA", &c::ORA, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"ORA", &c::ORA, &c::ABX, 4}, {"ASL", &c::ASL, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7},
		{"JSR", &c::JSR, &c::ABS, 6}, {"AND", &c::AND, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"BIT", &c::BIT, &c::ZPG, 3}, {"AND", &c::AND, &c::ZPG, 3}, {"ROL", &c::ROL, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"PLP", &c::PLP, &c::IMP, 4}, {"AND", &c::AND, &c::IMM, 2}, {"ROL", &c::ROL, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"BIT", &c::BIT, &c::ABS, 4}, {"AND", &c::AND, &c::ABS, 4}, {"ROL", &c::ROL, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BMI", &c::BMI, &c::REL, 2}, {"AND", &c::AND, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"AND", &c::AND, &c::ZPX, 4}, {"ROL", &c::ROL, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"SEC", &c::SEC, &c::IMP, 2}, {"AND", &c::AND, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"AND", &c::AND, &c::ABX, 4}, {"ROL", &c::ROL, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7},
		{"RTI", &c::RTI, &c::IMP, 6}, {"EOR", &c::EOR, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"EOR", &c::EOR, &c::ZPG, 3}, {"LSR", &c::LSR, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"PHA", &c::PHA, &c::IMP, 3}, {"EOR", &c::EOR, &c::IMM, 2}, {"LSR", &c::LSR, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"JMP", &c::JMP, &c::ABS, 3}, {"EOR", &c::EOR, &c::ABS, 4}, {"LSR", &c::LSR, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BVC", &c::BVC, &c::REL, 2}, {"EOR", &c::EOR, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"EOR", &c::EOR, &c::ZPX, 4}, {"LSR", &c::LSR, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"CLI", &c::CLI, &c::IMP, 2}, {"EOR", &c::EOR, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"EOR", &c::EOR, &c::ABX, 4}, {"LSR", &c::LSR, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7},
		{"RTS", &c::RTS, &c::IMP, 6}, {"ADC", &c::ADC, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"ADC", &c::ADC, &c::ZPG, 3}, {"ROR", &c::ROR, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"PLA", &c::PLA, &c::IMP, 4}, {"ADC", &c::ADC, &c::IMM, 2}, {"ROR", &c::ROR, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"JMP", &c::JMP, &c::IND, 5}, {"ADC", &c::ADC, &c::ABS, 4}, {"ROR", &c::ROR, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BVS", &c::BVS, &c::REL, 2}, {"ADC", &c::ADC, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"ADC", &c::ADC, &c::ZPX, 4}, {"ROR", &c::ROR, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"SEI", &c::SEI, &c::IMP, 2}, {"ADC", &c::ADC, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"ADC", &c::ADC, &c::ABX, 4}, {"ROR", &c::ROR, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7},
		{"???", &c::NOP, &c::IMP, 2}, {"STA", &c::STA, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"STY", &c::STY, &c::ZPG, 3}, {"STA", &c::STA, &c::ZPG, 3}, {"STX", &c::STX, &c::ZPG, 3}, {"???", &c::XXX, &c::IMP, 3}, {"DEY", &c::DEY, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"TXA", &c::TXA, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"STY", &c::STY, &c::ABS, 4}, {"STA", &c::STA, &c::ABS, 4}, {"STX", &c::STX, &c::ABS, 4}, {"???", &c::XXX, &c::IMP, 4},
		{"BCC", &c::BCC, &c::REL, 2}, {"STA", &c::STA, &c::INY, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"STY", &c::STY, &c::ZPX, 4}, {"STA", &c::STA, &c::ZPX, 4}, {"STX", &c::STX, &c::ZPY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"TYA", &c::TYA, &c::IMP, 2}, {"STA", &c::STA, &c::ABY, 5}, {"TXS", &c::TXS, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"STA", &c::STA, &c::ABX, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5},
		{"LDY", &c::LDY, &c::IMM, 2}, {"LDA", &c::LDA, &c::INX, 6}, {"LDX", &c::LDX, &c::IMM, 2}, {"???", &c::XXX, &c::IMP, 2}, {"LDY", &c::LDY, &c::ZPG, 3}, {"LDA", &c::LDA, &c::ZPG, 3}, {"LDX", &c::LDX, &c::ZPG, 3}, {"???", &c::XXX, &c::IMP, 3}, {"TAY", &c::TAY, &c::IMP, 2}, {"LDA", &c::LDA, &c::IMM, 2}, {"TAX", &c::TAX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"LDY", &c::LDY, &c::ABS, 4}, {"LDA", &c::LDA, &c::ABS, 4}, {"LDX", &c::LDX, &c::ABS, 4}, {"???", &c::XXX, &c::IMP, 4},
		{"BCS", &c::BCS, &c::REL, 2}, {"STA", &c::STA, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"LDY", &c::LDY, &c::ZPX, 4}, {"LDA", &c::LDA, &c::ZPX, 4}, {"LDX", &c::LDX, &c::ZPY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"CLV", &c::CLV, &c::IMP, 2}, {"LDA", &c::LDA, &c::ABY, 4}, {"TSX", &c::TSX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"LDY", &c::LDY, &c::ABX, 4}, {"LDA", &c::LDA, &c::ABX, 4}, {"LDX", &c::LDX, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4},
		{"CPY", &c::CPY, &c::IMM, 2}, {"CMP", &c::CMP, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"CPY", &c::CPY, &c::ZPG, 3}, {"CMP", &c::CMP, &c::ZPG, 3}, {"DEC", &c::DEC, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"INY", &c::INY, &c::IMP, 2}, {"CMP", &c::CMP, &c::IMM, 2}, {"DEX", &c::DEX, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"CPY", &c::CPY, &c::ABS, 4}, {"CMP", &c::CMP, &c::ABS, 4}, {"DEC", &c::DEC, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BNE", &c::BNE, &c::REL, 2}, {"CMP", &c::CMP, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"CMP", &c::CMP, &c::ZPX, 4}, {"DEC", &c::DEC, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"CLD", &c::CLD, &c::IMP, 2}, {"CMP", &c::CMP, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"CMP", &c::CMP, &c::ABX, 4}, {"DEC", &c::DEC, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7},
		{"CPX", &c::CPX, &c::IMM, 2}, {"SBC", &c::SBC, &c::INX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"???", &c::XXX, &c::IMP, 6}, {"CPX", &c::CPX, &c::ZPG, 3}, {"SBC", &c::SBC, &c::ZPG, 3}, {"INC", &c::INC, &c::ZPG, 5}, {"???", &c::XXX, &c::IMP, 5}, {"XIN", &c::XIN, &c::IMP, 2}, {"SBC", &c::SBC, &c::IMM, 2}, {"NOP", &c::NOP, &c::IMP, 2}, {"???", &c::XXX, &c::IMP, 2}, {"CPX", &c::CPX, &c::ABS, 4}, {"SBC", &c::SBC, &c::ABS, 4}, {"INC", &c::INC, &c::ABS, 6}, {"???", &c::XXX, &c::IMP, 6},
		{"BEQ", &c::BEQ, &c::REL, 2}, {"SBC", &c::SBC, &c::INY, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"???", &c::XXX, &c::IMP, 5}, {"SBC", &c::SBC, &c::ZPX, 4}, {"INC", &c::INC, &c::ZPX, 6}, {"???", &c::XXX, &c::IMP, 6}, {"SED", &c::SED, &c::IMP, 2}, {"SBC", &c::SBC, &c::ABY, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"???", &c::XXX, &c::IMP, 4}, {"SBC", &c::SBC, &c::ABX, 4}, {"INC", &c::INC, &c::ABX, 7}, {"???", &c::XXX, &c::IMP, 7}
	};

}

Cpu6502::~Cpu6502() {
}

uint8_t Cpu6502::read(uint16_t a) {
	return bus->read(a);
}

void Cpu6502::write(uint16_t a, uint8_t d) {
	bus->write(a, d);
}

uint8_t Cpu6502::getFlag(flags f) {
	return ((status & f) > 0) ? 1 : 0;
}

void Cpu6502::setFlag(flags f, bool v) {
	
	if (v) {
		status |= f;
	}
	else {
		status &= f;
	}
}

void Cpu6502::clock() {

	if (cycles == 0) {

		opcode = read(PC);
		PC++;

		cycles = instructions[opcode].cycles;

		uint8_t extraCycles1 = (this->*instructions[opcode].addrmode)();
		uint8_t extraCycles2 = (this->*instructions[opcode].operate)();

		cycles = cycles + extraCycles1 + extraCycles2;

	}

	cycles--;
}

uint8_t Cpu6502::grab() {

	if (!(instructions[opcode].addrmode == &Cpu6502::IMP)) {
		grabbed = read(absAddr);
	}

	return grabbed;
}

//Addressing Modes

uint8_t Cpu6502::ABS() {

	uint16_t lo = read(PC);
	PC++;

	uint16_t hi = read(PC);
	PC++;

	absAddr = (hi << 8) | lo;

	return 0;
}

uint8_t Cpu6502::ABX() {

	uint16_t lo = read(PC);
	PC++;

	uint16_t hi = read(PC);
	PC++;

	absAddr = (hi << 8) | lo;
	absAddr = absAddr + X;

	//Add page boundary condition to determine extra clock cycle;

	return 0;
}

uint8_t Cpu6502::ABY() {

	uint16_t lo = read(PC);
	PC++;

	uint16_t hi = read(PC);
	PC++;

	absAddr = (hi << 8) | lo;
	absAddr = absAddr + Y;

	//Add page boundary condition to determine extra clock cycle;

	return 0;
}

uint8_t Cpu6502::IMM() {

	absAddr = PC++;
	return 0;
}

uint8_t Cpu6502::IMP() {

	grabbed = acc;
	return 0;
}

uint8_t Cpu6502::IND() {

	uint16_t lo = read(PC);
	PC++;

	uint16_t hi = read(PC);
	PC++;

	uint16_t ptr = (hi << 8) | lo;

	absAddr = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

uint8_t Cpu6502::XIN() {

	uint16_t tmp = read(PC);
	PC++;

	uint16_t lo = read((uint16_t)(tmp + (uint16_t)X) & 0x00FF);
	uint16_t hi = read((uint16_t)(tmp + (uint16_t)X + 1) & 0x00FF);

	absAddr = (hi << 8) | lo;

	return 0;
}

uint8_t Cpu6502::YIN() {

	uint16_t tmp = read(PC);
	PC++;

	uint16_t lo = read((uint16_t)(tmp + (uint16_t)Y) & 0x00FF);
	uint16_t hi = read((uint16_t)(tmp + (uint16_t)Y + 1) & 0x00FF);

	absAddr = (hi << 8) | lo;

	return 0;
}

uint8_t Cpu6502::REL() {

	relAddr = read(PC);
	PC++;

	if (relAddr & 0x80) {
		relAddr |= 0xFF00;
	}

	return 0;
}

uint8_t Cpu6502::ZPG() {

	absAddr = read(PC);
	PC++;
	absAddr &= 0x00FF;

	return 0;
}

uint8_t Cpu6502::ZPX() {

	absAddr = read(PC + X);
	PC++;

	absAddr &= 0x00FF;

	return 0;
}

uint8_t Cpu6502::ZPY() {

	absAddr = read(PC + Y);
	PC++;

	absAddr &= 0x00FF;

	return 0;
}

//Opcodes
/*
On all opcodes NEED to look into returns, determine extra clock cycles etc. V. important to understand
Unsure on flag status when transferring from accumulator for example -> TAX transfers from A to X but how does that affect
status flags - does A register get cleared? swapped?

Can change a decent amount of Z flag statuses to tmp == 0x00, using same as ADC which is clumsy and only used for 16 bit words

Forgot how bitshift worked have done most bitshift ops wrong.
*/

uint8_t Cpu6502::ADC() {

	grab();
	uint16_t tmp = (uint16_t)acc + (uint16_t)grabbed + (uint16_t)getFlag(C);

	setFlag(N, tmp & 0x80); //Set the negative flag if most significant bit set
	setFlag(Z, (tmp & 0x00FF) == 0); //Set the zero flag if first 8 bits are zero
	setFlag(C, tmp > 255); //Set the carry flag conditional on whether the sum is greater than 255
	setFlag(V, (((uint16_t)acc ^ tmp) & ~((uint16_t)acc ^ (uint16_t)grabbed)) & 0x0080); //Overflow flag set given as V = (A^R)&~(A^M)

	acc = tmp & 0x00FF;

	return 1;
}

uint8_t Cpu6502::AND() {

	grab();

	acc = acc & grabbed;
	setFlag(N, acc & 0x80); //Set the negative flag if most significant bit set
	setFlag(Z, acc == 0x00);

	return 1; //UNSURE ON CLOCK CYCLE HERE
}

uint8_t Cpu6502::ASL() {

	//Implemented here for accumulator, unsure how to differentiate between ASL A and ASL oper
	setFlag(C, acc & 0x80);
	acc << 1;

	setFlag(N, acc & 0x80);
	setFlag(Z, acc == 0x00);

	return 0;
}

uint8_t Cpu6502::BCC() {

	if (getFlag(C) == 0) {
		cycles++; //Requires an extra cycle if the branch is on the same page
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) { //AND with 0x00FF and 0xFF00 gives easy comparison for whether page boundary is crossed
			cycles++; //Requires two extra cycles if the branch is taken to different page
		}
		PC = absAddr; //Update program counter to new address
	}

	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BCS() {

	if (getFlag(C) == 1) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BEQ() {

	if (getFlag(Z) == 1) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

uint8_t Cpu6502::BIT() {
	
	grab();

	setFlag(N, grabbed & 0x40);
	setFlag(Z, grabbed & acc);
	setFlag(V, grabbed & 0x20);

	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BMI() {

	if (getFlag(N) == 1) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}
//See BCC for code description
uint8_t Cpu6502::BNE() {

	if (getFlag(Z) == 0) { 
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BPL() {

	if (getFlag(N) == 0) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

uint8_t Cpu6502::BRK() {

	setFlag(I, true);

	PC += 2;
	write(0x0100 + SP, PC);
	write(0x0100 + SP--, status);
	SP--;
	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BVC() {

	if (getFlag(V) == 0) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

//See BCC for code description
uint8_t Cpu6502::BVS() {

	if (getFlag(V) == 1) {
		cycles++;
		absAddr = PC + relAddr;

		if ((absAddr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;
		}
		PC = absAddr;
	}

	return 0;
}

uint8_t Cpu6502::CLC() {

	setFlag(C, false);
	return 0;
}

uint8_t Cpu6502::CLD() {

	setFlag(D, false);
	return 0;
}

uint8_t Cpu6502::CLI() {

	setFlag(I, false);
	return 0;
}

uint8_t Cpu6502::CLV() {

	setFlag(V, false);
	return 0;
}

uint8_t Cpu6502::CMP() {

	grab();
	uint16_t sub = ((uint16_t)grabbed) ^ 0x00FF;
	uint16_t tmp = (uint16_t)acc + (uint16_t)sub; //CHECK THIS ACTUALLY NEGATES, PROBABLY NEEDS AND WITH 0x00FF

	if (tmp & 0x80) {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, false);
	}
	else if (tmp & 0x00FF) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	}
	else {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, true);
	}

	return 1; //V. Unsure on this return value
}

uint8_t Cpu6502::CPX() {

	grab();
	uint16_t sub = ((uint16_t)grabbed) ^ 0x00FF;
	uint16_t tmp = (uint16_t)X + (uint16_t)sub; //CHECK THIS ACTUALLY NEGATES, PROBABLY NEEDS AND WITH 0x00FF

	if (tmp & 0x80) {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, false);
	}
	else if (tmp & 0x00FF) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	}
	else {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, true);
	}

	return 1; //V. Unsure on this return value
}

uint8_t Cpu6502::CPY() {

	grab();
	uint16_t sub = ((uint16_t)grabbed) ^ 0x00FF;
	uint16_t tmp = (uint16_t)Y + (uint16_t)sub; //CHECK THIS ACTUALLY NEGATES, PROBABLY NEEDS AND WITH 0x00FF

	if (tmp & 0x80) {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, false);
	}
	else if (tmp & 0x00FF) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	}
	else {
		setFlag(N, tmp & 0x40);
		setFlag(Z, false);
		setFlag(C, true);
	}

	return 1; //V. Unsure on this return value
}

uint8_t Cpu6502::DEC() {

	uint8_t tmp = read(absAddr) - 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	write(absAddr, tmp);
	return 0;
}

uint8_t Cpu6502::DEX() {

	uint8_t tmp = X - 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	X = tmp;
	return 0;
}

uint8_t Cpu6502::DEY() {

	uint8_t tmp = Y - 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	X = tmp;
	return 0;
}

uint8_t Cpu6502::EOR() {

	grab();

	acc = acc ^ grabbed;
	setFlag(N, acc & 0x80); //Set the negative flag if most significant bit set
	setFlag(Z, (acc & 0xFF) == 0); //Set the zero flag if first 8 bits are zero

	return 1; //UNSURE ON CLOCK CYCLE HERE
}

uint8_t Cpu6502::INC() {

	uint8_t tmp = read(absAddr) + 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	write(absAddr, tmp);
	return 0;
}

uint8_t Cpu6502::INX() {

	uint8_t tmp = X + 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	X = tmp;
	return 0;
}

uint8_t Cpu6502::INY() {

	uint8_t tmp = Y + 1;

	setFlag(N, tmp & 0x80);
	setFlag(Z, (tmp & 0x00FF) == 0);

	X = tmp;
	return 0;
}

uint8_t Cpu6502::JMP() {

	PC = absAddr;
	return 0;
}

uint8_t Cpu6502::JSR() {

	PC--;

	write(0x0100 + SP, (PC >> 8) & 0x00FF);
	SP--;
	write(0x0100 + SP, PC & 0x00FF);
	SP--;

	PC = absAddr;
	return 0;
}

uint8_t Cpu6502::LDA() {

	acc = read(absAddr);

	setFlag(N, acc & 0x80);
	setFlag(Z, (acc & 0x00FF) == 0);

	return 1; //Again, unsure of return value
}

uint8_t Cpu6502::LDX() {

	X = read(absAddr);

	setFlag(N, X & 0x80);
	setFlag(Z, (X & 0x00FF) == 0);

	return 1; //Again, unsure of return value
}

uint8_t Cpu6502::LDY() {

	Y = read(absAddr);

	setFlag(N, Y & 0x80);
	setFlag(Z, (Y & 0x00FF) == 0);

	return 1; //Again, unsure of return value
}

uint8_t Cpu6502::LSR() {

	//Implemented here for accumulator, unsure how to differentiate between ASL A and ASL oper
	//Need to make sure that this shift right is working and makes sense.
	setFlag(C, acc & 0x01);
	acc >> 1;

	setFlag(N, acc & 0x80);
	setFlag(Z, acc == 0x00);

	return 0;
}

uint8_t Cpu6502::NOP() {

	return 0;
}

uint8_t Cpu6502::ORA() {

	grab();

	acc = acc | grabbed;
	setFlag(N, acc & 0x80); //Set the negative flag if most significant bit set
	setFlag(Z, acc & 0xFF); //Set the zero flag if first 8 bits are zero

	return 1; //UNSURE ON CLOCK CYCLE HERE
}

uint8_t Cpu6502::PHA() {

	write(0x0100 + SP, acc);
	SP--;
	return 0;
}

uint8_t Cpu6502::PHP() {

	write(0x0100 + SP, status);
	SP--;
	return 0;
}

uint8_t Cpu6502::PLA() {

	SP++;
	acc = read(0x0100 + SP);

	setFlag(N, acc & 0x80);
	setFlag(Z, (acc & 0x00FF) == 0);

	return 0;
}

//Could be a better way to set flags here
uint8_t Cpu6502::PLP() {

	SP++;
	status = read(0x0100 + SP);

	setFlag(N, status & 0x01);
	setFlag(V, status & 0x02);
	setFlag(U, status & 0x04);
	setFlag(B, status & 0x08);
	setFlag(D, status & 0x10);
	setFlag(I, status & 0x20);
	setFlag(Z, status & 0x40);
	setFlag(C, status & 0x80);

	return 0;
}

//There is a better way to perform the rotations here but this works and isn't a big efficiency killer
//Also having said this works needs checking.
uint8_t Cpu6502::ROL() {

	//Again, implemented for acc not mem, needs redoing
	uint8_t tmp = acc; //Can generalize to mem easier later

	setFlag(C, tmp & 0x80);
	tmp << 1;
	acc = tmp & (uint8_t)getFlag(C);

	return 0;
}

//Doubly needs checking line 719
uint8_t Cpu6502::ROR() {

	//Again, implemented for acc not mem, needs redoing
	uint8_t tmp = acc; //Can generalize to mem easier later

	setFlag(C, tmp & 0x80);
	tmp >> 1;
	acc = tmp & ((uint8_t)getFlag(C) << 7);

	return 0;
}

uint8_t Cpu6502::RTI() {

	SP++;
	status = read(0x0100 + SP);

	SP++;
	PC = (uint16_t)read(0x0100 + SP);
	SP++;
	PC |= (uint16_t)read(0x0100 + SP) << 8; //As program counter is a 16 bit word, need to read twice to obtain all information

	return 0;
}

uint8_t Cpu6502::RTS() {

	SP++;
	PC = (uint16_t)read(0x0100 + SP);
	SP++;
	PC |= (uint16_t)read(0x0100 + SP) << 8;
	PC++;

	return 0;
}

uint8_t Cpu6502::SBC() {

	grab();
	uint16_t subtrahend = ((uint16_t)grabbed) ^ 0x00FF; //XOR with 0x00FF gives inverse for last 8 bits (Only bits that could be set as grabbed is uint8_t)
	uint16_t tmp = (uint16_t)acc + (uint16_t)subtrahend + (uint16_t)getFlag(C); //Adding subtrahend provides subtraction

	setFlag(N, tmp & 0x80); //Set the negative flag if most significant bit set
	setFlag(Z, (tmp & 0x00FF) == 0); //Set the zero flag if first 8 bits are zero
	setFlag(C, tmp & 0xFF00); //Set the carry flag if result is of type uint16_t
	setFlag(V, ((subtrahend ^ tmp) & ((uint16_t)acc ^ tmp)) & 0x0080); //Overflow flag set given as (R^M)

	acc = tmp & 0x00FF;

	return 1; //UNSURE ON RETURN HERE
}

uint8_t Cpu6502::SEC() {

	setFlag(C, true);
	return 0;
}

uint8_t Cpu6502::SED() {

	setFlag(D, true);
	return 0;
}

uint8_t Cpu6502::SEI() {

	setFlag(I, true);
	return 0;
}

uint8_t Cpu6502::STA() {

	write(acc, absAddr);
	return 0;
}

uint8_t Cpu6502::STX() {

	write(X, absAddr);
	return 0;
}

uint8_t Cpu6502::STY() {

	write(Y, absAddr);
	return 0;
}

uint8_t Cpu6502::TAX() {

	X = acc;

	setFlag(N, X & 0x80);
	setFlag(Z, X == 0x00);

	return 0;
}

uint8_t Cpu6502::TAY() {

	Y = acc;

	setFlag(N, Y & 0x80);
	setFlag(Z, Y == 0x00);

	return 0;
}

uint8_t Cpu6502::TSX() {

	X = SP;

	setFlag(N, X & 0x80);
	setFlag(Z, X == 0x00);

	return 0;
}

uint8_t Cpu6502::TXA() {

	acc = X;

	setFlag(N, acc & 0x80);
	setFlag(Z, acc == 0x00);

	return 0;
}

uint8_t Cpu6502::TXS() {

	SP = X;
	return 0;
}

uint8_t Cpu6502::TYA() {

	acc = Y;

	setFlag(N, Y & 0x80);
	setFlag(Z, Y == 0x00);

	return 0;
}

//
uint8_t Cpu6502::XXX() {

	return 0;
}

void Cpu6502::reset() {
	
	absAddr = 0xFFFC;
	uint16_t PCL = read(absAddr);
	uint16_t PCH = read(absAddr + 1);

	PC = (PCH << 8) | PCL;

	acc = 0;
	X = 0;
	Y = 0;
	SP = 0xFD;
	status = 0x00;

	absAddr = 0x00;
	relAddr = 0x00;
	grabbed = 0x00;

	cycles = 8;
};

void Cpu6502::irq() {

	if (getFlag(I) == 0) {
		write(0x0100 + SP, (PC >> 8) & 0x00FF);
		SP--;
		write(0x0100 + SP, PC & 0x00FF);
		SP--;

		setFlag(I, true);
		write(0x0100 + SP, status);
		SP--;

		absAddr = 0xFFFE;
		uint16_t PCL = read(absAddr);
		uint16_t PCH = read(absAddr + 1);
		PC = (PCH << 8) | PCL;

		cycles = 7;
	}
};

void Cpu6502::nmi() {
	
	write(0x0100 + SP, (PC >> 8) & 0x00FF);
	SP--;
	write(0x0100 + SP, PC & 0x00FF);
	SP--;

	setFlag(I, true);
	write(0x0100 + SP, status);
	SP--;

	absAddr = 0xFFFA;
	uint16_t PCL = read(absAddr);
	uint16_t PCH = read(absAddr + 1);
	PC = (PCH << 8) | PCL;

	cycles = 8;
};