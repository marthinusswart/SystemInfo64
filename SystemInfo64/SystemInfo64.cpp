// SystemInfo64.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <wincon.h>
#include <thread>
#include "Ticker.h"
#include "TextWindowLib.h"
#include "SystemInfoWidget.h"
#include "MSIAfterburnerPlugin.h"
#include "MSICPUInfoWidget.h"
#include "MSIGPUInfoWidget.h"

void initWindow();
void keyEventProc(KEY_EVENT_RECORD ker, HANDLE handle, std::string* input);

int main()
{    
    HANDLE stdIn, stdOut;
    DWORD numRead, i;
    INPUT_RECORD irInBuf[128];
    int counter = 0;
    stdIn = GetStdHandle(STD_INPUT_HANDLE);
    stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SI64::MSIAfterburnerPlugin msiPlugin;
    SI64::MSICPUInfoWidget cpuWidget(stdOut, "CPU Information", 0, 0, 5, 27, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
    SI64::MSIGPUInfoWidget gpuWidget(stdOut, "GPU Information", 0, 28, 5, 55, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN);
    SI64::Ticker t(2500);      

    if ( (stdIn == INVALID_HANDLE_VALUE) || (stdOut == INVALID_HANDLE_VALUE) )
    {
        return 1;
    }
    
    t.start(); 
    cpuWidget.setMSIPlugin(&msiPlugin);
    gpuWidget.setMSIPlugin(&msiPlugin);    
    cpuWidget.repaint();   
    gpuWidget.repaint();
    
    //tempStr = std::to_string((int)msiPlugin.getGPUTemperature());
    //gpuWidget.drawString(tempStr, 1, 90);
    

    if (!SetConsoleTitle(L"System Info 64"))
    {
        _tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
        return 1;
    }

    do
    {
        //Input Loop
        /*
        switch (WaitForSingleObject(stdIn, 3000))
        {
        case(WAIT_TIMEOUT):
            break; // return from this function to allow thread to terminate
        case(WAIT_OBJECT_0):
            if (!ReadConsoleInput(
                stdIn,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &numRead)) // number of records read
            {
                return 1;
            }
            break;
        }

        // Dispatch the events to the appropriate handler.
        for (i = 0; i < numRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
            case KEY_EVENT: // keyboard input
                //KeyEventProc(irInBuf[i].Event.KeyEvent, hConsole, &input_string);
                break;

            case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                //ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
                break;

            }

        }
        numRead = 0;
        */

        t.get_tick();
        if (t.updated())
        {
            //tempStr = std::to_string((int)msiPlugin.getCPUTemperature());
            cpuWidget.onTick();
            gpuWidget.onTick();

            //tempStr = std::to_string((int)msiPlugin.getGPUTemperature());
            //gpuWidget.drawString(tempStr, 1, 90);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } while (true);
}



void initWindow()
{
    const HWND hWnd = GetConsoleWindow();
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    RECT rect;
    GetWindowRect(hWnd, &rect);

    if (!MoveWindow(hWnd, rect.left, rect.top, 1000, 500, TRUE))
    {
        //printf("SetConsoleWindowInfo (%d)\n", GetLastError());
        std::cout << "Failed to resize: " << GetLastError() << "\n";
    }
}

VOID keyEventProc(KEY_EVENT_RECORD ker, HANDLE handle, std::string* input)
{
    if (ker.bKeyDown)
    {
        if (ker.wVirtualKeyCode == VK_UP)
        {            
        }
        else if (ker.wVirtualKeyCode == VK_DOWN)
        {            
        }
        else if (ker.wVirtualKeyCode == VK_RETURN)
        {
        }
        else
        {
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
