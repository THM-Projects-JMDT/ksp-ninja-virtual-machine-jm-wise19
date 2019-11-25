#include "../../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <support.h>

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef = malloc(sizeof(unsigned int) + sizeof(int));

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  objRef->size = sizeof(int);

  return objRef;
}

void fatalError(char *msg) { /*TODO*/
}