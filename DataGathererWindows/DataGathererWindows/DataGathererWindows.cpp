// DataGathererWindows.cpp : Defines the entry point for the console application.

/*
	Project to develop a lightweight data collector for System Information.
	Plan is to take the data and place into a SOAP request that can be used
	for ITSM tools (or other tools) like ServiceNow, &c.

	Windows Specific.

	NOTE: Manifest File in Resource Files needed to support versioning for any OS later than Windows 6.2

*/

#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

//Declarations
void setCIComputerData();

int main()
{
	setCIComputerData();
	system("PAUSE"); // Breakpoint DEBUG ONLY
	return 0;

}

void temporaryPrint(std::vector<std::string> &readThisVector) {

	for (int i = 0; i < readThisVector.size(); i++) {
		std::cout << readThisVector.at(i) << ' ';
	}

}

std::vector<std::string> getCIHardware() {

	std::string networkAdapterDefaultGateway;
	std::vector<std::string> ciHardwareVector;
	ciHardwareVector.push_back(networkAdapterDefaultGateway);

	return ciHardwareVector;

}

std::vector<std::string> getCIComputerData() {

	std::string osOperatingSystem,
		osVersion,
		osServicePack,
		osName,
		cpuName,
		cpuManufacturer,
		cpuSpeed, // MHZ
		cpuCount,
		cpuCoreCount,
		cpuCoreThread,
		ram; // MB

	std::vector<std::string> ciComputerDataVector;
	ciComputerDataVector.push_back(osOperatingSystem);
	ciComputerDataVector.push_back(osVersion);
	ciComputerDataVector.push_back(osServicePack);
	ciComputerDataVector.push_back(osName);
	ciComputerDataVector.push_back(cpuName);
	ciComputerDataVector.push_back(cpuManufacturer);
	ciComputerDataVector.push_back(cpuSpeed);
	ciComputerDataVector.push_back(cpuCount);
	ciComputerDataVector.push_back(cpuCoreCount);
	ciComputerDataVector.push_back(cpuCoreThread);
	ciComputerDataVector.push_back(ram);

	return ciComputerDataVector;

}

void setCIComputerData() {

	// Helper Variables Initialized (Do Work in the Function)
	std::string osVersion = "";
	std::ostringstream stream; // For assistance converting DWORD to String Output

	// Output Parameter Variables (p) to be sent to getCIComputerData()
	std::string pOSOperatingSystem = "";

	// Get OS Version. IF >= Windows 8 Will Always Return Version 6 (Win8) unless Manifested. TODO: MANIFEST APPLICATION TO SUPPORT WIN 8.1 - 10
	// see https://msdn.microsoft.com/en-us/library/windows/desktop/dn481241(v=vs.85).aspx

	OSVERSIONINFO setOSVersionInfo;
	ZeroMemory(&setOSVersionInfo, sizeof(OSVERSIONINFO));
	setOSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&setOSVersionInfo);

	stream << setOSVersionInfo.dwMajorVersion << "." << setOSVersionInfo.dwMinorVersion << std::endl;
	osVersion = stream.str();
	if (osVersion == "10.0\n") {
		pOSOperatingSystem = "Windows 10 - Windows Server 2016";
	}
	else if (osVersion == "6.3\n") {
		pOSOperatingSystem = "Windows 8.1 - Windows Server 2012 R2";
	}
	else if (osVersion == "6.2\n") {
		pOSOperatingSystem = "Windows 8 - Windows Server 2012";
	}
	else if (osVersion == "6.1\n") {
		pOSOperatingSystem = "Windows 7 - Windows Server 2008 R2";
	}
	else if (osVersion == "6.0\n") {
		pOSOperatingSystem = "Windows Vista - Windows Server 2008";
	}
	else if (osVersion == "5.2\n") {
		pOSOperatingSystem = "Windows XP 64-Bit Edition - Windows Server 2003";
	}
	else if (osVersion == "5.1\n") {
		pOSOperatingSystem = "Windows XP";
	}
	else if (osVersion == "5.0\n") {
		pOSOperatingSystem = "Windows 2000";
	}
	else {
		pOSOperatingSystem = "ERROR: Version Unknown or Older than Windows 2000";
	}

	// TODO: Remove This Debug Line
	std::cout << pOSOperatingSystem + "\n"; // DEBUG

}


std::vector<std::string> getCIWinServerData() {

	std::string hostname,
		dnsDomain,
		osDomain,
		assignedTo,
		department,
		description,
		manufacturer,
		serial;

	std::vector<std::string> ciWinServerDataVector;
	ciWinServerDataVector.push_back(hostname);
	ciWinServerDataVector.push_back(dnsDomain);
	ciWinServerDataVector.push_back(osDomain);
	ciWinServerDataVector.push_back(assignedTo);
	ciWinServerDataVector.push_back(department);
	ciWinServerDataVector.push_back(description);
	ciWinServerDataVector.push_back(manufacturer);
	ciWinServerDataVector.push_back(serial);

	return ciWinServerDataVector;

}

std::vector<std::string> getCIDiskData() {

	std::string diskType,
		diskDescription,
		diskSpace, // GB Total
		freeSpace, // GB Free
		diskName, // C: D: &c
		volumeSerialNumber;

	std::vector<std::string> ciDiskDataVector;
	ciDiskDataVector.push_back(diskType);
	ciDiskDataVector.push_back(diskDescription);
	ciDiskDataVector.push_back(diskSpace);
	ciDiskDataVector.push_back(freeSpace);
	ciDiskDataVector.push_back(diskName);
	ciDiskDataVector.push_back(volumeSerialNumber);

	return ciDiskDataVector;

}

std::vector<std::string> getCIProcessData() {

	std::string runningProcessNames,
		runningProcessCommand,
		runningProcessConnectsTo,
		runningProcessListensOn,
		runningProcessType,
		runningProcessPID,
		runningProcessParams;

	std::vector<std::string> ciProcessDataVector;
	ciProcessDataVector.push_back(runningProcessNames);
	ciProcessDataVector.push_back(runningProcessCommand);
	ciProcessDataVector.push_back(runningProcessConnectsTo);
	ciProcessDataVector.push_back(runningProcessListensOn);
	ciProcessDataVector.push_back(runningProcessType);
	ciProcessDataVector.push_back(runningProcessPID);
	ciProcessDataVector.push_back(runningProcessParams);

	return ciProcessDataVector;

}

std::vector<std::string> getCINetworkData() {

	std::string networkAdapterName,
		networkAdapterIP,
		networkAdapterMAC,
		networkAdapterNetmask,
		networkAdapterDHCPEnabled,
		networkAdapterVendor;

	std::vector<std::string> ciNetworkDataVector;
	ciNetworkDataVector.push_back(networkAdapterName);
	ciNetworkDataVector.push_back(networkAdapterIP);
	ciNetworkDataVector.push_back(networkAdapterMAC);
	ciNetworkDataVector.push_back(networkAdapterNetmask);
	ciNetworkDataVector.push_back(networkAdapterDHCPEnabled);
	ciNetworkDataVector.push_back(networkAdapterVendor);

	return ciNetworkDataVector;

}

std::vector<std::string> getCIData() {

	std::string modelID;
	std::vector<std::string> ciDataVector;
	ciDataVector.push_back(modelID);

	return ciDataVector;

}