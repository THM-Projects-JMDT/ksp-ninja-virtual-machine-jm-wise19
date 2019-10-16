#ifndef NJCM_ERROR_H_INCLUDED
#define NJCM_ERROR_H_INCLUDED

void stackOverflowError();
void emptyStackError();
void unknownInstructionError(const int optCode);

#endif