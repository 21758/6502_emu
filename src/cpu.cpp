#include <cassert>
#include <cstdio>
#include "cpu.hpp"
#include "inst.hpp"

u32 CPU::ExecuteOnce()
  {
      InstCycles c;
      Inst i;
      u32 Cycles = c.getCycles(FetchInst());
      Byte inst = FetchByte(Cycles);
      InstructionFunc instfunc = i.getInstFunc(inst);
      instfunc(*this, Cycles);
      return Cycles;
  }

u32 CPU::Execute()
  {
    Inst i;
    u32 Cycles = 0;
    while (i.checkInst(FetchInst())) {
      Cycles += ExecuteOnce();
    }
    return Cycles;
  }