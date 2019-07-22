#pragma once
#include <conio.h>
#include "DocGia.h"
#include "Structs.h"
#include "Displays.h"
#include "TextHandler.h"

void DocGiaInfo(RECTANGLE rect, DOCGIA docGia)
{
	SetBGColor(BG_COLOR);
	SetTextColor(TEXT_INPUT_COLOR);
	string title = "THONG TIN DOC GIA";
	auto docGiaInfo = GetDGtoVector(docGia);
	//int size = SizeOfT(docGiaInfo);
	string labels[] = { "Ma doc gia", "Ho", "Ten", "Gioi tinh", "Trang thai the" };
	DrawRectangleBoder(rect);

	for (int i = 0; i < 5; i++)
	{
		GoToXY(rect.location.x + 2, rect.location.y + 1);
		cout << labels[i];
		GoToXY(rect.location.x + 18, rect.location.y + 1);
		cout << ":";
		GoToXY(rect.location.x + 20, rect.location.y + 1);
		cout << docGiaInfo[i];
		rect.location.y += 2;
	}
}