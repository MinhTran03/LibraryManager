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
typedef NODE_DOCGIA* LIST_DOCGIA;

void FreeMemory(NODE_DOCGIA* root);

// khoi toa cay
void init(LIST_DOCGIA& cay);
// them node
void insert(LIST_DOCGIA& cay, DOCGIA input);
// duyet cay
void NLR(LIST_DOCGIA cay);
// tim node
NODE_DOCGIA* search(LIST_DOCGIA cay, DOCGIA input);
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// xoa 1 node la 
void DeleteNode(LIST_DOCGIA& t, DOCGIA input);
// them phan tu 
void Add(LIST_DOCGIA& cay, DOCGIA input);
