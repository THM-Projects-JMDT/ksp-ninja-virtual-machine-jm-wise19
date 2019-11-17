#include "error.h"
#include "prettyPrint.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void vmError(const int errc, const char *em, ...) {
  va_list parms;

  setFormat(stderr, BOLD);
  setFormat(stderr, RED);

  fprintf(stderr, "An error occurred:\n");

  setFormat(stderr, BLACK);

  // Print Error code
  fprintf(stderr, "Error %d: ", errc);

  setFormat(stderr, RESET_FORMAT);

  setFormat(stderr, BOLD);

  // Print error
  va_start(parms, em);
  vfprintf(stderr, em, parms);
  va_end(parms);

  fprintf(stderr, "\n");

  setFormat(stderr, RESET_FORMAT);

  // Exit error
  exit(errc);
}

// Argument Errors codes 1x
void invalidArgumentError(const char *myself, const char *arg) {
  vmError(10, "unknown command line argument '%s', try '%s --help'", arg,
          myself);
}
void noPathError(const char *myself) {
  vmError(11, "A code file must be specified, try '%s --help'", myself);
}
void moreThanOneInputError(const char *myself) {
  vmError(12, "Only one code file may be specified, try '%s --help'", myself);
}

// File read Errors 2x
void invalidPathError(const char *path) {
  vmError(20, "can not open code File '%s'", path);
}
// TODO vtl with line or bytes
void invalidFileSizeError(void) {
  vmError(21, "the document size does not correspond to the NJBF");
}
void invalidFileIdentifierError(void) {
  vmError(22, "invalid code File format");
}
void invalidCodeVersionError(int fileVs, int vmVs) {
  vmError(23, "Version %d of the NJBF is not supported, please use version %d",
          fileVs, vmVs);
}
void cantCloseCodeFileError(void) { vmError(24, "cantCloseCodeFileError"); }

// Memory Errors 3x
void outOfMemoryError(void) { vmError(30, "Vm run out of Memory"); }

// Stack Errors 4x
void stackOverflowError(void) { vmError(40, "stackOverflowError"); }
void stackUnderflowError(void) { vmError(41, "stackUnderflowError"); }
void noStackFrameAllocatedError(void) {
  vmError(42, "locale variable used without reserving memory beforehand");
}

// Runtime Errors 5x
void unknownInstructionError(const int optCode) {
  vmError(50, "Opcode '%d' does not exist", optCode);
}
void dividedByZeroError(void) { vmError(51, "dividedByZeroError"); }
void invalidProgrammCodeError(void) { vmError(52, "Missing 'HALT' statement"); }
void invalidGlobalVarPositionError(const int pos) {
  vmError(53, "The global var %d does not exsist", pos);
}
void invalidJumpDestinationError(const int destination) {
  vmError(54, "The Jump Destination %d is invalid", destination);
}