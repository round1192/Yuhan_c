#include "screen.h"

int clearBuffer(char* screenBuf, int width, int height)
{
	int i = 0;	/* 가로 index */
	int j = 0;  /* 세로 index */
	while (j < height)
	{
		while (i < width + 1) /* 개행문자때문에 + 1*/
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

/* 수업시간에 배운 x,y에 스트링을 쓰는 함수를 짜면 됨. */
int writeStringToBuffer(char* screenBuf, const char* string, int x, int y, int width)
{

}

/* 타이틀 화면 그리는 버퍼랑 게임오버, 게임설명 등등 이런식으로 만들면 보기 편하겠죠? */
int setTitleToScreenBuffer(char* screenBuf, int width, int height)
{

}

int setGameOverToScreenBuffer(char* screenBuf, int width, int height)
{

}
