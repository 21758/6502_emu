#include <iostream>
#include "inst.hpp"
#include "cpu.hpp"
#include <cassert> // 包含 assert

#define TEST_MODE

#ifdef TEST_MODE
#define toS(x) #x
#define Print(x) std::cout << x << endl; 
#define TEST_SUCCESS(str) printf("\033[32m %s \033[0m \n", str);
#define TEST_FAIL(str) printf(" \033[31m %s \033[0m \n", str);
#define TEST_CODE(Name, x) \
    x; \
    TEST_SUCCESS(toS(Name))
#else
#define TEST_CODE(Name, x)
#endif

using namespace std;

int main() {
    CPU cpu;

    TEST_CODE(
        INST_LDA_IM,
        {
            cpu.Reset();
            cpu.mem[0xfffc] = Inst::INST_LDA_IM;
            cpu.mem[0xfffd] = 0x12;
            cpu.Execute(2);
            assert(cpu.A == 0x12); 
            assert(cpu.PC == (Word)0xFFFE); 
        }
    );

    TEST_CODE(
        INST_LDA_ZP,
        {
            cpu.Reset();
            cpu.mem[0xfffc] = Inst::INST_LDA_ZP;
            cpu.mem[0xfffd] = 0x12;
            cpu.mem[0x0012] = 0x34;
            cpu.Execute(3);
            assert(cpu.A == 0x34);
            assert(cpu.PC == (Word)0xFFFE); 
        }
    );

    TEST_SUCCESS("All tests passed!");
    return 0;
}
