#include "obj.h"
#include <stdio.h>
#include <stdlib.h>

ObjRef newIntObj(int value) {
  ObjRef objRef = malloc(sizeof(unsigned int) + sizeof(int));
  objRef->size = sizeof(int);
  *(int *)objRef->data = value;

  return objRef;
}