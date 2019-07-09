#pragma once
#include "MuonTra.h"

enum GioiTinh
{
	Nam,
	Nu
};
enum TrangThaiTheDG
{
	TheBiKhoa = 0,
	DangHoatDong = 1
};

struct DOCGIA
{
	// 0001 ... 9999
	char maDocGia[MADOCGIA_MAXKYTU + 1];
	std::string ho;
	std::string ten;
	GioiTinh gioiTinh;
	TrangThaiTheDG trangThai;

	LIST_MUONTRA listMuonTra;
};

struct NODE_DOCGIA
{
	DOCGIA data;

	NODE_DOCGIA* pLeft;
	NODE_DOCGIA* pRight;
};