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

}