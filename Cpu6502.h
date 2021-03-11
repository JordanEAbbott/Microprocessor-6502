#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Bus;

class Cpu6502
{
public:

	//Constructors/Destructors
	Cpu6502();
	~Cpu6502();

	//Connect Cpu to a bus
	void Connect(Bus* b) { bus = b; };

	//Initialise flags
	enum flags
	{
		N = (1 << 0),	//Negative
		V = (1 << 1),	//Overflow
		U = (1 << 2),	//Unused
		B = (1 << 3),	//Break, currently unused
		D = (1 << 4),	//Decimal (use BCD for arithmetics)
		I = (1 << 5),	//Interrupt (IRQ disable)
		Z = (1 << 6),	//Zero
		C = (1 << 7)	//Carry
	};

	//Registers

	uint8_t acc = 0x00;		//Accumulator register
	uint8_t X = 0x00;		//X register
	uint8_t Y = 0x00;		//Y register
	uint8_t status = 0x00;	//Status register
	uint8_t SP = 0x00;		//Stack pointer
	uint16_t PC = 0x0000;	//Program counter

	//Addressing Modes

	uint8_t ABS(); uint8_t ABX();
	uint8_t ABY(); uint8_t IMM();
	uint8_t IMP(); uint8_t IND();
	uint8_t XIN(); uint8_t YIN();
	uint8_t REL(); uint8_t ZPG();
	uint8_t ZPX(); uint8_t ZPY();

	//Opcodes
	
	uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC();
	uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI();
	uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC();
	uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); uint8_t CLI();
	uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY();
	uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR();
	uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
	uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY();
	uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA();
	uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL();
	uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC();
	uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA();
	uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY();
	uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();

	uint8_t XXX();

	void clock();
	void reset();
	void irq();
	void nmi();

	uint8_t grab();
	uint8_t grabbed = 0x00;

	uint16_t absAddr = 0x0000;
	uint16_t relAddr = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t cycles = 0;

private:

	//Initialise Bus
	Bus* bus = nullptr;

	//Send read/write requests to bus
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);

	//Status register access
	uint8_t getFlag(flags f);
	void setFlag(flags f, bool v);

	struct INSTRUCTION
	{
		std::string name;
		uint8_t(Cpu6502::* operate)(void) = nullptr;
		uint8_t(Cpu6502::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};

	std::vector<INSTRUCTION> instructions;
};

