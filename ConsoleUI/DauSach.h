#pragma once
#include "Sach.h"

struct  TOPSACH
{
	string info;
	int soSachMuon;
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
};

struct DAUSACH
{
	char isbn[ISBN_MAXSIZE + 1];
	string tenSach;
	int soTrang = NULL;
	string tenTacGia;
	int namXuatBan = NULL;
	string tenTheLoai;
	int soLuotMuon = 0;

	LIST_SACH dsSach;

	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	void PrintFull(MYPOINT location, Color backColor, Color textColor);
	// chen | giua cac field
	string ToString();
	string ToStringMuonTra();
	// chuyen object dau sach thanh string luu file
	string ToStringFile();
};

struct LIST_DAUSACH
{
	int size = 0;
	DAUSACH* nodes[SODAUSACH_MAX];
	string* dsTheLoai;
	int soTheLoai = 0;

	#pragma region Display
	// Print list DAUSACH theo the loai (Sap xep theo ten)
	string PrintByTheLoai(MYPOINT location, string tenTheLoai);
	// In tat ca the loai thanh nhieu page
	string PrintAllTheLoai(MYPOINT location);
	// In tat ca dau sach
	string PrintAll(MYPOINT location, int& page, Menu_Mode mode = Menu_Mode::Show_Only);
	// tim sach theo ten (chua xong)
	void PrintFindBooks(MYPOINT location, string tenSach);
	#pragma endregion

	// Cap nhat dsTheLoai
	void INotifyDSTheLoai();
	// Giai phong
	void Deconstructor();
	// kiem tra theLoai sach da ton tai hay chua
	bool IsContainTheLoai(string theLoai);
	// Doc obj DAUSACH tu file
	bool ReadFromFile(string path);
	// Ghi du lieu dau sach ra file text
	bool WriteToFile(string path);
	// lay dau sach theo ISBN
	DAUSACH* GetDauSach(char isbn[ISBN_MAXSIZE + 1]);
	// Return true if list full (1000)
	bool IsFull();
	// Return true if list empty
	bool IsEmpty();
	
	// kiem tra dau sach da ton tai isbn hay chua
	bool IsContainISBN(char isbn[ISBN_MAXSIZE + 1]);
	// DAUSACH phai dung tham bien (&) vi neu dung tham tri thi node se mat sau khi ra khoi ham
	// Do dac tinh cua tham tri la copy vo node
	bool Insert(DAUSACH& node, int index);
	// Lay dau sach dua vao ten the loai
	DAUSACH* GetTheLoai(string tenTheLoai, int &count);
	// in sach theo ten sach (chua xong)
	DAUSACH* FindBooks(string tenSach, int& count);
	string PrintAllSearch(MYPOINT location, string tenSach, Menu_Mode mode);
	// tim vi tri cua dau sach theo isbn
	int GetLocateDauSach(char isbn[ISBN_MAXSIZE + 1]);
	// Xoa 1 dau sach dua vao ISBN
	bool DeleteDauSach(char isbn[ISBN_MAXSIZE + 1]);
};

DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect);
DAUSACH InputFixDauSach(LIST_DAUSACH listDS, RECTANGLE rect, DAUSACH dauSach);
string PrintTopDauSach(LIST_DAUSACH listDS, MYPOINT location);