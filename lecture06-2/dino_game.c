#include <stdio.h>
#include "dino_screen_H.h"


int main() 
{
    print_title_screen();
    int huegang;
    int gongang;

    while (1) {  
        printf("게임 메뉴\n");
        printf("1. 게임 시작\n");
        printf("2. 게임 설명\n");
        printf("3. 종료\n");

        printf("선택 : ");
        scanf("%d", &huegang);
	
        if (huegang == 1) {
            printf("게임을 시작합니다.\n");
        } else if (huegang == 2) 
        {
            print_how_to_play_screen();
            printf("게임 설명\n");
            printf("이 게임은 ... (생략)\n");
            printf("Return to menu? (1.yes 2.no) : ");
            scanf("%d", &gongang);

            while (gongang != 1 && gongang != 2) 
            {
                printf("잘못된 선택입니다. 다시 입력해주세요.\n");
                printf("Return to menu? (1.yes 2.no) : ");
                scanf("%d", &gongang);
            }

            if (gongang == 1) 
            {
                continue;  
            } else if (gongang == 2) 
            {
                printf("게임 설명\n");
                printf("이 게임은 ... (생략)\n");
                printf("Return to menu? (1.yes 2.no) : ");
                scanf("%d", &gongang);

                while (gongang != 1 && gongang != 2) {
                    printf("잘못된 선택입니다. 다시 입력해주세요.\n");
                    printf("Return to menu? (1.yes 2.no) : ");
                    scanf("%d", &gongang);
                }

                if (gongang == 1) 
                {
                    continue;  
                } else {
                    break; 
                }
            }
        } else if (huegang == 3) {
            printf("게임을 종료합니다.\n");
            return 0;
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
