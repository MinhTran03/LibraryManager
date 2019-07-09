#pragma once
#include "Sach.h"

struct DAUSACH
{
	char isbn[ISBN_MAXSIZE + 1];
	std::string tenSach;
	int soTrang = NULL;
	std::string tenTacGia;
	int namXuatBan = NULL;
	std::string tenTheLoai;

	LIST_SACH dsSach;

	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	// chen | giua cac field
	std::string ToString();
};

struct LIST_DAUSACH
{
	int size = 0;
	DAUSACH* nodes[SODAUSACH_MAX];

	std::vector<std::string> dsTheLoai;
	void Deconstructor();
	// kiem tra theLoai sach da ton tai hay chua
	bool IsContainTheLoai(std::string theLoai);
	// Doc obj DAUSACH tu file
	bool ReadFromFile(std::string path);
	// Return true if list full (1000)
	bool IsFull();
	// Return true if list empty
	bool IsEmpty();
	// kiem tra dau sach da ton tai isbn hay chua
	bool IsContainISBN(char isbn[ISBN_MAXSIZE + 1]);
	// DAUSACH phai dung tham bien (&) vi neu dung tham tri thi node se mat sau khi ra khoi ham
	// Do dac tinh cua tham tri la copy vo node
	bool Insert(DAUSACH& node, int index);
	// Print list DAUSACH theo the loai (Sap xep theo ten)
	std::string PrintByTheLoai(MYPOINT location, std::string tenTheLoai);
	// In tat ca the loai thanh nhieu page
	std::string PrintAllTheLoai(MYPOINT location);
	// In tat ca dau sach
	std::string PrintAll(MYPOINT location, Menu_Mode mode = Menu_Mode::Show_Only);
	// Lay dau sach dua vao ten the loai
	std::vector<DAUSACH> GetTheLoai(std::string tenTheLoai);
	// tim sach theo ten (chua xong)
	void PrintFindBooks(MYPOINT location, std::string tenSach);
	// in sach theo ten sach (chua xong)
	std::vector<std::string> FindBooks(std::string tenSach);
};

DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect);