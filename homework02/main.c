#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

int main()
{
	/*  width : 30    height : 10    가로 여백 : 2    세로여백 :1 */
	char screenBuf[35 * 12 + 1];
	int width = 34;
	int height = 12;
	int isGamePlaying = 1;

	char input[10];

	while (isGamePlaying)
	{
		clearBuffer(screenBuf, width, height);

		setTitleToScreenBuffer(screenBuf, width, height); /* 이런식으로 짜주세용 */

		system("cls");
		printf("%s\ninput>", screenBuf);
		scanf("%s", input);

		if (input[0] == 'quit')	/*quit 누르면 종료*/
			isGamePlaying == 0;
	}

	return 0;
}
