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

TEST_F(M6502Test, LDA_ImmediateLoadsValue) {
    cpu.mem[0xFFFC] = Inst::INST_LDA_IM;
    cpu.mem[0xFFFD] = 0xF2;

    CPURun(2);

    RegTest(0xF2, 0, 0);
    PCTest(0xFFFE);
    PSTest(CPU::PS_N);
}

TEST_F(M6502Test, LDA_ZeroPageLoadsValue) {
    cpu.mem[0xFFFC] = Inst::INST_LDA_ZP;
    cpu.mem[0xFFFD] = 0x12;
    cpu.mem[0x0012] = 0x34;

    CPURun(3);

    RegTest(0x34, 0, 0);
    PCTest(0xFFFE);
    PSTest(0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}