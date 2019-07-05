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