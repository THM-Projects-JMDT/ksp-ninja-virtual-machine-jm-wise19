#include "debugCmdDef.h"
#include "../runner/runner.h"
#include "debugInput.h"
#include "debugger.h"
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
void breakpointSubCmd(char *self) {
  printf("breakpointSubCmd\n");
  cmdReset();
}

// Sub Commands Arrays
debugCmd inspectSubCmds[] = {
    {"stack", cmdStack}, {"data", cmdData}, {"quit", cmdReset}};
int inspectSubCount = 3;
debugCmd breakpointSubCmds[] = {{"t", breakpointSubCmd}, {"quit", cmdReset}};
int breakpointSubCount = 2;

// Commands
void cmdInspect(char *self) {
  setActCmds(inspectSubCount, inspectSubCmds, self);
}
void cmdList(char *self) {
  printSep();
  execList();
  printSep();
}
void cmdBreakpoint(char *self) {
  setActCmds(breakpointSubCount, breakpointSubCmds, self);
}
void cmdStep(char *self) { printf("cmdStep\n"); }
void cmdRun(char *self) { printf("cmdRun\n"); }

// Commands Array
debugCmd cmds[] = {
    {"inspect", cmdInspect}, {"list", cmdList}, {"breakpoint", cmdBreakpoint},
    {"step", cmdStep},       {"run", cmdRun},   {"quit", stopDebugging}};
int cmdsCount = 6;

// Reset Function
void cmdReset() { setActCmds(cmdsCount, cmds, NULL); }