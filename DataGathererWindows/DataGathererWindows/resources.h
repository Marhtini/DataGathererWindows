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

//Declaration of C++ Functions in DataGathererWindows.cpp
void setCIComputerData();
std::vector<std::string> getCIHardwareData(std::vector<std::string> pMasterCIHardwareDataVector);
std::vector<std::string> getCIComputerData(std::vector<std::string> pMasterCIComputerDataVector);
std::vector<std::string> getCIWinVersionData(std::vector<std::string> pMasterCIWinVersionDataVector);
std::vector<std::string> getCIWinServerData(std::vector<std::string> pMasterCIWinServerDataVector);
std::vector<std::string> getCIDiskData(std::vector<std::string> pMasterCIDiskDataVector);
std::vector<std::string> getCIProcessData(std::vector<std::string> pMasterCIProcessDataVector);
std::vector<std::string> getCINetworkData(std::vector<std::string> pMasterCINetworkDataVector);
std::vector<std::string> getCIModelData(std::vector<std::string> pMasterCIModelDataVector);
