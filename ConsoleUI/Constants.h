#pragma once
#include "Enums.h"

#pragma region -----------------------------------------------------DISPLAY
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
#define TEXT_GUILD_COLOR Color::Light_Magenta

const unsigned int SCREEN_HEIGHT = 44;
const unsigned int FOOTER_HEIGHT = 5;
const unsigned MAX_ROW_PER_PAGE = 20;

const int MAGIC_NUMBER = -1;

#define WARNING_CANT_DELETE_DS "DAU SACH DA CO DOC GIA MUON. KHONG DUOC XOA"
#define WARNING_CANT_DELETE_SACH "SACH DA CO DOC GIA MUON. KHONG DUOC XOA"
#define WARNING_CANT_FIX_SACH "SACH DA CO DOC GIA MUON. KHONG DUOC CHINH SUA"
#pragma endregion

#pragma region -----------------------------------------------------Dau sach
const unsigned int ISBN_MAXSIZE = 6;
const unsigned int TENSACH_MAXSIZE = 36;
const unsigned int TENTACGIA_MAXSIZE = 30;
const unsigned int TENTHELOAI_MAXSIZE = 20;
const unsigned int SOTRANG_MAXKYTU = 6; // 6 SO
const unsigned int SODAUSACH_MAX = 100;

const unsigned int ISBN_WIDTH = ISBN_MAXSIZE;
const unsigned int TENSACH_WIDTH = 36;
const unsigned int TENTACGIA_WIDTH = 21;
const unsigned int TENTHELOAI_WIDTH = 20;
const unsigned int SOTRANG_WIDTH = 8;
const unsigned int NAMXUATBAN_WIDTH = 4;
const unsigned int SOLUOTMUON_WIDTH = 15;

const unsigned int DAUSACH_TOTAL_WIDTH = ISBN_WIDTH + TENSACH_WIDTH + TENTACGIA_WIDTH + TENTHELOAI_WIDTH + SOTRANG_WIDTH + NAMXUATBAN_WIDTH + 7;

const unsigned int TOPDAUSACH_MAX = 10;
#pragma endregion

#pragma region -----------------------------------------------------Danh muc sach
const unsigned int MASACH_MAXSIZE = 11;
const unsigned int VITRI_MAXSIZE = 5;

const unsigned int MASACH_WIDTH = MASACH_MAXSIZE + 3;
const unsigned int VITRI_WIDTH = VITRI_MAXSIZE + 3;
const unsigned int TRANGTHAISACH_WIDTH = 16;
const unsigned int DMS_TOTAL_WIDTH = MASACH_WIDTH + VITRI_WIDTH + TRANGTHAISACH_WIDTH + 4;
#pragma endregion

#pragma region -----------------------------------------------------Doc Gia
#define MADOCGIA_FILE_PATH "\\MaDocGiaArray.txt"

const unsigned int MAX_DOCGIA = 1000;

const unsigned int MADOCGIA_WIDTH = 10;
const unsigned int HODOCGIA_WIDTH = 20;
const unsigned int TENDOCGIA_WIDTH = 10;
const unsigned int GIOITINH_WIDTH = 10;
const unsigned int TRANGTHAIDG_WIDTH = 16;

const unsigned int DOCGIA_TOTAL_WIDTH = MADOCGIA_WIDTH + HODOCGIA_WIDTH + TENDOCGIA_WIDTH + GIOITINH_WIDTH + TRANGTHAIDG_WIDTH + 6;
#pragma endregion

#pragma region -----------------------------------------------------Muon tra
#define MUONTRA_FILE_PATH "\\MuonTra\\"

const unsigned int SONGAYMUON_TOIDA = 7;
const unsigned int SOSACHMUON_TOIDA = 3;

const unsigned int NGAY_WIDTH = 14;
const unsigned int TRANGTHAI_MUONTRA_WIDTH = 20;
const unsigned int SONGAYMUON_WIDTH = 16;

const unsigned int MUONTRA_TOTAL_WIDTH = MASACH_WIDTH + TENSACH_WIDTH + NGAY_WIDTH * 2 + 
							VITRI_WIDTH + TRANGTHAI_MUONTRA_WIDTH + SONGAYMUON_WIDTH + 8;
#pragma endregion