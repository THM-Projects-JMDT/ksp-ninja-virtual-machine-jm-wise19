#include "runner.h"
#include "../Interpreter/interpreter.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"

int haltProg = 0;
int pc = 0;
static int lc = 0;

// Display all Instructions in Memory
void execList() {
  while (lc < memorySize) {
    unsigned int ir = programMemory[lc];
    lc++;
    execInst(ir, lc, 1);
  }
  lc = 0;
}

// Run Programm in Memory
void execprog() {
  while (!haltProg) {
    if (pc == memorySize)
      invalidProgrammCodeError();

    unsigned int ir = programMemory[pc];
    pc++;
    execInst(ir, pc, 0);
  }
  pc = 0;
}