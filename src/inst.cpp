#include "cpu.hpp"
#include "inst.hpp"

void Inst::LDA_IM(CPU& cpu, u32& Cycles) {
    cpu.A = cpu.FetchByte(Cycles);
    cpu.PS = CPU::setR((cpu.A == 0), cpu.PS, cpu.PS_Z);   // check if A == 0
    cpu.PS = CPU::setR((cpu.A & (1 << 6)), cpu.PS, cpu.PS_N);  // check if A is negetive
}