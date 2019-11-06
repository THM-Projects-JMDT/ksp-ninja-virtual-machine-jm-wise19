#ifndef NJCM_RUNNER_H_INCLUDED
#define NJCM_RUNNER_H_INCLUDED

void stopProgramm(void);
void changePC(const int dest);
void execList(void);
void step(void);
void execprog(void);
void execProgBreak(int b);
int getPC(void);

#endif