#include "TextWindowLib.h"
#include <iostream>
#include <wincon.h>

bool SI64::DrawFrame(HANDLE stdOut, int top, int left, int bottom, int right, int color)
{
    // Get console info
    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(stdOut, &conInfo);
    SetConsoleTextAttribute(stdOut, color);

    COORD currentPos = conInfo.dwCursorPosition;
    COORD newPos;
    newPos.X = left;
    newPos.Y = top;

    BOOL success = SetConsoleCursorPosition(stdOut, newPos);
    if (success)
    {
        for (int lines = top; lines <= bottom; lines++)
        {
            for (int i = left; i <= right; i++)
            {
                if (lines == top)
                {                   
                    if (i == left)
                    {
                        std::cout << char(213);
                    }
                    else if (i == right)
                    {
                        std::cout << char(184);
                    }
                    else
                    {
                        std::cout << char(205);
                    }

                } 
                else if (lines == bottom)
                {
                    if (i == left)
                    {
                        std::cout << char(212);
                    }
                    else if (i == right)
                    {
                        std::cout << char(190);
                    }
                    else
                    {
                        std::cout << char(205);
                    }

                }
                else if ((lines != top) && (lines != bottom))
                {
                    if ((i == left) || (i == right))
                    {
                        std::cout << char(179);
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }
            }

            newPos.X = left;
            newPos.Y++;
            success = SetConsoleCursorPosition(stdOut, newPos);
            if (!success)
            {
                return success;
            }
        }

        success = SetConsoleCursorPosition(stdOut, currentPos);
    }

    return success;
}

bool SI64::DrawString(HANDLE stdOut, std::string text, int top, int left, int color)
{
    // Get console info
    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(stdOut, &conInfo);
    SetConsoleTextAttribute(stdOut, color);

    COORD currentPos = conInfo.dwCursorPosition;
    COORD newPos;
    newPos.X = left;
    newPos.Y = top;

    BOOL success = SetConsoleCursorPosition(stdOut, newPos);
    if (success)
    {
        std::cout << text;
        success = SetConsoleCursorPosition(stdOut, currentPos);
    }

    return success;
}
