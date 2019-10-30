#ifndef NJCM_PROGRAMMEMORY_H_INCLUDED
#define NJCM_PROGRAMMEMORY_H_INCLUDED

unsigned int getInst(const int pos);
void freeProgMem();
extern int memorySize;
int getGlobVar(const int pos);
void setGlobVar(const int pos, const int val);
void freeGlobVars();
extern int globalVarSize;

void loadprog(const char *x);

#endif