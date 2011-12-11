#include "externals.h"
#include "Map.h"
#include "Database.h"

static PyObject*
asgard_LoadBoundingBox(PyObject* self, PyObject* args)
{
   int x;
   int y;
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "ii", &x, &y))
      return Py_None;
   Database::getInstance()->loadBoundingBox(x, y);
   return Py_None;
}

static PyObject*
asgard_LoadDrawable(PyObject* self, PyObject* args)
{
   char *drawableName = new char[50];
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "s", &drawableName))
      return Py_None;
   Database::getInstance()->loadDrawable(drawableName);
   return Py_None;
}

static PyMethodDef AsgardMethods[] = {
    {"LoadBoundingBox", asgard_LoadBoundingBox, METH_VARARGS,
     "Load the contents of a Bounding Box into memory."},
    {"LoadDrawable", asgard_LoadDrawable, METH_VARARGS,
     "Load a Drawable and Display it."},
    {NULL, NULL, 0, NULL}
};

static PyObject*
map_SetFocus(PyObject* self, PyObject* args)
{
   int x;
   int y;
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "ii", &x, &y))
      return Py_None;
   Map::getInstance()->setFocusPoint(x, y);
   return Py_None;
}

static PyMethodDef MapMethods[] = {
    {"SetFocus", map_SetFocus, METH_VARARGS,
     "Change the center of the Map."},
    {NULL, NULL, 0, NULL}
};
