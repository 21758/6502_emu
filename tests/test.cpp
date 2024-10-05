#include "../src/cpu.hpp"
#include "../src/inst.hpp"  // 假设有这个头文件
#include <gtest/gtest.h>

class M6502Test : public testing::Test {
private:
    // test value
    static constexpr Byte TV = 0x55;
    // test address
    static constexpr Byte TA = 0x12;
public:
    CPU cpu;

    void SetUp() override {
        cpu.Reset();
    }

    void TearDown() override {
    }

    void CPUJmp(Word PC) {
        cpu.PC = PC;
    }

    void CPURun() {
        EXPECT_EQ(cpu.Execute(), 0);
    }

    void PCTest(Word PC) {
        EXPECT_EQ(cpu.PC, PC) << "Program counter incorrect";
    }

    void RegTest(Byte& R, const Byte expectedR) {
        EXPECT_EQ(R, expectedR) << "Reg mismatch";
    }

    void MemTest(Word Addr, Byte& R) {
        EXPECT_EQ(cpu.mem[Addr], R) << "Mem mismatch Reg";
    }

    void PSTest(Byte expectedStatus) {
        EXPECT_EQ(cpu.PS, expectedStatus) << "Processor status mismatch";
    }

    void LD_IM_TEST(const Byte Inst, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0xF5;

        CPURun();

        RegTest(R, 0xF5);
        PCTest(0xFFFE);
        PSTest(CPU::PS_N);
        cpu.Reset();
    }

    void LD_ZP_TSET(const Byte Inst, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0x0012] = TV;

        CPURun();

        RegTest(R, TV);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }

    void LD_ZP_R_TSET(const Byte Inst, Byte& Rs, Byte& Rd) {
        Rs = 0x43;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0x0055] = 0xF5;

        CPURun();

        RegTest(Rd, 0xF5);
        PCTest(0xFFFE);
        PSTest(CPU::PS_N);
        cpu.Reset();
    }

    void LD_ABS_TSET(const Byte Inst, Byte& R) {
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1234] = TV;

        CPURun();

        RegTest(R, TV);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void LD_ABS_R_TEST(const Byte Inst, Byte& Rs, Byte& Rd) {
        Rs = 0x11;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1245] = TV;

        CPURun();

        RegTest(Rd, TV);
        RegTest(Rs, 0x11);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void LDA_IND_R_TEST(const Byte Inst, Byte& R) {
        R = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x10;
        cpu.mem[0x0065] = 0x12;
        cpu.mem[0x0066] = 0x34;
        cpu.mem[0x1234] = TV;

        CPURun();
        
        RegTest(cpu.A, TV);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }

    void ST_ZP_TSET(const Byte Inst, Byte& R) {
        R = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = TA;
        cpu.mem[TA] = 0;

        CPURun();

        MemTest(TA, R);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }

    void ST_ZP_R_TSET(const Byte Inst, Byte& Rs, Byte& Rd) {
        Rs = 0x43;
        Rd = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0x0055] = 0;

        CPURun();

        MemTest(0x55, Rd);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }

    void ST_ABS_TSET(const Byte Inst, Byte& R) {
        R = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1234] = 0;

        CPURun();

        MemTest(0x1234, R);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void STA_ABS_R_TEST(const Byte Inst, Byte& Rs, Byte& Rd) {
        Rs = 0x11;
        Rd = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x12;
        cpu.mem[0xFFFE] = 0x34;
        cpu.mem[0x1245] = 0;

        CPURun();

        MemTest(0x1245, Rd);
        PCTest(0xFFFF);
        PSTest(0);
        cpu.Reset();
    }

    void STA_IND_R_TEST(const Byte Inst, Byte& R) {
        R = TV;
        cpu.mem[0xFFFC] = Inst;
        cpu.mem[0xFFFD] = 0x10;
        cpu.mem[0x0065] = 0x12;
        cpu.mem[0x0066] = 0x34;
        cpu.mem[0x1234] = 0;

        CPURun();
        
        MemTest(0x1234, cpu.A);
        PCTest(0xFFFE);
        PSTest(0);
        cpu.Reset();
    }
};

TEST_F(M6502Test, INST_LDA_DIRECT_TEST) {
    LD_IM_TEST(Inst::INST_LDA_IM, cpu.A);
    LD_ZP_TSET(Inst::INST_LDA_ZP, cpu.A);
    LD_ZP_R_TSET(Inst::INST_LDA_ZP_X, cpu.X, cpu.A);
    LD_ABS_TSET(Inst::INST_LDA_ABS, cpu.A);
    LD_ABS_R_TEST(Inst::INST_LDA_ABS_X, cpu.X, cpu.A);
    LDA_IND_R_TEST(Inst::INST_LDA_IND_X, cpu.X);
    LDA_IND_R_TEST(Inst::INST_LDA_IND_Y, cpu.Y);
}

TEST_F(M6502Test, INST_LDX_TEST) {
    LD_IM_TEST(Inst::INST_LDX_IM, cpu.X);
    LD_ZP_TSET(Inst::INST_LDX_ZP, cpu.X);
    LD_ZP_R_TSET(Inst::INST_LDX_ZP_Y, cpu.Y, cpu.X);
    LD_ABS_TSET(Inst::INST_LDX_ABS, cpu.X);
    LD_ABS_R_TEST(Inst::INST_LDX_ABS_Y, cpu.Y, cpu.X);
}

TEST_F(M6502Test, INST_LDY_TEST) {
    LD_IM_TEST(Inst::INST_LDY_IM, cpu.Y);
    LD_ZP_TSET(Inst::INST_LDY_ZP, cpu.Y);
    LD_ZP_R_TSET(Inst::INST_LDY_ZP_X, cpu.X, cpu.Y);
    LD_ABS_TSET(Inst::INST_LDY_ABS, cpu.Y);
    LD_ABS_R_TEST(Inst::INST_LDY_ABS_X, cpu.X, cpu.Y);
}

TEST_F(M6502Test, INST_STA_TEST) {
    ST_ZP_TSET(Inst::INST_STA_ZP, cpu.A);
    ST_ZP_R_TSET(Inst::INST_STA_ZP_X, cpu.X, cpu.A);
    ST_ABS_TSET(Inst::INST_STA_ABS, cpu.A);
    STA_ABS_R_TEST(Inst::INST_STA_ABS_X, cpu.X, cpu.A);
    STA_ABS_R_TEST(Inst::INST_STA_ABS_Y, cpu.Y, cpu.A);
    STA_IND_R_TEST(Inst::INST_STA_IND_X, cpu.X);
    STA_IND_R_TEST(Inst::INST_STA_IND_Y, cpu.Y);
}

TEST_F(M6502Test, INST_STX_TEST) {
    ST_ZP_TSET(Inst::INST_STX_ZP, cpu.X);
    ST_ZP_R_TSET(Inst::INST_STX_ZP_Y, cpu.Y, cpu.X);
    ST_ABS_TSET(Inst::INST_STX_ABS, cpu.X);
}

TEST_F(M6502Test, INST_STY_TEST) {
    ST_ZP_TSET(Inst::INST_STY_ZP, cpu.Y);
    ST_ZP_R_TSET(Inst::INST_STY_ZP_X, cpu.X, cpu.Y);
    ST_ABS_TSET(Inst::INST_STY_ABS, cpu.Y);
}

TEST_F(M6502Test, INST_JMP_ABS) {
    cpu.mem[0xFFFC] = Inst::INST_JMP_ABS;
    cpu.mem[0xFFFD] = 0x10;
    cpu.mem[0xFFFE] = 0x00;

    CPURun();

    PCTest(0x1000);
    PSTest(0);
}

TEST_F(M6502Test, INST_JMP_IND) {
    cpu.mem[0x1000] = 0x20;
    cpu.mem[0x1001] = 0x00;
    cpu.mem[0xFFFC] = Inst::INST_JMP_IND;
    cpu.mem[0xFFFD] = 0x10;
    cpu.mem[0xFFFE] = 0x00;

    CPURun();

    PCTest(0x2000);
    PSTest(0);
}

TEST_F(M6502Test, INST_JSR_ABS) {
    cpu.mem[0x1000] = Inst::INST_JSR_ABS;
    cpu.mem[0x1001] = 0x20;
    cpu.mem[0x1002] = 0x00;
    
    CPUJmp(0x1000);
    CPURun();

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

    CPURun();

    RegTest(cpu.A, 0x34);
    PCTest(0xff05);
    PSTest(0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}