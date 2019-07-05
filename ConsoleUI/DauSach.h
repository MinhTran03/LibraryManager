#pragma once
#include "Sach.h"
#include "FileHandler.h"

struct DAUSACH
{
	char isbn[ISBN_MAXSIZE + 1] = "";
	std::string tenSach;
	int soTrang = NULL;
	std::string tenTacGia;
	int namXuatBan = NULL;
	std::string tenTheLoai;
	LIST_SACH dsSach;

	// hien form nhap DAUSACH
	DAUSACH Input(RECTANGLE rect);
	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	// chen | giua cac field
	std::string ToString();
};

struct ISBN_TENSACH
{
	char isbn[ISBN_MAXSIZE + 1] = "";
	std::string tenSach;
};

struct LIST_DAUSACH
{
	int size = 0;
	DAUSACH* nodes[SODAUSACH_MAX];
	std::vector<std::string> dsTheLoai;

	// kiem tra theLoai sach da ton tai hay chua
	bool IsContainTheLoai(std::string theLoai);
	// Doc obj DAUSACH tu file
	bool ReadFromFile(std::string path);
	// Return true if list full (1000)
	bool IsFull();
	// Return true if list empty
	bool IsEmpty();
	// DAUSACH phai dung tham bien (&) vi neu dung tham tri thi node se mat sau khi ra khoi ham
	// Do dac tinh cua tham tri la copy vo node
	bool Insert(DAUSACH& node, int index);
	// Print list DAUSACH theo the loai (Sap xep theo ten)
	std::string PrintByTheLoai(MYPOINT location, std::string tenTheLoai);
	// In tat ca the loai thanh nhieu page
	std::string PrintAllTheLoai(MYPOINT location);
	// Lay dau sach dua vao ten the loai
	std::vector<DAUSACH> GetTheLoai(std::string tenTheLoai);
	std::string PrintFindBooks(MYPOINT location, std::string tenSach);
	std::vector<std::string> FindBooks(std::string tenSach);
};