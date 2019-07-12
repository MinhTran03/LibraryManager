#pragma once
#include "FormInput.h"
#include "FileHandler.h"

enum TrangThaiSach
{
	ChoMuonDuoc = 0,
	DaMuon = 1,
	DaThanhLy = 2
};

struct SACH
{
	// "isbn(6 so)_masach(day so sinh tu dong(4 so))"
	std::string maSach;
	TrangThaiSach trangThai = ChoMuonDuoc;
	std::string viTri;

	// hien form nhap SACH
	SACH Input(RECTANGLE rect, std::string maSach);
	SACH InputFix(RECTANGLE rect);
	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	// chen | giua cac field
	std::string ToString();
	// chuyen object sach sach thanh string luu file
	std::string ToStringFile();
	// kiem tra sach co xoa duoc khong
	bool CanDelete();
};

struct NODE_SACH
{
	SACH data;
	NODE_SACH* pNext;

	// Khoi tao 1 node sach moi
	NODE_SACH(SACH& data);
};

struct LIST_SACH
{
	NODE_SACH* pHead;
	NODE_SACH* pTail;

	// kiem tra rong
	bool IsEmpty();
	// Duyet lay kich co cua ds Sach
	int Size();
	// in ra mh
	std::string PrintAll(MYPOINT location, Menu_Mode mode);
	// Delete
	void Deconstructor();
	// constructor Init ds moi
	LIST_SACH();
	// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
	bool ReadFromFile(std::string path);
	// Doc obj SACH tu file
	bool WriteToFile(std::string path);
	// Thuat toan tu sinh ma sach
	std::string AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1]);
	// Them vao cuoi ds sach
	void AddTail(NODE_SACH& node);
	// Tim sach theo ma
	NODE_SACH* Search(std::string maSach);
	// Xoa node dau tien trong dslk
	bool DeleteFirst();
	// Xoa node sau 1 node p
	bool DeleteAfter(NODE_SACH* beforeNode);
	// Xoa 1 sach dua vao ma sach
	bool Delete(std::string maSach);
	// Kiem tra LIST_SACH co xoa duoc hay khong
	bool CanDelete();
};