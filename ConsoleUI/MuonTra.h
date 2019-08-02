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
	string maSach; // key
	DATETIME ngayMuon; // key
	DATETIME ngayTra;
	TrangThaiMuonTra trangThai;
	/// <summary>
	/// Lấy ToString của đầu sách và in ra màn hình
	/// </summary>
	/// <param name="dauSach">Data DAUSACH can in</param>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
	void Print(DAUSACH dauSach, MYPOINT location, Color bgColor = BG_COLOR, Color textColor = TEXT_INPUT_COLOR);
	/// <summary>
	/// In ra DAUSACH bang cach chen | giua cac field, can DAUSACH de tim ten sach
	/// </summary>
	/// <param name="dauSach">Data DAUSACH can in</param>
	/// <returns>SACH as string in List</returns>
	string ToString(DAUSACH dauSach);
	/// <summary>
	/// In ra DAUSACH bang cach chen | giua cac field bao gom ca MUONTRA, can DAUSACH de tim ten sach 
	/// </summary>
	/// <param name="dauSach">Data DAUSACH can in</param>
	/// <returns>SACH as string in List</returns>
	string ToStringMuonSach(DAUSACH dauSach);
	/// <summary>
	/// Tao line string de ghi ra file
	/// </summary>
	/// <returns>string</returns>
	string ToStringFile();
	/// <summary>
	/// Kiem tra SACH qua han hay khong
	/// </summary>
	/// <returns>bool</returns>
	bool IsQuaHan();
	/// <summary>
	/// Lay so ngay qua han cua sach
	/// </summary>
	/// <returns>int</returns>
	int GetSoNgayQuaHan();
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

	/// <summary>
	/// Constructor Init ds moi
	/// </summary>
	LIST_MUONTRA();
	/// <summary>
	/// Kiem tra trung key [maSach, ngayMuon] co trung khong
	/// </summary>
	/// <param name="maSach"> Ma SACH de truy cap node </param>
	/// <returns>bool</returns>
	bool IsLoopKey(string maSach);
	/// <summary>
	/// Kiem tra co rong kohng
	/// </summary>
	/// <returns>bool</returns>
	bool IsEmpty();
	/// <summary>
	/// Hien form muon sach
	/// </summary>
	/// <param name="listDS"> List DAUSACH chua data can in </param>
	/// <param name="location"> Location </param>
	/// <param name="mode"> Lua chon giua cac che do hien thi </param>
	/// <param name="totalLine"> tong so hang can de in data </param>
	/// <returns>string</returns>
	string ShowFormMuonSach(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode, int totalLine = 3);
	/// <summary>
	/// Tao moi mot Node
	/// </summary>
	/// <returns>NODE_MUONTRA*</returns>
	NODE_MUONTRA* MakeNode(MUONTRA muonTra);
	/// <summary>
	/// Them o dau
	/// </summary>
	/// <returns>void</returns>
	void InsertAtHead(MUONTRA muonTra);
	/// <summary>
	/// Them o cuoi
	/// </summary>
	/// <returns>void</returns>
	void InsertAtTail(MUONTRA muonTra);
	/// <summary>
	/// Xoa o dau
	/// </summary>
	/// <returns>void</returns>
	void DeleteAtHead();
	/// <summary>
	/// Xoa o cuoi
	/// </summary>
	/// <returns>void</returns>
	void DeleteAtTail();
	/// <summary>
	/// Tim muon tra theo Ma SACH
	/// </summary>
	/// <param name="maSach"> Ma SACH can tim </param>
	/// <returns>NODE_MUONTRA*</returns>
	NODE_MUONTRA* Search(string maSach);
	/// <summary>
	/// Hien thi cac SACH ma DOC GIA dang muon
	/// </summary>
	/// <param name="listDS"> List DAUSACH chua data can in </param>
	/// <param name="location"> Location </param>
	/// <param name="mode"> Both bao gom ca hai che do Show va Bat phim </param>
	/// <returns>string</returns>
	string Show(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode = Both);
	/// <summary>
	/// Duyet List lay Data, can DAU SACH de tim ten sach
	/// </summary>
	/// <param name="listDS"> List DAUSACH chua data can in </param>
	/// <param name="count"> Bo dem kich thuoc cua du lieu </param>
	/// <returns>string*</returns>
	string* GetAllNodeString(LIST_DAUSACH listDS, int& count);
	/// <summary>
	/// Duyet List lay Data kieu String, can DAU SACH de tim ten sach
	/// </summary>
	/// <param name="listDS"> List DAUSACH chua data can in </param>
	/// <param name="count"> Bo dem kich thuoc cua du lieu </param>
	/// <returns>string*</returns>
	string* GetAllNodeStringMuonSach(LIST_DAUSACH listDS, int& count);
	/// <summary>
	/// Xoa dua vao maSach
	/// </summary>
	/// <param name="maSach"> Ma SACH can tim </param>
	/// <returns>bool</returns>
	bool Delete(string maSach);
	/// <summary>
	/// Xoa sau node before
	/// </summary>
	/// <param name="beforeNode"> Node phia truoc </param>
	/// <returns>bool</returns>
	bool DeleteAfter(NODE_MUONTRA* beforeNode);
	/// <summary>
	/// Ghi ra filr text
	/// </summary>
	/// <param name="path"> Duong dan file </param>
	/// <returns>bool</returns>
	bool WriteToFile(string path);
	/// <summary>
	/// Doc tu file
	/// </summary>
	/// <param name="path"> Duong dan file </param>
	/// <returns>bool</returns>
	bool ReadFromFile(string path);
	/// <summary>
	/// Dem so Sach doc gia muon
	/// </summary>
	/// <returns>int</returns>
	int DuyetDSSachChuaTra();

};