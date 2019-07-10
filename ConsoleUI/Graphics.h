#pragma once
#include <Windows.h>
#include <string>
#include "Enums.h"
#include <iostream>

void GoToXY(int x, int y);
int WhereX(void);
int WhereY(void);
void SetTextColor(WORD color);
void SetBGColor(WORD color);
void ResizeConsole(int width, int height);
void Clrscr();
void HidePointer();
void ShowPointer();

void ClearScreen(WORD color);
void ClearArea(int x, int y, int width, int height, WORD color = 7);
void fullscreen();
void HightLight(std::string text, Color bgColor, Color textColor);
void MaximizeWindow();