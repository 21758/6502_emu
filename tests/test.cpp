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

    void RegTest(Byte expectedA, Byte expectedX, Byte expectedY) {
        EXPECT_EQ(cpu.A, expectedA) << "Accumulator mismatch";
        EXPECT_EQ(cpu.X, expectedX) << "X register mismatch";
        EXPECT_EQ(cpu.Y, expectedY) << "Y register mismatch";
    }

    void PSTest(Byte expectedStatus) {
        EXPECT_EQ(cpu.PS, expectedStatus) << "Processor status mismatch";
    }
};

TEST_F(M6502Test, INST_LDA_IM) {
    cpu.mem[0xFFFC] = Inst::INST_LDA_IM;
    cpu.mem[0xFFFD] = 0xF2;

    CPURun(InstCycles::LDA_IM);

    RegTest(0xF2, 0, 0);
    PCTest(0xFFFE);
    PSTest(CPU::PS_N);
}

TEST_F(M6502Test, INST_LDA_ZP) {
    cpu.mem[0xFFFC] = Inst::INST_LDA_ZP;
    cpu.mem[0xFFFD] = 0x12;
    cpu.mem[0x0012] = 0x34;

    CPURun(InstCycles::LDA_ZP);

    RegTest(0x34, 0, 0);
    PCTest(0xFFFE);
    PSTest(0);
}

TEST_F(M6502Test, INST_LDA_ABS) {
    cpu.mem[0xFFFC] = Inst::INST_LDA_ABS;
    cpu.mem[0xFFFD] = 0x12;
    cpu.mem[0xFFFE] = 0x34;
    cpu.mem[0x1234] = 0x34;

    CPURun(InstCycles::LDA_ABS);

    RegTest(0x34, 0, 0);
    PCTest(0xFFFF);
    PSTest(0);
}

TEST_F(M6502Test, INST_LDA_ABS_X) {
    cpu.X = 0x11;
    cpu.mem[0xFFFC] = Inst::INST_LDA_ABS_X;
    cpu.mem[0xFFFD] = 0x12;
    cpu.mem[0xFFFE] = 0x34;
    cpu.mem[0x1245] = 0x34;

    CPURun(InstCycles::LDA_ABS_X + 1);

    RegTest(0x34, 0x11, 0);
    PCTest(0xFFFF);
    PSTest(0);
}

TEST_F(M6502Test, INST_JMP_ABS) {
    cpu.mem[0xFFFC] = Inst::INST_JMP_ABS;
    cpu.mem[0xFFFD] = 0x10;
    cpu.mem[0xFFFE] = 0x00;

    CPURun(InstCycles::JMP_ABS);

    RegTest(0, 0, 0);
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

    RegTest(0, 0, 0);
    PCTest(0x2000);
    PSTest(0);
}

TEST_F(M6502Test, INST_JSR_ABS) {
    cpu.mem[0x1000] = Inst::INST_JSR_ABS;
    cpu.mem[0x1001] = 0x20;
    cpu.mem[0x1002] = 0x00;
    
    CPUJmp(0x1000);
    CPURun(InstCycles::JSR_ABS);

    RegTest(0, 0, 0);
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

    RegTest(0x34, 0, 0);
    PCTest(0xff05);
    PSTest(0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}