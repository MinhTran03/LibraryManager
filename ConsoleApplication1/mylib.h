#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include<time.h>
#define PASSWORD "abcdef"

#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75

#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64

#define boxx 15 //Vi tri x bat dau cua box
#define boxy 10 //Vi tri y bat dau cua box
#define boxs 60 //Box size
#define tabx 5 // vi tri x bat dau cua table
#define taby 4  // vi tri y bat dau cua table
#define tabs 105 // be ngang cua bang
#define tabw 23 // chieu cao cua ban

//#define ArrowLEFT 26
//#define ArrowUP 25
//#define ArrowDOWN 24
using namespace std;
char* Pwd() {
	char S[40]; int i = 0;
	while ((S[i] = getch()) != ENTER)
	{
		printf("%c", '*'); i++;
	}
	S[i] = '\0';
	return S;
}

int CheckPwd() {
	int dem = 0;
	for (dem = 1; dem <= 3; dem++)
	{
		printf("Password :");
		if (strcmp(Pwd(), PASSWORD) == 0)   return 1;
		else printf("\nPassword sai. Hay nhap lai\n");
	}
	return 0;
}

void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

template <typename T>
void inxy(short x, short y, const T& t) {
	gotoxy(x, y);
	cout << t;
}

int wherex(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
void clreol() {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	gotoxy(info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void hidecursor()
{
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 30;
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void textcolor(int x)    // mau chu viet
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}
void Baoloi(string s)
{
	int x = wherex();
	int y = wherey();
	gotoxy(10, y + 2);
	cout << s;
	sleep(10);
	gotoxy(20, y + 2);
	for (int i = 0; i < s.length(); i++)
		cout << " ";
	gotoxy(x, y);
}
void Del_Error()
{
	textcolor(15);
	gotoxy(boxx + 14, 29);
	for (int i = 0; i < 50; i++)
		cout << " ";
}
void Xuat_Chuoi(string s, int y, int x)
{
	gotoxy(boxx + x, boxy + y);
	if (s.length() >= boxs - x)
	{
		for (int i = 0; i < boxs - x; i++)
			cout << s[i];
	}
	else if (s.length() < boxs - x)
	{
		cout << s;
		for (int i = 0; i < boxs - x - s.length(); i++)
			cout << " ";
	}
}
void HighLight() {
	SetColor(15); // mau chu 
	SetBGColor(124);
}
void Normal() {
	SetColor(15);
	SetBGColor(0);
}
//=== PHIM NHAN ==== 
void Button_Sreach()
{
	HighLight();
	gotoxy(8, 31); cout << "        ";
	gotoxy(8, 32); cout << "   F4   ";
	gotoxy(8, 33); cout << "        ";
	Normal();
	gotoxy(8, 35); cout << "  TIM  ";

}

void Button_OK()
{
	HighLight();
	gotoxy(20, 31); cout << "        ";
	gotoxy(20, 32); cout << " ENTER  ";
	gotoxy(20, 33); cout << "        ";
	Normal();
}

void Button_Them()
{
	HighLight();
	gotoxy(25, 31); cout << "        ";
	gotoxy(25, 32); cout << "   F1   ";
	gotoxy(25, 33); cout << "        ";
	Normal();
	gotoxy(25, 35); cout << "  THEM  ";
}

void Button_Muon()
{
	HighLight();
	gotoxy(8, 31); cout << "        ";
	gotoxy(8, 32); cout << "   F5   ";
	gotoxy(8, 33); cout << "        ";
	Normal();
	gotoxy(8, 35); cout << "  MUON  ";
}

void Button_Tra()
{
	HighLight();
	gotoxy(8, 31); cout << "        ";
	gotoxy(8, 32); cout << "   F6   ";
	gotoxy(8, 33); cout << "        ";
	Normal();
	gotoxy(8, 35); cout << "  TRA  ";
}

void Button_Xoa()
{
	HighLight();
	gotoxy(42, 31); cout << "        ";
	gotoxy(42, 32); cout << "   F2   ";
	gotoxy(42, 33); cout << "        ";
	Normal();
	gotoxy(42, 35); cout << "  XOA   ";
}

void Button_Sua()
{
	HighLight();
	gotoxy(58, 31); cout << "        ";
	gotoxy(58, 32); cout << "   F3   ";
	gotoxy(58, 33); cout << "        ";
	Normal();
	gotoxy(58, 35); cout << "  SUA   ";
}
void Button_ESC()
{
	HighLight();
	gotoxy(75, 31); cout << "        ";
	gotoxy(75, 32); cout << "   ESC  ";
	gotoxy(75, 33); cout << "        ";
	Normal();
	gotoxy(75, 35); cout << " TRO VE ";
}
//=== TAO BANG ====
void Table_Dau_Sach()
{
	HighLight();
	gotoxy(40, 1);	cout << "                    ";
	gotoxy(40, 2);	cout << " DANH SACH DAU SACH ";
	gotoxy(40, 3);	cout << "                    ";
	Normal();
	gotoxy(tabx, taby);   // (4,6) hien bang
	cout << "+";
	for (int i = 1; i < tabs - 13; i++)  // hang ngang dau tien
		cout << "+";
	cout << "+";
	for (int i = 1; i < tabw + 1; i++)   // cot dau tien
	{
		gotoxy(tabx, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 13, taby + i); // cot cuoi
		cout << "+";
	}
	for (int i = 1; i < tabs - 13; i++)    // hang cuoi
	{
		gotoxy(tabx + i, taby + tabw);
		cout << "+";
	}
	for (int i = 1; i < tabs - 13; i++)   // hang tach muc voi noi dung
	{
		gotoxy(tabx + i, taby + 2);
		cout << "+";
	}

	// ISBN
	gotoxy(tabx + 3, taby + 1); cout << "ISBN";
	for (int i = 1; i < tabw + 1; i++)   // cot ke ISBN 
	{
		gotoxy(tabx + 10, taby + i);
		cout << "+";
	}

	// Ten Sach
	gotoxy(tabx + 15, taby + 1); cout << "Ten Sach";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 30, taby + i);
		cout << "+";
	}

	// Tac Gia
	gotoxy(tabx + 34, taby + 1); cout << "Tac Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 45, taby + i);
		cout << "+";
	}

	//The loai
	gotoxy(tabx + 48, taby + 1); cout << "The Loai";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 58, taby + i);
		cout << "+";
	}

	//So trang
	gotoxy(tabx + 60, taby + 1); cout << "So Trang";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 70, taby + i);
		cout << "+";
	}

	//Nam XB
	gotoxy(tabx + 72, taby + 1); cout << "Nam XB";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 82, taby + i);
		cout << "+";
	}

	// So lan muon
	gotoxy(tabx + 85, taby + 1); cout << "SL Muon";
}

void Table_Danh_Sach_Sach()
{
	HighLight();
	gotoxy(40, 1);	cout << "                    ";
	gotoxy(40, 2);	cout << "   DANH SACH SACH   ";
	gotoxy(40, 3);	cout << "                    ";
	Normal();
	gotoxy(tabx, taby);   // (4,6) hien bang
	cout << "+";
	for (int i = 1; i < tabs - 33; i++)  // hang ngang dau tien
		cout << "+";
	cout << "+";
	for (int i = 1; i < tabw + 1; i++)   // cot dau tien
	{
		gotoxy(tabx, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 33, taby + i); // cot cuoi
		cout << "+";
	}
	for (int i = 1; i < tabs - 33; i++)    // hang cuoi
	{
		gotoxy(tabx + i, taby + tabw);
		cout << "+";
	}
	for (int i = 1; i < tabs - 33; i++)   // hang tach muc voi noi dung
	{
		gotoxy(tabx + i, taby + 2);
		cout << "+";
	}

	gotoxy(tabx + 3, taby + 1); cout << "ISBN";
	for (int i = 1; i < tabw + 1; i++)   // cot ke ISBN 
	{
		gotoxy(tabx + 10, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 15, taby + 1); cout << "Ma Sach";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 25, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 30, taby + 1); cout << "Ten Sach";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 50, taby + i);
		cout << "+";
	}
	gotoxy(tabx + 52, taby + 1); cout << "Trang Thai";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 63, taby + i);
		cout << "+";
	}
	gotoxy(tabx + 65, taby + 1); cout << "Vi Tri";
}

void Table_Doc_Gia()
{
	HighLight();
	gotoxy(40, 1);	cout << "                     ";
	gotoxy(40, 2);	cout << "  DANH SACH DOC GIA  ";
	gotoxy(40, 3);	cout << "                     ";
	Normal();
	gotoxy(tabx, taby);
	cout << "+";
	for (int i = 1; i < tabs - 23; i++)
		cout << "+";
	cout << "+";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 23, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabs - 23; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << "+";
	}
	for (int i = 1; i < tabs - 23; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << "+";
	}

	gotoxy(tabx + 2, taby + 1); cout << "Ma Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 14, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 16, taby + 1); cout << "Ho Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 30, taby + i);
		cout << "+";
	}
	gotoxy(tabx + 32, taby + 1); cout << "Ten Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 47, taby + i);
		cout << "+";
	}
	// Phai
	gotoxy(tabx + 51, taby + 1); cout << "Phai";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 58, taby + i);
		cout << "+";
	}
	// TT The
	gotoxy(tabx + 65, taby + 1); cout << "Trang Thai The";
}
// bang Danh Sach Doc Gia Muon Qua Han
void Table_Qua_Han()
{
	HighLight();
	gotoxy(40, 1);	cout << "                           ";
	gotoxy(40, 2);	cout << " DANH SACH DOC GIA QUA HAN ";
	gotoxy(40, 3);	cout << "                           ";
	Normal();
	gotoxy(tabx, taby);
	cout << "+";
	for (int i = 1; i < tabs - 33; i++)
		cout << "+";
	cout << "+";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 33, taby + i);
		cout << "+";
	}
	for (int i = 1; i < tabs - 33; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << "+";
	}
	for (int i = 1; i < tabs - 33; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << "+";
	}

	gotoxy(tabx + 2, taby + 1); cout << "Ma Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 14, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 17, taby + 1); cout << "Ho Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 30, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 32, taby + 1); cout << "Ten Doc Gia";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 47, taby + i);
		cout << "+";
	}

	gotoxy(tabx + 50, taby + 1); cout << "Phai";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 58, taby + i);
		cout << "+";
	}
	// SO NGAY QUA HAN
	gotoxy(tabx + 60, taby + 1); cout << "NGAY QUA HAN";
}
//=== Tao Box Nhap====
void Box_Nhap_Dau_Sach()
{
	textcolor(15);
	gotoxy(boxx, boxy); cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
	gotoxy(boxx, boxy + 1);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 1);	cout << "+";
	gotoxy(boxx, boxy + 2);	cout << "+" << " Nhap ISBN: ";
	gotoxy(boxx + boxs + 1, boxy + 2);	cout << "+";
	gotoxy(boxx, boxy + 3);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 3);	cout << "+";
	gotoxy(boxx, boxy + 4);	cout << "+" << " Ten Sach: ";
	gotoxy(boxx + boxs + 1, boxy + 4);	cout << "+";
	gotoxy(boxx, boxy + 5);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 5);	cout << "+";
	gotoxy(boxx, boxy + 6);	cout << "+" << " Tac Gia: ";
	gotoxy(boxx + boxs + 1, boxy + 6);	cout << "+";
	gotoxy(boxx, boxy + 7);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 7);	cout << "+";
	gotoxy(boxx, boxy + 8);	cout << "+" << " The loai: ";
	gotoxy(boxx + boxs + 1, boxy + 8);	cout << "+";
	gotoxy(boxx, boxy + 9);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 9);	cout << "+";
	gotoxy(boxx, boxy + 10);	cout << "+" << " So trang: ";
	gotoxy(boxx + boxs + 1, boxy + 10);	cout << "+";
	gotoxy(boxx, boxy + 11);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 11);	cout << "+";
	gotoxy(boxx, boxy + 12);	cout << "+" << " Nam Xuat Ban: ";
	gotoxy(boxx + boxs + 1, boxy + 12);	cout << "+";
	gotoxy(boxx, boxy + 13);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 13); cout << "+";
	gotoxy(boxx, boxy + 14);	cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
}

void Box_Nhap_Danh_Muc_Sach()
{
	textcolor(15);
	gotoxy(boxx, boxy); cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
	gotoxy(boxx, boxy + 1);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 1);	cout << "+";
	gotoxy(boxx, boxy + 2);	cout << "+" << " Nhap Ma Sach: ";
	gotoxy(boxx + boxs + 1, boxy + 2);	cout << "+";
	gotoxy(boxx, boxy + 3);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 3);	cout << "+";
	gotoxy(boxx, boxy + 4);	cout << "+" << " Nhap Trang Thai: ";
	gotoxy(boxx + boxs + 1, boxy + 4);	cout << "+";
	gotoxy(boxx, boxy + 5);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 5);  cout << "+";
	gotoxy(boxx, boxy + 6);	cout << "+" << " Nhap Vi Tri: ";
	gotoxy(boxx + boxs + 1, boxy + 6);	cout << "+";
	gotoxy(boxx, boxy + 7);	cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
}

void Box_Nhap_Doc_Gia()
{
	textcolor(15);
	gotoxy(boxx, boxy); cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
	gotoxy(boxx, boxy + 1);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 1);	cout << "+";
	gotoxy(boxx, boxy + 2);	cout << "+" << " Nhap Ma DG: ";
	gotoxy(boxx + boxs + 1, boxy + 2);	cout << "+";
	gotoxy(boxx, boxy + 3);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 3);	cout << "+";
	gotoxy(boxx, boxy + 4);	cout << "+" << " Ho Doc Gia: ";
	gotoxy(boxx + boxs + 1, boxy + 4);	cout << "+";
	gotoxy(boxx, boxy + 5);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 5);	cout << "+";
	gotoxy(boxx, boxy + 6);	cout << "+" << " Ten Doc Gia: ";
	gotoxy(boxx + boxs + 1, boxy + 6);	cout << "+";
	gotoxy(boxx, boxy + 7);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 7);	cout << "+";
	gotoxy(boxx, boxy + 8);	cout << "+" << " Gioi Tinh: ";
	gotoxy(boxx + boxs + 1, boxy + 8);	cout << "+";
	gotoxy(boxx, boxy + 9);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 9);	cout << "+";
	gotoxy(boxx, boxy + 10);	cout << "+" << " Trang thai the: ";
	gotoxy(boxx + boxs + 1, boxy + 10);	cout << "+";
	gotoxy(boxx, boxy + 11);	cout << "+";
	for (int i = 1; i < boxs + 1; i++)
		cout << "+";
}

void Box_Nhap_Ngay_Muon()
{
	textcolor(15);
	gotoxy(boxx, boxy); cout << "+";
	for (int i = 1; i <= boxs + 1; i++)
		cout << "+";
	gotoxy(boxx, boxy + 1);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 1);	cout << "+";
	gotoxy(boxx, boxy + 2);	cout << "+" << " Nam Muon: ";
	gotoxy(boxx + boxs + 1, boxy + 2);	cout << "+";
	gotoxy(boxx, boxy + 3);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 3);	cout << "+";
	gotoxy(boxx, boxy + 4);	cout << "+" << " Thang Muon: ";
	gotoxy(boxx + boxs + 1, boxy + 4);	cout << "+";
	gotoxy(boxx, boxy + 5);	cout << "+";
	gotoxy(boxx + boxs + 1, boxy + 5);	cout << "+";
	gotoxy(boxx, boxy + 6);	cout << "+" << " Ngay Muon: ";
	gotoxy(boxx + boxs + 1, boxy + 6);	cout << "+";
	gotoxy(boxx, boxy + 7);	cout << "+";
	for (int i = 1; i <= boxs + 1; i++)
		cout << "+";
}
//===khung Frame Nhap===
void Frame_Dau_Sach(int x, int y)
{
	gotoxy(40, 15);
	textcolor(112);
	gotoxy(x, y - 1);		cout << "                           ";
	gotoxy(x, y);		cout << "      NHAP VAO MA ISBN     ";
	gotoxy(x, y + 1);		cout << " ";
	gotoxy(x + 1, y + 1); 	cout << "                          ";
	gotoxy(x + 26, y + 1); 	cout << " ";
	gotoxy(x, y + 2); 	cout << "                          ";
	textcolor(15);
}

void Frame_Doc_Gia(int x, int y)
{
	gotoxy(40, 15);
	textcolor(112);
	gotoxy(x, y - 1);		cout << "                           ";
	gotoxy(x, y);		cout << "    NHAP VAO MA DOC GIA    ";
	gotoxy(x, y + 1);		cout << " ";
	gotoxy(x + 1, y + 1); 	cout << "                         ";
	gotoxy(x + 26, y + 1); 	cout << " ";
	gotoxy(x, y + 2); 	cout << "                           ";
	textcolor(15);
}

void Frame_Muc_Sach(int x, int y)
{
	gotoxy(40, 15);
	textcolor(112);
	gotoxy(x, y - 1);		cout << "                           ";
	gotoxy(x, y);		cout << "      NHAP VAO MA SACH     ";
	gotoxy(x, y + 1);		cout << " ";
	gotoxy(x + 1, y + 1);	cout << "                         ";
	gotoxy(x + 26, y + 1); 	cout << " ";
	gotoxy(x, y + 2);		cout << "                           ";
	textcolor(15);
}

void Frame_Ten_Sach(int x, int y)
{
	gotoxy(40, 15);
	textcolor(112);
	gotoxy(x, y - 1);		cout << "                           ";
	gotoxy(x, y);		cout << "      NHAP VAO TEN SACH    ";
	gotoxy(x, y + 1);		cout << " ";
	gotoxy(x + 1, y + 1);	cout << "                         ";
	gotoxy(x + 26, y + 1);	cout << " ";
	gotoxy(x, y + 2);		cout << "                           ";
	textcolor(15);
}
int Xac_Nhan_Xoa()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	HighLight();
	cout << "                                 ";
	gotoxy(40, 16); cout << "                                 ";
	gotoxy(40, 17); cout << "  BAN CO CHAC CHAN XOA HAY KHONG?";
	gotoxy(40, 18); cout << "                                 ";
	gotoxy(40, 19); cout << "     YES                NO       ";
	gotoxy(40, 20); cout << "                                 ";

	int keyhit;
	do {
		gotoxy(45, 19);
		switch (x)
		{
		case 45:
			gotoxy(45, 19);
			cout << "YES";
			break;
		case 64:
			gotoxy(64, 19);
			cout << "NO";
			break;
		}
		keyhit = getch();
		if (keyhit == LEFT)
		{
			gotoxy(45, 19);
			textcolor(112);
			switch (x)
			{
			case 45:
				gotoxy(45, 19);
				cout << "YES";
				break;
			case 64:
				gotoxy(64, 19);
				cout << "NO";
				break;
			}
			x -= 19;	// 64-45 , nhay trai phai
			if (x != 45)
				x = 64;
		}
		else if (keyhit == RIGHT)
		{
			gotoxy(45, 19);
			textcolor(112);
			switch (x)
			{
			case 45:
				gotoxy(45, 19);
				cout << "YES";
				break;
			case 64:
				gotoxy(64, 19);
				cout << "NO";
				break;
			}
			x += 19;
			if (x != 64)
				x = 45;
		}
		else if (x == 45 && keyhit == ENTER)  // dong y xoa
		{
			gotoxy(boxx + 32, 29);
			cout << "XOA THANH CONG";
			Normal();
			Sleep(1000);
			return 1;
		}
		else if (x == 64 && keyhit == ENTER) // khong xoa
			return 0;
	} while (true);
}

int Xac_Nhan_Luu_File()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	HighLight();
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON LUU FILE KHONG?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";

	int keybhit;
	do {
		gotoxy(45, 19);
		switch (x)
		{
		case 45:
			gotoxy(45, 19);
			cout << "YES";
			break;
		case 64:
			gotoxy(64, 19);
			cout << "NO";
			break;
		}
		keybhit = getch();
		if (keybhit == LEFT)
		{
			gotoxy(45, 19);
			switch (x)
			{
			case 45:
				gotoxy(45, 19);
				cout << "YES";
				break;
			case 64:
				gotoxy(64, 19);
				cout << "NO";
				break;
			}
			x -= 19;
			if (x != 45)
				x = 64;
		}
		else if (keybhit == RIGHT)
		{
			gotoxy(45, 19);
			switch (x)
			{
			case 45:
				gotoxy(45, 19);
				cout << "YES";
				break;
			case 64:
				gotoxy(64, 19);
				cout << "NO";
				break;
			}
			x += 19;
			if (x != 64)
				x = 45;
		}
		else if (x == 45 && keybhit == ENTER)
		{
			gotoxy(boxx + 32, 29);
			cout << "LUU FILE THANH CONG";
			Normal();
			Sleep(1000);
			return 1;
		}
		else if (x == 64 && keybhit == ENTER)
			return 0;
	} while (true);
}
