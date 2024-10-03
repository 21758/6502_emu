#include <cassert>
#include <cstdio>
#include "cpu.hpp"
#include "inst.hpp"

s32 CPU::Execute( u32 Cycles )
  {
    while (Cycles > 0)
    {
      Byte inst = FetchByte(Cycles);
      switch (inst)
      {
        case Inst::INST_LDA_IM:
          Inst::LDA_IM(*this, Cycles);
          break;
        case Inst::INST_LDA_ZP: 
          Inst::LDA_ZP(*this, Cycles);
          break;
        case Inst::INST_LDA_ZP_X:
          Inst::LDA_ZP_X(*this, Cycles);
          break;
        case Inst::INST_LDA_ABS:
          Inst::LDA_ABS(*this, Cycles);
          break;
        case Inst::INST_LDA_ABS_X:
          Inst::LDA_ABS_X(*this, Cycles);
          break;
        case Inst::INST_LDA_ABS_Y:
          Inst::LDA_ABS_Y(*this, Cycles);
          break;
        case Inst::INST_LDA_IND_X:
          Inst::LDA_IND_X(*this, Cycles);
          break;
        case Inst::INST_LDA_IND_Y:
          Inst::LDA_IND_Y(*this, Cycles);
          break;
        case Inst::INST_JMP_ABS:
          Inst::JMP_ABS(*this, Cycles);
          break;
        case Inst::INST_JMP_IND:
          Inst::JMP_IND(*this, Cycles);
          break;
        case Inst::INST_JSR_ABS:
          Inst::JSR_ABS(*this, Cycles);
          break;
        case Inst::INST_RTS:
          Inst::RTS(*this, Cycles);
          break;
        default:
        {
          printf("Invalid Inst: %x\n", inst);
        } break;
      }
    }
    return Cycles;
  }