#pragma once
#include <conio.h>
#include "DocGia.h"
#include "Structs.h"
#include "Displays.h"
#include "TextHandler.h"


void DocGiaInfo(RECTANGLE rect, DOCGIA docGia)
{
	std::string title = "THONG TIN DOC GIA";
	std::vector<std::string> docGiaInfo = GetDGtoVector(docGia);
	std::vector<std::string> labels = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	DrawRectangleBoder(rect);

	for (size_t i = 0; i < docGiaInfo.size(); i++)
	{
		GoToXY(rect.location.x + 2, rect.location.y + 1);
		cout << labels[i];
		GoToXY(rect.location.x + 8, rect.location.y + 1);
		cout << ":";
		GoToXY(rect.location.x + 10, rect.location.y + 1);
		cout << docGiaInfo[i];
	}

}