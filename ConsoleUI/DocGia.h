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

static int MADOCGIAARR[MAX_DOCGIA];

struct DOCGIA
{
	// 0001 ... 9999
	int maDocGia;
	std::string ho;
	std::string ten;
	GioiTinh gioiTinh;
	TrangThaiTheDG trangThai;

	LIST_MUONTRA listMuonTra;

	// in ra node
	void Print(MYPOINT location, Color backColor, Color textColor);
	// chen | vao giua field
	std::string ToString();
};

struct NODE_DOCGIA
{
	DOCGIA data;

	NODE_DOCGIA* pLeft;
	NODE_DOCGIA* pRight;

	NODE_DOCGIA(DOCGIA& data);
};

typedef NODE_DOCGIA* LIST_DOCGIA;

// so node cua cay
int Size(LIST_DOCGIA listDG);
// Doc tu file txt
bool ReadFromFile(LIST_DOCGIA& listDG,std::string path);
// tao mang random maDocGia
void MakeRandomArrayMaDG(LIST_DOCGIA listDG);
// sinh madocgia ngau nhien tu dong
int GetRandomMaDG(LIST_DOCGIA listDG, int& position);
// ...
void SwapMaDG(int pos1, int pos2);
// Chuyen vector string thanh doc gia
DOCGIA ParseVectorString(std::vector<std::string> data);
// Giai phong vung nho
void FreeMemory(NODE_DOCGIA* root);
// form nhap doc gia moi
DOCGIA InputDocGia(int maThe, RECTANGLE rect);
// khoi toa cay
void Init(LIST_DOCGIA& listDG);
// them node
void Insert(LIST_DOCGIA& listDG, DOCGIA docGia);
// duyet cay
void NLR(LIST_DOCGIA listDG);
// tim doc gia dua vao maDocGia
NODE_DOCGIA* Search(LIST_DOCGIA listDG, int maDocGia);
// ...
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// ...
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// xoa 1 doc gia
bool DeleteNode(LIST_DOCGIA& listDG, DOCGIA docGia);
// In ds doc gia theo maDocGia tang dan
void PrintDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode = 1);