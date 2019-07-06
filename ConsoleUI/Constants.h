#pragma once
#include "Enums.h"

#pragma region DISPLAY
#define BG_COLOR Color::White
#define TEXT_INPUT_COLOR Color::Black
#define TEXT_INPUT_DEFAULT_COLOR Color::Gray
#define LABEL_TEXT_COLOR Color::Black

#define BUTTON_BG_COLOR Color::Green
#define BUTTON_TEXT_COLOR Color::Black
#define BUTTON_HIGHLIGHT_BG_COLOR Color::Blue
#define BUTTON_HIGHLIGHT_TEXT_COLOR Color::Black

#define BORDER_COLOR Color::Black
#define WARNING_TEXT_COLOR Color::Red
#pragma endregion

const int magicNumber = -1;

#pragma region Dau sach
const unsigned int ISBN_MAXSIZE = 6;
const unsigned int TENSACH_MAXSIZE = 30;
const unsigned int TENTACGIA_MAXSIZE = 30;
const unsigned int TENTHELOAI_MAXSIZE = 30;
const unsigned int SOTRANG_MAXKYTU = 6; // 6 SO
const unsigned int SODAUSACH_MAX = 50;

const unsigned int ISBN_WIDTH = ISBN_MAXSIZE + 1;
const unsigned int TENSACH_WIDTH = 30;
const unsigned int TENTACGIA_WIDTH = 30;
const unsigned int TENTHELOAI_WIDTH = 20;
const unsigned int SOTRANG_WIDTH = 9;
const unsigned int NAMXUATBAN_WIDTH = 13;
const unsigned int DAUSACH_TOTAL_WIDTH = ISBN_WIDTH + TENSACH_WIDTH + TENTACGIA_WIDTH + TENTHELOAI_WIDTH + SOTRANG_WIDTH + NAMXUATBAN_WIDTH + 7;
#pragma endregion

#pragma region Danh muc sach
const unsigned int MASACH_MAXSIZE = 11;
const unsigned int VITRI_MAXSIZE = 5;
#pragma endregion