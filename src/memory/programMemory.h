#ifndef NJCM_PROGRAMMEMORY_H_INCLUDED
#define NJCM_PROGRAMMEMORY_H_INCLUDED

unsigned int getInst(const int pos);
void freeProgMem(void);
extern int memorySize;
int getGlobVar(const int pos);
void setGlobVar(const int pos, const int val);
void freeGlobVars(void);
extern int globalVarSize;
void printglobalvars(void);

void loadprog(const char *x);

#endif