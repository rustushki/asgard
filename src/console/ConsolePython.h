#include <python2.6/Python.h>
#include "MessageFactory.h"

static PyObject*
asgard_LoadBoundingBox(PyObject* self, PyObject* args)
{
   int boundingbox_id;
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "i", &boundingbox_id))
      return Py_None;
   MessageFactory::makeLoadBoundingBox(boundingbox_id);
   return Py_None;
}

static PyMethodDef AsgardMethods[] = {
    {"LoadBoundingBox", asgard_LoadBoundingBox, METH_VARARGS,
     "Load the contents of a Bounding Box into memory."},
    {NULL, NULL, 0, NULL}
};
