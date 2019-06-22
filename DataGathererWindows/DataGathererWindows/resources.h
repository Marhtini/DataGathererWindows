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
void setCIComputerData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIHardwareData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIComputerData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIWinVersionData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIWinServerData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIDiskData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIProcessData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCINetworkData(std::vector<std::vector<std::string>> pMasterCIDataVector);
std::vector<std::string> getCIModelData(std::vector<std::vector<std::string>> pMasterCIDataVector);
