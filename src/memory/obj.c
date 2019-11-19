#include "obj.h"
#include <stdio.h>
#include <stdlib.h>

ObjRef createObjRef(unsigned int size) {
  ObjRef objRef = malloc(sizeof(unsigned int) + size);
  objRef->size = size;

  return objRef;
}

ObjRef createObjRefInt(int value) {
  ObjRef objRef = createObjRef(sizeof(int));
  *(int *)objRef->data = value;

  return objRef;
}

ObjRef createObjRefChar(char value) {
  ObjRef objRef = createObjRef(sizeof(char));
  *(char *)objRef->data = value;

  return objRef;
}

ObjRef createObjRefBool(bool value) {
  ObjRef objRef = createObjRef(sizeof(bool));
  *(bool *)objRef->data = value;

  return objRef;
}