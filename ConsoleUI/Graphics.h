#pragma once
#include <Windows.h>
#include <string>
#include "Enums.h"
#include <iostream>
#include "Constants.h"

void GoToXY(int x, int y);
int WhereX(void);
int WhereY(void);
void SetTextColor(WORD color);
void SetBGColor(WORD color);
void ResizeConsole(int width, int height);
void Clrscr();
void HidePointer();
void ShowPointer();

void PutPixel(int x, int y, char c, WORD color);
void DrawLine(int x, int y, int width, char c, WORD color);
void ClearScreen(WORD color, int height = SCREEN_HEIGHT - FOOTER_HEIGHT);
void ClearLine(int lineNumber, int begin = 0, int end = 168, WORD color = 7);
void ClearArea(int x, int y, int width, int height, WORD color = 7, int s = 0);
void fullscreen();
void HightLight(std::string text, Color bgColor, Color textColor);
void NormalColor();
void MaximizeWindow();

// in trang
void ShowPageNumber(int currentPage, int totalPages, int x, int y);