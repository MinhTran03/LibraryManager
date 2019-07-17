#pragma once
#include <conio.h>
#include "DocGia.h"
#include "Structs.h"
#include "TextHandler.h"

struct FORMINFO
{
	int totalLine;
	BORDER border;
	RECTANGLE rect;
	std::string title;
	std::vector<std::string> labels;
	std::vector<int> rows;
	std::vector<int> cols;
	std::vector<int> colsLabel;

	FORMINFO(std::vector<std::string> labels, DOCGIA docGia, RECTANGLE rect, std::string title)
		: rect(rect), title(title), border(rect.location, rect.size)
	{
		this->labels = labels;
		this->totalLine = labels.size();
		for (int i = 1; i <= totalLine; i++)
		{

		}
	}
};