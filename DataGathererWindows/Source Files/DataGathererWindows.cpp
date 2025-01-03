// DataGathererWindows.cpp : Defines the entry point for the console application.

/*
	Project to develop a lightweight data collector for System Information.
	Plan is to take the data and place into a SOAP request that can be used
	for ITSM tools (or other tools) like ServiceNow, &c.

	Windows Specific.

	NOTE: Manifest File in Resource Files needed to support versioning for any OS later than Windows 6.2

*/

#include "stdafx.h"
#include "resources.h" // Library inclusions, ComputerDataContainer Definition, wtos()


int main()
{

	ComputerDataContainer cdc;
	cdc.setCIComputerData();

	return 0;

}


void getCIProcessorData(ComputerDataContainer& pCdc) {

	// OEM ID, Processors, Processor Type, Page Size, Min/Max Application Address, Processor Mask
	// Structure for storing system info 
	// https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo); // Populate structure

	// Processor Architecture Check (dwOemId)
	switch (sysinfo.dwOemId) {
		case 9:
			pCdc.cpuManufacturer = "x64 (AMD or Intel)";
			break;
		case 5:
			pCdc.cpuManufacturer = "ARM";
			break;
		case 12:
			pCdc.cpuManufacturer = "ARM64";
			break;
		case 6:
			pCdc.cpuManufacturer = "Intel Itanium-based";
			break;
		case 0:
			pCdc.cpuManufacturer = "x86";
			break;
		case 0xffff:
			pCdc.cpuManufacturer = "Unknown Architecture";
			break;
		default:
			pCdc.cpuManufacturer = "Error in architecture detection.";
			break;
	}

	// Start Filling Values
	pCdc.cpuCoreCount = std::to_string(sysinfo.dwNumberOfProcessors);
	pCdc.cpuPageSize = std::to_string(sysinfo.dwPageSize);
	pCdc.cpuMask = std::to_string(sysinfo.dwActiveProcessorMask);

}


void getCIWinVersionData(ComputerDataContainer& pCdc) {
	// Helper Variables Initialized (Do Work in the Function)
	std::string osVersion{ "" };
	std::ostringstream stream; // For assistance converting DWORD to String Output

	// Get OS Version. IF >= Windows 8 Will Always Return Version 6 (Win8) unless Manifested.
	// see https://msdn.microsoft.com/en-us/library/windows/desktop/dn481241(v=vs.85).aspx

	OSVERSIONINFOEX setOSVersionInfo;
	ZeroMemory(&setOSVersionInfo, sizeof(OSVERSIONINFOEX));
	setOSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO*)&setOSVersionInfo);

	stream << setOSVersionInfo.dwMajorVersion << "." << setOSVersionInfo.dwMinorVersion << std::endl;
	pCdc.osVersion = stream.str();

	if (pCdc.osVersion == "10.0\n") {
		if (setOSVersionInfo.dwBuildNumber >= 22000) {
			pCdc.osOperatingSystem = "Windows 11";
		}
		else {
			pCdc.osOperatingSystem = "Windows 10 - Windows Server 2016";
		}
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

	pCdc.osBuildNumber = std::to_string(setOSVersionInfo.dwBuildNumber);

	if (setOSVersionInfo.szCSDVersion[0] == '\0') { // If first WCHAR* element is Null Byte...
		pCdc.osServicePack = "No Service Pack Installed.";
	}
	else if (setOSVersionInfo.szCSDVersion != nullptr) {
		pCdc.osServicePack = wtos(setOSVersionInfo.szCSDVersion);
	}
	else {
		pCdc.osServicePack = "Error identifying service pack.";
	}
}

void getCIAdapterData(ComputerDataContainer& pCdc) {
 
	// Variables
	DWORD dwSize{ 0 };
	DWORD dwReturnValue{ 0 }; // Error checking

	// TODO: Type Conversion for all members of GetAdaptersAddresses() 
	// See: http://www.rapideuphoria.com/getadaptersaddresses.ew

	// For converting LPSTR to String
	char cWsaAddressBuffer[64] = { 0 };
	DWORD dwSizeOfString{ sizeof(cWsaAddressBuffer) };
	LPWSTR lDhcpv4Server{ nullptr };


	// Getting PIP_ADAPTER_ADDRESSES data structure for parsing
	PIP_ADAPTER_ADDRESSES pAddresses{ nullptr };
	ULONG outputBuffer{ 15000000 }; // Buffer Size (Can expand if needed)
	pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, (outputBuffer));
	dwReturnValue = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr, pAddresses, &outputBuffer);

	pCdc.adapterName = pAddresses->AdapterName;
	pCdc.dhcpv4Server = WSAAddressToStringW(pAddresses->Dhcpv4Server.lpSockaddr, 14, nullptr, lDhcpv4Server, &dwSizeOfString); // TODO, lots of data still needs to be pulled out of pAddresses Struct
	pCdc.dnsDomain = wtos(pAddresses->DnsSuffix);
	pCdc.networkAdapterType = wtos(pAddresses->FriendlyName);
	pCdc.networkAdapterName = wtos(pAddresses->Description);


}

void getCIRam(ComputerDataContainer& pCdc) {

	std::string tempRam{};
	PULONGLONG memoryInKB{};
	GetPhysicallyInstalledSystemMemory(memoryInKB); // TODO: Convert from PULONGLONG to String. Wish C++20 worked :( could use std::format.

}

void getCIHostname(ComputerDataContainer& pCdc) {

	const int HOSTNAME_LENGTH{ 255 };
	char hostname[HOSTNAME_LENGTH];
	gethostname(hostname, HOSTNAME_LENGTH);
	
	pCdc.hostname = std::string(hostname);

}

void getCISerialNumber(ComputerDataContainer& pCdc) {

	/*
		getCISerialNumber(): Query the SMBIOS table and pull the Serial Number

	
	*/

}
