/*
 * debugger.h -- Main debugger Loop and debugger help functions
 */

#ifndef NJVM_DEBUGGER_H_INCLUDED
#define NJVM_DEBUGGER_H_INCLUDED

#include <stdio.h>

void showFileLoaded(const int codeSize, const int dataSize);
void startDebug(void);
void printSep(void);
void printPromt(void);
void printMsPromt(void);
void setSubPromt(char *new);
void resetSubPromt(void);
void printErrorInst(const int code);
void printNextInst(void);
void stopDebugging();

#endif