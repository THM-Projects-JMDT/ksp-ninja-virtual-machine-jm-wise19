/*
 * error.h -- Functions for all errors cases
 */

#ifndef NJCM_ERROR_H_INCLUDED
#define NJCM_ERROR_H_INCLUDED

void vmError(const int errc, const char *em, ...);
void stackOverflowError(void);
void stackUnderflowError(void);
void popNoObjRefError(void);
void localNoObjRefError(const int var);
void noIntError(void);
void unknownInstructionError(const int optCode);
void dividedByZeroError(void);
void outOfMemoryError(void);
void invalidProgrammCodeError(void);
void moreThanOneInputError(const char *myself);
void invalidArgumentError(const char *myself, const char *arg);
void noPathError(const char *myself);
void invalidPathError(const char *path);
void invalidFileSizeError(void);
void invalidFileIdentifierError(void);
void invalidCodeVersionError(int fileVs, int vmVs);
void invalidGlobalVarPositionError(const int pos);
void noStackFrameAllocatedError(void);
void cantCloseCodeFileError(void);
void invalidJumpDestinationError(const int destination);
void ilegalNilRefecenceError(void);
void notACompundObjectError(void);
void indexOutofBoundsError(const int size, const int index);
void argumentNoInteger(const char *myself);
void missingArgument(const char *myself);

#endif