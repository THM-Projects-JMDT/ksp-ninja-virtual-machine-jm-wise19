#include "../../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <support.h>

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef = malloc(sizeof(unsigned int) + dataSize);

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  objRef->size = dataSize;

  return objRef;
}

void fatalError(char *msg) { vmError(55, msg); }