/*
 * compoundObject.c -- Compound Object support Functions
 */

#include "CompoundObject.h"
#include "../memory/heap.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ObjRef newCompoundObject(int numObjRefs) {
  // int size + pointer size
  ObjRef objRef =
      allocOnHeap(sizeof(unsigned int) + numObjRefs * sizeof(ObjRef));

  // set size to numObjRefs and set MSB to 1
  objRef->size = numObjRefs | MSB;

  // init filds with NULL
  memset(objRef->data, 0, numObjRefs * sizeof(ObjRef));

  return objRef;
}

void checkIsCompundObject(ObjRef obj) {
  if (obj == NULL)
    ilegalNilRefecenceError();

  // If is no CompundObject -> error
  if (IS_PRIM(obj))
    notACompundObjectError();
}

void checkIndex(ObjRef obj, int i) {
  if (GET_SIZE(obj) - 1 < i || i < 0)
    indexOutofBoundsError(GET_SIZE(obj), i);
}

int getTotalSize(ObjRef obj) {
  unsigned int size = sizeof(unsigned int);

  if (IS_PRIM(obj))
    return size + GET_SIZE(obj);

  return size + GET_SIZE(obj) * sizeof(ObjRef);
}