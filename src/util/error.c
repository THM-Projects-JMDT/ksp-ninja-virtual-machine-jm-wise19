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

  setFormat(stderr, RESET_FORMAT);

  // Print Error code
  fprintf(stderr, "Error %d: ", errc);

  setFormat(stderr, BOLD);

  // Print error
  va_start(parms, em);
  vfprintf(stderr, em, parms);
  va_end(parms);

  setFormat(stderr, RESET_FORMAT);

  fprintf(stderr, "\n");

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
void invalidFileSizeError() {
  vmError(21, "the document size does not correspond to the NJBF");
}
void invalidFileIdentifierError() { vmError(22, "invalid code File format"); }
void invalidCodeVersionError(int fileVs, int vmVs) {
  vmError(23, "Version %d of the NJBF is not supported, please use version %d",
          fileVs, vmVs);
}
void cantCloseCodeFileError() { vmError(24, "cantCloseCodeFileError"); }

// Memory Errors 3x
void outOfMemoryError() { vmError(30, "Vm run out of Memory"); }

// Stack Errors 4x
void stackOverflowError() { vmError(40, "stackOverflowError"); }
void stackUnderflowError() { vmError(41, "stackUnderflowError"); }
void noStackFrameAllocatedError() {
  vmError(42, "locale variable used without reserving memory beforehand");
}

// Runtime Errors 5x
void unknownInstructionError(const int optCode) {
  vmError(50, "Opcode '%d' does not exist", optCode);
}
void dividedByZeroError() { vmError(51, "dividedByZeroError"); }
void invalidProgrammCodeError() { vmError(52, "Missing 'HALT' statement"); }
void invalidGlobalVarPositionError(const int pos) {
  vmError(53, "The global var %d does not exsist", pos);
}
void invalidLocalVarPositionError(const int pos) {
  vmError(54, "The Local var %d does not exsist", pos);
}
void invalidJumpDestinationError(const int destination) {
  vmError(55, "The Jump Destination %d is invalid", destination);
}