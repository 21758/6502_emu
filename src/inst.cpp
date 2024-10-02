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
    Byte ZeroPageAddr = cpu.FetchByte(Cycles);
    cpu.A = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDASetStatus(cpu);
}

// consume 4 cycles
void Inst::LDA_ZP_X(CPU& cpu, u32& Cycles) {
    Byte ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.X, Cycles);
    cpu.A = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDASetStatus(cpu);
}

void Inst::JSR_ABS(CPU& cpu, u32& Cycles) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    cpu.Push(cpu.mem[cpu.PC ++], Cycles);
    cpu.Push(cpu.mem[cpu.PC ++], Cycles);
    cpu.SetPC(TargetAddr, Cycles);
}