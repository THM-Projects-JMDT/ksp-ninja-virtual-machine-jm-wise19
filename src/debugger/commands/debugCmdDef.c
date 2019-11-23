#include "debugCmdDef.h"
#include "../../memory/obj.h"
#include "../../memory/programMemory.h"
#include "../../memory/stack.h"
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
void cmdObject(char *self, char *input) {
  pprintf(BLACK, "Object Refernece?\n");
  void *p = NULL;
  scanf("%p", &p);
  printSep();
  pprintf(YELLOW, "-- Object --\n");
  // TODO check if pointer is valid
  // TODO mit nicht int Werte
  pprintf(BOLD, "%p -> %d\n", p, *(int *)((ObjRef)p)->data);

  pprintf(YELLOW, "-- End of Object --\n");
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
DebugCmd inspectSubCmds[] = {{"stack", checkChar, cmdStack},
                             {"frame", checkChar, cmdFrame},
                             {"data", checkChar, cmdData},
                             {"object", checkChar, cmdObject},
                             {"quit", checkChar, cmdReset}};
int inspectSubCount = 5;
DebugCmd breakpointSubCmds[] = {{"address to set", checkInt, cmdAddress},
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
DebugCmd cmds[] = {{"inspect", checkChar, cmdInspect, 1},
                   {"list", checkChar, cmdList},
                   {"breakpoint", checkChar, cmdBreakpoint, 1},
                   {"step", checkChar, cmdStep},
                   {"run", checkChar, cmdRun},
                   {"quit", checkChar, stopDebugging}};
int cmdsCount = 6;

// Reset Function (no (void) -> to use it in the DebugCmd struct)
void cmdReset() { setActCmds(cmdsCount, cmds, NULL); }