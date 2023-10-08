#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		2
#define DIR_DOWN	3
#define DIR_LEFT	1
#define DIR_RIGHT	0

void mugunghwa_init(void);
void move_manual(key_t key);
void move_random(int i);
void move_tail(int i, int nx, int ny);
void message(void);
void Younghee_turn(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];

char Younghee[31] = "����ȭ�����Ǿ����ϴ�";

int tick2 = 0;
int tick3 = 0;

void mugunghwa_init(void) {
	map_init(9, 35);
	for (int i = 0; i < n_player; i++) {
		px[i] = N_COL - 2;
		py[i] = 2 + i;

		period[i] = randint(20, 50); //���� 200 500

		back_buf[py[i]][px[i]] = '0' + i;
	}
	for (int i = 0; i < n_player; i++) {
		for (int j = 0; j < n_player; j++) {
			if (period[i] == period[j]) {
				period[j] = randint(20, 50);
			}
		}
	}
	for (int i = 3; i <= 5; i++) {	//����
		back_buf[i][1] = '#';
	}
	tick = 10;
}

void move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { 1, -1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}



void move_random(int player) {
	int p = player;
	int nx, ny;
	//���� ��ó ���
	if (back_buf[py[p] + 1][px[p]] == '#' || back_buf[py[p]][px[p] - 1] == '#' || back_buf[py[p] - 1][px[p]] == '#') {
		return;
	}
	if (back_buf[py[p] + 1][px[p]] == '@' || back_buf[py[p]][px[p] - 1] == '@' || back_buf[py[p] - 1][px[p]] == '@') {
		return;
	}

	do {
		int rnd_num = randint(1, 1000);
		if (rnd_num >= 1 && rnd_num <= 700) {
			nx = px[p] - 1;
			ny = py[p];
		}
		else if (rnd_num >= 701 && rnd_num <= 800) {
			nx = px[p];
			ny = py[p] - 1;
		}
		else if (rnd_num >= 801 && rnd_num <= 900) {
			nx = px[p];
			ny = py[p] + 1;
		}
		else {
			nx = px[p];
			ny = py[p];
		}
		for (int i = 0; i < n_player; i++) {	//���� �ؿ� �÷��̾� 2�� ���� ��� ����placable ���� �ذ�
			if (back_buf[ny][nx] == '0' + i) {
				return;
			}
		}
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void move_tail(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[ny][nx] = back_buf[py[p]][px[p]];
	back_buf[py[p]][px[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void message(void) {
	gotoxy(0, N_ROW + 1);
	//switch������ �����ϱ�
	switch (tick2) {
		case 0: for (int i = 0; i <= 1; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 500: for (int i = 0; i <= 3; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 1100: for (int i = 0; i <= 5; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 1800: for (int i = 0; i <= 7; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 2800: for (int i = 0; i <= 9; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 3400: for (int i = 0; i <= 11; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 3800: for (int i = 0; i <= 13; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4100: for (int i = 0; i <= 15; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4300: for (int i = 0; i <= 17; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4500: for (int i = 0; i <= 19; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
	}

	tick2 += 10;
}

void Younghee_turn(void) {
	
	if (tick2 == 4510) {
		for (int i = 3; i <= 5; i++) {	
			back_buf[i][1] = '@';
		}
		
		
		tick3 = 0;
	}
	tick3 += 10;
	if (tick3 == 3000) {
		for (int i = 3; i <= 5; i++) {	
			back_buf[i][1] = '#';
		}
	}
}

void mugunghwa(void) {
	mugunghwa_init();
	display();
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		/*if (//�ٷ� �������� ���̸�)*/
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random(i);
			}
		}

		message();
		Younghee_turn();


		display();
		Sleep(10);
		tick += 10;

	}

	display();
}