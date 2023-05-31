#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <wincon.h>
#include <time.h>


int i, j, direct, t = 50, speed = 500;
int const HEIGHT = 30, WIDTH = 30;

int gameover = 0;
int headx = HEIGHT / 2;
int heady = WIDTH / 2;
int score = 0;


struct Point {
	int x;
	int y;
};


void clearGameField(char s[HEIGHT][(WIDTH + 1)]) {
	for (int i = 1; i < HEIGHT - 2; i++) {
		for (int j = 1; j < WIDTH - 2; j++) {
			s[i][j] = ' ';
		}
	}
}

void drawSnake(char s[HEIGHT][(WIDTH + 1)], int len, Point tail[50]) {
	s[heady][headx] = '0';

	for (int k = 0; k < len; k++) {
		s[tail[k].y][tail[k].x] = 'o';
	}
}

void drawApples(char s[HEIGHT][(WIDTH + 1)], int count, Point* apples) {
	for (int i = 0; i < count; i++) {
		s[apples[i].y][apples[i].x] = '@';
	}

	s[0][0] = '#';
}

void drawStrings(char s[HEIGHT][(WIDTH + 1)]) {
	for (int i = 0; i < HEIGHT; i++) {
		printf("%s\n", s[i]);
	}

	printf("\n");
}

void drawFrame(char s[HEIGHT][(WIDTH + 1)], int count, Point* apples, int tailLen, Point tail[50]) {
	system("cls");
	printf(" \n");

	clearGameField(s);
	drawSnake(s, tailLen, tail);
	drawApples(s, count, apples);
	drawStrings(s);

	printf("Очки: % d\n", score);
	printf("\n");
}

void spawnApples(int count, Point apples[5]) {
	for (int i = 0; i < count; i++) {
		apples[i].x = (rand() % (WIDTH - 3)) + 1;
		apples[i].y = (rand() % (HEIGHT - 2)) + 1;
	}
}


void fillField(char s[HEIGHT][(WIDTH + 1)]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			s[i][j] = ' ';
		}
	}
}

void placeWalls(char s[HEIGHT][(WIDTH + 1)]) {
	for (int i = 0; i < WIDTH; i++) {
		s[0][i] = '#';
		s[(HEIGHT - 1)][i] = '#';
	}
	for (int i = 0; i < HEIGHT; i++) {
		s[i][0] = '#';
		s[i][WIDTH - 1] = '#';
		s[i][WIDTH] = '\0';
	}
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			direct = 1;
			break;
		case 's':
			direct = 2;
			break;
		case 'd':
			direct = 3;
			break;
		case 'w':
			direct = 4;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}

void tailmove(Point tail[50], int tailLen) {
	int preX = tail[0].x;
	int preY = tail[0].y;
	int pre2X, pre2Y;
	tail[0].x = headx;
	tail[0].y = heady;
	for (int i = 1; i < tailLen; i++) {
		pre2X = tail[i].x;
		pre2Y = tail[i].y;
		tail[i].x = preX;
		tail[i].y = preY;
		preX = pre2X;
		preY = pre2Y;
	}
}

void snakemove() {
	switch (direct) {
	case 1:
		headx--;
		break;
	case 2:
		heady++;
		break;
	case 3:
		headx++;
		break;
	case 4:
		heady--;
		break;
	default:
		break;
	}
}

void objColision(Point tail[50], int tailLen) {
	if (headx <= 0 || headx >= HEIGHT - 1 || heady <= 0 || heady >= WIDTH - 2) {
		gameover = 1;
	}

	for (int i = 0; i < tailLen; i++) {
		if (tail[i].x == headx && tail[i].y == heady) {
			gameover = 1;
		}
	}
}

void levelUp(int* applecount) {
	*(applecount) += 1;
	if (speed > 50) {
		speed -= 50;
	}
	if ((score / 50) % 2 == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	}
}

void logic(int* applecount, Point apples[5], int tailLen, Point tail[50]) {
	tailmove(tail, tailLen);

	Sleep(speed);
	snakemove();

	objColision(tail, tailLen);

	for (int i = 0; i < *(applecount); i++) {
		if ((headx == (apples[i].x)) && (heady == (apples[i].y))) {
			tailLen++;
			score += 10;
			if (score % t == 0) {
				levelUp(applecount);
			}
			spawnApples(*(applecount), apples);
		}
	}
}


void gameOverprint() {
	Sleep(3000);
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);

	printf("                                                                            \n");
	printf("                                                                            \n");
	printf("                                                                            \n");
	printf("     *******            ******      ****           ****      ************   \n");
	printf("    *********          *** ***      ******       ******      ************   \n");
	printf("   ***     **         ***  ***      *** ***     *** ***      ***            \n");
	printf("   ***               ***   ***      ***  ***   ***  ***      ***            \n");
	printf("   ***              ***    ***      ***   *** ***   ***      ********       \n");
	printf("   ***    ***       **********      ***     ***     ***      ********       \n");
	printf("   ***      **      **********      ***             ***      ***            \n");
	printf("   ***      **      ***    ***      ***             ***      ***            \n");
	printf("   ***      **      ***    ***      ***             ***      ***            \n");
	printf("    *********       ***    ***      ***             ***      ************   \n");
	printf("     *******        ***    ***      ***             ***      ************   \n");
	printf("                                                                            \n");
	printf("                                                                            \n");
	printf("     ********        ***         ***      ************     **********       \n");
	printf("    **********       ***         ***      ************     ***********      \n");
	printf("   ***      ***      ***         ***      ***              ***      ***     \n");
	printf("   ***      ***      ***         ***      ***              ***      ***     \n");
	printf("   ***      ***      ***         ***      ********         ***      ***     \n");
	printf("   ***      ***      ***         ***      ********         ***     ***      \n");
	printf("   ***      ***       ***       ***       ***              **********       \n");
	printf("   ***      ***        ***     ***        ***              ***********      \n");
	printf("   ***      ***         ***   ***         ***              ***      ***     \n");
	printf("    **********           *** ***          ************     ***       ***    \n");
	printf("     ********             *****           ************     ***        ***   \n");
	printf("                                                                            \n");
	printf("                                                                            \n");
	printf("                                                                            \n");
}

void gameLoop(char s[HEIGHT][(WIDTH + 1)], int* applecount, Point apples[5], int tailLen, Point tail[50]) {
	while (!gameover) {
		drawFrame(s, *(applecount), apples, tailLen, tail);
		input();
		logic(applecount, apples, tailLen, tail);
	}

	gameOverprint();
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	srand(time(NULL));
	rand();

	char field[HEIGHT][(WIDTH + 1)];

	int applecount = 1;
	struct Point apples[5];
	spawnApples(applecount, apples);

	fillField(field);

	placeWalls(field);

	int tailLen = 0;
	struct Point tail[50];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);

	gameLoop(field, &applecount, apples, tailLen, tail);

	_getch();
	return 0;
}
