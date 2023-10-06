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
void one_survive();





char Younghee[31] = "무궁화꽃이피었습니다";
int tick2 = 0;
int tick3 = 3100;
int round_out = 0;
char out_player[19] = {' '};
int out = 0;
int flag[PLAYER_MAX] = { 0 };
int can_behind = 0;
int behind = 0;
int dead = 0;
int one = 0;
int p_exist = 1;

void one_survive()
{
	for (int i = 0; i < n_player; i++) {
		one += player[i];
	}
		if (one == 1) {
			//ending();
			display();
			dialog_mugunghwa("player", "dead!", out_player, out);
			exit(0);
		}
		else {
			one = 0;
		}
}

void mugunghwa_init(void) {
	map_init(9, 35);
	for (int i = 0; i < n_player; i++) {
		px[i] = N_COL - 2;
		py[i] = 2 + i;

		period[i] = randint(10, 150);

		back_buf[py[i]][px[i]] = '0' + i;
	}
	for (int i = 0; i < n_player; i++) {
		for (int j = 0; j < n_player; j++) {
			if (period[i] == period[j]) {
				period[j] = randint(20, 50);
			}
		}
	}
	for (int i = 3; i <= 5; i++) {	//영희
		back_buf[i][1] = '#';
	}
	tick = 10;
}

void move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { 1, -1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
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
	} while (!placable(nx, ny));
	if (can_behind == 1 && nx == px[p] - 1) {
		behind = 1;
		can_behind = 0;
	}
	move_tail(p, nx, ny);
	if (back_buf[py[p] + 1][px[p]] == '#' || back_buf[py[p]][px[p] - 1] == '#' || back_buf[py[p] - 1][px[p]] == '#') {
		back_buf[py[p]][px[p]] = ' ';
		flag[p] = 1;
		//dead만 안뜨게 처리해줘야함, flag만들어서 메인함수에서 if조건문 2개에 하나 더 추가시켜서 flase 안뜨게 해주자
	}
}

void move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
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
		for (int i = 3; i <= 5; i++) {	
			back_buf[i][1] = '@';
		}
		
		tick3 = 0;
	}
	tick3 += 10;
	if (tick3 == 3000) {                            // dialog 끝나고 숫자없는지 확인해서 게임이 끝난건지 확인
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
		for (int i = 3; i <= 5; i++) {	
			back_buf[i][1] = '#';
		}
		gotoxy(0, N_ROW + 1);
		printf("                             ");
		tick2 = 0;
		tick3 = 3100;
	}
}

void gameend(void) {
	p_exist = 0;
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 34; j++) {
			for (int k = 0; k < n_player; k++) {
				if (back_buf[i][j] == '0' + k) {
					p_exist = 1;
				}
			}
		}
	}
	if (p_exist == 0) {
		//다음게임으로넘어감
		return;
	}
}

void mugunghwa(void) {
	mugunghwa_init();
	left_player();
	system("cls");
	display();
	//탈락자 다수일시 중간에 넣을 출력값
	for (int i = 1; i < 19; i += 2) {
		out_player[i] = ',';
	}
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			if (tick3 <= 3000 && flag[0] == 0&&dead==0) {
				for (int i = 1; i < px[0]; i++) {
					for (int j = 0; j < n_player; j++) {
						if (back_buf[py[0]][px[0] - i] == '0' + j) {
							can_behind = 1;
						}
					}
				}
				if(can_behind==1&&key==K_LEFT){
					move_manual(key);
					can_behind = 0;
				}
				else {
					if (key == K_UP || key == K_DOWN || key == K_LEFT) {
						move_manual(key);
						player[0] = false;
						out_player[out] = '0';
						out += 2;
						can_behind = 0;
						dead = 1;
					}
				}
				one_survive();
			}
			else {
				move_manual(key);
			}
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		if (tick3 <= 3000) {
			
			for (int i = 1; i < n_player; i++) {
				int rnd_10 = randint(1, 1000);
				if (tick % period[i] == 0 && rnd_10 <= 100 && flag[i]==0) {
					for (int j = 1; j < px[i]; j++) {
						for (int k = 0; k < n_player; k++) {
							if (back_buf[py[i]][px[i] - j] == '0'+k) {
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
				if (tick % period[i] == 0) {
					move_random(i);
				}
			}
		
		}
		message();
		Younghee_turn();
		gameend();
		if (p_exist == 0) {
			break;
		}
		one_survive();
		display();
		Sleep(10);
		tick += 10;
	}
}


