#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <wincon.h>
#include <time.h>
#include "stfn.h"
//������ 50 ����� �������� ���������� ������, ��������, ����

int i, j, gameover, x, y, fruit1x, fruit1y, score, flag, t = 50, sl = 500;
int const height = 30, width = 30;
int tailx[100], taily[100], tail;
int fruits[10][2], fruitcount;
char pixels[height][(width + 1)];
char nickname[100];




//�������� ����
void draw() {
	system("cls"); //- ��������� �� � �������

	printf(" \n");// ������� �� ������ ������ �������//

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			pixels[i][j] = ' ';
		}
	}
	pixels[0][0] = '#';


	pixels[y][x] = '0';
	for (int k = 0; k < tail; k++) {
		pixels[taily[k]][tailx[k]] = 'o';
	}
	for (int z = 0; z < fruitcount; z++) {
		pixels[fruits[z][1]][fruits[z][0]] = '@';
	}

	for (int i = 0; i < height; i++) {
		printf("%s\n", pixels[i]);
	}

	printf("\n");
	printf("����: % d\n", score);

	printf("������� X ��� ������ �� ����\n");
	//printf("x:%d y:%d", x, y);
}

void createFruit() {
	for (int i = 0; i < fruitcount; i++) {
		fruits[i][0] = (rand() % (height - 2)) + 1;
		fruits[i][1] = (rand() % (height - 2)) + 1;
	}
}

//����� ��������� ������ � "�����"
void setup() {

	printf("������� ��� (1 �����):");
	scanf("%s", nickname);
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);

	srand(time(NULL));
	rand();
	fruitcount = 1;
	gameover = 0;

	__asm {
		mov eax, height
		mov ebx, width
		sar eax, 1
		sar ebx, 1
		mov x, eax
		mov y, ebx
	}
	/*x = height / 2;
	y = width / 2;*/
	createFruit();
	score = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j] = ' ';
		}
	}

	for (int i = 0; i < width; i++) { // ���������� ������� � ������ ����� ����
		pixels[0][i] = '#';
		pixels[(height - 1)][i] = '#';
	}
	for (int i = 0; i < height; i++) { // ���������� ������ � ����� ������
		pixels[i][0] = '#';
		pixels[i][width - 1] = '#';
		pixels[i][width] = '\0';
	}
}

//����� ����� � ����������
void input() {
	if (_kbhit()) { //��� ������� � ����������
		switch (_getch()) { //switch - ��������� ��� if
		case 'a':           //getch - ������ ������� � ����������. ������ �� ���������
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}

//�������� ������ ���������
void logic() {
	int preX = tailx[0];
	int preY = taily[0];
	int pre2X, pre2Y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++) {
		pre2X = tailx[i];
		pre2Y = taily[i];
		tailx[i] = preX;
		taily[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}

	Sleep(sl); //��������� ���������� ����
	switch (flag) { //���������  ������� � ��������� ������
	case 1:
		x--;
		break;
	case 2:
		y++;
		break;
	case 3:
		x++;
		break;
	case 4:
		y--;
		break;
	default:
		break;
	}

	// ���� ���� �������������

	__asm {
		mov eax, x
		mov ebx, y
		mov ecx, height
		mov edx, width

		dec ecx				//height - 1
		dec edx				//width - 1
		cmp ebx, 0			// ���� y <= 0
		jbe l1
		cmp ebx, ecx				// ���� y >= (height - 1)
		jae l1 
		cmp eax, 0					// ���� x <= 0
		jbe l1 
		cmp eax, edx				// ���� x >= (width - 1)
		jae l1 
		jmp l2
		l1:
			xor eax, eax			// eax = 0
			mov eax, 1
			mov gameover, eax		// gameover = 1
		l2:
	}
	/*if (y <= 0 || y >= (height - 1) || x <= 0 || x >= (width - 1)) {
		gameover = 1;
	}*/

	for (int i = 0; i < tail; i++) {
		if (tailx[i] == x && taily[i] == y) {
			gameover = 1;
		}
	}

	for (int i = 0; i < fruitcount; i++) {
		if (x == fruits[i][0] && y == fruits[i][1]) { //���� ���� ����� ����
			score += 10; // ���������� �����
			tail++;

			if (score == t) {
				fruitcount++;
				if (sl > 50) {
					sl -= 50;
				}
				if ((t / 50) % 2 == 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
				}
				t += 50;
			}
			createFruit();
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);

	start(); //��������

	setup(); //������ ����

	while (!gameover) { //���� ���� �� ����������

		draw();
		input();
		logic();
	}
	if (gameover) {

		const char* path = "score.txt";

		FILE* fp;
		char buffer[150];
		char scoreTable[100][150];

		fp = fopen(path, "r");
		if (fp){
			int c = 0;
			bool fl = true;
			while ( fgets(buffer, 150, fp) != NULL || buffer == "") {
				char nick[100];
				int sc;
				sscanf(buffer, "%s - %d �����\n", &nick, &sc);
				if (fl && score >= sc) {
					sprintf(scoreTable[c], "%s - %d �����\n", nickname, score);
					c++;
					fl = false;
				}
				sprintf(scoreTable[c], "%s - %d �����\n", nick, sc);
				c++;
			}
			fclose(fp);

			fp = fopen(path, "w");
			for (int i = 0; i < c; i++){
				fprintf(fp, "%s", scoreTable[i]);
			}

		}
		else {
			fp = fopen(path, "a+");
			fprintf(fp, "%s - %d �����\n", nickname, score);
		}

		
		fclose(fp);

		Sleep(3000);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
		
		

		finish();

		_getch();
		return 0;
	}
}