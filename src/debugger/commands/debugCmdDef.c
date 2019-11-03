#include "debugCmdDef.h"
#include "../../runner/runner.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmds.h"
#include <stdio.h>

// Init Declaration
void cmdReset();

// Sub Commands
// Inspect Sub
void cmdStack(char *self) {
  printf("cmdStack\n");
  cmdReset();
}
void cmdData(char *self) {
  printf("cmdData\n");
  cmdReset();
}

// Breakpoint Sub
void cmdAddress(char *self) {
  printf("cmdAddress\n");
  cmdReset();
}
void cmdClear(char *self) {
  printf("cmdClear\n");
  cmdReset();
}

// Sub Commands Arrays
debugCmd inspectSubCmds[] = {
    {"stack", cmdStack}, {"data", cmdData}, {"quit", cmdReset}};
int inspectSubCount = 3;
debugCmd breakpointSubCmds[] = {
    {"address to set", cmdAddress}, {"clear", cmdClear}, {"quit", cmdReset}};
int breakpointSubCount = 3;

// Commands
void cmdInspect(char *self) {
  setActCmds(inspectSubCount, inspectSubCmds, self);
}
void cmdList(char *self) {
  printSep();
  pprintf(BLUE, "-- Program Code --\n");
  execList();
  pprintf(BLUE, "-- end of Code --\n");
}
void cmdBreakpoint(char *self) {
  setActCmds(breakpointSubCount, breakpointSubCmds, self);

  printMsPromt();
  // TODO print seted Breakpoints
  pprintf(BOLD, "Current Breakpoints: cleared\n");
}
void cmdStep(char *self) { printf("cmdStep\n"); }
void cmdRun(char *self) { printf("cmdRun\n"); }

// Commands Array
debugCmd cmds[] = {{"inspect", cmdInspect, 1},
                   {"list", cmdList},
                   {"breakpoint", cmdBreakpoint, 1},
                   {"step", cmdStep},
                   {"run", cmdRun},
                   {"quit", stopDebugging}};
int cmdsCount = 6;

// Reset Function
void cmdReset() { setActCmds(cmdsCount, cmds, NULL); }