/*
 * error.c -- Functions for all errors cases
 */

#include "error.h"
#include "../debugger/debugger.h"
#include "../njvm.h"
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

  // If debug
  if (debug)
    printErrorInst(errc);

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

void argumentNoInteger(const char *arg, const char *size, const char *myself) {
  vmError(13, "illegal size '%s' for Argument '%s', try '%s --help'", size, arg,
          myself);
}

void missingArgument(const char *arg, const char *myself) {
  vmError(14, "Argument '%s' needs a size specification, try '%s --help'", arg,
          myself);
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
void outOfHeapSpaceError(void) { vmError(31, "Vm run out of Heap space"); }

// Stack Errors 4x
void stackOverflowError(void) { vmError(40, "stackOverflowError"); }
void stackUnderflowError(void) { vmError(41, "stackUnderflowError"); }
void noStackFrameAllocatedError(void) {
  vmError(42, "locale variable used without reserving memory beforehand");
}
void popNoObjRefError(void) {
  vmError(43, "Top of Stack is not from Type ObjRef");
}
void localNoObjRefError(const int var) {
  vmError(44, " %s is not from Type ObjRef",
          // Check if is var or parm
          var < 0 ? "Parameter" : "Local Variable");
}
void noIntError(void) { vmError(45, "Top of Stack is not from Type int"); }

// Runtime Errors 5x
void unknownInstructionError(const int optCode) {
  vmError(50, "Opcode '%d' does not exist", optCode);
}
void invalidProgrammCodeError(void) { vmError(51, "Missing 'HALT' statement"); }
void invalidGlobalVarPositionError(const int pos) {
  vmError(52, "The global var %d does not exsist", pos);
}
void invalidJumpDestinationError(const int destination) {
  vmError(53, "The Jump Destination %d is invalid", destination);
}
// Runtime Error 54 -> bigInt error (in Support.c)
void ilegalNilRefecenceError(void) { vmError(55, "Invalid 'nil reference'"); }
void notACompundObjectError(void) {
  vmError(
      56,
      "Invalid attempt to use a 'Primitive Object' as an 'Compound Object'");
}
void indexOutofBoundsError(const int size, const int index) {
  vmError(57, "Index %d out of bounds for length %d", index, size);
}