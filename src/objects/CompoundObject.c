#include "CompoundObject.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

ObjRef newCompoundObject(int numObjRefs) {
  // u int size + pointer size
  ObjRef objRef = malloc(sizeof(unsigned int) + numObjRefs * sizeof(NULL));

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  // set size to numObjRefs and set MSB to 1
  objRef->size = numObjRefs | 0x80000000;

  return objRef;
}

void checkIsCompundObject(ObjRef obj) {
  if (obj == NULL)
    ilegalNilRefecenceError();

  // If is no CompundObject -> error
  if (!Get_MSB(obj->size))
    notACompundObjectError();
}