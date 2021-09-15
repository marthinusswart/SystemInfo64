#pragma once
#ifndef MSIAFTERBURNERPLUGIN_H
#define MSIAFTERBURNERPLUGIN_H

#include <windows.h>
#include <string>

namespace SI64
{
	//MSI Afterburner
	typedef BOOL(*GETVERSIONINFO)(std::string*);
	typedef BOOL(*INITMSIAFTERBURNER)(void);
	typedef FLOAT(*GETGPUTEMPERATURE)(void);
	typedef FLOAT(*GETGPUFANSPEED)(void);
	typedef FLOAT(*GETGPUCORECLOCK)(void);
	typedef FLOAT(*GETGPUMEMORYCLOCK)(void);
	typedef FLOAT(*GETGPUUSAGE)(void);
	typedef FLOAT(*GETGPUMEMORYUSAGE)(void);
	typedef FLOAT(*GETFRAMERATE)(void);
	typedef FLOAT(*GETCPUTEMPERATURE)(void);
	typedef FLOAT(*GETCPUUSAGE)(void);
	typedef FLOAT(*GETRAMUSAGE)(void);
	typedef FLOAT(*GETCPUCLOCK)(void);

	class MSIAfterburnerPlugin
	{
	protected:
		GETVERSIONINFO _getVersionInfo;    // Function pointer
		INITMSIAFTERBURNER _initMSIAfterburner; // Function pointer
		GETGPUTEMPERATURE _getGPUTemperature;
		GETGPUFANSPEED _getGPUFanspeed;
		GETGPUCORECLOCK _getGPUCoreClock;
		GETGPUMEMORYCLOCK _getGPUMemoryClock;
		GETGPUUSAGE _getGPUUsage;
		GETGPUMEMORYUSAGE _getGPUMemoryUsage;
		GETFRAMERATE _getFramerate;
		GETCPUTEMPERATURE _getCPUTemperature;
		GETCPUUSAGE _getCPUUsage;
		GETRAMUSAGE _getRAMUsage;
		GETCPUCLOCK _getCPUClock;

		bool _wasInitialised = false;
		int initMSIAfterburnerPlugin();		
	public:
		MSIAfterburnerPlugin(); // Default constructor
		float getGPUTemperature();
		float getGPUFanspeed();
		float getGPUCoreClock();
		float getGPUMemoryClock();
		float getGPUUsage();
		float getGPUMemoryUsage();
		float getFramerate();
		float getCPUTemperature();
		float getCPUUsage();
		float getRAMUsage();
		float getCPUClock();

	};
};

#endif
