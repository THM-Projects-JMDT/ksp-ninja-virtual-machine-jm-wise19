#ifndef NJVM_DEBUGCMDs_H_INCLUDED
#define NJVM_DEBUGCMDs_H_INCLUDED

#include "debugCmdDef.h"

void printCmds();
void findCmd(char *input);
void setActCmds(int count, debugCmd newCmds[], char *command);

#endif