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
#include <Psapi.h>
#pragma comment(lib, "Iphlpapi.lib")

struct ComputerDataContainer;
void getCIHardwareData(ComputerDataContainer& pCdc);
void getCIWinVersionData(ComputerDataContainer& pCdc);
SYSTEM_INFO prepareSysinfo();

struct ComputerDataContainer {

	// Constructor
	ComputerDataContainer() {};
	// Destructor
	~ComputerDataContainer() {};

	std::string
		adapterName,
		firstUnicastAddress,
		firstMulticastAddress,
		firstDnsServerAddress,
		// dnsSuffix, TODO: PWCHAR to String
		// description, TODO: PWCHAR to String
		// friendlyName, TODO: PWCHAR to String
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
		osServicePack,
		osName,
		cpuName,
		cpuManufacturer,
		cpuMask,
		cpuSpeed, // MHZ
		cpuCount,
		cpuCoreCount,
		cpuCoreThread,
		cpuPageSize,
		cpuType,
		ram, // MB
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
		networkAdapterIP,
		networkAdapterMAC,
		networkAdapterNetmask,
		networkAdapterDHCPEnabled,
		networkAdapterVendor,
		modelID;

	void setCIComputerData(ComputerDataContainer& pCdc) {
		getCIHardwareData(pCdc);
		getCIWinVersionData(pCdc);

	}

};