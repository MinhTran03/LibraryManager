#pragma once
#include "Structs.h"

struct MENU
{
	std::vector<std::string> labels;
	Color selectColor = Color::Light_Blue;
	Color bgColor = Color::Black;
	Color textColor = Color::White;
	Color borderColor = Color::White;
	int currentLine = 0;
	int totalLine;
	std::vector<int> rows;
	std::vector<int> cols;
	MYSIZE size = MYSIZE(20, 5);
	int padding = 4;
	MYPOINT location;
	MENU(std::vector<std::string> labels, MYPOINT location) : location(location)
	{
		this->labels = labels;
		totalLine = labels.size();
		size.width = MaxLengthTextLabels() + padding;
	}

	int MaxLengthTextLabels()
	{
		int max = 0;
		for (auto label : labels)
		{
			if (label.length() > max) max = label.length();
		}
		return max;
	}
	void SetupButtonVertical(std::vector<BUTTON>& btns)
	{
		if (rows.size() != 0) rows.clear();
		for (int i = 0; i < labels.size(); i++)
		{
			rows.push_back(location.y + size.height * i);
			btns.push_back(BUTTON({ {location.x, rows[i]}, size }, labels[i]));
		}
	}
	void ShowBtns(std::vector<BUTTON>& btns)
	{
		for (auto item : btns)
		{
			//Sleep(15);
			item.Draw(bgColor, textColor, borderColor, Align::Left, Border::TwoLine);
		}
		btns[currentLine].Draw(selectColor, textColor, selectColor, Align::Center, Border::TwoLine);
	}
	int ShowInVertical()
	{
		std::vector<BUTTON> btns;
		SetupButtonVertical(btns);
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
				if (inputKey == Key::UP)
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
				else if (inputKey == Key::DOWN)
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
				else if (inputKey == Key::LEFT)
				{
					return -1;
				}
				else if (inputKey == Key::RIGHT)
				{
					return -2;
				}
			}
			if (inputKey == Key::ENTER)
			{
				return currentLine;
			}
		} while (!_kbhit());
		return -1;
	}
	void SetupButtonHorizontal(std::vector<BUTTON>& btns)
	{
		if (cols.size() != 0) cols.clear();
		for (int i = 0; i < labels.size(); i++)
		{
			cols.push_back(location.x + size.width * i);
			btns.push_back(BUTTON({ {cols[i], location.y}, size }, labels[i]));
		}
	}
	int ShowInHorizontal(int i)
	{
		std::vector<BUTTON> btns;
		SetupButtonHorizontal(btns);
		ShowBtns(btns);
		if (i == -1)return-1;
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