#pragma once

#include <Windows.h>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <psapi.h>
#include <map>

#include "headers/utils/Utils.h"
#include "libs/headers/HookLib.h"
#include "headers/runtime/Logger.h"
#include "headers/segment/Segment.h"
#include "headers/utils/PanicUtils.h"
#include "headers/frameworks/GameFramework.h"
#include "headers/frameworks/SegmentFramework.h"

#pragma comment (lib, "libs/libs/HookLib.lib")