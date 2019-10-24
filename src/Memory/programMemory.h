#ifndef NJCM_PROGRAMMEMORY_H_INCLUDED
#define NJCM_PROGRAMMEMORY_H_INCLUDED

extern unsigned int *programMemory;
extern int memorySize;
extern int *globalvars;
extern int globalVarSize;

void loadprog(const char *x);

#endif