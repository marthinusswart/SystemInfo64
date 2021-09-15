#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include <string>
#include "MAHMSharedMemory.h"
#include "MSIAfterburnerExports.h"
#include "MSIAfterburnerMonitoringSourceDesc.h"
#include "MSIAfterburnerLibrary.h"

UINT m_nTimerID;
HANDLE m_hMapFile;
LPVOID m_pMapAddr;
int gpuTempIndex, gpuUsageIndex, gpuMemUsageIndex, gpuCoreClockIndex, gpuMemoryClockIndex, gpuFanSpeedIndex, cpuUsageIndex, cpuClockIndex, cpuTempindex, ramUsageIndex, framerateIndex;

void Connect();
void Disconnect();
void InitMeasures(DWORD gpuIndex);

bool getVersionInfo(std::string* versionInfoString)
{
	versionInfoString->append("MSI Afterburner Library Version 1.0");
	return 1;
}

bool initMSIAfterburner()
{
	if (!m_pMapAddr)
		Connect();

	if (m_pMapAddr)
		//if we're connected to shared memory, we must check if it is valid or not and reconnect if necessary
	{
		LPMAHM_SHARED_MEMORY_HEADER lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;

		if (lpHeader->dwSignature == 0xDEAD)
			//if the memory is marked as dead (e.g. MSI Afterburner was unloaded), we should disconnect from it and
			//try to connect again
			Connect();

		InitMeasures(0);
	}

	return (m_pMapAddr != NULL);
}

void Connect()
{
	Disconnect();
	//we must disconnect from the previously connected shared memory before
	//connecting to new one

	m_hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MAHMSharedMemory");

	if (m_hMapFile)
		m_pMapAddr = MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

void Disconnect()
{
	if (m_pMapAddr)
		UnmapViewOfFile(m_pMapAddr);

	m_pMapAddr = NULL;

	if (m_hMapFile)
   	 CloseHandle(m_hMapFile);

	m_hMapFile = NULL;
}

void InitMeasures(DWORD gpuIndex)
{
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	//get ptr to the current GPU entry		

	DWORD dwSources = lpHeader->dwNumEntries;

	for (DWORD dwSource = 0; dwSource < dwSources; dwSource++)
	{
		LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + dwSource * lpHeader->dwEntrySize);
		//get ptr to the current data source entry

		switch (lpEntry->dwSrcId)
		{
		case MONITORING_SOURCE_ID_GPU_TEMPERATURE:
			gpuTempIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_FAN_SPEED:
			gpuFanSpeedIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_CORE_CLOCK:
			gpuCoreClockIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_MEMORY_CLOCK:
			gpuMemoryClockIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_GPU_USAGE:
			gpuUsageIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_MEMORY_USAGE:
			gpuMemUsageIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_FRAMERATE:
			framerateIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_CPU_TEMPERATURE:
			cpuTempindex = dwSource;
			break;
		case MONITORING_SOURCE_ID_CPU_USAGE:
			if (strcmp(lpEntry->szSrcName, "CPU usage") == 0)
			{
				cpuUsageIndex = dwSource;
			}
			break;
		case MONITORING_SOURCE_ID_RAM_USAGE:
			ramUsageIndex = dwSource;
			break;
		case MONITORING_SOURCE_ID_CPU_CLOCK:
			cpuClockIndex = dwSource;
			break;
		}

	}
}

float getGPUTemperature()
{
	int gpuIndex = 0;
	int measureIndex = gpuTempIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getGPUFanspeed()
{
	int gpuIndex = 0;
	int measureIndex = gpuFanSpeedIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getGPUCoreClock()
{
	int gpuIndex = 0;
	int measureIndex = gpuCoreClockIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getGPUMemoryClock()
{
	int gpuIndex = 0;
	int measureIndex = gpuMemoryClockIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getGPUUsage()
{
	int gpuIndex = 0;
	int measureIndex = gpuUsageIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getGPUMemoryUsage()
{
	int gpuIndex = 0;
	int measureIndex = gpuMemUsageIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getFramerate()
{
	int gpuIndex = 0;
	int measureIndex = framerateIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getCPUTemperature()
{
	int gpuIndex = 0;
	int measureIndex = cpuTempindex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getCPUUsage()
{
	int gpuIndex = 0;
	int measureIndex = cpuUsageIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getRAMUsage()
{
	int gpuIndex = 0;
	int measureIndex = ramUsageIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

float getCPUClock()
{
	int gpuIndex = 0;
	int measureIndex = cpuClockIndex;
	LPMAHM_SHARED_MEMORY_HEADER	lpHeader = (LPMAHM_SHARED_MEMORY_HEADER)m_pMapAddr;
	LPMAHM_SHARED_MEMORY_GPU_ENTRY	lpGpuEntry = (LPMAHM_SHARED_MEMORY_GPU_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + lpHeader->dwNumEntries * lpHeader->dwEntrySize + gpuIndex * lpHeader->dwGpuEntrySize);
	LPMAHM_SHARED_MEMORY_ENTRY	lpEntry = (LPMAHM_SHARED_MEMORY_ENTRY)((LPBYTE)lpHeader + lpHeader->dwHeaderSize + measureIndex * lpHeader->dwEntrySize);

	return lpEntry->data;
}

