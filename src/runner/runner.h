#ifndef NJCM_RUNNER_H_INCLUDED
#define NJCM_RUNNER_H_INCLUDED

void stopProgramm();
void changePC(const int dest);
void execList();
void step();
void execprog();
void execProgBreak(int b);
int getPC();

#endif