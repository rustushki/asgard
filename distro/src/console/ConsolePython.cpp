#include "ConsolePython.h"

PyObject* map_SetFocus(PyObject* self, PyObject* args) {
   int x;
   int y;
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "ii", &x, &y))
      return Py_None;
   Map::getInstance()->setFocusPoint(x, y);
   return Py_None;
}

PyObject* asgard_LoadBoundingBox(PyObject* self, PyObject* args) {
   int x;
   int y;
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "ii", &x, &y))
      return Py_None;
   Database::getInstance()->loadBoundingBox(x, y);
   return Py_None;
}

PyObject* asgard_LoadDrawable(PyObject* self, PyObject* args) {
   char *drawableName = new char[50];
   Py_INCREF(Py_None);
   if(!PyArg_ParseTuple(args, "s", &drawableName))
      return Py_None;
   Database::getInstance()->loadDrawable(drawableName);
   return Py_None;
}
