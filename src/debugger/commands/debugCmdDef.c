#include "debugCmdDef.h"
#include "../../memory/programMemory.h"
#include "../../memory/stack.h"
#include "../../objects/CompoundObject.h"
#include "../../runner/runner.h"
#include "../../util/prettyPrint.h"
#include "../debugger.h"
#include "debugCmds.h"
#include <bigint.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Helper vars
static int breakPoint = -1;

// Init Declaration
void cmdReset();
int checkChar(char *input, char *cmd);
int checkInt(char *input, char *cmd);
int checkHex(char *input, char *cmd);
void cmdInspect(char *input, char *cmd);
extern DebugCmd objectSubCmds[];
extern int objectSubCount;

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
  setActCmds(objectSubCount, objectSubCmds, "inspect-object");
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

// Inspect Object sub
void cmdGetValue(char *self, char *input) {
  void *p = NULL;
  // Get Pointer from char
  sscanf(input, "%p", &p);
  printSep();

  // TODO check if pointer is valid
  if (p != NULL) {
    ObjRef obj = (ObjRef)p;
    // If is CompoundObject
    if (Get_MSB(obj->size)) {
      pprintf(YELLOW, "-- Compound Object --\n");
      setFormat(stdout, BOLD);

      for (int i = 0; i < GET_SIZE(obj->size); i++) {
        printf("obj[%04d] -> (objref) %p\n", i, (void *)CP_OBj_VALUE(obj));
      }
    } else {
      pprintf(YELLOW, "-- Primitive Object --\n");

      bip.op1 = obj;
      setFormat(stdout, BOLD);
      printf("(objref)%p -> ", p);
      bigPrint(stdout);

      printf("\n");
    }

    setFormat(stdout, RESET_FORMAT);
    pprintf(YELLOW, "-- End of Object --\n");
  }

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
                             {"object", checkChar, cmdObject, 1},
                             {"quit", checkChar, cmdReset}};
int inspectSubCount = 5;
DebugCmd objectSubCmds[] = {{"pointer to Object", checkHex, cmdGetValue},
                            {"quit", checkChar, cmdReset}};
int objectSubCount = 2;
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
int checkHex(char *input, char *cmd) { return isxdigit(input[0]); }

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