/*
 * compoundObject.c -- Compound Object support Functions
 */

#include "CompoundObject.h"
#include "../util/error.h"
#include <stdio.h>
#include <stdlib.h>

ObjRef newCompoundObject(int numObjRefs) {
  // int size + pointer size
  ObjRef objRef = malloc(sizeof(unsigned int) + numObjRefs * sizeof(ObjRef));

  // check if malloc worked
  if (objRef == NULL)
    outOfMemoryError();

  // set size to numObjRefs and set MSB to 1
  objRef->size = numObjRefs | MSB;

  // TODO init fields with null

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