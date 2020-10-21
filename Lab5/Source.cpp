#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
int j = 0;
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	setcolor(2, 0); gotoxy(x, y); printf("<-0->");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y); setcolor(0, 0); printf("     ");
}
void draw_bullet(int x, int y)
{
	setcolor(5, 0);	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); setcolor(5, 0); printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
	setcolor(2, 0);
}
void random()
{
	int starx[20], stary[20];
	starx[j] = rand() % 70 + 11;
	stary[j] = rand() % 4 + 2;
	gotoxy(starx[j], stary[j]);
	printf("*");
	setcolor(2, 0);
}
char cursor(int x, int y) 
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}
void score(int x)
{
	gotoxy(90, 0);
	setcolor(11, 0);
	printf("Score : %d", x);
}

int main()
{
	setcolor(2, 0);
	char ch = '.';
	int x = 38, y = 20;
	int bx[5], by[5];
	bool isFired[5] = { };
	int direction_ship = 0;
	int scores = 0;
	srand(time(NULL));
	for (int a = 0; a < 20; a++)
	{
		random();
	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x >= 1) { direction_ship = -1; }
			if (ch == 'd' && x <= 80) { direction_ship = 1; }
			if (ch == 's') { direction_ship = 0; }
			if (isFired[j] != 1 && ch == ' ') { isFired[j] = 1; bx[j] = x + 2; by[j] = y - 1; j++; if (j == 5) { j = 0; } }
			fflush(stdin);
		}
		if (direction_ship == 1 && x <= 80) { erase_ship(x, y); draw_ship(++x, y); }
		if (direction_ship == -1 && x >= 1) { erase_ship(x, y); draw_ship(--x, y); }
		if (direction_ship == 0) { draw_ship(x, y); }
		for (int k = 0; k <= 4; k++)
		{
			if (isFired[k] == 1) 
			{ 
				clear_bullet(bx[k], by[k]);
				if (by[k] == 0) 
				{
					isFired[k] = 0;
				} 
				else 
				{  
					if (cursor(bx[k], by[k] - 1) == '*')
					{
						Beep(500, 100);
						clear_bullet(bx[k], by[k] - 1);
						scores++;
						random();
					}
					draw_bullet(bx[k], --by[k]);
				}
				
			}
		}
		score(scores);
		setcursor(0);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}