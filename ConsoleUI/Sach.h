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
	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	// chen | giua cac field
	std::string ToString();
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

	bool IsEmpty();
	int Size();
	// in ra mh
	std::string PrintAll(MYPOINT location, Menu_Mode mode);
	void Deconstructor();
	// constructor Init ds moi
	LIST_SACH();
	// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
	bool ReadFromFile(std::string path);
	// Thuat toan tu sinh ma sach
	std::string AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1]);
	// Them vao cuoi ds sach
	void AddTail(NODE_SACH& node);
};