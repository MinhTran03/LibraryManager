#pragma once
#include "Graphics.h"
#include "Enums.h"
#include "Structs.h"
#include "DauSach.h"
#include <iostream>

using namespace std;

void DrawRectangle(RECTANGLE rectangle, char getChar, Color textColor, Color bgColor);
void DrawRectangleBoder(RECTANGLE rectangle);
void DrawButton(RECTANGLE rectangle, std::string text, char getChar, Color textColor, Color bgColor);
void DrawMessageBox(MYPOINT point, string text, string& inputText, bool& isEnter,
	bool& isCancel, char getChar, Menu_Mode mode = Both, int maxyTu = 32);