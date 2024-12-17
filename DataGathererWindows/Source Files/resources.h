#pragma once
#include <string>
#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <Psapi.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

struct ComputerDataContainer;
void getCIProcessorData(ComputerDataContainer& pCdc);
void getCIWinVersionData(ComputerDataContainer& pCdc);
void getCIAdapterData(ComputerDataContainer& pCdc);
void getCIRam(ComputerDataContainer& pCdc);
void getCISerialNumber(ComputerDataContainer& pCdc);

struct ComputerDataContainer {

	// Constructor
	ComputerDataContainer() {};
	// Destructor
	~ComputerDataContainer() {};

	std::string
		adapterName,
		firstDnsServerAddress,
		physicalAddress,
		ddnsEnabled,
		dhcpv4Enabled,
		noMulticast,
		netbiosOverTcpEnabled,
		ipv4Enabled,
		ipv6Enabled,
		mtu,
		ifType,
		operationStatus,
		firstWinsServerAddress,
		firstGatewayAddress,
		luid,
		dhcpv4Server,
		networkGuid,
		connectionType,
		tunnelType,
		dhcpv6Server,
		dhcpv6ClientDuid,
		osOperatingSystem,
		osVersion,
		osBuildNumber,
		osServicePack,
		cpuName,
		cpuManufacturer,
		cpuMask,
		cpuSpeed, // MHZ
		cpuCoreCount,
		cpuCoreThread,
		cpuPageSize,
		cpuType,
		ram, // KB
		hostname,
		dnsDomain,
		osDomain,
		assignedTo,
		department,
		description,
		manufacturer,
		serial,
		diskType,
		diskDescription,
		diskSpace, // GB Total
		freeSpace, // GB Free
		diskName, // C: D: &c
		volumeSerialNumber,
		runningProcessNames,
		runningProcessCommand,
		runningProcessConnectsTo,
		runningProcessListensOn,
		runningProcessType,
		runningProcessPID,
		runningProcessParams,
		networkAdapterName,
		networkAdapterType,
		networkAdapterIP,
		networkAdapterMAC,
		networkAdapterNetmask,
		networkAdapterDHCPEnabled,
		networkAdapterVendor,
		modelID;

	void setCIComputerData() {
		getCIProcessorData(*this);
		getCIWinVersionData(*this);
		getCIAdapterData(*this);

	}

};

std::string wtos(wchar_t* pStr){

	/* 
		WCHAR to String Converter, thank god for that.
	*/

	std::string newStr;
	while (*pStr)
		newStr += (char)*pStr++;
	return newStr;
}
