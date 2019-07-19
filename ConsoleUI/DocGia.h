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

	LIST_MUONTRA listMuonTra = LIST_MUONTRA();

	// in ra node
	void Print(MYPOINT location, Color backColor, Color textColor);
	// chen | vao giua field
	std::string ToString();
	// chuyen object dau sach thanh string luu file
	std::string ToStringFile();
};

struct NODE_DOCGIA
{
	DOCGIA data;

	NODE_DOCGIA* pLeft;
	NODE_DOCGIA* pRight;

	NODE_DOCGIA(DOCGIA& data);
};

typedef NODE_DOCGIA* LIST_DOCGIA;

// Ghi du lieu ma doc gia ra file text
bool WriteMaDGToFile(std::string path);
// Ghi du lieu doc gia ra file text
bool WriteToFile(LIST_DOCGIA lstDG, std::string path);
// Remove ma doc gia from array khi them moi doc gia
void RemoveMaDG();
// Doc mang MADOCGIA tu file
bool ReadMaDGFromFile(std::string path);
// so node cua cay
int Size(LIST_DOCGIA listDG);
// Doc tu file txt
bool ReadFromFile(LIST_DOCGIA& listDG,std::string path);
// sinh madocgia ngau nhien tu dong
int GetRandomMaDG(LIST_DOCGIA listDG);
// ...
void SwapMaDG(int pos1, int pos2);
// Chuyen vector string thanh doc gia
DOCGIA ParseVectorString(std::vector<std::string> data);
//
std::vector<std::string> GetDGtoVector(DOCGIA docGia);
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
std::vector<std::string> GetAllStringNode(LIST_DOCGIA listDG);
// ...
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// ...
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);
// xoa 1 doc gia
bool DeleteNode(LIST_DOCGIA& listDG, DOCGIA docGia);
// In ds doc gia: mode = 1 (Sort theo maDG)
//                mode = 2 (Sort theo hoTen)
std::string PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode = 1, Menu_Mode m = Both);
// ...
DOCGIA InputFixDocGia(RECTANGLE rect, DOCGIA docGia);
// ...
void PrintStringDocGia(std::string data, MYPOINT location);
// ...
std::string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int& page, Menu_Mode mode);
// luu list muon tra vo file
void DuyetLuuFile(LIST_DOCGIA lstDG);
void DuyetDocFile(LIST_DOCGIA& lstDG);