#include "debugger.h"
#include "../Interpreter/interpreter.h"
#include "../Memory/programMemory.h"
#include "../runner/runner.h"
#include "../util/prettyPrint.h"
#include "commands/debugCmdDef.h"
#include "commands/debugCmds.h"
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 20

static int runDebug = 1;
char *promt[2] = {"NJVM-DEBUG"};

void stopDebugging() { runDebug = 0; }

// TODo change
void setSubPromt(char *sub) { promt[1] = sub; }

void printMsPromt() {
  pprintf(GREEN, "[%s] ", promt[0]);
  if (promt[1] != NULL)
    pprintf(GREEN, "[%s] ", promt[1]);
}
void printPromt() {
  if (promt[1] != NULL)
    pprintf(GREEN, "%s@", promt[1]);

  pprintf(GREEN, "%s$ ", promt[0]);
}
void printSep() { pprintf(BLUE, "======\n"); }
void printNextInst() {
  printSep();
  execInst(getInst(getPC()), getPC() + 1, 1);
  printSep();
}

void showFileLoaded(const int codeSize, const int dataSize) {
  printMsPromt();
  printf("code file ");
  pprintf(BOLD, "'test.bin'");
  printf(" loaded (code size = %d, data size = %d)\n", codeSize, dataSize);
}

void startDebug() {
  cmdReset();
  printNextInst();

  // Debug Loop
  while (runDebug) {
    char input[INPUT_SIZE];

    printCmds();

    // Read input
    printPromt();
    fgets(input, INPUT_SIZE, stdin);

    // check input
    if (input == NULL)
      continue;

    findCmd(input);
  }
}