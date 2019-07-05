#pragma once
#include "FormInput.h"
#include "Constants.h"

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
};

struct NODE_SACH
{
	SACH data;
	NODE_SACH* pNext;

	//~NODE_SACH();
};

struct LIST_SACH
{
	NODE_SACH* pHead;
	NODE_SACH* pTail;
};