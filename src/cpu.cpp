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
        // case Inst::INST_JSR_ABS:
        //   Inst::JMP_ABS(*this, Cycles);
        //   break;
        default:
        {
          printf("Invalid Inst: %x\n", inst);
        } break;
      }
    }
    return Cycles;
  }