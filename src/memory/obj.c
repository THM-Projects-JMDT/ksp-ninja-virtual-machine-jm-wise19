#include "obj.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

ObjRef newIntObj(int value) {
  ObjRef objRef = malloc(sizeof(unsigned int) + sizeof(int));

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  objRef->size = sizeof(int);
  *(int *)objRef->data = value;

  return objRef;
}