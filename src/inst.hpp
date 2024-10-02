#pragma once
#include "cpu.hpp"

class Inst {
    private:

    public:
        /* opcodes */
        // Load/Store Operations
        static constexpr Byte
            // LDA
            INST_LDA_IM = 0xA9,
            INST_LDA_ZP = 0xA5,
            INST_LDA_ZP_X = 0xB5,
            INST_LDA_ABS = 0xAD,
            INST_LDA_ABS_X = 0xBD,
            INST_LDA_ABS_Y = 0xB9,
            INST_LDA_IND_X = 0xA1,
            INST_LDA_IND_Y = 0xB1,
            
            // LDX
            INST_LDX_IM = 0xA2,
            INST_LDX_ZP = 0xA6,
            INST_LDX_ZP_Y = 0xB6,
            INST_LDX_ABS = 0xAE,
            INST_LDX_ABS_Y = 0xBE,
            
            // LDY
            INST_LDY_IM = 0xA0,
            INST_LDY_ZP = 0xA4,
            INST_LDY_ZP_X = 0xB4,
            INST_LDY_ABS = 0xAC,
            INST_LDY_ABS_X = 0xBC,
            
            // STA
            INST_STA_ZP = 0x85,
            INST_STA_ZP_X = 0x95,
            INST_STA_ABS = 0x8D,
            INST_STA_ABS_X = 0x9D,
            INST_STA_ABS_Y = 0x99,
            INST_STA_IND_X = 0x81,
            INST_STA_IND_Y = 0x91,
            
            // STX
            INST_STX_ZP = 0x86,
            INST_STX_ZP_Y = 0x96,
            INST_STX_ABS = 0x8E,
            
            // STY
            INST_STY_ZP = 0x84,
            INST_STY_ZP_X = 0x94,
            INST_STY_ABS = 0x8C;

        // Register Transfers
        static constexpr Byte
            INST_TAX = 0xAA,
            INST_TAY = 0xA8,
            INST_TXA = 0x8A,
            INST_TYA = 0x98;

        // Stack Operations
        static constexpr Byte
            INST_TSX = 0xBA,
            INST_TXS = 0x9A,
            INST_PHA = 0x48,
            INST_PHP = 0x08,
            INST_PLA = 0x68,
            INST_PLP = 0x28;

        // Logical Operations
        static constexpr Byte
            // AND
            INST_AND_IM = 0x29,
            INST_AND_ZP = 0x25,
            INST_AND_ZP_X = 0x35,
            INST_AND_ABS = 0x2D,
            INST_AND_ABS_X = 0x3D,
            INST_AND_ABS_Y = 0x39,
            INST_AND_IND_X = 0x21,
            INST_AND_IND_Y = 0x31,
            
            // EOR
            INST_EOR_IM = 0x49,
            INST_EOR_ZP = 0x45,
            INST_EOR_ZP_X = 0x55,
            INST_EOR_ABS = 0x4D,
            INST_EOR_ABS_X = 0x5D,
            INST_EOR_ABS_Y = 0x59,
            INST_EOR_IND_X = 0x41,
            INST_EOR_IND_Y = 0x51,
            
            // ORA
            INST_ORA_IM = 0x09,
            INST_ORA_ZP = 0x05,
            INST_ORA_ZP_X = 0x15,
            INST_ORA_ABS = 0x0D,
            INST_ORA_ABS_X = 0x1D,
            INST_ORA_ABS_Y = 0x19,
            INST_ORA_IND_X = 0x01,
            INST_ORA_IND_Y = 0x11,
            
            // BIT
            INST_BIT_ZP = 0x24,
            INST_BIT_ABS = 0x2C;

        // Arithmetic Operations
        static constexpr Byte
            // ADC
            INST_ADC_IM = 0x69,
            INST_ADC_ZP = 0x65,
            INST_ADC_ZP_X = 0x75,
            INST_ADC_ABS = 0x6D,
            INST_ADC_ABS_X = 0x7D,
            INST_ADC_ABS_Y = 0x79,
            INST_ADC_IND_X = 0x61,
            INST_ADC_IND_Y = 0x71,
            
            // SBC
            INST_SBC_IM = 0xE9,
            INST_SBC_ZP = 0xE5,
            INST_SBC_ZP_X = 0xF5,
            INST_SBC_ABS = 0xED,
            INST_SBC_ABS_X = 0xFD,
            INST_SBC_ABS_Y = 0xF9,
            INST_SBC_IND_X = 0xE1,
            INST_SBC_IND_Y = 0xF1,
            
            // CMP
            INST_CMP_IM = 0xC9,
            INST_CMP_ZP = 0xC5,
            INST_CMP_ZP_X = 0xD5,
            INST_CMP_ABS = 0xCD,
            INST_CMP_ABS_X = 0xDD,
            INST_CMP_ABS_Y = 0xD9,
            INST_CMP_IND_X = 0xC1,
            INST_CMP_IND_Y = 0xD1,
            
            // CPX
            INST_CPX_IM = 0xE0,
            INST_CPX_ZP = 0xE4,
            INST_CPX_ABS = 0xEC,
            
            // CPY
            INST_CPY_IM = 0xC0,
            INST_CPY_ZP = 0xC4,
            INST_CPY_ABS = 0xCC;

        // Increments & Decrements
        static constexpr Byte
            INST_INC_ZP = 0xE6,
            INST_INC_ZP_X = 0xF6,
            INST_INC_ABS = 0xEE,
            INST_INC_ABS_X = 0xFE,
            INST_INX = 0xE8,
            INST_INY = 0xC8,
            INST_DEC_ZP = 0xC6,
            INST_DEC_ZP_X = 0xD6,
            INST_DEC_ABS = 0xCE,
            INST_DEC_ABS_X = 0xDE,
            INST_DEX = 0xCA,
            INST_DEY = 0x88;

        // Shifts
        static constexpr Byte
            INST_ASL_ACC = 0x0A,
            INST_ASL_ZP = 0x06,
            INST_ASL_ZP_X = 0x16,
            INST_ASL_ABS = 0x0E,
            INST_ASL_ABS_X = 0x1E,
            INST_LSR_ACC = 0x4A,
            INST_LSR_ZP = 0x46,
            INST_LSR_ZP_X = 0x56,
            INST_LSR_ABS = 0x4E,
            INST_LSR_ABS_X = 0x5E,
            INST_ROL_ACC = 0x2A,
            INST_ROL_ZP = 0x26,
            INST_ROL_ZP_X = 0x36,
            INST_ROL_ABS = 0x2E,
            INST_ROL_ABS_X = 0x3E,
            INST_ROR_ACC = 0x6A,
            INST_ROR_ZP = 0x66,
            INST_ROR_ZP_X = 0x76,
            INST_ROR_ABS = 0x6E,
            INST_ROR_ABS_X = 0x7E;

        // Jumps & Calls
        static constexpr Byte
            INST_JMP_ABS = 0x4C,
            INST_JMP_IND = 0x6C,
            INST_JSR_ABS = 0x20,
            INST_RTS = 0x60;

        // Branches
        static constexpr Byte
            INST_BCC = 0x90,
            INST_BCS = 0xB0,
            INST_BEQ = 0xF0,
            INST_BMI = 0x30,
            INST_BNE = 0xD0,
            INST_BPL = 0x10,
            INST_BVC = 0x50,
            INST_BVS = 0x70;

        // Status Flag Changes
        static constexpr Byte
            INST_CLC = 0x18,
            INST_CLD = 0xD8,
            INST_CLI = 0x58,
            INST_CLV = 0xB8,
            INST_SEC = 0x38,
            INST_SED = 0xF8,
            INST_SEI = 0x78;

        // System Functions
        static constexpr Byte
            INST_BRK = 0x00,
            INST_NOP = 0xEA,
            INST_RTI = 0x40;
        
        /* functions */
        // LDA
        static void LDASetStatus(CPU& cpu);
        static void LDA_IM(CPU& cpu, u32& Cycles);
        static void LDA_ZP(CPU& cpu, u32& Cycles);
        static void LDA_ZP_X(CPU& cpu, u32& Cycles);
        static void LDA_ABS(CPU& cpu, u32& Cycles);
        static void LDA_ABS_X(CPU& cpu, u32& Cycles);
        static void LDA_ABS_Y(CPU& cpu, u32& Cycles);
        static void LDA_IND_X(CPU& cpu, u32& Cycles);
        static void LDA_IND_Y(CPU& cpu, u32& Cycles);

        // LDX
        static void LDXSetStatus(CPU& cpu);
        static void LDX_IM(CPU& cpu, u32& Cycles);
        static void LDX_ZP(CPU& cpu, u32& Cycles);
        static void LDX_ZP_Y(CPU& cpu, u32& Cycles);
        static void LDX_ABS(CPU& cpu, u32& Cycles);
        static void LDX_ABS_Y(CPU& cpu, u32& Cycles);
        
        // LDY
        static void LDYSetStatus(CPU& cpu);
        static void LDY_IM(CPU& cpu, u32& Cycles);
        static void LDY_ZP(CPU& cpu, u32& Cycles);
        static void LDY_ZP_X(CPU& cpu, u32& Cycles);
        static void LDY_ABS(CPU& cpu, u32& Cycles);
        static void LDY_ABS_X(CPU& cpu, u32& Cycles);

        // Store Operations
        // STA
        static void STA_ZP(CPU& cpu, u32& Cycles);
        static void STA_ZP_X(CPU& cpu, u32& Cycles);
        static void STA_ABS(CPU& cpu, u32& Cycles);
        static void STA_ABS_X(CPU& cpu, u32& Cycles);
        static void STA_ABS_Y(CPU& cpu, u32& Cycles);
        static void STA_IND_X(CPU& cpu, u32& Cycles);
        static void STA_IND_Y(CPU& cpu, u32& Cycles);
        
        // STX
        static void STX_ZP(CPU& cpu, u32& Cycles);
        static void STX_ZP_Y(CPU& cpu, u32& Cycles);
        static void STX_ABS(CPU& cpu, u32& Cycles);
        
        // STY
        static void STY_ZP(CPU& cpu, u32& Cycles);
        static void STY_ZP_X(CPU& cpu, u32& Cycles);
        static void STY_ABS(CPU& cpu, u32& Cycles);

        // Register Transfers
        static void TAX(CPU& cpu, u32& Cycles);
        static void TAY(CPU& cpu, u32& Cycles);
        static void TXA(CPU& cpu, u32& Cycles);
        static void TYA(CPU& cpu, u32& Cycles);
        static void TSX(CPU& cpu, u32& Cycles);
        static void TXS(CPU& cpu, u32& Cycles);

        // Stack Operations
        static void PHA(CPU& cpu, u32& Cycles);
        static void PHP(CPU& cpu, u32& Cycles);
        static void PLA(CPU& cpu, u32& Cycles);
        static void PLP(CPU& cpu, u32& Cycles);

        // Logical Operations
        // AND
        static void ANDSetStatus(CPU& cpu);
        static void AND_IM(CPU& cpu, u32& Cycles);
        static void AND_ZP(CPU& cpu, u32& Cycles);
        static void AND_ZP_X(CPU& cpu, u32& Cycles);
        static void AND_ABS(CPU& cpu, u32& Cycles);
        static void AND_ABS_X(CPU& cpu, u32& Cycles);
        static void AND_ABS_Y(CPU& cpu, u32& Cycles);
        static void AND_IND_X(CPU& cpu, u32& Cycles);
        static void AND_IND_Y(CPU& cpu, u32& Cycles);
        
        // EOR
        static void EORSetStatus(CPU& cpu);
        static void EOR_IM(CPU& cpu, u32& Cycles);
        static void EOR_ZP(CPU& cpu, u32& Cycles);
        static void EOR_ZP_X(CPU& cpu, u32& Cycles);
        static void EOR_ABS(CPU& cpu, u32& Cycles);
        static void EOR_ABS_X(CPU& cpu, u32& Cycles);
        static void EOR_ABS_Y(CPU& cpu, u32& Cycles);
        static void EOR_IND_X(CPU& cpu, u32& Cycles);
        static void EOR_IND_Y(CPU& cpu, u32& Cycles);
        
        // ORA
        static void ORASetStatus(CPU& cpu);
        static void ORA_IM(CPU& cpu, u32& Cycles);
        static void ORA_ZP(CPU& cpu, u32& Cycles);
        static void ORA_ZP_X(CPU& cpu, u32& Cycles);
        static void ORA_ABS(CPU& cpu, u32& Cycles);
        static void ORA_ABS_X(CPU& cpu, u32& Cycles);
        static void ORA_ABS_Y(CPU& cpu, u32& Cycles);
        static void ORA_IND_X(CPU& cpu, u32& Cycles);
        static void ORA_IND_Y(CPU& cpu, u32& Cycles);
        
        // BIT
        static void BITSetStatus(CPU& cpu);
        static void BIT_ZP(CPU& cpu, u32& Cycles);
        static void BIT_ABS(CPU& cpu, u32& Cycles);

        // Arithmetic Operations
        // ADC
        static void ADCSetStatus(CPU& cpu);
        static void ADC_IM(CPU& cpu, u32& Cycles);
        static void ADC_ZP(CPU& cpu, u32& Cycles);
        static void ADC_ZP_X(CPU& cpu, u32& Cycles);
        static void ADC_ABS(CPU& cpu, u32& Cycles);
        static void ADC_ABS_X(CPU& cpu, u32& Cycles);
        static void ADC_ABS_Y(CPU& cpu, u32& Cycles);
        static void ADC_IND_X(CPU& cpu, u32& Cycles);
        static void ADC_IND_Y(CPU& cpu, u32& Cycles);
        
        // SBC
        static void SBCSetStatus(CPU& cpu);
        static void SBC_IM(CPU& cpu, u32& Cycles);
        static void SBC_ZP(CPU& cpu, u32& Cycles);
        static void SBC_ZP_X(CPU& cpu, u32& Cycles);
        static void SBC_ABS(CPU& cpu, u32& Cycles);
        static void SBC_ABS_X(CPU& cpu, u32& Cycles);
        static void SBC_ABS_Y(CPU& cpu, u32& Cycles);
        static void SBC_IND_X(CPU& cpu, u32& Cycles);
        static void SBC_IND_Y(CPU& cpu, u32& Cycles);
        
        // Compare Operations
        static void CMPSetStatus(CPU& cpu, Byte reg, Byte mem);
        static void CMP_IM(CPU& cpu, u32& Cycles);
        static void CMP_ZP(CPU& cpu, u32& Cycles);
        static void CMP_ZP_X(CPU& cpu, u32& Cycles);
        static void CMP_ABS(CPU& cpu, u32& Cycles);
        static void CMP_ABS_X(CPU& cpu, u32& Cycles);
        static void CMP_ABS_Y(CPU& cpu, u32& Cycles);
        static void CMP_IND_X(CPU& cpu, u32& Cycles);
        static void CMP_IND_Y(CPU& cpu, u32& Cycles);
        
        static void CPX_IM(CPU& cpu, u32& Cycles);
        static void CPX_ZP(CPU& cpu, u32& Cycles);
        static void CPX_ABS(CPU& cpu, u32& Cycles);
        
        static void CPY_IM(CPU& cpu, u32& Cycles);
        static void CPY_ZP(CPU& cpu, u32& Cycles);
        static void CPY_ABS(CPU& cpu, u32& Cycles);

        // Increments & Decrements
        static void INCSetStatus(CPU& cpu);
        static void INC_ZP(CPU& cpu, u32& Cycles);
        static void INC_ZP_X(CPU& cpu, u32& Cycles);
        static void INC_ABS(CPU& cpu, u32& Cycles);
        static void INC_ABS_X(CPU& cpu, u32& Cycles);
        static void INX(CPU& cpu, u32& Cycles);
        static void INY(CPU& cpu, u32& Cycles);
        
        static void DECSetStatus(CPU& cpu);
        static void DEC_ZP(CPU& cpu, u32& Cycles);
        static void DEC_ZP_X(CPU& cpu, u32& Cycles);
        static void DEC_ABS(CPU& cpu, u32& Cycles);
        static void DEC_ABS_X(CPU& cpu, u32& Cycles);
        static void DEX(CPU& cpu, u32& Cycles);
        static void DEY(CPU& cpu, u32& Cycles);

        // Shifts
        static void ASLSetStatus(CPU& cpu);
        static void ASL_ACC(CPU& cpu, u32& Cycles);
        static void ASL_ZP(CPU& cpu, u32& Cycles);
        static void ASL_ZP_X(CPU& cpu, u32& Cycles);
        static void ASL_ABS(CPU& cpu, u32& Cycles);
        static void ASL_ABS_X(CPU& cpu, u32& Cycles);
        
        static void LSRSetStatus(CPU& cpu);
        static void LSR_ACC(CPU& cpu, u32& Cycles);
        static void LSR_ZP(CPU& cpu, u32& Cycles);
        static void LSR_ZP_X(CPU& cpu, u32& Cycles);
        static void LSR_ABS(CPU& cpu, u32& Cycles);
        static void LSR_ABS_X(CPU& cpu, u32& Cycles);
        
        static void ROLSetStatus(CPU& cpu);
        static void ROL_ACC(CPU& cpu, u32& Cycles);
        static void ROL_ZP(CPU& cpu, u32& Cycles);
        static void ROL_ZP_X(CPU& cpu, u32& Cycles);
        static void ROL_ABS(CPU& cpu, u32& Cycles);
        static void ROL_ABS_X(CPU& cpu, u32& Cycles);
        
        static void RORSetStatus(CPU& cpu);
        static void ROR_ACC(CPU& cpu, u32& Cycles);
        static void ROR_ZP(CPU& cpu, u32& Cycles);
        static void ROR_ZP_X(CPU& cpu, u32& Cycles);
        static void ROR_ABS(CPU& cpu, u32& Cycles);
        static void ROR_ABS_X(CPU& cpu, u32& Cycles);

        // Jumps & Calls
        static void JMP_ABS(CPU& cpu, u32& Cycles);
        static void JMP_IND(CPU& cpu, u32& Cycles);
        static void JSR_ABS(CPU& cpu, u32& Cycles);
        static void RTS(CPU& cpu, u32& Cycles);

        // Branches
        static void BranchRelative(CPU& cpu, u32& Cycles, bool condition);
        static void BCC(CPU& cpu, u32& Cycles);
        static void BCS(CPU& cpu, u32& Cycles);
        static void BEQ(CPU& cpu, u32& Cycles);
        static void BMI(CPU& cpu, u32& Cycles);
        static void BNE(CPU& cpu, u32& Cycles);
        static void BPL(CPU& cpu, u32& Cycles);
        static void BVC(CPU& cpu, u32& Cycles);
        static void BVS(CPU& cpu, u32& Cycles);

        // Status Flag Changes
        static void CLC(CPU& cpu, u32& Cycles);
        static void CLD(CPU& cpu, u32& Cycles);
        static void CLI(CPU& cpu, u32& Cycles);
        static void CLV(CPU& cpu, u32& Cycles);
        static void SEC(CPU& cpu, u32& Cycles);
        static void SED(CPU& cpu, u32& Cycles);
        static void SEI(CPU& cpu, u32& Cycles);

        // System Functions
        static void BRK(CPU& cpu, u32& Cycles);
        static void NOP(CPU& cpu, u32& Cycles);
        static void RTI(CPU& cpu, u32& Cycles);
};