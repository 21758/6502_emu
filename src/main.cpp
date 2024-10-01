#include <iostream>
#include "cpu.hpp"

using namespace std;

int main() {
    CPU cpu;
    cpu.Reset();
    cpu.mem[0xfffc] = 0xa9;
    cpu.mem[0xfffd] = 0x12;
    cpu.Execute(2);
    printf("PC: 0x%X\n", cpu.PC);
    printf("A: 0x%X\n", cpu.A);
    return 0;
}