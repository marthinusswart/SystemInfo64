#pragma once
#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <windows.h>
#include <string>
#include "TextWindowLib.h"

namespace SI64
{
	class SystemInfoWidget
	{
	protected:
		int _color;
		int _top;
		int _left;
		int _right;
		int _bottom;
		HANDLE _stdOut;
		std::string _title;
	public:
		SystemInfoWidget(); // Default constructor		
		SystemInfoWidget(HANDLE stdOut, std::string title, int top, int left, int bottom, int right, int color);
		virtual void onTick();
		virtual void repaint();
		bool drawFrame();
		bool drawString(std::string text, int top, int left);
	};
};

#endif
