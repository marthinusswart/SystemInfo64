#pragma once
#pragma once
#ifndef MSIGPUINFOWIDGET_H
#define MSIGPUINFOWIDGET_H

#include <windows.h>
#include <string>
#include "TextWindowLib.h"
#include "SystemInfoWidget.h"
#include "MSIAfterburnerPlugin.h"

namespace SI64
{
	class MSIGPUInfoWidget : public SystemInfoWidget
	{
	protected:
		MSIAfterburnerPlugin* _msiPlugin;
		void drawDetail();
	public:
		MSIGPUInfoWidget() : SystemInfoWidget() {}; // Default constructor		
		MSIGPUInfoWidget(HANDLE stdOut, std::string title, int top, int left, int bottom, int right, int color) : SystemInfoWidget(stdOut, title, top, left, bottom, right, color) {};
		void onTick();
		void repaint();
		void setMSIPlugin(MSIAfterburnerPlugin* msiPlugin);
	};
};

#endif