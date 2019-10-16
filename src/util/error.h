#ifndef NJCM_ERROR_H_INCLUDED
#define NJCM_ERROR_H_INCLUDED

void stackOverflowError();
void stackUnderflowError();
void unknownInstructionError(const int optCode);
void dividedByZeroError();

#endif