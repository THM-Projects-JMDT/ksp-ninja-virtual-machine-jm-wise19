/*
 * interpreter.h -- All functions that determine which instruction to execute
 */

#ifndef NJCM_INTERPRETER_H_INCLUDED
#define NJCM_INTERPRETER_H_INCLUDED

void execInst(const unsigned int inst, const int counter, const int dpMode);

#endif