#include "MSICPUInfoWidget.h"

void SI64::MSICPUInfoWidget::onTick()
{
    drawDetail();
}

void SI64::MSICPUInfoWidget::repaint()
{
    drawFrame();
    drawString("CPU Temperature", _top + 1, _left + 1);
    drawString("CPU Core Clock", _top + 2, _left + 1);
    drawString("CPU Usage", _top + 3, _left + 1);
    drawString("RAM Usage", _top + 4, _left + 1);
    drawDetail();    
}

void SI64::MSICPUInfoWidget::setMSIPlugin(MSIAfterburnerPlugin* msiPlugin)
{
    _msiPlugin = msiPlugin;
}

void SI64::MSICPUInfoWidget::drawDetail()
{
    if (_msiPlugin != NULL)
    {
        std::string tempStr = std::to_string((int)_msiPlugin->getCPUTemperature());
        tempStr.append(" C");
        drawString(tempStr, _top + 1, _left + 18);

        tempStr = std::to_string((int)_msiPlugin->getCPUClock());
        tempStr.append(" MHz");
        drawString(tempStr, _top + 2, _left + 18);

        float value = _msiPlugin->getCPUUsage();
        char str[10];
        sprintf_s(str, "%.1f", value);
        tempStr = str;
        tempStr.append(" %  ");
        drawString(tempStr, _top + 3, _left + 18);

        tempStr = std::to_string((int)_msiPlugin->getRAMUsage());
        tempStr.append(" MB");
        drawString(tempStr, _top + 4, _left + 18);
    }
}