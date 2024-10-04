#include "../src/cpu.hpp"
#include "../src/inst.hpp"  // 假设有这个头文件
#include <gtest/gtest.h>

class M6502Test : public testing::Test {
protected:
    CPU cpu;

    void SetUp() override {
        cpu.Reset();
    }

    void TearDown() override {
    }

    void CPUJmp(Word PC) {
        cpu.PC = PC;
    }

    void CPURun(u32 Cycles) {
        EXPECT_EQ(cpu.Execute(Cycles), 0);
    }

    void PCTest(Word PC) {
        EXPECT_EQ(cpu.PC, PC) << "Program counter incorrect";
    }

    void RegTest(Byte& R, const Byte expectedR) {
        EXPECT_EQ(R, expectedR) << "Reg mismatch";
    }

    void PSTest(Byte expectedStatus) {
        EXPECT_EQ(cpu.PS, expectedStatus) << "Processor status mismatch";
    }

    void LD_IM_TEST(const Byte Inst, const u32 Cycles, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0xF5;

        CPURun(Cycles);

        RegTest(R, 0xF5);
        PCTest(0xFFFE);
        PSTest(CPU::PS_N);
        cpu.Reset();
    }

    void LD_ZP_TSET(const Byte Inst, const u32 Cycles, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0x0012] = 0x55;

        CPURun(Cycles);

        RegTest(R, 0x55);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }

    void LD_ZP_R_TSET(const Byte Inst, const u32 Cycles, Byte& Rs, Byte& Rd) {
        Rs = 0x43;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0x0055] = 0xF5;

        CPURun(Cycles);

        RegTest(Rd, 0xF5);
        PCTest(0xFFFE);
        PSTest(CPU::PS_N);
        cpu.Reset();
    }

    void LD_ABS_TSET(const Byte Inst, const u32 Cycles, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1234] = 0x55;

        CPURun(Cycles);

        RegTest(R, 0x55);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void LD_ABS_R_TEST(const Byte Inst, const u32 Cycles, Byte& Rs, Byte& Rd) {
        Rs = 0x11;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1245] = 0x55;

        CPURun(Cycles);

        RegTest(Rd, 0x55);
        RegTest(Rs, 0x11);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void LDA_IND_R_TEST(const Byte Inst, const u32 Cycles, Byte& R) {
        R = 0x55;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x10;
        cpu.mem[0x0065] = 0x12;
        cpu.mem[0x0066] = 0x34;
        cpu.mem[0x1234] = 0x55;

        CPURun(Cycles);
        
        RegTest(cpu.A, 0x55);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }
};

TEST_F(M6502Test, INST_LDA_DIRECT_TEST) {
    LD_IM_TEST(Inst::INST_LDA_IM, InstCycles::LDA_IM, cpu.A);
    LD_ZP_TSET(Inst::INST_LDA_ZP, InstCycles::LDA_ZP, cpu.A);
    LD_ZP_R_TSET(Inst::INST_LDA_ZP_X, InstCycles::LDA_ZP_X, cpu.X, cpu.A);
    LD_ABS_TSET(Inst::INST_LDA_ABS, InstCycles::LDA_ABS, cpu.A);
    LD_ABS_R_TEST(Inst::INST_LDA_ABS_X, InstCycles::LDA_ABS_X + 1, cpu.X, cpu.A);
    LDA_IND_R_TEST(Inst::INST_LDA_IND_X, InstCycles::LDA_IND_X, cpu.X);
    LDA_IND_R_TEST(Inst::INST_LDA_IND_Y, InstCycles::LDA_IND_Y + 1, cpu.Y);
}

TEST_F(M6502Test, INST_JMP_ABS) {
    cpu.mem[0xFFFC] = Inst::INST_JMP_ABS;
    cpu.mem[0xFFFD] = 0x10;
    cpu.mem[0xFFFE] = 0x00;

    CPURun(InstCycles::JMP_ABS);

    PCTest(0x1000);
    PSTest(0);
}

TEST_F(M6502Test, INST_JMP_IND) {
    cpu.mem[0x1000] = 0x20;
    cpu.mem[0x1001] = 0x00;
    cpu.mem[0xFFFC] = Inst::INST_JMP_IND;
    cpu.mem[0xFFFD] = 0x10;
    cpu.mem[0xFFFE] = 0x00;

    CPURun(InstCycles::JMP_IND);

    PCTest(0x2000);
    PSTest(0);
}

TEST_F(M6502Test, INST_JSR_ABS) {
    cpu.mem[0x1000] = Inst::INST_JSR_ABS;
    cpu.mem[0x1001] = 0x20;
    cpu.mem[0x1002] = 0x00;
    
    CPUJmp(0x1000);
    CPURun(InstCycles::JSR_ABS);

    PCTest(0x2000);
    EXPECT_EQ(cpu.SP, 0x0102);
    EXPECT_EQ(cpu.mem[0x0100], 0x03);
    EXPECT_EQ(cpu.mem[0x0101], 0x10);
    PSTest(0);
}

TEST_F(M6502Test, CallFunctionAndReturn) {
    CPUJmp(0xff00);

    cpu.mem[0xff00] = Inst::INST_JSR_ABS;
    cpu.mem[0xff01] = 0x80;
    cpu.mem[0xff02] = 0x00;
    cpu.mem[0x8000] = Inst::INST_RTS;
    cpu.mem[0xff03] = Inst::INST_LDA_IM;
    cpu.mem[0xff04] = 0x34;
    
    u32 Cycles = 
        InstCycles::JSR_ABS + 
        InstCycles::RTS + 
        InstCycles::LDA_IM;

    CPURun(Cycles);

    RegTest(cpu.A, 0x34);
    PCTest(0xff05);
    PSTest(0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}