#pragma once
#include <vector>
#include <string>
#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#pragma comment(lib, "Iphlpapi.lib")

struct ComputerDataContainer;
void getCIHardwareData(ComputerDataContainer& pCdc);
void getCIWinVersionData(ComputerDataContainer& pCdc);