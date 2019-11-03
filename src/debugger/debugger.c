#include "debugger.h"
#include "../util/prettyPrint.h"
#include "debugCmdDef.h"
#include "debugInput.h"
#include <stdio.h>
#include <string.h>

char *promt[2] = {"NJVM-DEBUG"};

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

void showFileLoaded(const int codeSize, const int dataSize) {
  printMsPromt();
  printf("code file ");
  pprintf(BOLD, "'test.bin'");
  printf(" loaded (code size = %d, data size = %d)\n", codeSize, dataSize);
}

void startDebug() {
  cmdReset();
  cmdLoop();

  /*

  printSep();
  pprintf(BOLD, "0000:\trdint\n");
  printSep();

  printSep();
  execList();
  printSep(); */
}