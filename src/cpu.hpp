#pragma once
#include <cassert>
#include <cstdio>

#define INST_TO_CYCLES(inst) InstCycles::inst

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;
using s32 = int;

struct Mem {
  static constexpr u32 MAX_MEM = 1024 * 64;  // 64 KB
  Byte Data[MAX_MEM];    // 0x0000 - 0xffff

  void init() {
    for (u32 i = 0; i < MAX_MEM; ++ i)
      Data[i] = 0;
  }
  /* read 1 Byte*/
  Byte operator[]( u32 Address ) const {
    assert(Address < MAX_MEM);
    return Data[Address];
  }
  /*write 1 Byte*/
  Byte& operator[]( u32 Address ) {
    assert(Address < MAX_MEM);
    return Data[Address];
  }

};

struct CPU {
  Mem mem;

  Word PC;
  Word SP;    // 0x0100 - 0x01ff
  static constexpr Word
    MAX_SP = 0x1FF,
    MIN_SP = 0x100;

  Byte A, X, Y, PS;

  static constexpr Byte 
    PS_N = (1 << 7),
    PS_V = (1 << 6),
    PS_B = (1 << 4),
    PS_D = (1 << 3),
    PS_I = (1 << 2),
    PS_Z = (1 << 1),
    PS_C = (1 << 0),
    bitA = 0xFF;

  static constexpr Byte
  setR (bool c, Byte R, Byte x) 
    { 
      return c ? (R | x) : R;
    }

  static constexpr Byte
    clearR (bool c, Byte R, Byte x) 
    { 
      return c ? (R & ~x) : R;
    }

  static constexpr Byte
    getH (Word Val)
    {
      return (Byte)(Val >> 8);
    }
    
  static constexpr Byte
    getL (Word Val)
    {
      return (Byte)(Val & 0x00FF);
    }

  Word addM(Word a, Word b, u32& Cycles, bool mode)
  {
    Cycles --;
    if (mode)
      return (a + b) & (Word)bitA;
    else
      return a + b;
  }

  void Reset() 
  {
    PC = 0xFFFC;
    SP = 0x0100;
    /* init all registers */
    PS = clearR(1, PS, bitA);
    A = clearR(1, A, bitA);
    X = clearR(1, X, bitA);
    Y = clearR(1, Y, bitA);
    /* init memory */
    mem.init();
  }

  void Info()
  {
    printf("------------Reg-------------\n");
    printf(" PC: 0x%X                   \n", PC);
    printf(" A: 0x%X   X: 0x%X   Y: 0x%X   \n", A, X, Y);
    printf(" SP: 0x%X      PS: 0x%X      \n", SP, PS);
    printf("------------Mem-------------\n");
    for (u32 i = 0; i < mem.MAX_MEM; ++ i) {
      if (mem.Data[i])
        printf("Addr: 0x%X\t  0x%X\n", i, mem.Data[i]);
    }
    printf("----------------------------\n");
  }

  Byte FetchByte( u32& Cycles )
  {
    Cycles --;
    return mem[PC ++];
  }

  Byte CheckInst()
  {
    return mem[PC];
  }

  Word FetchWord( u32& Cycles )
  {
    Cycles -= 2;
    Word hByte = mem[PC ++] << 8;
    return hByte | mem[PC ++];
  }

  void Push(Byte Data, u32& Cycles )
  {
    assert(SP <= MAX_SP);
    Cycles --;
    mem[SP ++] = Data;
  }

  Byte Pop( u32& Cycles )
  {
    assert(SP >= MIN_SP);
    Cycles --;
    return mem[-- SP];
  }

  Byte ReadAddr( Word Addr, u32& Cycles )
  {
    Cycles --;
    return mem[(Word) Addr];
  }

  u32 ExecuteOnce();
};

