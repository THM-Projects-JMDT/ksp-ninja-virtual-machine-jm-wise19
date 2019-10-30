#include "runner.h"
#include "../Interpreter/interpreter.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"

static int haltProg = 0;
static int pc = 0;
static int lc = 0;

// Stop Runner
void stopProgramm() { haltProg = 1; }

// Change Programm Counter
void changePC(const int dest) {
  if (dest < 0 || dest > memorySize)
    invalidJumpDestinationError(dest);

  pc = dest;
}

// Display all Instructions in Memory
void execList() {
  while (lc < memorySize) {
    unsigned int ir = getInst(lc);
    lc++;
    execInst(ir, lc, 1);
  }
  lc = 0;
}

// Run Programm in Memory
void execprog() {
  while (!haltProg) {
    unsigned int ir = getInst(pc);
    pc++;
    execInst(ir, pc, 0);
  }
  pc = 0;
}