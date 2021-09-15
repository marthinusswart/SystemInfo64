#include "SystemInfoWidget.h"

SI64::SystemInfoWidget::SystemInfoWidget()
{

}

SI64::SystemInfoWidget::SystemInfoWidget(HANDLE stdOut, std::string title, int top, int left, int bottom, int right, int color)
{
	_top = top;
	_bottom = bottom;
	_left = left;
	_right = right;
	_color = color;
	_stdOut = stdOut;
	_title = title;
}

void SI64::SystemInfoWidget::onTick()
{
}

void SI64::SystemInfoWidget::repaint()
{
}

bool SI64::SystemInfoWidget::drawFrame()
{
	bool success = SI64::DrawFrame(_stdOut, _top, _left, _bottom, _right, _color);
	if (success)
	{
		success = SI64::DrawString(_stdOut, _title, _top, _left+1, _color);
	}
	return success;
}

bool SI64::SystemInfoWidget::drawString(std::string text, int top, int left)
{
	bool success = SI64::DrawString(_stdOut, text, top, left, _color);	
	return success;
}