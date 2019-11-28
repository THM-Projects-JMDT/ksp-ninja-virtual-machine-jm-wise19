#ifndef NJCM_INSTRUCTIONS_H_INCLUDED
#define NJCM_INSTRUCTIONS_H_INCLUDED

#include <support.h>

void printInst(char *inst, int ct);
void printInstValue(char *inst, int value, int ct);
void execHalt(void);
void execPushc(int value);
void execAdd(void);
void execSub(void);
void execMul(void);
void execDiv(void);
void execMod(void);
void execRdint(void);
void execWrint(void);
void execRdchr(void);
void execWrchr(void);
void execPushg(int n);
void execPopg(int n);
void execAsf(int n);
void execRsf(void);
void execPushl(int n);
void execPopl(int n);
void execEq(void);
void execNe(void);
void execLt(void);
void execLe(void);
void execGt(void);
void execGe(void);
void execJmp(int n);
void execBrf(int n);
void execBrt(int n);
void execCall(int n);
void execRet(void);
void execDrop(int n);
void execPushr(void);
void execPopr(void);
void execDup(void);
void execNew(int n);
void execGetf(int n);
void execPutf(int n);
void execNewa(void);
void execGetfa(void);
void execPutfa(void);
void execGetsz(void);
void execPushn(void);
void execRefeq(void);
void execRefne(void);

#endif