#ifndef NJVM_DEBUGCmdDef_H_INCLUDED
#define NJVM_DEBUGCmdDef_H_INCLUDED

typedef struct
{
  char command[30];
  void (*action)(char *);
} debugCmd;

void cmdReset();

#endif