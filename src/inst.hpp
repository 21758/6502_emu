#pragma once
#include "cpu.hpp"

class Inst {
    private:

    public:
        // opcodes
        static constexpr Byte
            INST_LDA_IM = 0xA9,
            INST_LDA_ZP = 0xA5,
            INST_LDA_ZP_X = 0xB5,
            INST_LDA_ABS = 0xAD,
            INST_LDA_ABS_X = 0xBD,
            INST_LDA_ABS_Y = 0xB9,
            INST_LDA_IND_X = 0xA1,
            INST_LDA_IND_Y = 0xB1;
        
        static void LDA_IM(CPU& cpu, u32& Cycles);
        static void LDA_ZP(CPU& cpu, u32& Cycles);
        static void LDA_ZP_X(CPU& cpu, u32& Cycles);
        static void LDA_ABS(CPU& cpu, u32& Cycles);
        static void LDA_ABS_X(CPU& cpu, u32& Cycles);
        static void LDA_ABS_Y(CPU& cpu, u32& Cycles);
        static void LDA_IND_X(CPU& cpu, u32& Cycles);
        static void LDA_IND_Y(CPU& cpu, u32& Cycles);
};