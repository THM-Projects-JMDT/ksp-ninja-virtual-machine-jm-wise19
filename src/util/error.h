#ifndef NJCM_ERROR_H_INCLUDED
#define NJCM_ERROR_H_INCLUDED

void vmError(const int errc, const char *em, ...);
void stackOverflowError();
void stackUnderflowError();
void unknownInstructionError(const int optCode);
void dividedByZeroError();
void outOfMemoryError();
void invalidProgrammCodeError();
void moreThanOneInputError(const char *myself);
void invalidArgumentError(const char *myself, const char *arg);
void noPathError(const char *myself);
void invalidPathError(const char *path);
void invalidFileSizeError();
void invalidFileIdentifierError();
void invalidCodeVersionError(int fileVs, int vmVs);
void invalidGlobalVarPositionError(const int pos);
void noStackFrameAllocatedError();
void cantCloseCodeFileError();
void invalidLocalVarPositionError(const int pos);
void invalidJumpDestinationError(const int destination);

#endif