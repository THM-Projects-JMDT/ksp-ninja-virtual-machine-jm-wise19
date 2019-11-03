#ifndef NJVM_DEBUGGER_H_INCLUDED
#define NJVM_DEBUGGER_H_INCLUDED

#include <stdio.h>

void showFileLoaded(const int codeSize, const int dataSize);
void startDebug();
void printSep();
void printPromt();
void printMsPromt();
void setSubPromt(char *new);
void resetSubPromt();

#endif