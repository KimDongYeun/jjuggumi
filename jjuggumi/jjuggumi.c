// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);
void ascii_art(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

void ascii_art(void) {
	system("cls");
	printf("======================================================\n\n"); Sleep(100);
	printf("               (:��)�� �޲ٹ� ���� ��(��:)\n\n"); Sleep(100);
	printf("======================================================\n"); Sleep(100);
	printf("   ___    ___  _   _  _____  _____  _   _ ___  ___ _____   _____   ___  ___  ___ _____\n");
	printf("  |_  |  |_  || | | ||  __ \\|  __ \\| | | ||  \\/  ||_   _| |  __ \\ / _ \\ |  \\/  ||  ___|\n");
	printf("    | |    | || | | || |  \\/| |  \\/| | | || .  . |  | |   | |  \\/ /_\\ \\| .  . || |__\n");
	printf("    | |    | || | | || | __ | | __ | | | || |\\/| |  | |   | | __ |  _  || |\\/| ||  __|\n");
	printf("/\\__/ //\\__/ /| |_| || |_/ /| |_/ /| |_| || |  | | _| |_  | |_/ /| | | || |  | || |___\n");
	printf("\\____/ \\____/  \\___/  \\____/ \\____/ \\___/ \\_|  |_/ \\___/   \\____/\\_| |_/\\_|  |_/\\____/\n\n");
	printf("======================================================\n"); Sleep(100);
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

int intro(void) {
	ascii_art(); //��Ʈ�� 
	printf("\n������ �����մϴ�!\n"); Sleep(3000); //3�� �Ŀ� ���ӽ���
	system("cls");
	return 0;
}


int main(void) {
	jjuggumi_init();
	intro();
	mugunghwa();
	ending();
	return 0;
}
