#ifndef NJVM_PRETTYPRITN_H_INCLUDED
#define NJVM_PRETTYPRITN_H_INCLUDED

#include <stdio.h>

typedef enum {
  RESET_FORMAT,
  BOLD,
  UNDERLINE = 4,
  INVERSE = 7,
  BLACK = 30,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  BG_BLACK = 40,
  BG_RED,
  BG_GREEN,
  BG_YELLOW,
  BG_BLUE,
  BG_MAGENTA,
  BG_CYAN,
  BG_WHITE,
} Formats;

void pprintf(const Formats color, const char *msg, ...);
void setFormat(FILE *stream, const Formats format);

#endif