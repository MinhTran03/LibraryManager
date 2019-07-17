#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <sstream>
#include <ctime>
#include <Windows.h>
#define MAX 100
#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75 
#define boxx 15 //Vi tri x bat dau cua box
#define boxy 13 //Vi tri y bat dau cua box
#define boxs 60 //Box size
#define tabx 6 // vi tri x bat dau cua table
#define taby 4  // vi tri y bat dau cua table
#define tabs 90 // table box
#define tabw 23 // table hight

#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64

#define ArrowRIGHT 27
#define ArrowLEFT 26
#define ArrowUP 25
#define ArrowDOWN 24
#include<mylib.h>
using namespace std;

void Table()
{
	SetWindow(120, 40);
	gotoxy(35, 2);
	gotoxy(tabx, taby);
	cout << "*";
	for (int i = 1; i < tabs - 13; i++)   // ve hang ngang dau tien
		cout << "*";
	cout << "*";
	for (int i = 1; i < tabw + 1; i++)  // ve cot dau tien
	{
		gotoxy(tabx, taby + i);
		cout << "*";
	}
	for (int i = 1; i < tabw + 1; i++)   // ve cot cuoi
	{
		gotoxy(tabx + tabs - 13, taby + i);
		cout << "*";
	}
	gotoxy(tabx, taby + tabw);
	cout << "*";
	for (int i = 1; i < tabs - 13; i++)  // hang cuoi
	{
		gotoxy(tabx + i, taby + tabw);
		cout << "*";
	}
	gotoxy(tabx + tabs - 13, taby + tabw);
	cout << "*";
	// ISBN
	gotoxy(tabx + 3, taby + 1);
	gotoxy(tabx + 8, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)  // cot tiep theo 
	{
		gotoxy(tabx + 8, taby + i); cout << "*";  // cách cot dau 8
	}
	gotoxy(tabx, taby + 2);
	cout << char(195);
	for (int i = 1; i < tabs - 13; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << "*";
	}
	gotoxy(tabx + 8, taby + 2); cout << "*";
	gotoxy(tabx + tabs - 13, taby + 2); cout << "*";
	gotoxy(tabx + 8, taby + tabw); cout << "*";

	// Ten Sach
	gotoxy(tabx + 12, taby + 1);
	gotoxy(tabx + 22, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 22, taby + i); cout << "*";
	}
	gotoxy(tabx + 22, taby + 2); cout << "*";
	gotoxy(tabx + 22, taby + tabw); cout << "*";

	// Tac Gia
	gotoxy(tabx + 26, taby + 1);
	gotoxy(tabx + 35, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 35, taby + i); cout << "*";
	}
	gotoxy(tabx + 35, taby + 2); cout << "*";
	gotoxy(tabx + 35, taby + tabw); cout << "*";

	//The loai
	gotoxy(tabx + 36, taby + 1);
	gotoxy(tabx + 45, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 45, taby + i); cout << "*";
	}
	gotoxy(tabx + 45, taby + 2); cout << "*";
	gotoxy(tabx + 45, taby + tabw); cout << "*";

	//So trang
	gotoxy(tabx + 47, taby + 1);
	gotoxy(tabx + 55, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 55, taby + i); cout << "*";
	}
	gotoxy(tabx + 55, taby + 2); cout << "*";
	gotoxy(tabx + 55, taby + tabw); cout << "*";

	//Nam XB
	gotoxy(tabx + 57, taby + 1);
	gotoxy(tabx + 65, taby); cout << "*";
	for (int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 65, taby + i); cout << "*";
	}
	gotoxy(tabx + 65, taby + 2); cout << "*";
	gotoxy(tabx + 65, taby + tabw); cout << "*";
	// So lan muon
	gotoxy(tabx + 68, taby + 1);
}
void Button()
{
	HighLight();
	gotoxy(20, 31); cout << "        ";
	gotoxy(20, 32); cout << "  XXXX  ";
	gotoxy(20, 33); cout << "        ";
	Normal();
}
void Frame(int x, int y)
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

int main()
{
	//							cout<<char(179)<<endl<<endl;// 	|
	//							cout<<char(217)<<endl<<endl;// 	_|
	//							cout<<char(195)<<endl<<endl;// 	|-
	//							cout<<char(196)<<endl<<endl;//	-
	//							cout<<char(180)<<endl<<endl;//	-|
	//							cout<<char(194)<<endl<<endl;//	T
	//							cout<<char(193)<<endl<<endl;//	_L
	//							cout<<char(218)<<endl<<endl;//   L nguoc
	//							cout<<char(192)<<endl<<endl;//	L
		//Table();
		//Button();
	//	Frame(10,10);
	Box_Nhap_Ngay_Muon();
	int c = getch();
	//Frame(10,10);
}
