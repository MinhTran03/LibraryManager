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
enum ExeptionMuonSach
{
	Accept,
	BiKhoaThe,
	SachBiMat,
	GiuQua7Ngay,
	MuonDuSach,
	KeyLoop
};

struct DOCGIA
{
	// 0001 ... 9999
	int maDocGia;
	string ho;
	string ten;
	GioiTinh gioiTinh;
	TrangThaiTheDG trangThai;

	LIST_MUONTRA listMuonTra = LIST_MUONTRA();

	/// <summary>
	/// Lấy ToString của DOCGIA và in ra màn hình
	/// </summary>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
	void Print(MYPOINT location, Color backColor, Color textColor);

	/// <summary>
	/// Chuyển obj DOCGIA thành line string để in dưới dạng List
	/// </summary>
	/// <returns>DOCGIA as string in List</returns>
	string ToString();

	/// <summary>
	/// Chuyển obj DOCGIA thành line string để lưu vô file text
	/// </summary>
	/// <returns>DOCGIA as string in File</returns>
	string ToStringFile();

	/// <summary>
	/// Kiểm tra xem DOCGIA đủ điều kiện mượn sách
	/// 0> Không làm mất sách
	/// 1> Không giữ sách quá 7 ngày
	/// 2> Thẻ độc giả đang hoạt động
	/// 3> Mượn tối đa 3 sách
	/// </summary>
	/// <returns>ExeptionMuonSach</returns>
	ExeptionMuonSach IsMuonSach();

	/// <summary>
	/// Chuyển obj DOCGIA mượn sách quá hạn thành line string để in dưới dạng List
	/// </summary>
	/// <returns>DOCGIA quá hạn as string in List</returns>
	string* ToStringQuaHan(LIST_DAUSACH listSach, int& count);
};

struct NODE_DOCGIA
{
	DOCGIA data;

	NODE_DOCGIA* pLeft;
	NODE_DOCGIA* pRight;

	/// <summary>
	/// Constructor
	/// </summary>
	NODE_DOCGIA(DOCGIA& data);
};

typedef NODE_DOCGIA* LIST_DOCGIA;

#pragma region LIST_DOCGIA

// kiem tra xem doc gia co duoc phep xoa hay khong
bool IsDelete(DOCGIA& docGia);

// Ghi du lieu ma doc gia ra file text
bool WriteMaDGToFile(string path, LIST_DOCGIA listDG);

// Ghi du lieu doc gia ra file text
bool WriteToFile(LIST_DOCGIA lstDG, string path);

// Remove ma doc gia from array khi them moi doc gia
void RemoveMaDG(LIST_DOCGIA listDG);

// Doc mang MADOCGIA tu file
bool ReadMaDGFromFile(string path);

// so node cua cay
int Size(LIST_DOCGIA listDG);


string* GetAllStringFileNodeLRN(LIST_DOCGIA listDG);

// Doc tu file txt
bool ReadFromFile(LIST_DOCGIA& listDG,string path);

// sinh madocgia ngau nhien tu dong
int GetRandomMaDG(LIST_DOCGIA listDG);

// Chuyen vector string thanh doc gia
DOCGIA ParseVectorStringDG(string* data);

// ...
string* GetDGToListString(DOCGIA docGia);

// Giai phong vung nho
void FreeMemory(NODE_DOCGIA* root);

// form nhap doc gia moi
DOCGIA InputDocGia(int maThe, RECTANGLE rect);

// khoi toa cay
void Init(LIST_DOCGIA& listDG);

// them node
void Insert(LIST_DOCGIA& listDG, DOCGIA docGia);

// tim doc gia dua vao maDocGia
NODE_DOCGIA* Search(LIST_DOCGIA listDG, int maDocGia);

// ...
string* GetAllStringNode(LIST_DOCGIA listDG, int& count);

// ...
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);

// ...
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);

// xoa 1 doc gia
bool DeleteNode(LIST_DOCGIA& listDG, DOCGIA docGia);

// In ds doc gia: mode = 1 (Sort theo maDG)
//                mode = 2 (Sort theo hoTen)
string PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode = 1, Menu_Mode m = Both);

// ...
void PrintStringDocGia(string data, MYPOINT location);

// ...
string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int& page, Menu_Mode mode, int line = 0);

// luu list muon tra vo file
void DuyetLuuFile(LIST_DOCGIA lstDG, string defaultPath);
void DuyetDocFile(LIST_DOCGIA& lstDG, string path);

// Show ds qua han
void ShowListQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG);

#pragma endregion

/// <summary>
///  Hiện form sửa thông tin DOCGIA
/// </summary>
/// <param name="docGia">DOCGIA cần chỉnh sửa</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DOCGIA</returns>
DOCGIA InputFixDocGia(RECTANGLE rect, DOCGIA docGia);