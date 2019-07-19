#pragma once
#include "Constants.h"
#include "DateTime.h"
#include "Structs.h"
#include "DauSach.h"

enum TrangThaiMuonTra
{
	SachChuaTra = 0,
	SachDaTra = 1,
	LamMatSach = 2,
};

struct MUONTRA
{
	std::string maSach;
	DATETIME ngayMuon;
	DATETIME ngayTra;
	TrangThaiMuonTra trangThai;

	void Print(DAUSACH dauSach, MYPOINT location, Color bgColor = BG_COLOR, Color textColor = TEXT_INPUT_COLOR);
	// can dau sach de tim ten sach
	std::string ToString(DAUSACH dauSach);
	std::string ToStringMuonSach(DAUSACH dauSach);
	// tao line string de ghi ra file
	std::string ToStringFile();
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

	LIST_MUONTRA();
	// kiem tra rong
	bool IsEmpty();
	// hien form muon sach
	std::string ShowFormMuonSach(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode, int totalLine = 3);
	// kiem tra rong
	// tao moi 1 node
	NODE_MUONTRA* MakeNode(MUONTRA muonTra);
	// them o dau
	void InsertAtHead(MUONTRA muonTra);
	// them o cuoi
	void InsertAtTail(MUONTRA muonTra);
	// xoa o dau
	void DeleteAtHead();
	// xoa o cuoi
	void DeleteAtTail();
	// Tim muon tra theo ma sach
	NODE_MUONTRA* Search(std::string maSach);
	// hien thi cac sach doc gia dang muon
	std::string Show(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode = Both);
	// duyet list lay data, can dau sach de tim ten sach
	std::string* GetAllNodeString(LIST_DAUSACH listDS);
	// duyet list lay data
	std::string* GetAllNodeStringMuonSach(LIST_DAUSACH listDS);
	// xoa dua vao maSach
	bool Delete(std::string maSach);
	// xoa sau node before
	bool DeleteAfter(NODE_MUONTRA* beforeNode);
	// ghi ra filr text
	bool WriteToFile(std::string path);
	// doc tu file
	bool ReadFromFile(std::string path);
};

