/*
 * debugCmdDef.h -- All functions that execute the debug commands and the debug
 * command definitions
 */

#ifndef NJVM_DEBUGCmdDef_H_INCLUDED
#define NJVM_DEBUGCmdDef_H_INCLUDED

typedef struct {
  char command[30];
  int (*check)(char *, char *);
  void (*action)(char *, char *);
  int hasSubCmd;
} DebugCmd;

void cmdReset();

#endif