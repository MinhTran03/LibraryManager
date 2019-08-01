/*
	Nhap vao 30000 so phan biet khac nhau trong pham vi tu 0 den 32000.
	Sort
	Tinh thoi gian thuc thi chuong trinh
*/
#include <iostream>
#include <time.h>
#include <Windows.h>

const int CAC_SO = 10;
const int MAX = 15;
const int SO_BYTE = MAX / 8 + 1;

void GoToXY(int x, int y)
{
	COORD co = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

int WhereX(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int WhereY(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}

void Lietke(unsigned char A[], unsigned int cols[])
{
	unsigned int mask = 0x80;
	GoToXY(5, 0);
	std::cout << "SO DA DUOC SAP: ";
	for (int i = 0; i < SO_BYTE; i++)
	{
		mask = 0x80;
		for (int j = 0; j < 8; j++)
		{
			Sleep(1000);
			GoToXY(cols[8 * i + j], 1);
			if ((A[i] & mask) == mask)
			{
				GoToXY(cols[8 * i + j], 0);
				std::cout << i * 8 + j << " ";
			}
			mask = mask >> 1;
		}
	}
}

int main()
{
	srand((unsigned int)time((time_t)NULL));
	unsigned char A[SO_BYTE] = { 0 };
	unsigned int cols[SO_BYTE * 8] = { 0 };
	int so;
	int byte, bit, mask;
	unsigned int n = 0;
	GoToXY(20, 1);
	for (int i = 0; i < SO_BYTE; i++)
	{
		std::cout << "Byte " << i + 1 << ": ";
		std::cout << "[ ";
		for (int j = 0; j < 7; j++)
		{
			cols[8 * i + j] = WhereX();
			std::cout << 0 << ", ";
		}
		cols[8 * i + 7] = WhereX();
		std::cout << 0 << "] ";
	}
	// Lay thoi gian bat dau

	int row = n;
	do
	{
		so = rand() % MAX + 1; //tra ve so ngau nhien tu 0 -> MAX -1
		Sleep(1000);
		GoToXY(5, 3 + row++);
		std::cout << "So duoc random: " << so;

		byte = so / 8;
		bit = so % 8;
		switch (bit)
		{
		case 0:
			mask = 0x80;
			break;
		case 1:
			mask = 0x40;
			break;
		case 2:
			mask = 0x20;
			break;
		case 3:
			mask = 0x10;
			break;
		case 4:
			mask = 0x8;
			break;
		case 5:
			mask = 0x4;
			break;
		case 6:
			mask = 0x2;
			break;
		case 7:
			mask = 0x1;
			break;
		}
		if ((A[byte] & mask) == 0)
		{
			n++;
			A[byte] = A[byte] | mask;

			Sleep(1000);
			GoToXY(cols[byte * 8 + bit], 1);
			std::cout << 1;
		}
		else
		{
			Sleep(1000);
			GoToXY(5, 3 + row++);
			std::cout << "So bi trung";
		}
	} while (n < CAC_SO);

	Lietke(A, cols);

	GoToXY(30, 30);
	system("pause");
	return 0;
}