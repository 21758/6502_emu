#include "cpu.hpp"
#include "inst.hpp"

/* LD Functions */
void Inst::LDSetStatus(CPU& cpu, Byte& R) {
    cpu.PS = CPU::setR((R == 0), cpu.PS, cpu.PS_Z);   // check if R == 0
    cpu.PS = CPU::setR((R & (1 << 7)), cpu.PS, cpu.PS_N);  // check if R is negetive
}

void Inst::LD_IM(CPU& cpu, u32& Cycles, Byte& R) {
    R = cpu.FetchByte(Cycles);
    LDSetStatus(cpu, R);
}

void Inst::LD_ZP(CPU& cpu, u32& Cycles, Byte& R) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    R = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDSetStatus(cpu, R);
}

void Inst::LD_ZP_R(CPU& cpu, u32& Cycles, Byte& Rd, Byte& Rs) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, Rs, Cycles, 1);
    Rd = cpu.ReadAddr(ZeroPageAddr, Cycles);
    LDSetStatus(cpu, Rd);
}

void Inst::LD_ABS(CPU& cpu, u32& Cycles, Byte& R) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    R = cpu.ReadAddr(TargetAddr, Cycles);
    LDSetStatus(cpu, R);
}

void Inst::LD_ABS_R(CPU& cpu, u32& Cycles, Byte& Rd, Byte& Rs) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    TargetAddr = cpu.addM(TargetAddr, Rs, Cycles, 0);
    Rd = cpu.ReadAddr(TargetAddr, Cycles);
    LDSetStatus(cpu, Rd);
}

/* LDA Functions */
void Inst::LDA_IM(CPU& cpu, u32& Cycles) {
    LD_IM(cpu, Cycles, cpu.A);
}

void Inst::LDA_ZP(CPU& cpu, u32& Cycles) {
    LD_ZP(cpu, Cycles, cpu.A);
}

void Inst::LDA_ZP_X(CPU& cpu, u32& Cycles) {
    LD_ZP_R(cpu, Cycles, cpu.A, cpu.X);
}

void Inst::LDA_ABS(CPU& cpu, u32& Cycles) {
    LD_ABS(cpu, Cycles, cpu.A);
}

void Inst::LDA_ABS_X(CPU& cpu, u32& Cycles) {
    LD_ABS_R(cpu, Cycles, cpu.A, cpu.X);
}

void Inst::LDA_ABS_Y(CPU& cpu, u32& Cycles) {
    LD_ABS_R(cpu, Cycles, cpu.A, cpu.Y);
}

void Inst::LDA_IND_X(CPU& cpu, u32&Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.X, Cycles, 1);
    Word IndAddr = ((Word)cpu.ReadAddr(ZeroPageAddr, Cycles) << 8) |
                    ((Word)cpu.ReadAddr(ZeroPageAddr + 1, Cycles));
    cpu.A = cpu.ReadAddr(IndAddr, Cycles);
    LDSetStatus(cpu, cpu.A);
}

void Inst::LDA_IND_Y(CPU& cpu, u32&Cycles) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, cpu.Y, Cycles, 1);
    Word IndAddr = ((Word)cpu.ReadAddr(ZeroPageAddr, Cycles) << 8) |
                    ((Word)cpu.ReadAddr(ZeroPageAddr + 1, Cycles));
    cpu.A = cpu.ReadAddr(IndAddr, Cycles);
    LDSetStatus(cpu, cpu.A);
}

/* LDX Functions */
void Inst::LDX_IM(CPU& cpu, u32& Cycles) {
    LD_IM(cpu, Cycles, cpu.X);
}

void Inst::LDX_ZP(CPU& cpu, u32& Cycles) {
    LD_ZP(cpu, Cycles, cpu.X);
}

void Inst::LDX_ZP_Y(CPU& cpu, u32& Cycles) {
    LD_ZP_R(cpu, Cycles, cpu.X, cpu.Y);
}

void Inst::LDX_ABS(CPU& cpu, u32& Cycles) {
    LD_ABS(cpu, Cycles, cpu.X);
}

void Inst::LDX_ABS_Y(CPU& cpu, u32& Cycles) {
    LD_ABS_R(cpu, Cycles, cpu.X, cpu.Y);
}

/* LDY Functions */
void Inst::LDY_IM(CPU& cpu, u32& Cycles) {
    LD_IM(cpu, Cycles, cpu.Y);
}

void Inst::LDY_ZP(CPU& cpu, u32& Cycles) {
    LD_ZP(cpu, Cycles, cpu.Y);
}

void Inst::LDY_ZP_X(CPU& cpu, u32& Cycles) {
    LD_ZP_R(cpu, Cycles, cpu.Y, cpu.X);
}

void Inst::LDY_ABS(CPU& cpu, u32& Cycles) {
    LD_ABS(cpu, Cycles, cpu.Y);
}

void Inst::LDY_ABS_X(CPU& cpu, u32& Cycles) {
    LD_ABS_R(cpu, Cycles, cpu.Y, cpu.X);
}

/* ST Functions */
void Inst::ST_ZP(CPU& cpu, u32& Cycles, Byte& R) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    cpu.mem[ZeroPageAddr] = R;
    Cycles --;
}

void Inst::ST_ZP_R(CPU& cpu, u32& Cycles, Byte& Rd, Byte& Rs) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, Rs, Cycles, 1);
    cpu.mem[ZeroPageAddr] = Rd;
    Cycles --;
}

void Inst::ST_ABS(CPU& cpu, u32& Cycles, Byte& R) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    cpu.mem[TargetAddr] = R;
    Cycles --;
}

void Inst::ST_ABS_R(CPU& cpu, u32& Cycles, Byte& Rd, Byte& Rs) {
    Word TargetAddr = cpu.FetchWord(Cycles);
    TargetAddr = cpu.addM(TargetAddr, Rs, Cycles, 0);
    cpu.mem[TargetAddr] = Rd;
    Cycles --;
}

void Inst::ST_IND_R(CPU& cpu, u32& Cycles, Byte& Rd, Byte& Rs) {
    Word ZeroPageAddr = cpu.FetchByte(Cycles);
    ZeroPageAddr = cpu.addM(ZeroPageAddr, Rs, Cycles, 1);
    Word IndAddr = ((Word)cpu.ReadAddr(ZeroPageAddr, Cycles) << 8) |
                    ((Word)cpu.ReadAddr(ZeroPageAddr + 1, Cycles));
    cpu.mem[IndAddr] = Rd;
    Cycles --;
}

/* STA Functions */
void Inst::STA_ZP(CPU& cpu, u32& Cycles) {
    ST_ZP(cpu, Cycles, cpu.A);
}

void Inst::STA_ZP_X(CPU& cpu, u32& Cycles) {
    ST_ZP_R(cpu, Cycles, cpu.A, cpu.X);
}

void Inst::STA_ABS(CPU& cpu, u32& Cycles) {
    ST_ABS(cpu, Cycles, cpu.A);
}

void Inst::STA_ABS_X(CPU& cpu, u32& Cycles) {
    ST_ABS_R(cpu, Cycles, cpu.A, cpu.X);
}

void Inst::STA_ABS_Y(CPU& cpu, u32& Cycles) {
    ST_ABS_R(cpu, Cycles, cpu.A, cpu.Y);
}

void Inst::STA_IND_X(CPU& cpu, u32& Cycles) {
    ST_IND_R(cpu, Cycles, cpu.A, cpu.X);
}

void Inst::STA_IND_Y(CPU& cpu, u32& Cycles) {
    ST_IND_R(cpu, Cycles, cpu.A, cpu.Y);
}

/* STX Functions */
void Inst::STX_ZP(CPU& cpu, u32& Cycles) {
    ST_ZP(cpu, Cycles, cpu.X);
}

void Inst::STX_ZP_Y(CPU& cpu, u32& Cycles) {
    ST_ZP_R(cpu, Cycles, cpu.X, cpu.Y);
}

void Inst::STX_ABS(CPU& cpu, u32& Cycles) {
    ST_ABS(cpu, Cycles, cpu.X);
}

/* STY Functions */
void Inst::STY_ZP(CPU& cpu, u32& Cycles) {
    ST_ZP(cpu, Cycles, cpu.Y);
}

void Inst::STY_ZP_X(CPU& cpu, u32& Cycles) {
    ST_ZP_R(cpu, Cycles, cpu.Y, cpu.X);
}

void Inst::STY_ABS(CPU& cpu, u32& Cycles) {
    ST_ABS(cpu, Cycles, cpu.Y);
}

/* JMP Functions */
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