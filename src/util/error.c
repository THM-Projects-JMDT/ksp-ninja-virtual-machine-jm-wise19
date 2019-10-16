#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void vmError(const int errc, const char *em, ...) {
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

void stackOverflowError() { vmError(101, "stackOverflowError"); }
void emptyStackError() { vmError(102, "emtyStackError"); }
void unknownInstructionError(const int optCode) {
  vmError(103, "Opcode '%d' does not exist\n", optCode);
}
