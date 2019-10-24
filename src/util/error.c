#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void vmError(const int errc, const char *em, ...) {
  va_list parms;

  if (errc < 10 || errc >= 20) {
    // Change the Text Color to Red
    fprintf(stderr, "\033[0;31m");

    fprintf(stderr, "An error occurred:\n");

    // Reset Text Color
    fprintf(stderr, "\033[0m");

    // Print Error code
    fprintf(stderr, "Error %d: \033[1m", errc);
  }

  // Print error
  va_start(parms, em);
  vfprintf(stderr, em, parms);
  va_end(parms);

  fprintf(stderr, "\033[0m\n");

  // Exit error
  exit(errc);
}

// Argument Errors codes 1_
void invalidArgumentError(const char *myself, const char *arg) {
  vmError(10, "unknown command line argument '%s', try '%s --help'", arg,
          myself);
}
void noPathError(const char *myself) {
  vmError(11, "no code file specified, try '%s --help'", myself);
}

// File read Errors 2_
void moreThanOneInputError() {
  vmError(20, "more than one code file specified");
}
void invalidPathError(const char *path) {
  vmError(21, "can not open code File '%s'", path);
}
// TODO vtl with line or bytes
void invalidFileSizeError() {
  vmError(22, "the document size does not correspond to the NJBF");
}
void invalidFileIdentifierError() { vmError(23, "invalid code File format"); }
void invalidCodeVersion(int fileVs, int vmVs) {
  vmError(24, "Version %d of the NJBF is not supported, please use version %d",
          fileVs, vmVs);
}

// Memory Errors 3_
void outOfMemoryError() { vmError(30, "Vm run out of Memory"); }

// Stack Errors 4_
void stackOverflowError() { vmError(40, "stackOverflowError"); }
void stackUnderflowError() { vmError(41, "stackUnderflowError"); }

// Runtime Errors 5_
void unknownInstructionError(const int optCode) {
  vmError(50, "Opcode '%d' does not exist", optCode);
}
void dividedByZeroError() { vmError(51, "dividedByZeroError"); }
void invalidProgrammCodeError() { vmError(52, "Missing 'HALT' statement"); }