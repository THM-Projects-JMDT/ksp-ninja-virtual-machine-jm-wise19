#ifndef NJCM_COMPOUNDOBJECT_H_INCLUDED
#define NJCM_COMPOUNDOBJECT_H_INCLUDED

#include <Support.h>

#define GET_REF_COUNT(s) ((s) & (0xFFFFFFFF >> 1))

ObjRef newCompoundObject(int numObjRefs);

#endif