#include "debugger.h"
#include "../runner/runner.h"
#include "../util/prettyPrint.h"
#include <stdio.h>

#define PROMT "NJVM-DEBUG"

void printMsPromt() { pprintf(GREEN, "%s: ", PROMT); }
void printPromt() { pprintf(GREEN, "%s$ ", PROMT); }
void printSep() { pprintf(BLUE, "======\n"); }

void showFileLoaded(const int codeSize, const int dataSize) {
  printMsPromt();
  printf("code file ");
  pprintf(BOLD, "'test.bin'");
  printf(" loaded (code size = %d, data size = %d)\n", codeSize, dataSize);
}

void startDebug() {
  int myInt;

  printSep();
  pprintf(BOLD, "0000:\trdint\n");
  printSep();

  printMsPromt();
  pprintf(BOLD, "inspect, list, breakpoint, step, run, quit?\n");

  printPromt();
  scanf("%d", &myInt);

  printSep();
  execList();
  printSep();
}