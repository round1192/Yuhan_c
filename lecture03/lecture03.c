#include <stdio.h>

int main()
{
	int game_state = 5;
	
	scanf("%d",&game_state);

	if(game_state)
	{	
		printf("나는 연애 %d번 해본 정상인임.",game_state);
	}
	else
	{
		printf("내가 참 슬프다...");
	}

	return 0;
}
