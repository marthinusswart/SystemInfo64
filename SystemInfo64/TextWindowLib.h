#pragma once
#ifndef TEXTWINDOWLIB_H
#define TEXTWINDOWLIB_H

#include <windows.h>
#include <string>

namespace SI64
{
	bool DrawFrame(HANDLE stdOut, int top, int left, int bottom, int right, int color);
	bool DrawString(HANDLE stdOut, std::string text, int top, int left, int color);
}

#endif