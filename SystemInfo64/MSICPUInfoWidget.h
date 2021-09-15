#pragma once
#ifndef MSICPUINFOWIDGET_H
#define MSICPUINFOWIDGET_H

#include <windows.h>
#include <string>
#include "TextWindowLib.h"
#include "SystemInfoWidget.h"
#include "MSIAfterburnerPlugin.h"

namespace SI64
{
	class MSICPUInfoWidget : public SystemInfoWidget
	{
	protected:
		MSIAfterburnerPlugin* _msiPlugin;
		void drawDetail();
	public:
		MSICPUInfoWidget() : SystemInfoWidget() {}; // Default constructor		
		MSICPUInfoWidget(HANDLE stdOut, std::string title, int top, int left, int bottom, int right, int color) : SystemInfoWidget(stdOut, title, top, left, bottom, right, color) {};
		void onTick();	
		void repaint();
		void setMSIPlugin(MSIAfterburnerPlugin* msiPlugin);
	};
};

#endif