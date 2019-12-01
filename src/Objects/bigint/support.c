#include "../../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <support.h>

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef = malloc(sizeof(unsigned int) + dataSize);

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  // set size to dataSize and set MSB to 0
  objRef->size = dataSize & (0xFFFFFFFF > 1);

  return objRef;
}

void fatalError(char *msg) { vmError(55, msg); }