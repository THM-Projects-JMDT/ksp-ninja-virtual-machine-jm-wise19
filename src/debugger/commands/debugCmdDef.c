#include "debugCmdDef.h"
#include "../../Memory/programMemory.h"
#include "../../Memory/stack.h"
#include "../../runner/runner.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmds.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Helper vars
static int breakPoint = -1;

// Init Declaration
void cmdReset();
int checkChar(char *input, char *cmd);
int checkInt(char *input, char *cmd);

// Sub Commands
// Inspect Sub
void cmdStack(char *self, char *input) {
  printSep();
  pprintf(YELLOW, "-- Stack --\n");
  printStack(0);
  pprintf(YELLOW, "-- bottom of Stack --\n");
  cmdReset();
}
void cmdData(char *self, char *input) {
  printSep();
  pprintf(YELLOW, "----Beginn of Data----\n");
  printglobalvars();
  pprintf(YELLOW, "----End of Data----\n");

  cmdReset();
}
void cmdFrame(char *self, char *input) {
  printSep();
  pprintf(YELLOW, "-- Current Stack Frame --\n");
  printStack(1);
  pprintf(YELLOW, "-- bottom of Frame --\n");
  cmdReset();
}

// Breakpoint Sub
void cmdAddress(char *self, char *input) {
  breakPoint = atoi(input);
  printMsPromt();
  pprintf(YELLOW, "breakpoint now set at %d\n", breakPoint);
  cmdReset();
}
void cmdClear(char *self, char *input) {
  breakPoint = -1;
  printMsPromt();
  pprintf(YELLOW, "breakpoint now cleared\n");
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

  // Print current breakpoint
  printMsPromt();
  pprintf(YELLOW, "Current Breakpoint: ");

  if (breakPoint == -1)
    pprintf(YELLOW, "cleared\n");
  else
    pprintf(YELLOW, "%d\n", breakPoint);
}
void cmdStep(char *self, char *input) {
  step();
  // Todo if somethig was printed print \n and vlt. sepeareter
}
void cmdRun(char *self, char *input) { execProgBreak(breakPoint); }

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