#pragma once

enum Menu_Mode
{
	Show_Only,
	GetKey_Only,
	Both
};

enum Color
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Yellow = 6,
	White = 7,
	Gray = 8,
	Light_Blue = 9,
	Light_Green = 10,
	Light_Cyan = 11,
	Light_Red = 12,
	Light_Magenta = 13,
	Light_Yellow = 14,
	Bright_White = 15
};

enum Key
{
	_NULL = 0,
	SPACE = 32,
	ESC = 27,
	ENTER = 13,
	BACKSPACE = 8,
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	F2 = 60,
	F3 = 61,
	F4 = 62,
	F10 = 68,
	PAGE_DOWN = 81,
	PAGE_UP = 73,
	TAB = 9,

	NUMBER_ZERO = 48,
	NUMBER_NINE = 57,

	LETTER_A = 65,
	LETTER_Z = 90,
	LETTER_a = 97,
	LETTER_z = 122
};

enum WordType
{
	Word_Only,
	Name,
	Number_Only,
	Mix,
	Upper_Only,
	Lower_Only,
	Gender,
	DateTime,
	BirthDay,
	Year,
	All,
	Enum,
	Enum2
};

enum DialogResult
{
	OK,
	Cancel,
	Yes,
	No,
	Null,
	OK_Cancel,
	Yes_No
};

enum Align
{
	Left,
	Center
};

enum Border
{
	None,
	OneLine,
	TwoLine
};
