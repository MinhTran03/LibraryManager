#pragma once
#include "Enums.h"

#pragma region DISPLAY
#define BG_COLOR Color::White
#define TEXT_INPUT_COLOR Color::Black
#define TEXT_INPUT_DEFAULT_COLOR Color::Gray
#define LABEL_TEXT_COLOR Color::Black

#define BUTTON_BG_COLOR Color::Green
#define BUTTON_TEXT_COLOR Color::White
#define BUTTON_HIGHLIGHT_BG_COLOR Color::Blue
#define BUTTON_HIGHLIGHT_TEXT_COLOR Color::Bright_White

#define BORDER_COLOR Color::Black
#define WARNING_TEXT_COLOR Color::Red
#define DISABLE_COLOR Color::Gray
#pragma endregion

const int magicNumber = -1;
const unsigned MAX_ROW_PER_PAGE = 33;
#define WARNING_CANT_DELETE_DS "DAU SACH DA CO DOC GIA MUON. KHONG DUOC XOA"
#define WARNING_CANT_DELETE_SACH "SACH DA CO DOC GIA MUON. KHONG DUOC XOA"
#define WARNING_CANT_FIX_SACH "SACH DA CO DOC GIA MUON. KHONG DUOC CHINH SUA"

#pragma region Dau sach
const unsigned int ISBN_MAXSIZE = 6;
const unsigned int TENSACH_MAXSIZE = 30;
const unsigned int TENTACGIA_MAXSIZE = 30;
const unsigned int TENTHELOAI_MAXSIZE = 30;
const unsigned int SOTRANG_MAXKYTU = 6; // 6 SO
const unsigned int SODAUSACH_MAX = 50;


const unsigned int ISBN_WIDTH = ISBN_MAXSIZE;
const unsigned int TENSACH_WIDTH = 30;
const unsigned int TENTACGIA_WIDTH = 21;
const unsigned int TENTHELOAI_WIDTH = 15;
const unsigned int SOTRANG_WIDTH = 8;
const unsigned int NAMXUATBAN_WIDTH = 4;
const unsigned int DAUSACH_TOTAL_WIDTH = ISBN_WIDTH + TENSACH_WIDTH + TENTACGIA_WIDTH + TENTHELOAI_WIDTH + SOTRANG_WIDTH + NAMXUATBAN_WIDTH + 7;
#pragma endregion

#pragma region Danh muc sach
const unsigned int MASACH_MAXSIZE = 11;
const unsigned int VITRI_MAXSIZE = 5;

const unsigned int MASACH_WIDTH = MASACH_MAXSIZE + 3;
const unsigned int VITRI_WIDTH = VITRI_MAXSIZE + 3;
const unsigned int TRANGTHAISACH_WIDTH = 16;
const unsigned int DMS_TOTAL_WIDTH = MASACH_WIDTH + VITRI_WIDTH + TRANGTHAISACH_WIDTH + 4;
#pragma endregion

#pragma region Doc Gia
const unsigned int MAX_DOCGIA = 100;

const unsigned int MADOCGIA_WIDTH = 10;
const unsigned int HODOCGIA_WIDTH = 20;
const unsigned int TENDOCGIA_WIDTH = 10;
const unsigned int GIOITINH_WIDTH = 10;
const unsigned int TRANGTHAIDG_WIDTH = 16;

#pragma endregion