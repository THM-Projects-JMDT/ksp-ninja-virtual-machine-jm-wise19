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

  exit(errc);
}

void stackOverflowError() { vmError(1, "stackOverflowError\n"); }
void stackUnderflowError() { vmError(2, "stackUnderflowError\n"); }
void unknownInstructionError(const int optCode) {
  vmError(103, "Opcode '%d' does not exist\n", optCode);
}
void dividedByZeroError() { vmError(3, "dividedByZeroError\n"); }
void outOfMemoryError() { vmError(4, "Vm run out of Memory\n"); }
void invalidProgrammCodeError() { vmError(5, "No program selected\n"); }