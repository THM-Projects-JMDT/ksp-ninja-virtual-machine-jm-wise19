#include "runner.h"
#include "../Interpreter/interpreter.h"
#include "../Memory/programMemory.h"
#include "../util/error.h"
#include "../util/prettyPrint.h"

static int haltProg = 0;
static int pc = 0;
static int lc = 0;

// Stop Runner
void stopProgramm() { haltProg = 1; }
int getPC() { return pc; }

// Change Programm Counter
void changePC(const int dest) {
  if (dest < 0 || dest > memorySize)
    invalidJumpDestinationError(dest);

  pc = dest;
}

// Display all Instructions in Memory
void execList() {
  lc = 0;

  while (lc < memorySize) {
    unsigned int ir = getInst(lc);
    lc++;
    execInst(ir, lc, 1);
  }
}

void step() {
  unsigned int ir = getInst(pc);
  pc++;
  execInst(ir, pc, 0);
}

// Run Programm in Memory
void execprog() {
  pprintf(GREEN, "======\n");

  while (!haltProg) {
    step();
  }

  pprintf(GREEN, "======\n");
}

void execProgBreak(int b) {
  while (!haltProg) {
    step();
    if (pc == b)
      return;
  }
}