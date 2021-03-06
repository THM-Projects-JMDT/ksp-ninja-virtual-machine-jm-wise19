/*
 * runner.c -- Functions that execute or display the program
 */

#include "runner.h"
#include "../interpreter/interpreter.h"
#include "../memory/programMemory.h"
#include "../util/error.h"
#include <stdbool.h>

static bool haltProg = false;
static int pc = 0;
static int lc = 0;

// Stop Runner
void stopProgramm(void) { haltProg = true; }
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
    execInst(ir, lc, true);
  }
}

void step(void) {
  unsigned int ir = getInst(pc);
  pc++;
  execInst(ir, pc, false);
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