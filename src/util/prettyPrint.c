/*
 * prettyPrint.c -- Functions for formatted prints
 */

#include "prettyPrint.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void setFormat(FILE *stream, const Formats format) {
  fprintf(stream, "\033[%dm", format);
}

void pprintf(const Formats format, const char *msg, ...) {
  va_list parms;

  // Change Color
  setFormat(stdout, format);

  // print String with parms
  va_start(parms, msg);
  vprintf(msg, parms);
  va_end(parms);

  // Reset Color
  setFormat(stdout, RESET_FORMAT);
}