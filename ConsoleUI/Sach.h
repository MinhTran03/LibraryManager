#pragma once
#include "FormInput.h"
#include "FileHandler.h"
using namespace std;
enum TrangThaiSach
{
	ChoMuonDuoc = 0,
	DaMuon = 1,
	DaThanhLy = 2
};

struct SACH
{
	// "isbn(6 so)_masach(day so sinh tu dong(4 so))"
	string maSach;
	TrangThaiSach trangThai = ChoMuonDuoc;
	string viTri;

	// hien form nhap SACH
	SACH Input(RECTANGLE rect, string maSach);
	SACH InputFix(RECTANGLE rect);
	// in ra node
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
	// chen | giua cac field
	string ToString();
	// chuyen object sach sach thanh string luu file
	string ToStringFile();
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
	string PrintAll(MYPOINT location, Menu_Mode mode);
	// in ra mh sach cho muoc duoc
	string PrintAllChoMuonDuoc(MYPOINT location, Menu_Mode mode);
	// Delete
	void Deconstructor();
	// constructor Init ds moi
	LIST_SACH();
	// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
	bool ReadFromFile(string path);
	// Doc obj SACH tu file
	bool WriteToFile(string path);
	// Thuat toan tu sinh ma sach
	string AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1]);
	// Them vao cuoi ds sach
	void AddTail(NODE_SACH& node);
	// Tim sach theo ma
	NODE_SACH* Search(string maSach);
	// Xoa node dau tien trong dslk
	bool DeleteFirst();
	// Xoa node sau 1 node p
	bool DeleteAfter(NODE_SACH* beforeNode);
	// Xoa 1 sach dua vao ma sach
	bool Delete(string maSach);
	// Kiem tra LIST_SACH co xoa duoc hay khong
	bool CanDelete();
};