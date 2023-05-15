#include <stdio.h>
#include <string.h>

#define BOX_WIDTH 40
#define BOX_HEIGHT 20

void draw_screen(char* title, char* option1, char* option2) {
    char screen[] = "Title Screen";

    for(int i=0; i<BOX_HEIGHT; i++) {
        for(int j=0; j<BOX_WIDTH; j++) {
            if(i==0 || i==BOX_HEIGHT-1) {
                printf("-");
            }
            else if(j==0 || j==BOX_WIDTH-1) {
                printf("|");
            }
            else if(i==1 && j==(BOX_WIDTH-strlen(title))/2) {
                printf("%s", title);
                j += strlen(title) - 1;
            }
            else if(i==BOX_HEIGHT/2 && j>=2 && j<=BOX_WIDTH-9) {
                if(j==BOX_WIDTH-9) {
                    printf("[%s]", option2);
                    j += strlen(option2) + 1;
                }
                else if(j==2) {
                    printf("[%s]", option1);
                    j += strlen(option1) + 1;
                }
                else {
                    printf(" ");
                }
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    char input[10];

    while(1) {
        draw_screen("Rhythm Machinery", "start", "quit");

        printf("\nInput: ");
        scanf("%s", input);

        if(strcmp(input, "start") == 0) {
            draw_screen("Repair", "in", "out");

            printf("\nPress Enter key to return to the title screen.");
            getchar();
            getchar();
        }
        else if(strcmp(input, "quit") == 0) {
            draw_screen("Are you quit?", "yes", "no");

            printf("\nInput: ");
            scanf("%s", input);

            if(strcmp(input, "yes") == 0) {
                break;
            }
        }
    }

    return 0;
}