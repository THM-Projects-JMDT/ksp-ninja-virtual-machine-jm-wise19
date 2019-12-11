/*
 * debugger.c -- Main debugger Loop and debugger help functions
 */

#include "debugger.h"
#include "../interpreter/interpreter.h"
#include "../memory/heap.h"
#include "../memory/programMemory.h"
#include "../memory/stack.h"
#include "../njvm.h"
#include "../runner/runner.h"
#include "../util/prettyPrint.h"
#include "commands/debugCmdDef.h"
#include "commands/debugCmds.h"
#include <stdio.h>

#define INPUT_SIZE 20

char *promt[2] = {"NJVM-DEBUG"};

// Stop Debugging (no (void) -> to use it in the DebugCmd struct)
void stopDebugging() { debug = 0; }

// TODo change
void setSubPromt(char *sub) { promt[1] = sub; }

void printMsPromt(void) {
  pprintf(GREEN, "[%s] ", promt[0]);

  // Print sub Promt
  if (promt[1] != NULL) {
    setFormat(stdout, BOLD);
    pprintf(BLACK, "[%s] ", promt[1]);
  }
}
void printPromt(void) {
  // Print sub Promt
  if (promt[1] != NULL) {
    setFormat(stdout, BOLD);
    pprintf(BLACK, "%s@", promt[1]);
  }

  pprintf(GREEN, "%s$ ", promt[0]);
}
void printSep(void) { pprintf(BLUE, "======\n"); }

void printDebugInst(const int pc) {
  printSep();
  execInst(getInst(pc), pc + 1, 1);
  printSep();
}

void printErrorInst(const int code) {
  // if error is not arg or file error
  if (code >= 30) {
    printMsPromt();
    pprintf(BOLD, "Error caused by instruction:\n");
    printDebugInst(getPC() - 1);
  }

  printMsPromt();
  pprintf(RED, "Debugger stopped with errors\n");
}
void printNextInst(void) {
  // TODO vtl anderst lösen
  // check if debugger is still runnig
  if (debug)
    printDebugInst(getPC());
}

void debugStartMsg(const char *file, const int codeSize, const int dataSize) {
  printMsPromt();
  pprintf(BOLD, "Debugger Started\n");
  printSep();
  pprintf(YELLOW, "-- VM Informations --\n");
  pprintf(BOLD, "file  : '%s'\n", file);
  pprintf(BOLD, "code  : %d Instructions\n", codeSize);
  pprintf(BOLD, "data  : %d objects\n", dataSize);
  pprintf(BOLD, "stack : %d slots\n", getStackSize());
  pprintf(BOLD, "heap  : 2 * %d bytes\n", getHeapSize() / 2);
  pprintf(YELLOW, "-- End --\n");
  printSep();
}

void startDebug(void) {
  cmdReset();
  printNextInst();

  while (debug) {
    char input[INPUT_SIZE];

    printCmds();

    // Read input
    printPromt();
    // Rest stdin buffer
    fgets(input, INPUT_SIZE, stdin);

    // check input
    if (input == NULL)
      continue;

    findCmd(input);
  }
}