#pragma once
#include "Structs.h"

struct MENU
{
	std::vector<std::string> labels;
	Color selectColor = Color::Light_Blue;
	Color bgColor = BG_COLOR;
	Color textColor = TEXT_INPUT_COLOR;
	Color textHLColor = BUTTON_HIGHLIGHT_TEXT_COLOR;
	Color borderColor = BORDER_COLOR;
	int currentLine = 0;
	int totalLine;
	std::vector<int> rows;
	std::vector<int> cols;
	MYSIZE size = MYSIZE(20, 5);
	int padding = 10;
	MYPOINT location;
	MENU(std::vector<std::string> labels, MYPOINT location) : location(location)
	{
		this->labels = labels;
		totalLine = labels.size();
		size.width = MaxLengthTextLabels() + padding;
	}

	int MaxLengthTextLabels()
	{
		size_t max = 0;
		for (auto label : labels)
		{
			if (label.length() > max) max = label.length();
		}
		return max;
	}
	void SetupButtonVertical(std::vector<BUTTON>& btns)
	{
		if (rows.size() != 0) rows.clear();
		for (size_t i = 0; i < labels.size(); i++)
		{
			rows.push_back(location.y + size.height * i);
			btns.push_back(BUTTON({ {location.x, rows[i]}, size }, labels[i]));
		}
	}
	void ShowBtns(std::vector<BUTTON>& btns)
	{
		for (auto item : btns)
		{
			item.Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
		}
		btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
	}
	int ShowInVertical(Menu_Mode mode)
	{
		std::vector<BUTTON> btns;
		SetupButtonVertical(btns);
		if (mode == Show_Only || mode == Both)
		{
			ShowBtns(btns);
		}
		if (mode == GetKey_Only || mode == Both)
		{
			char inputKey = NULL;
			HidePointer();
			do
			{
				inputKey = _getch();
				if (inputKey == Key::_NULL) inputKey = _getch();
				if (inputKey == -32)
				{
					inputKey = _getch();
					if (inputKey == Key::UP)
					{
						if (currentLine > 0)
						{
							btns[currentLine--].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
						}
						else
						{
							btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							currentLine = totalLine - 1;
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
						}
					}
					else if (inputKey == Key::DOWN)
					{
						if (currentLine < totalLine - 1)
						{
							btns[currentLine++].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
						}
						else
						{
							btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							currentLine = 0;
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
						}
					}
					else if (inputKey == Key::LEFT)
					{
						return Key::LEFT;
					}
					/*else if (inputKey == Key::RIGHT)
					{
						return Key::RIGHT;
					}*/
				}
				if (inputKey == Key::ENTER)
				{
					return currentLine;
				}
			} while (!_kbhit());
		}
		return -1;
	}
	void SetupButtonHorizontal(std::vector<BUTTON>& btns)
	{
		if (cols.size() != 0) cols.clear();
		for (size_t i = 0; i < labels.size(); i++)
		{
			cols.push_back(location.x + size.width * i);
			btns.push_back(BUTTON({ {cols[i], location.y}, size }, labels[i]));
		}
	}
	int ShowInHorizontal()
	{
		std::vector<BUTTON> btns;
		SetupButtonHorizontal(btns);
		ShowBtns(btns);
		char inputKey = NULL;
		HidePointer();
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::LEFT)
				{
					if (currentLine > 0)
					{
						btns[currentLine--].Draw(bgColor, textColor, borderColor, Align::Left, Border::TwoLine);
						btns[currentLine].Draw(selectColor, textColor, selectColor, Align::Center, Border::TwoLine);
					}
					else
					{
						btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Left, Border::TwoLine);
						currentLine = totalLine - 1;
						btns[currentLine].Draw(selectColor, textColor, selectColor, Align::Center, Border::TwoLine);
					}
				}
				else if (inputKey == Key::RIGHT)
				{
					if (currentLine < totalLine - 1)
					{
						btns[currentLine++].Draw(bgColor, textColor, borderColor, Align::Left, Border::TwoLine);
						btns[currentLine].Draw(selectColor, textColor, selectColor, Align::Center, Border::TwoLine);
					}
					else
					{
						btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Left, Border::TwoLine);
						currentLine = 0;
						btns[currentLine].Draw(selectColor, textColor, selectColor, Align::Center, Border::TwoLine);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				return currentLine;
			}
		} while (!_kbhit());
		return -1;
	}
	void ClearInVertical()
	{
		std::vector<BUTTON> btns;
		SetupButtonVertical(btns);
		SetTextColor(Color::Black);
		for (auto item : btns)
		{
			item.Draw(bgColor, bgColor);
		}
	}
	void ClearInHorizontal()
	{
		std::vector<BUTTON> btns;
		SetupButtonHorizontal(btns);
		SetTextColor(Color::Black);
		for (auto item : btns)
		{
			item.Draw(bgColor, bgColor);
		}
	}
};