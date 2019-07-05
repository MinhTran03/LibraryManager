#pragma once
#include <iostream>
#include "Enums.h"
#include "Graphics.h"
#include <conio.h>
#include <string>
#include <vector>

struct CONDITION
{
	int maxLength;
	int minLength;
	WordType type;

	CONDITION(WordType type, int minLength, int maxlength)
		: maxLength(maxlength), type(type), minLength(minLength)
	{

	}
};

struct MYPOINT
{
	int x;
	int y;
	MYPOINT(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct MYSIZE
{
	int width;
	int height;
	MYSIZE(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
};

struct BORDER
{
	MYPOINT location;
	MYSIZE size;
	BORDER(MYPOINT location, MYSIZE size) : location(location.x, location.y), size(size.width, size.height)
	{
	}
	void Draw1Line(Color borderColor)
	{
		SetTextColor(borderColor);
		SetBGColor(Color::Black);
		// to 4 goc
		GoToXY(location.x, location.y);
		std::cout << char(218);
		GoToXY(location.x + size.width - 1, location.y);
		std::cout << char(191);
		GoToXY(location.x, location.y + size.height - 1);
		std::cout << char(192);
		GoToXY(location.x + size.width - 1, location.y + size.height - 1);
		std::cout << char(217);
		// to canh
		GoToXY(location.x + 1, location.y);
		std::cout << std::string(size.width - 2, char(196));
		GoToXY(location.x + 1, location.y + size.height - 1);
		std::cout << std::string(size.width - 2, char(196));
		for (int y = location.y + 1; y < location.y + size.height - 1; y++)
		{
			GoToXY(location.x, y);
			std::cout << char(179);
			GoToXY(location.x + size.width - 1, y);
			std::cout << char(179);
		}
	}
	void Draw2Line(Color borderColor)
	{
		SetTextColor(borderColor);
		SetBGColor(Color::Black);
		// to 4 goc
		GoToXY(location.x, location.y);
		std::cout << char(201);
		GoToXY(location.x + size.width - 1, location.y);
		std::cout << char(187);
		GoToXY(location.x, location.y + size.height - 1);
		std::cout << char(200);
		GoToXY(location.x + size.width - 1, location.y + size.height - 1);
		std::cout << char(188);
		// to canh
		GoToXY(location.x + 1, location.y);
		std::cout << std::string(size.width - 2, char(205));
		GoToXY(location.x + 1, location.y + size.height - 1);
		std::cout << std::string(size.width - 2, char(205));
		for (int y = location.y + 1; y < location.y + size.height - 1; y++)
		{
			GoToXY(location.x, y);
			std::cout << char(186);
			GoToXY(location.x + size.width - 1, y);
			std::cout << char(186);
		}
	}
};

struct BORDERTEXT
{
	BORDER border;
	BORDERTEXT(BORDER border) :border(border)
	{

	}
	void Draw1Line(std::string text, Align align = Align::Left, Color borderColor = Color::White)
	{
		int x = border.location.x + 1;
		int y = border.location.y + border.size.height / 2;
		if (align == Align::Center)
		{
			int lengthText = text.length();
			x += border.size.width / 2 - lengthText / 2 - lengthText % 2 - 1;
		}
		border.Draw1Line(borderColor);
		GoToXY(x, y);
		std::cout << text;
	}
};

struct LISTBORDERTEXT
{
	std::vector<std::string> labels;
	LISTBORDERTEXT(std::vector<std::string> labels) : labels(labels)
	{

	}
	void Draw(MYPOINT location, std::vector<int> widths, int row, Color borderColor = Color::White)
	{
		auto temp = location;
		for (int i = 0; i < labels.size(); i++)
		{
			auto b = BORDER(location, { widths[i] + 2, 3 + row + 1 });
			b.Draw1Line(borderColor);
			auto b1 = BORDERTEXT({ location, {widths[i] + 2, 3} });
			b1.Draw1Line(labels[i], Align::Center, borderColor);
			location.x += b1.border.size.width - 1;
			if (i > 0 && i < labels.size())
			{
				GoToXY(location.x - b1.border.size.width + 1, location.y);
				std::cout << char(194);
				GoToXY(location.x - b1.border.size.width + 1, location.y + 2);
				std::cout << char(197);
				GoToXY(location.x - b1.border.size.width + 1, location.y + 2 + row + 1);
				std::cout << char(193);
			}
		}

		GoToXY(temp.x, temp.y + 2);
		std::cout << char(195);
		GoToXY(location.x, location.y + 2);
		std::cout << char(180);


	}
};

struct RECTANGLE
{
	MYPOINT location;
	MYSIZE size;
	RECTANGLE(MYPOINT location, MYSIZE size) : location(location.x, location.y), size(size.width, size.height)
	{
	}
	void DrawCustom(Color color, char getChar)
	{
		SetTextColor(color);
		GoToXY(location.x, location.y);
		std::cout << std::string(size.width, getChar);
		GoToXY(location.x, location.y + size.height - 1);
		std::cout << std::string(size.width, getChar);
		/*for (int x = location.x; x < location.x + size.width; x++)
		{
			GoToXY(x, location.y);
			std::cout << getChar;
		}*/
		/*for (int x = location.x; x < location.x + size.width; x++)
		{
			GoToXY(x, location.y + size.height - 1);
			std::cout << getChar;
		}*/
		for (int y = location.y; y < location.y + size.height; y++)
		{
			GoToXY(location.x, y);
			std::cout << getChar;
		}
		for (int y = location.y; y < location.y + size.height; y++)
		{
			GoToXY(location.x + size.width - 1, y);
			std::cout << getChar;
		}
	}
	void Fill(Color borderColor, Color bgColor)
	{
		DrawCustom(borderColor, char(219));
		SetTextColor(bgColor);
		for (int i = location.y + 1; i < location.y + size.height - 1; i++)
		{
			/*for (int j = location.x + 1; j < location.x + size.width - 1; j++)
			{
				GoToXY(j, i);
				std::cout << char(219);
			}*/
			GoToXY(location.x + 1, i);
			std::cout << std::string(size.width - 2, char(219));
		}
	}
};

struct BUTTON
{
	RECTANGLE rect;
	BORDER border;
	std::string text;
	BUTTON(RECTANGLE rect, std::string text) : rect(rect), text(text), border(rect.location, rect.size)
	{
		if (rect.size.height > 1)
		{
			this->rect.location = { rect.location.x + 1, rect.location.y + 1 };
			this->rect.size = { rect.size.width - 2, rect.size.height - 2 };
		}
	}
	void Draw(Color bgColor, Color textColor, Color borderColor = Color::White,
		Align align = Center, Border borderStyle = Border::None)
	{
		switch (borderStyle)
		{
		case None:
		{
			RECTANGLE rectTemp = rect;
			if (rect.size.height != 1)
			{
				rectTemp.location = { rect.location.x - 1, rect.location.y - 1 };
				rectTemp.size = { rect.size.width + 2, rect.size.height + 2 };
			}
			rectTemp.Fill(bgColor, bgColor);
			break;
		}
		case OneLine:
			rect.Fill(bgColor, bgColor);
			border.Draw1Line(borderColor);
			break;
		case TwoLine:
			rect.Fill(bgColor, bgColor);
			border.Draw2Line(borderColor);
			break;
		default:
			break;
		}
		ShowText(bgColor, textColor, align);
	}
	void ShowText(Color bgColor, Color textColor, Align align = Center)
	{
		int lengthText = text.length();
		int x = rect.location.x;
		int y = rect.location.y + rect.size.height / 2;
		if (align == Center)
		{
			x = rect.location.x + rect.size.width / 2 - lengthText / 2;
		}
		SetTextColor(textColor);
		SetBGColor(bgColor);
		GoToXY(x, y);
		std::cout << text;
		GoToXY(rect.location.x, rect.location.y);
	}
};

struct CONFIRMDIALOG
{
	DialogResult result;
	MYPOINT location;
	MYSIZE size;
	CONFIRMDIALOG(MYPOINT location)
		: location(location), result(DialogResult::Null), size(0, 0)
	{
	}
	void Show(std::string message, DialogResult result, Color bgColor = Color::Cyan, Color btnColor = Color::Green, Color textColor = Color::White)
	{
		int padding = 10;
		Color selectColor = Color::Blue;
		int lengthText = message.length();
		size = { lengthText + padding, 7 };
		HidePointer();
		// To nen
		auto rect = RECTANGLE(location, size);
		auto border = BORDER(location, size);
		rect.Fill(bgColor, bgColor);
		border.Draw2Line(bgColor);

		// In button
		std::string text1, text2;
		int widthBtn = 8;
		int heightBtn = 1;
		int x = rect.location.x + rect.size.width / 4 - widthBtn / 2 - widthBtn % 2;
		int y = rect.location.y + rect.size.height / 2 + 1;
		switch (result)
		{
		case OK_Cancel:
			text1 = "OK";
			text2 = "CANCEL";
			break;
		case Yes_No:
			text1 = "YES";
			text2 = "NO";
			break;
		default:
			break;
		}
		auto btn1 = BUTTON({ {x, y}, {widthBtn, heightBtn} }, text1);
		btn1.Draw(selectColor, textColor);
		x += rect.size.width / 2 + 1;
		if (lengthText % 2 != 0) x += 1;
		auto btn2 = BUTTON({ {x, y}, {widthBtn, heightBtn} }, text2);
		btn2.Draw(btnColor, textColor);

		// In message
		y = rect.location.y + rect.size.height / 2 - 1;
		x = rect.location.x + padding / 2;
		SetTextColor(textColor);
		SetBGColor(bgColor);
		GoToXY(x, y);
		std::cout << message;
		GoToXY(rect.location.x, rect.location.y);

		// Bat phim
		char inputKey = NULL;
		bool isReturn = true;
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::RIGHT)
				{
					btn2.Draw(selectColor, textColor);
					btn1.Draw(btnColor, textColor);
					isReturn = false;
				}
				else if (inputKey == Key::LEFT)
				{
					btn1.Draw(selectColor, textColor);
					btn2.Draw(btnColor, textColor);
					isReturn = true;
				}
				continue;
			}
			if (inputKey == Key::ENTER)
			{
				if (isReturn)
				{
					if (result == OK_Cancel) this->result = OK;
					else this->result = Yes;
				}
				else
				{
					if (result == OK_Cancel) this->result = Cancel;
					else this->result = No;
				}
				return;
			}
		} while (!_kbhit());
	}
};
