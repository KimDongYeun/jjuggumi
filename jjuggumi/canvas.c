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

// (zero-base) row행, col열로 커서 이동
void gotoxy(int col, int row) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int col, int row) {
	gotoxy(col, row);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int col, int row) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(0, N_ROW + 4);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
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

//dialog 구현 
char backup[ROW_MAX][COL_MAX];

void dialog(char message[]) {
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			backup[i][j] = back_buf[i][j];
		}
	} //전 화면 복사해놓기

	int message_long = strlen(message); //메시지 길이 출력
	int center = N_COL / 2 - message_long / 2; //메시지 내용 가로 중앙 출력
	int message_row = N_ROW / 2;
	int message_col = center;
	//메시지 출력할 곳

	int time = DIALOG_DURATION_SEC;

	while (time >= 0) {
		if (time > 0) {
			//메시지 칸 들어갈 곳에 있는 거 다 없애기
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row - 1);
			}
			for (int i = message_col - 8; i < N_COL / 2 + 17; i++) {
				printxy(' ', i, message_row);
			}
			for (int i = N_COL / 10 - 1; i < N_COL - N_COL / 10 + 1; i++) {
				printxy(' ', i, message_row + 1);
			}

			//메시지 창 출력
			gotoxy(N_COL / 10, message_row - 1);
			for (int i = 0; i <= N_COL - N_COL / 4; i++) {
				printf("*");
			} //위쪽 * 출력

			gotoxy(N_COL / 10, message_row);
			for (int i = 0; i < 1; i++) {
				printf("*");
			} // 메시지 앞 * 출력

			gotoxy(N_COL / 10 + 4, message_row); //남은 시간 출력
			printf("%d", time);
			gotoxy(message_col + 1, message_row); //메시지 출력
			printf("%s", message);

			gotoxy(N_COL - N_COL / 10 - 2, message_row); //dialog 뒤 * 출력
			for (int i = 0; i < 1; i++) {
				printf("*");
			}

			gotoxy(N_COL / 10, message_row + 1); //아래쪽 * 출력
			for (int i = 0; i <= N_COL - N_COL / 4; i++) {
				printf("*");
			}

			Sleep(1000); //1초 대기
		}
		else if (time == 0) { //남은 시간이 0일때 메시지창 없애기
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
	// 이전 화면을 복구
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = backup[i][j];
		}
	}
}
