#include <stdio.h>

int main() {
	int attack_power, enemy_hp = 30;


	printf("주인공의 공격력을 입력하세요: ");
	scanf("%d", &attack_power);


	printf("주인공은 공격력이 %d입니다.\n", attack_power);


	enemy_hp -= attack_power;
	printf("주인공이 적을 공격하여 %d의 데미지를 입혔습니다.\n", attack_power);
	printf("적의 잔여 HP : %d\n", enemy_hp);


	if (enemy_hp <= 0) {
		printf("적을 물리쳤습니다!\n");
		printf("Happy End\n");
	} else {
		printf("저런! 적이 주인공을 공격하고 주인공은 뒤지고 세계는 멸망했습니다.\n");
		printf("Game Over\n");
	}
	  	

	return 0;
}
