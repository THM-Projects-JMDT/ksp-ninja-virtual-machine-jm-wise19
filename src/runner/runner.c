#include "runner.h"
#include "../Interpreter/interpreter.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"

static int haltProg = 0;
static int pc = 0;
static int lc = 0;

// Stop Runner
void stopProgramm(void) { haltProg = 1; }
int getPC(void) { return pc; }

// Change Programm Counter
void changePC(const int dest) {
  if (dest < 0 || dest > memorySize)
    invalidJumpDestinationError(dest);

  pc = dest;
}

// Display all Instructions in Memory
void execList(void) {
  lc = 0;

  while (lc < memorySize) {
    unsigned int ir = getInst(lc);
    lc++;
    execInst(ir, lc, 1);
  }
}

void step(void) {
  unsigned int ir = getInst(pc);
  pc++;
  execInst(ir, pc, 0);
}

// Run Programm in Memory
void execprog(void) {
  while (!haltProg) {
    step();
  }
}

void execProgBreak(int b) {
  while (!haltProg) {
    step();
    if (pc == b)
      return;
  }
}