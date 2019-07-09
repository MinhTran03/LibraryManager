#pragma once
#include "Constants.h"
#include "DateTime.h"

enum TrangThaiMuonTra
{
	SachChuaTra = 0,
	SachDaTra = 1,
	LamMatSach = 2,
};

struct MUONTRA
{
	char maSach[MASACH_MAXSIZE + 1];
	DATETIME ngayMuon;
	DATETIME ngayTra;
	TrangThaiMuonTra trangThai;
};

struct NODE_MUONTRA
{
	MUONTRA data;
	NODE_MUONTRA* pNext;
	NODE_MUONTRA* pPrev;
};

struct LIST_MUONTRA
{
	NODE_MUONTRA* pHead;
	NODE_MUONTRA* pTail;
};