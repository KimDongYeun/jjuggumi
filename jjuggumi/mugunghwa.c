#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <time.h>


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
void if_behind(void);
void one_survive(void);
void move_0(int);
void gameend(void);
void move_other(void);




char Younghee[31] = "����ȭ�����Ǿ����ϴ�";
int tick2 = 0;
int round_out = 0;
char out_player[19] = {' '};
int out = 0;
int flag[PLAYER_MAX] = { 0 };
int can_behind = 0;
int behind = 0;
int dead = 0;
int winner_num = 0;
int p_exist = 1;
double endtime;
double starttime;
double turntime = -1;
period[PLAYER_MAX] = {0,100,230,200,250,160,220,240,130,260};

void one_survive(void) // �Ѹ� ��Ƴ��� ���
{
	for (int i = 0; i < n_player; i++) {
		winner_num += player[i];
	}
		if (winner_num == 1) {
			display();
			dialog_mugunghwa("player", "dead!", out_player, out);
			ending();
			exit(0);
		}
		else {
			winner_num = 0;
		}
}

void mugunghwa_init(void) {
	map_init(11, 35);
	for (int i = 0; i < n_player; i++) {
		px[i] = N_COL - 2;
		if (n_player <= 3) {
			py[i] = 4 + i;
		}
		else if (n_player <= 5) {
			py[i] = 3 + i;
		}
		else if (n_player <= 7) {
			py[i] = 2 + i;
		}
		else{
			py[i] = 1 + i;
		}

		back_buf[py[i]][px[i]] = '0' + i;
	}
	for (int i = 4; i <= 6; i++) {	//����
		back_buf[i][1] = '#';
	}
	for (int i = 1; i < 19; i += 2) { //Ż���� �ټ��Ͻ� �߰��� ���� ��°�
		out_player[i] = ',';
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
	if (back_buf[py[0] + 1][px[0]] == '#' || back_buf[py[0]][px[0] - 1] == '#' || back_buf[py[0] - 1][px[0]] == '#') {
		back_buf[py[0]][px[0]] = ' ';
		flag[0] = 1;
	}
}



void move_random(int player) {
	int p = player;
	int nx, ny;
	int a=0, b=0, c=0, d = 0;

	do {
		int rnd_num = randint(1, 1000);
		if (rnd_num >= 1 && rnd_num <= 700) {
			nx = px[p] - 1;
			ny = py[p];
			a++;
		}
		else if (rnd_num >= 701 && rnd_num <= 800) {
			nx = px[p];
			ny = py[p] - 1;
			b++;
		}
		else if (rnd_num >= 801 && rnd_num <= 900) {
			nx = px[p];
			ny = py[p] + 1;
			c++;
		}
		else {
			nx = px[p];
			ny = py[p];
			d++;
		}
		if (a >= 2 && b >= 2 && c >= 2 && d >= 2) {
			break;
		}
	} while (!placable(nx, ny));
	if (can_behind == 1 && nx == px[p] - 1) {
		behind = 1;
		can_behind = 0;
	}
	else {
		behind = 0;
	}
	move_tail(p, nx, ny);
	if (back_buf[py[p] + 1][px[p]] == '#' || back_buf[py[p]][px[p] - 1] == '#' || back_buf[py[p] - 1][px[p]] == '#') {
		back_buf[py[p]][px[p]] = ' ';
		flag[p] = 1;
	}
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
	
	switch (tick2) {
		case 0: for (int i = 0; i <= 1; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 400: for (int i = 0; i <= 3; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 1000: for (int i = 0; i <= 5; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 1800: for (int i = 0; i <= 7; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 2800: for (int i = 0; i <= 9; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 3500: for (int i = 0; i <= 11; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4000: for (int i = 0; i <= 13; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4300: for (int i = 0; i <= 15; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4500: for (int i = 0; i <= 17; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		case 4600: for (int i = 0; i <= 19; i += 2) {
			printf("%c%c ", Younghee[i], Younghee[i + 1]);
		} break;
		default: break;
	}

	tick2 += 10;
}

void Younghee_turn(void) {
	
	if (tick2 == 4600) {
		for (int i = 4; i <= 6; i++) {	
			back_buf[i][1] = '@';
		}
		
		endtime = (unsigned)time(NULL);
		endtime += 3;
	}
	starttime = (unsigned)time(NULL);
	turntime = endtime - starttime;
	if (turntime == 0) {                            
		for (int i = 0; i < n_player; i++) {
			if (player[i] == false) {
				back_buf[py[i]][px[i]] = ' ';
				round_out++;
			}
		}
		if (out > 0) {
			dialog_mugunghwa("player", "dead!", out_player, out);
		}
		else {

		}
		for (int i = 0; i < 19; i++) {
			out_player[i] = ' ';
		}
		
		out = 0;
		n_alive = n_player - round_out;
		round_out = 0;
		for (int i = 4; i <= 6; i++) {	
			back_buf[i][1] = '#';
		}
		gotoxy(0, N_ROW + 1);
		printf("                             ");
		tick2 = 0;
		turntime = -1;
	}
}

void gameend(void) {
	p_exist = 0;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 34; j++) {
			for (int k = 0; k < n_player; k++) {
				if (back_buf[i][j] == '0' + k) {
					p_exist = 1;
				}
			}
		}
	}
	if (p_exist == 0) {
		//�����������γѾ
		return;
	}
}

void if_behind(void)
{
	for (int i = 1; i < px[0]; i++) {
		for (int j = 0; j < n_player; j++) {
			if (back_buf[py[0]][px[0] - i] == '0' + j) {
				can_behind = 1;
			}
		}
	}
}

void move_0(int key) {
	if (can_behind == 1 && key == K_LEFT || can_behind == 1 && key == K_RIGHT) {
		move_manual(key);
		can_behind = 0;
	}
	else {
		if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT) {
			move_manual(key);
			player[0] = false;
			out_player[out] = '0';
			out += 2;
			can_behind = 0;
			dead = 1;
			flag[0] = 1;
		}
	}
}

void move_other(void)
{
	if (turntime>0) {
		for (int i = 1; i < n_player; i++) {
			int rnd_10 = randint(1, 1000);
			if (tick % period[i] == 0 && rnd_10 <= 100 && flag[i] == 0) {
				for (int j = 1; j < px[i]; j++) {
					for (int k = 0; k < n_player; k++) {
						if (back_buf[py[i]][px[i] - j] == '0' + k) {
							can_behind = 1;
						}
					}
				}
				move_random(i);
				if (behind == 1) {
					behind = 0;
				}
				else {
					player[i] = false;
					flag[i] = 1;
					out_player[out] = '0' + i;
					out += 2;
					behind = 0;
				}
			}
			one_survive();
		}
	}
	else {
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0 && flag[i] == 0) {
				move_random(i);
			}
		}

	}
}

void mugunghwa(void) {
	mugunghwa_init();
	left_player();
	system("cls");
	display();
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			if (turntime>0 && flag[0] == 0&&dead==0) {
				if_behind();
				move_0(key);
				one_survive();
			}
			else {
				if (player[0] == true) {
					move_manual(key);
				}
			}
		}
		// player 1 ���ʹ� �������� ������(8����)
		move_other();
		message();
		Younghee_turn();
		gameend();
		if (p_exist == 0) {
			break;	//������������ �Ѿ���ϳ� ���������� ���� �����Ƿ� 2���� �����ص� ����� ������ ���� ���
		}
		one_survive();
		display();
		Sleep(10);
		tick += 10;
	}
}


