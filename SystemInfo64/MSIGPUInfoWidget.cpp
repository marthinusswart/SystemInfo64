#include "MSIGPUInfoWidget.h"

void SI64::MSIGPUInfoWidget::onTick()
{
    drawDetail();
}

void SI64::MSIGPUInfoWidget::repaint()
{
    drawFrame();
    drawString("GPU Temperature", _top + 1, _left + 1);
    drawString("GPU Core Clock", _top + 2, _left + 1);
    drawString("GPU Mem Clock", _top + 3, _left + 1);
    drawString("GPU Usage", _top + 4, _left + 1);    
    drawDetail();
}

void SI64::MSIGPUInfoWidget::setMSIPlugin(MSIAfterburnerPlugin* msiPlugin)
{
    _msiPlugin = msiPlugin;
}

void SI64::MSIGPUInfoWidget::drawDetail()
{
    if (_msiPlugin != NULL)
    {
        std::string tempStr = std::to_string((int)_msiPlugin->getGPUTemperature());
        tempStr.append(" C");
        drawString(tempStr, _top + 1, _left + 18);

        tempStr = std::to_string((int)_msiPlugin->getGPUCoreClock());
        tempStr.append(" MHz");
        drawString(tempStr, _top + 2, _left + 18);

        tempStr = std::to_string((int)_msiPlugin->getGPUMemoryClock());
        tempStr.append(" MHz");
        drawString(tempStr, _top + 3, _left + 18);

        float value = _msiPlugin->getGPUUsage();
        char str[10];
        sprintf_s(str, "%.1f", value);
        tempStr = str;
        tempStr.append(" %  ");
        drawString(tempStr, _top + 4, _left + 18);

        
    }
}