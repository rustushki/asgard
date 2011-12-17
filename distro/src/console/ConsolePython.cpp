#include "ConsolePython.h"

/* Initialize Asgard's Python Interface.  It starts by starting Python.  Then
 * it creates Asgards modules based on the PyMethodDef objects define in
 * ConsolePython.h
 *
 * @return void
 */
void InitAsgardPython() {
   // Initialize Python
   Py_Initialize();

   // Some error handling.
   if (Py_IsInitialized() != true) {
      std::cout << "Python failed to initialize." << std::endl;

      // TODO: Remove this exit() in favor of a systemic system exitter.
      exit(0);
   }

   // Initialize Asgard's Modules.
   Py_InitModule("asgard", AsgardMethods);
   Py_InitModule("map",    MapMethods);
}

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
