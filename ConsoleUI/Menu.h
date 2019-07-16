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
	MYSIZE btnSize = MYSIZE(20, 5);
	int padding = 10;
	MYPOINT location;
	MENU(std::vector<std::string> labels, MYPOINT location) : location(location)
	{
		this->labels = labels;
		totalLine = labels.size();
		btnSize.width = MaxLengthTextLabels() + padding;
	}

	void AddButton(std::string btnText)
	{
		labels.push_back(btnText);
		totalLine++;
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
			rows.push_back(location.y + btnSize.height * i);
			btns.push_back(BUTTON({ {location.x, rows[i]}, btnSize }, labels[i]));
		}
	}
	void ShowBtns(std::vector<BUTTON>& btns, int mode)
	{
		for (auto item : btns)
		{
			//Sleep(15);
			item.Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
		}
		if (mode == 1)//mode 1 cho vertical => co arrow ">"
			btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine, 0);
		else
			btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine);
	}
	int ShowInVertical(Menu_Mode mode)
	{
		std::vector<BUTTON> btns;
		SetupButtonVertical(btns);
		if (mode == Show_Only || mode == Both)
		{
			ShowBtns(btns, 1);
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
				}
				if (inputKey == Key::ENTER)
				{
					//btns[currentLine].Draw(DISABLE_COLOR, textHLColor, DISABLE_COLOR, Align::Center, Border::TwoLine);
					return currentLine;
				}
				else if (inputKey == Key::ESC)
				{
					return Key::ESC;
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
			cols.push_back(location.x + btnSize.width * i);
			btns.push_back(BUTTON({ {cols[i], location.y}, btnSize }, labels[i]));
		}
	}
	int ShowInHorizontal(Menu_Mode mode)
	{
		std::vector<BUTTON> btns;
		SetupButtonHorizontal(btns);
		if (mode == Show_Only || mode == Both)
		{
			ShowBtns(btns, 0);
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
					if (inputKey == Key::LEFT)
					{
						if (currentLine > 0)
						{
							btns[currentLine--].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine);
						}
						else
						{
							btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							currentLine = totalLine - 1;
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine);
						}
					}
					else if (inputKey == Key::RIGHT)
					{
						if (currentLine < totalLine - 1)
						{
							btns[currentLine++].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine);
						}
						else
						{
							btns[currentLine].Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
							currentLine = 0;
							btns[currentLine].Draw(selectColor, textHLColor, selectColor, Align::Center, Border::TwoLine);
						}
					}
				}
				if (inputKey == Key::ENTER)
				{
					btns[currentLine].Draw(DISABLE_COLOR, textHLColor, DISABLE_COLOR, Align::Center, Border::TwoLine);
					return currentLine;
				}
				else if (inputKey == Key::PAGE_DOWN)
				{
					return Key::PAGE_DOWN;
				}
				else if (inputKey == Key::PAGE_UP)
				{
					return Key::PAGE_UP;
				}
				else if (inputKey == Key::ESC)
				{
					return Key::ESC;
				}
			} while (!_kbhit());
		}
		return -1;
	}

	void ClearInVertical()
	{
		/*std::vector<BUTTON> btns;
		SetupButtonVertical(btns);
		SetTextColor(Color::Black);
		for (auto item : btns)
		{
			item.Draw(bgColor, bgColor);
		}*/
		ClearArea(location.x, location.y, btnSize.width, btnSize.height * totalLine);
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

	void ShowDisableModeInHorizontal()
	{
		std::vector<BUTTON> btns;

		if (cols.size() != 0) cols.clear();
		for (size_t i = 0; i < labels.size(); i++)
		{
			cols.push_back(location.x + btnSize.width * i);
			btns.push_back(BUTTON({ {cols[i], location.y}, btnSize }, labels[i]));
		}

		for (auto item : btns)
		{
			item.Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
		}
		btns[currentLine].Draw(DISABLE_COLOR, textHLColor, DISABLE_COLOR, Align::Center, Border::TwoLine);
	}
	void ShowDisableModeInVertical()
	{
		std::vector<BUTTON> btns;

		if (rows.size() != 0) rows.clear();
		for (size_t i = 0; i < labels.size(); i++)
		{
			rows.push_back(location.y + btnSize.height * i);
			btns.push_back(BUTTON({ {location.x, rows[i]}, btnSize }, labels[i]));
		}

		for (auto item : btns)
		{
			item.Draw(bgColor, textColor, borderColor, Align::Center, Border::TwoLine);
		}
		btns[currentLine].Draw(DISABLE_COLOR, textHLColor, DISABLE_COLOR, Align::Center, Border::TwoLine);
	}
};