#ifndef NJCM_INSTRUCTIONS_H_INCLUDED
#define NJCM_INSTRUCTIONS_H_INCLUDED

void printInst(char *inst, int ct);
void printInstValue(char *inst, int value, int ct);
void execHalt();
void execPushc(int value);
void execAdd();
void execSub();
void execMul();
void execDiv();
void execMod();
void execRdint();
void execWrint();
void execRdchr();
void execWrchr();
void execPushg(int n);
void execPopg(int n);
void execAsf(int n);
void execRsf();
void execPushl(int n);
void execPopl(int n);

#endif