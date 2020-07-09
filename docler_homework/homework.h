#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/timeb.h>

#include <list>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <fstream>
#include <string>

#include "base/types.h"
#include "base/error.h"
#include "base/coord.h"

#include "output/ioutput.h"
#include "output/console.h"

#include "art/drawer.h"

#include "animation/animation.h"

#include "asciiart/dictionaryobject.h"
#include "asciiart/docobject.h"
#include "asciiart/document.h"
#include "asciiart/documentdrawer.h"
