#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void vmError(const int errc, const char *em, ...) {
  va_list errV;

  // Change the Text Color to Red
  fprintf(stderr, "\033[0;31m");

  fprintf(stderr, "An error occurred:\n");

  // Reset Text Color
  fprintf(stderr, "\033[0m");

  // Print error
  va_start(errV, em);
  vfprintf(stderr, em, errV);
  va_end(errV);

  fprintf(stderr, "\n");

  exit(errc);
}

// TODO error codes vtl als like HTTP error
void stackOverflowError() { vmError(1, "stackOverflowError"); }
void stackUnderflowError() { vmError(2, "stackUnderflowError"); }
void unknownInstructionError(const int optCode) {
  vmError(103, "Opcode '%d' does not exist", optCode);
}
void dividedByZeroError() { vmError(3, "dividedByZeroError"); }
void outOfMemoryError() { vmError(4, "Vm run out of Memory"); }
void invalidProgrammCodeError() { vmError(5, "No program selected"); }
void moreThanOneInputError() {
  vmError(6, "more than one code file specified");
}
void noPathError() { vmError(7, "no code File specified"); }
void invalidPathError(const char *path) {
  vmError(8, "can not open code File '%s'", path);
}
// TODO vtl with line or bytes
void invalidFileSizeError() {
  vmError(9, "the document size does not correspond to the NJBF");
}
void invalidFileIdentifierError() { vmError(10, "invalid code File format"); }
void invalidCodeVersion(int fileVs, int vmVs) {
  vmError(11, "Version %d of the NJBF is not supported, please use version %d",
          fileVs, vmVs);
}