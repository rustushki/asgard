#ifndef EXTERNALS_H
#define EXTERNALS_H
typedef unsigned int uint;

// Standard Library
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <map>
#include <unistd.h>
#include <vector>


// Boost
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <boost/signals/trackable.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/thread.hpp>

// Glog
#include <glog/logging.h>

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// Python
#include <python2.7/Python.h>

// Sqlite
#include <sqlite3.h>

// Constants
const float PI = 3.14159265;

#endif//EXTERNALS_H
