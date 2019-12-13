/*
 * support.c -- object representation and support functions
 */

#include "../../memory/heap.h"
#include "../../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <support.h>

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef = allocOnHeap(sizeof(unsigned int) + dataSize);

  objRef->size = dataSize;

  return objRef;
}

void fatalError(char *msg) { vmError(54, msg); }