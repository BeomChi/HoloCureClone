#pragma once


#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "Defines.h"
#include "Utils.h"

#define NOMINMAX
#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <random>
#include <iostream>
#include <format>
#include <filesystem>




using namespace std;

namespace fs = std::filesystem;

#pragma comment(lib, "Msimg32.lib")


#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// »ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dsound.lib")