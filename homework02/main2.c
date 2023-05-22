#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"

#define MAX_INPUT_LENGTH 10

void drawTitleScreen(char* screenBuf, int width, int height);
void drawInGameScreen(char* screenBuf, int width, int height);

int main()
{
	char screenBuf[35 * 12 + 1];
	int width = 34;
	int height = 12;
	int isGamePlaying = 1;

	char input[MAX_INPUT_LENGTH];
	int isInGame = 0;

	while (isGamePlaying)
	{
		clearBuffer(screenBuf, width, height);

		if (!isInGame)
		{
			drawTitleScreen(screenBuf, width, height);

			system("cls");
			printf("%s\ninput> ", screenBuf);
			scanf("%s", input);

			if (strcmp(input, "start") == 0)
				isInGame = 1;
			else if (strcmp(input, "quit") == 0)
				isGamePlaying = 0;
		}
		else
		{
			drawInGameScreen(screenBuf, width, height);

			system("cls");
			printf("%s\ninput> ", screenBuf);
			scanf("%s", input);

			if (strcmp(input, "quit") == 0)
				isInGame = 0;
		}
	}

	return 0;
}

void drawTitleScreen(char* screenBuf, int width, int height)
{
	int centerRow = height / 2;
	int centerCol = width / 2;
	char* title = "Eunseok's C Language";
	char* startButton = "start";
	char* quitButton = "quit";
	int titleLength = strlen(title);
	int buttonLength = strlen(startButton);

	int titleStartCol = centerCol - (titleLength / 2);
	int buttonStartCol = centerCol - (buttonLength / 2);

	int i, j;

	for (i = 0; i < width; i++)
	{
		if (i >= buttonStartCol && i < buttonStartCol + buttonLength)
		{
			if (i == buttonStartCol || i == buttonStartCol + buttonLength - 1)
				screenBuf[i + centerRow * (width + 1)] = '|';
			else
				screenBuf[i + centerRow * (width + 1)] = startButton[i - buttonStartCol];
		}
		else if (i >= titleStartCol && i < titleStartCol + titleLength)
		{
			screenBuf[i + (centerRow - 1) * (width + 1)] = title[i - titleStartCol];
		}
		else
		{
			screenBuf[i + (centerRow - 1) * (width + 1)] = '-';
		}
	}

	for (j = 0; j < height; j++)
	{
		if (j == centerRow)
		{
			screenBuf[centerCol - 1 + j * (width + 1)] = '|';
			screenBuf[centerCol + buttonLength + j * (width + 1)] = '|';
			screenBuf[centerCol + buttonLength + 1 + j * (width + 1)] = '|';
		}
		else
		{
			screenBuf[centerCol - 1 + j * (width + 1)] = '|';
			screenBuf[centerCol + buttonLength + 1 + j * (width + 1)] = '|';
		}
	}
}

void drawInGameScreen(char* screenBuf, int width, int height)
{
	int centerRow = height / 2;
	int centerCol = width / 2;
	char* entrance = "Entrance";
	char* in = "in";
	char* out = "out";
	int entranceLength = strlen(entrance);
	int inOutLength = strlen(in);

	int entranceStartCol = centerCol - (entranceLength / 2);
	int inOutStartCol = centerCol - (inOutLength / 2);

	int i, j;

	for (i = 0; i < width; i++)
	{
		if (i >= inOutStartCol && i < inOutStartCol + inOutLength)
		{
			if (i == inOutStartCol || i == inOutStartCol + inOutLength - 1)
				screenBuf[i + centerRow * (width + 1)] = '|';
			else
				screenBuf[i + centerRow * (width + 1)] = in[i - inOutStartCol];
		}
		else if (i >= entranceStartCol && i < entranceStartCol + entranceLength)
		{
			screenBuf[i + (centerRow - 1) * (width + 1)] = entrance[i - entranceStartCol];
		}
		else
		{
			screenBuf[i + (centerRow - 1) * (width + 1)] = '-';
		}
	}

	for (j = 0; j < height; j++)
	{
		if (j == centerRow)
		{
			screenBuf[centerCol - 1 + j * (width + 1)] = '|';
			screenBuf[centerCol + inOutLength + j * (width + 1)] = '|';
			screenBuf[centerCol + inOutLength + 1 + j * (width + 1)] = '|';
		}
		else
		{
			screenBuf[centerCol - 1 + j * (width + 1)] = '|';
			screenBuf[centerCol + inOutLength + 1 + j * (width + 1)] = '|';
		}
	}
}
