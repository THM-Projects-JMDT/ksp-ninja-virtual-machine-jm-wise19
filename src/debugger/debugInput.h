#ifndef NJVM_DEBUGINPUT_H_INCLUDED
#define NJVM_DEBUGINPUT_H_INCLUDED

#include "debugCmdDef.h"

void stopDebugging();
void cmdLoop();
void printCmds();
void findCmd(char *input);
void setActCmds(int count, debugCmd newCmds[], char *command);

#endif