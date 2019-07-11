#pragma once
#include "MuonTra.h"
#include "TextHandler.h"
#include "Displays.h"

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
	int maDocGia;
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

DOCGIA ParseVectorString(std::vector<std::string> data);

void FreeMemory(NODE_DOCGIA* root);
DOCGIA InputDocGia(LIST_DOCGIA listDS, int maThe, RECTANGLE rect);
// khoi toa cay
void Init(LIST_DOCGIA& cay);
// them node
void Insert(LIST_DOCGIA& cay, DOCGIA input);
// duyet cay
void NLR(LIST_DOCGIA cay);
// tim node
NODE_DOCGIA* Search(LIST_DOCGIA cay, DOCGIA input);
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// xoa 1 node la 
void DeleteNode(LIST_DOCGIA& t, DOCGIA input);
// them phan tu 
void Add(LIST_DOCGIA& cay, DOCGIA input);
// Kiem tra ma doc gia co bi trung hay chua
//bool IsContainMADOCGIA(LIST_DOCGIA listDG, int maDocGia);
