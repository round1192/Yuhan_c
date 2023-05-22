#include <stdio.h>
#include <string.h>
#include "screen.h"

int clearBuffer(char* screenBuf, int width, int height)
{
    int i = 0;
    int j = 0;
    while (j < height)
    {
        while (i < width + 1)
        {
            if (i == width)
                screenBuf[i + (j * (width + 1))] = '\n';
            else
            {
                if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
                    screenBuf[i + (j * (width + 1))] = '-';
                else
                    screenBuf[i + (j * (width + 1))] = ' ';
            }
            i = i + 1;
        }
        i = 0;
        j = j + 1;
    }

    screenBuf[height * (width + 1) - 1] = '\0';
}

int writeStringToBuffer(char* screenBuf, const char* string, int x, int y, int width)
{
    int i = 0;
    while (string[i] != '\0')
    {
        screenBuf[x + i + (y * (width + 1))] = string[i];
        i++;
    }
}

int setTitleToScreenBuffer(char* screenBuf, int width, int height)
{
    clearBuffer(screenBuf, 30, 15);
    writeStringToBuffer(screenBuf, "Eunseok's C Language", 5, 6, 30);
    writeStringToBuffer(screenBuf, "start", 13, 9, 30);
    writeStringToBuffer(screenBuf, "menu", 14, 10, 30);
    writeStringToBuffer(screenBuf, "quit", 14, 11, 30);
}

int setGameExitToScreenBuffer(char* screenBuf, int width, int height)
{
    clearBuffer(screenBuf, 30, 15);
    writeStringToBuffer(screenBuf, "Are you quit?", 10, 6, 30);
    writeStringToBuffer(screenBuf, "yes", 14, 9, 30);
    writeStringToBuffer(screenBuf, "no", 15, 10, 30);
}

int setGameMenuToScreenBuffer(char* screenBuf, int width, int height)
{
    clearBuffer(screenBuf, 30, 15);
    writeStringToBuffer(screenBuf, "Game Menu", 12, 6, 30);
    writeStringToBuffer(screenBuf, "start", 13, 9, 30);
    writeStringToBuffer(screenBuf, "quit", 14, 10, 30);
}

int main()
{
    char screenBuf[465];
    int width = 30;
    int height = 15;
    int isGamePlaying = 1;
    int isMenu = 0;
    int isQuitConfirmation = 0;
    char input[10];

    while (isGamePlaying)
    {
        if (!isMenu && !isQuitConfirmation)
            setTitleToScreenBuffer(screenBuf, width, height);
        else if (isMenu)
            setGameMenuToScreenBuffer(screenBuf, width, height);
        else if (isQuitConfirmation)
            setGameExitToScreenBuffer(screenBuf, width, height);

        printf("%s\ninput> ", screenBuf);
        scanf("%s", input);

        if (!isMenu && !isQuitConfirmation)
        {
            if (strcmp(input, "quit") == 0)
                isQuitConfirmation = 1;
            else if (strcmp(input, "menu") == 0)
            {
                isMenu = 1;
                clearBuffer(screenBuf, width, height);
            }
        }
        else if (isQuitConfirmation)
        {
            if (strcmp(input, "yes") == 0)
                isGamePlaying = 0;
            else if (strcmp(input, "no") == 0)
                isQuitConfirmation = 0;
            else if (strcmp(input, "menu") == 0)
            {
                isQuitConfirmation = 0;
                isMenu = 1;
                clearBuffer(screenBuf, width, height);
            }
        }
        else if (isMenu)
        {
            if (strcmp(input, "start") == 0)
                printf("Game started!\n");
            else if (strcmp(input, "quit") == 0)
                isQuitConfirmation = 1;
        }
    }

    return 0;
}
