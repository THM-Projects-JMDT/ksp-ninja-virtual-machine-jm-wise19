#include "debugCmdDef.h"
#include "../../runner/runner.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmds.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Init Declaration
void cmdReset();
int checkChar(char *input, char *cmd);
int checkInt(char *input, char *cmd);

// Sub Commands
// Inspect Sub
void cmdStack(char *self, char *input) {
  printf("cmdStack\n");
  cmdReset();
}
void cmdData(char *self, char *input) {
  printf("cmdData\n");
  cmdReset();
}
void cmdFrame(char *self, char *input) {
  printf("cmdFrame\n");
  cmdReset();
}

// Breakpoint Sub
void cmdAddress(char *self, char *input) {
  printf("cmdAddress %d\n", atoi(input));
  cmdReset();
}
void cmdClear(char *self, char *input) {
  printf("cmdClear\n");
  cmdReset();
}

// Sub Commands Arrays
debugCmd inspectSubCmds[] = {{"stack", checkChar, cmdStack},
                             {"frame", checkChar, cmdFrame},
                             {"data", checkChar, cmdData},
                             {"quit", checkChar, cmdReset}};
int inspectSubCount = 4;
debugCmd breakpointSubCmds[] = {{"address to set", checkInt, cmdAddress},
                                {"clear", checkChar, cmdClear},
                                {"quit", checkChar, cmdReset}};
int breakpointSubCount = 3;

// Commands
void cmdInspect(char *self, char *input) {
  setActCmds(inspectSubCount, inspectSubCmds, self);
}
void cmdList(char *self, char *input) {
  printSep();
  pprintf(YELLOW, "-- Program Code --\n");
  execList();
  pprintf(YELLOW, "-- end of Code --\n");
}
void cmdBreakpoint(char *self, char *input) {
  setActCmds(breakpointSubCount, breakpointSubCmds, self);

  printMsPromt();
  // TODO print seted Breakpoints
  pprintf(YELLOW, "Current Breakpoints: cleared\n");
}
void cmdStep(char *self, char *input) { printf("cmdStep\n"); }
void cmdRun(char *self, char *input) { printf("cmdRun\n"); }

// Command Help functions
int checkChar(char *input, char *cmd) { return cmd[0] == input[0]; }
int checkInt(char *input, char *cmd) { return isdigit(input[0]); }

// Commands Array
debugCmd cmds[] = {{"inspect", checkChar, cmdInspect, 1},
                   {"list", checkChar, cmdList},
                   {"breakpoint", checkChar, cmdBreakpoint, 1},
                   {"step", checkChar, cmdStep},
                   {"run", checkChar, cmdRun},
                   {"quit", checkChar, stopDebugging}};
int cmdsCount = 6;

// Reset Function
void cmdReset() { setActCmds(cmdsCount, cmds, NULL); }