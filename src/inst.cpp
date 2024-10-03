#include "cpu.hpp"
#include "inst.hpp"

/* LDA Functions */
void Inst::LDASetStatus(CPU& cpu) {
    cpu.PS = CPU::setR((cpu.A == 0), cpu.PS, cpu.PS_Z);   // check if A == 0
    cpu.PS = CPU::setR((cpu.A & (1 << 6)), cpu.PS, cpu.PS_N);  // check if A is negetive
}

// consume 2 cycles
void Inst::LDA_IM(CPU& cpu, u32& Cycles) {
    cpu.A = cpu.FetchByte(Cycles);
    LDASetStatus(cpu);
}

// consume 3 cycles
void Inst::LDA_ZP(CPU& cpu, u32& Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    cpu.A = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDASetStatus(cpu);
}

// consume 4 cycles
void Inst::LDA_ZP_X(CPU& cpu, u32& Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.X, Cycles, 1);
    cpu.A = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::LDA_ABS(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    cpu.A = cpu.ReadAddr(TargetAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::LDA_ABS_X(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    TargetAddr = cpu.addM(TargetAddr, cpu.X, Cycles, 0);
    cpu.A = cpu.ReadAddr(TargetAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::LDA_ABS_Y(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    TargetAddr = cpu.addM(TargetAddr, cpu.Y, Cycles, 0);
    cpu.A = cpu.ReadAddr(TargetAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::LDA_IND_X(CPU& cpu, u32&Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.X, Cycles, 1);
    Word IndAddr = ((Word)cpu.ReadAddr(ZeroPageAddr, Cycles) << 8) |
                    ((Word)cpu.ReadAddr(ZeroPageAddr + 1, Cycles));
    cpu.A = cpu.ReadAddr(IndAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::LDA_IND_Y(CPU& cpu, u32&Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.Y, Cycles, 1);
    Word IndAddr = ((Word)cpu.ReadAddr(ZeroPageAddr, Cycles) << 8) |
                    ((Word)cpu.ReadAddr(ZeroPageAddr + 1, Cycles));
    cpu.A = cpu.ReadAddr(IndAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::JSR_ABS(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    cpu.Push(CPU::getL(cpu.PC), Cycles);
    cpu.Push(CPU::getH(cpu.PC), Cycles);
    cpu.PC = TargetAddr;
    Cycles --;
}

void Inst::RTS(CPU& cpu, u32& Cycles) {
    Word RetAddr = cpu.Pop(Cycles) << 8;
    RetAddr |= cpu.Pop(Cycles);
    cpu.PC = RetAddr;
    Cycles -= 3;
}

void Inst::JMP_ABS(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    cpu.PC = TargetAddr;
}

void Inst::JMP_IND(CPU& cpu, u32& Cycles) {
    Word IndAddr = cpu.FetchWord(Cycles);
    Word TargetAddr = ((Word)cpu.ReadAddr(IndAddr, Cycles) << 8 | 
                        (Word)cpu.ReadAddr(IndAddr + 1, Cycles));
    cpu.PC = TargetAddr;
}