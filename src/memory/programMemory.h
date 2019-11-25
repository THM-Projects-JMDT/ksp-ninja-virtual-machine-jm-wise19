#ifndef NJCM_PROGRAMMEMORY_H_INCLUDED
#define NJCM_PROGRAMMEMORY_H_INCLUDED

#include <support.h>

unsigned int getInst(const int pos);
void freeProgMem(void);
extern int memorySize;
ObjRef getGlobVar(const int pos);
void setGlobVar(const int pos, const ObjRef val);
void freeGlobVars(void);
extern int globalVarSize;
void printglobalvars(void);

void loadprog(const char *x);

#endif