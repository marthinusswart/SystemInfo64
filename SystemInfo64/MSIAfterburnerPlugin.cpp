#include "MSIAfterburnerPlugin.h"

SI64::MSIAfterburnerPlugin::MSIAfterburnerPlugin()
{
    initMSIAfterburnerPlugin();
}

int SI64::MSIAfterburnerPlugin::initMSIAfterburnerPlugin()
{
    HINSTANCE hDLL;               // Handle to DLL
    HRESULT hrReturnVal;
    std::string version_string = "";

    hDLL = LoadLibrary(L"MSIAfterburnerLibrary");
    if (NULL != hDLL)
    {
        _getVersionInfo = (GETVERSIONINFO)GetProcAddress(hDLL, "getVersionInfo");
        if (NULL != _getVersionInfo)
        {
            // call the function
            if (!_getVersionInfo(&version_string))
            {
                return 1;
            }
            else
            {                
                _initMSIAfterburner = (INITMSIAFTERBURNER)GetProcAddress(hDLL, "initMSIAfterburner");
                if (!_initMSIAfterburner())
                {
                    return 1;
                }   

                _getGPUTemperature = (GETGPUTEMPERATURE)GetProcAddress(hDLL, "getGPUTemperature");
                _getGPUFanspeed = (GETGPUFANSPEED)GetProcAddress(hDLL, "getGPUFanspeed");
                _getGPUCoreClock = (GETGPUCORECLOCK)GetProcAddress(hDLL, "getGPUCoreClock");
                _getGPUMemoryClock = (GETGPUMEMORYCLOCK)GetProcAddress(hDLL, "getGPUMemoryClock");
                _getGPUUsage = (GETGPUUSAGE)GetProcAddress(hDLL, "getGPUUsage");
                _getGPUMemoryUsage = (GETGPUMEMORYUSAGE)GetProcAddress(hDLL, "getGPUMemoryUsage");
                _getFramerate = (GETFRAMERATE)GetProcAddress(hDLL, "getFramerate");
                _getCPUTemperature = (GETCPUTEMPERATURE)GetProcAddress(hDLL, "getCPUTemperature");
                _getCPUUsage = (GETCPUUSAGE)GetProcAddress(hDLL, "getCPUUsage");
                _getRAMUsage = (GETRAMUSAGE)GetProcAddress(hDLL, "getRAMUsage");
                _getCPUClock = (GETCPUCLOCK)GetProcAddress(hDLL, "getCPUClock");
            }
        }
        else
        {            
            // report the error
            hrReturnVal = ERROR_DELAY_LOAD_FAILED;
        }
    }
    else
    {
        return 1;
    }

    _wasInitialised = true;
    return 0;
}

float SI64::MSIAfterburnerPlugin::getGPUTemperature()
{
    return _getGPUTemperature();
}
float SI64::MSIAfterburnerPlugin::getGPUFanspeed()
{
    return _getGPUFanspeed();
}
float SI64::MSIAfterburnerPlugin::getGPUCoreClock()
{
    return _getGPUCoreClock();
}
float SI64::MSIAfterburnerPlugin::getGPUMemoryClock()
{
    return _getGPUMemoryClock();
}
float SI64::MSIAfterburnerPlugin::getGPUUsage()
{
    return _getGPUUsage();
}
float SI64::MSIAfterburnerPlugin::getGPUMemoryUsage()
{
    return _getGPUMemoryUsage();
}
float SI64::MSIAfterburnerPlugin::getFramerate()
{
    return _getFramerate();
}
float SI64::MSIAfterburnerPlugin::getCPUTemperature()
{
    return _getCPUTemperature();
}
float SI64::MSIAfterburnerPlugin::getCPUUsage()
{
    return _getCPUUsage();
}
float SI64::MSIAfterburnerPlugin::getRAMUsage()
{
    return _getRAMUsage();
}
float SI64::MSIAfterburnerPlugin::getCPUClock()
{
    return _getCPUClock();
}