#pragma once

const int magicNumber = -1;

#pragma region Dau sach
const unsigned int ISBN_MAXSIZE = 6;
const unsigned int TENSACH_MAXSIZE = 50;
const unsigned int TENTACGIA_MAXSIZE = 50;
const unsigned int TENTHELOAI_MAXSIZE = 50;
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
const unsigned int MASACH_MAXSIZE = 10;
const unsigned int VITRI_MAXSIZE = 3;
#pragma endregion