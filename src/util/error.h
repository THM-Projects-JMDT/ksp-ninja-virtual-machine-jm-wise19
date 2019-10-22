#ifndef NJCM_ERROR_H_INCLUDED
#define NJCM_ERROR_H_INCLUDED

void vmError(const int errc, const char *em, ...);
void stackOverflowError();
void stackUnderflowError();
void unknownInstructionError(const int optCode);
void dividedByZeroError();
void outOfMemoryError();
void invalidProgrammCodeError();
void moreThanOneInputError();

#endif