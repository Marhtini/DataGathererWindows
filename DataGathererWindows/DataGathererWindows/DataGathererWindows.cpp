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
		cpuSpeed, // MHZ
		cpuCount,
		cpuCoreCount,
		cpuCoreThread,
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

	void setCIComputerData(ComputerDataContainer &pCdc) {
		getCIHardwareData(pCdc);
		getCIWinVersionData(pCdc);
		
	}
	
};


int main()
{

	ComputerDataContainer cdc;

	ComputerDataContainer *pCdc { &cdc };

	cdc.setCIComputerData(*pCdc);

	return 0;

}

void getCIHardwareData(ComputerDataContainer& pCdc) {

	// Variables
	DWORD dwSize{ 0 };
	DWORD dwReturnValue{ 0 }; // Error checking
	 
	// TODO: Type Conversion for all members of GetAdaptersAddresses() 
	// See: http://www.rapideuphoria.com/getadaptersaddresses.ew
	

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
	pCdc.adapterName = pAddresses->AdapterName;
	//dhcpv4Server = WSAAddressToStringW(pAddresses->Dhcpv4Server.lpSockaddr, 14, NULL, lDhcpv4Server, &dwSizeOfString);   //TODO: LNK2019 Error, unresolved external symbol __imp_WSAAddressToStringW 

}


void getCIWinVersionData(ComputerDataContainer& pCdc) {
	// Helper Variables Initialized (Do Work in the Function)
	std::string osVersion{ "" };
	std::ostringstream stream; // For assistance converting DWORD to String Output

	// Get OS Version. IF >= Windows 8 Will Always Return Version 6 (Win8) unless Manifested.
	// see https://msdn.microsoft.com/en-us/library/windows/desktop/dn481241(v=vs.85).aspx

	OSVERSIONINFO setOSVersionInfo;
	ZeroMemory(&setOSVersionInfo, sizeof(OSVERSIONINFO));
	setOSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&setOSVersionInfo);

	stream << setOSVersionInfo.dwMajorVersion << "." << setOSVersionInfo.dwMinorVersion << std::endl;
	pCdc.osVersion = stream.str();

	if (pCdc.osVersion == "10.0\n") {
		pCdc.osOperatingSystem = "Windows 10 - Windows Server 2016";
	}
	else if (pCdc.osVersion == "6.3\n") {
		pCdc.osOperatingSystem = "Windows 8.1 - Windows Server 2012 R2";
	}
	else if (pCdc.osVersion == "6.2\n") {
		pCdc.osOperatingSystem = "Windows 8 - Windows Server 2012";
	}
	else if (pCdc.osVersion == "6.1\n") {
		pCdc.osOperatingSystem = "Windows 7 - Windows Server 2008 R2";
	}
	else if (pCdc.osVersion == "6.0\n") {
		pCdc.osOperatingSystem = "Windows Vista - Windows Server 2008";
	}
	else if (pCdc.osVersion == "5.2\n") {
		pCdc.osOperatingSystem = "Windows XP 64-Bit Edition - Windows Server 2003";
	}
	else if (pCdc.osVersion == "5.1\n") {
		pCdc.osOperatingSystem = "Windows XP";
	}
	else if (pCdc.osVersion == "5.0\n") {
		pCdc.osOperatingSystem = "Windows 2000";
	}
	else {
		pCdc.osOperatingSystem = "ERROR: Version Unknown or Older than Windows 2000";
	}

}
