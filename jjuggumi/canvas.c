#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int col, int row) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int col, int row) {
	gotoxy(col, row);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int col, int row) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(0, N_ROW + 4);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], col, row);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");
	}
}

//dialog ���� 
char backup[ROW_MAX][COL_MAX];

void dialog(char message[]) {
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			backup[i][j] = back_buf[i][j];
		}
	} //�� ȭ�� �����س���

	int message_long = strlen(message); //�޽��� ���� ���
	int center = N_COL / 2 - message_long / 2; //�޽��� ���� ���� �߾� ���
	int message_row = N_ROW / 2;
	int message_col = center;
	//�޽��� ����� ��

	int time = DIALOG_DURATION_SEC;

	while (time >= 0) {
		if (time > 0) {
			//�޽��� ĭ �� ���� �ִ� �� �� ���ֱ�
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row - 1);
			}
			for (int i = message_col - 8; i < N_COL / 2 + 17; i++) {
				printxy(' ', i, message_row);
			}
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row + 1);
			}

			//�޽��� â ���
			gotoxy(N_COL / 10, message_row - 1);
			for (int i = 0; i <= N_COL - N_COL / 4; i++) {
				printf("*");
			} //���� * ���

			gotoxy(N_COL / 10, message_row);
			for (int i = 0; i < 1; i++) {
				printf("*");
			} // �޽��� �� * ���

			gotoxy(N_COL / 10 + 4, message_row); //���� �ð� ���
			printf("%d", time);
			gotoxy(message_col + 1, message_row); //�޽��� ���
			printf("%s", message);

			gotoxy(N_COL - N_COL / 10 - 2, message_row); //dialog �� * ���
			for (int i = 0; i < 1; i++) {
				printf("*");
			}

			gotoxy(N_COL / 10, message_row + 1); //�Ʒ��� * ���
			for (int i = 0; i <= N_COL - N_COL / 4; i++) {
				printf("*");
			}

			Sleep(1000); //1�� ���
		}
		else if (time == 0) { //���� �ð��� 0�϶� �޽���â ���ֱ�
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row - 1);
			}
			for (int i = message_col - 8; i < N_COL / 2 + 17; i++) {
				printxy(' ', i, message_row);
			}
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row + 1);
			}
		}
		time--;
	}
	// ���� ȭ���� ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = backup[i][j];
		}
	}
}
