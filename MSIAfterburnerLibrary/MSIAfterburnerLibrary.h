#pragma once
#ifdef MSIAFTERBURNERLIBRARY_EXPORTS
#define MSIAFTERBURNERLIBRARY_API __declspec(dllexport)
#else
#define MSIAFTERBURNERLIBRARY_API __declspec(dllimport)
#endif

#include <string>

extern "C" MSIAFTERBURNERLIBRARY_API bool getVersionInfo(std::string * versionInfoString);
extern "C" MSIAFTERBURNERLIBRARY_API bool initMSIAfterburner();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUTemperature();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUFanspeed();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUCoreClock();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUMemoryClock();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUUsage();
extern "C" MSIAFTERBURNERLIBRARY_API float getGPUMemoryUsage();
extern "C" MSIAFTERBURNERLIBRARY_API float getFramerate();
extern "C" MSIAFTERBURNERLIBRARY_API float getCPUTemperature();
extern "C" MSIAFTERBURNERLIBRARY_API float getCPUUsage();
extern "C" MSIAFTERBURNERLIBRARY_API float getRAMUsage();
extern "C" MSIAFTERBURNERLIBRARY_API float getCPUClock();