// DataGathererWindows.cpp : Defines the entry point for the console application.

/*
	Project to develop a lightweight data collector for System Information.
	Plan is to take the data and place into a SOAP request that can be used
	for ITSM tools (or other tools) like ServiceNow, &c.

	Windows Specific.

	NOTE: Manifest File in Resource Files needed to support versioning for any OS later than Windows 6.2

*/

#include "stdafx.h"
#include "resources.h" // Tons of Resources


int main()
{
	// Initialize Master Data Vector

	std::vector<std::vector<std::string>> masterCIDataVector;
	setCIComputerData(masterCIDataVector);

	
	return 0;

}

void setCIComputerData(std::vector<std::vector<std::string>> pMasterCIDataVector) {
	// Collect all vectors from other data and put into master vector

	getCIHardwareData(pMasterCIDataVector);
	getCIComputerData(pMasterCIDataVector);
	getCIWinVersionData(pMasterCIDataVector);
	getCIWinServerData(pMasterCIDataVector);
	getCIDiskData(pMasterCIDataVector);
	getCIProcessData(pMasterCIDataVector);
	getCINetworkData(pMasterCIDataVector);
	getCIModelData(pMasterCIDataVector);

}

std::vector<std::string> getCIHardwareData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

	// Variables
	DWORD dwSize = 0;
	DWORD dwReturnValue = 0; // Error checking
	std::vector<std::string> ciHardwareVector; // Returnable Vector

// TODO: Type Conversion for all members of GetAdaptersAddresses() 
// See: http://www.rapideuphoria.com/getadaptersaddresses.ew
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
		dhcpv6ClientDuid;

	// For converting LPSTR to String
	char cWsaAddressBuffer[64] = { 0 };
	DWORD dwSizeOfString = sizeof(cWsaAddressBuffer);
	LPWSTR lDhcpv4Server = NULL;


	// Getting PIP_ADAPTER_ADDRESSES data structure for parsing
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	ULONG outputBuffer = 15000000; // Buffer Size (Can expand if needed)
	pAddresses = (IP_ADAPTER_ADDRESSES *)HeapAlloc(GetProcessHeap(), 0, (outputBuffer));
	dwReturnValue = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &outputBuffer);
	
	// Start Filling Values
	adapterName = pAddresses->AdapterName;
	//dhcpv4Server = WSAAddressToStringW(pAddresses->Dhcpv4Server.lpSockaddr, 14, NULL, lDhcpv4Server, &dwSizeOfString);   //TODO: LNK2019 Error, unresolved external symbol __imp_WSAAddressToStringW 
	
	// std::cout << lDhcpv4Server; TODO: See Above ^ ^
	return ciHardwareVector;

}

std::vector<std::string> getCIComputerData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

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


std::vector<std::string> getCIWinVersionData(std::vector<std::vector<std::string>> pMasterCIDataVector) {
	// Helper Variables Initialized (Do Work in the Function)
	std::string osVersion = "";
	std::ostringstream stream; // For assistance converting DWORD to String Output

	// Vector Init
	std::vector<std::string> ciWinVersionDataVector;

	// Output Parameter Variables (p) to be sent to getCIComputerData()
	std::string pOSOperatingSystem = "";

	// Get OS Version. IF >= Windows 8 Will Always Return Version 6 (Win8) unless Manifested.
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

	ciWinVersionDataVector.push_back(pOSOperatingSystem);

	return ciWinVersionDataVector;
}


std::vector<std::string> getCIWinServerData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

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


std::vector<std::string> getCIDiskData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

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

std::vector<std::string> getCIProcessData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

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

std::vector<std::string> getCINetworkData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

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

std::vector<std::string> getCIModelData(std::vector<std::vector<std::string>> pMasterCIDataVector) {

	std::string modelID;
	std::vector<std::string> ciDataVector;
	ciDataVector.push_back(modelID);

	return ciDataVector;

}