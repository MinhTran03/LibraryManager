#pragma once
#include "FormInput.h"
#include "FileHandler.h"

using namespace std;

enum TrangThaiSach
{
	ChoMuonDuoc = 0,
	DaMuon = 1,
	DaThanhLy = 2
};

struct SACH
{
	// "isbn(6 so)_masach(day so sinh tu dong(4 so))"
	string maSach;
	TrangThaiSach trangThai = ChoMuonDuoc;
	string viTri;

	/// <summary>
	/// In ra SACH dưới dạng list bang cach chen | giua cac field
	/// </summary>
	/// <returns>SACH as string in List</returns>
	string ToString();

	/// <summary>
	/// Chuyển obj SACH thành line string để lưu vơ file text
	/// </summary>
	/// <returns>SACH as string in File</returns>
	string ToStringFile();

	/// <summary>
	/// Hien form nhap SACH
	/// </summary>
	/// <param name="rect">kích thước hình chữ nhật dựa trên tọa độ x, y và width height</param>
	/// <param name="maSach">Mã sách truyền vào</param>
	/// <returns>SACH</returns>
	SACH Input(RECTANGLE rect, string maSach);

	/// <summary>
	/// Hien form sua sach SACH
	/// </summary>
	/// <param name="rect">kích thước hình chữ nhật dựa trên tọa độ x, y và width height</param>
	/// <returns>SACH</returns>
	SACH InputFix(RECTANGLE rect);

	/// <summary>
	/// Lấy ToString của đầu sách và in ra màn hình
	/// </summary>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);

	/// <summary>
	/// Kiem tra SACH co xoa duoc khong 
	/// </summary>
	/// <returns>bool</returns>
	bool CanDelete();
};

struct NODE_SACH
{
	SACH data;
	NODE_SACH* pNext;

	// Khoi tao 1 node sach moi
	NODE_SACH(SACH& data);
};

struct LIST_SACH
{
	NODE_SACH* pHead;
	NODE_SACH* pTail;

	/// <summary>
	/// Kiem tra LIST SACH co rong khong
	/// </summary>
	/// <returns>bool</returns>
	bool IsEmpty();

	/// <summary>
	/// Duyet lay kich co cua ds Sach
	/// </summary>
	/// <returns>int</returns>
	int Size();

	/// <summary>
	/// In danh sách SACH của toàn bộ LIST SACH
	/// </summary>
	/// <param name="location">Location</param>
	/// <param name="mode"> Lua chon giua cac che do hien thi</param>
	/// <returns>Phím người dùng ấn as string</returns>
	string PrintAll(MYPOINT location, Menu_Mode mode);

	/// <summary>
	/// In ra man hinh SACH cho muon duoc
	/// </summary>
	/// <param name="location">Location</param>
	/// <param name="mode"> Lua chon giua cac che do hien thi </param>
	/// <returns>Phím người dùng ấn as string</returns>
	string PrintAllChoMuonDuoc(MYPOINT location, Menu_Mode mode);

	/// <summary>
	/// Delete SACH
	/// </summary>
	/// <returns>void</returns>
	void Deconstructor();

	/// <summary>
	/// Constructor Init ds moi
	/// </summary>
	LIST_SACH();

	/// <summary>
	/// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
	/// </summary>
	/// <param name="path"> Duong dan file </param>
	/// <returns>bool</returns>
	bool ReadFromFile(string path);

	/// <summary>
	/// Doc obj SACH tu file
	/// </summary>
	/// <param name="path"> Duong dan file </param>
	/// <returns>bool</returns>
	bool WriteToFile(string path);

	/// <summary>
	/// Thuat toan tu sinh ma sach
	/// </summary>
	/// <param name="isbn"> Ma ISBN dua tren ma dang co + them  </param>
	/// <returns>string</returns>
	string AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1]);

	/// <summary>
	/// Them vao cuoi ds sach
	/// </summary>
	/// <param name="node"> Node SACH chua </param>
	/// <returns>void</returns>
	void AddTail(NODE_SACH& node);

	/// <summary>
	/// Tim sach theo Ma SACH
	/// </summary>
	/// <param name="maSach"> Ma SACH can tim </param>
	/// <returns>NODE_SACH*</returns>
	NODE_SACH* Search(string maSach);

	/// <summary>
	/// Xoa Node dau tien trong dslk
	/// </summary>
	/// <returns>bool</returns>
	bool DeleteFirst();

	/// <summary>
	/// Xoa Node sau 1 Node p
	/// </summary>
	/// <returns>bool</returns>
	bool DeleteAfter(NODE_SACH* beforeNode);

	/// <summary>
	/// Xoa 1 sach dua vao Ma SACH
	/// </summary>
	/// <returns>bool</returns>
	bool Delete(string maSach);

	/// <summary>
	/// Kiem tra LIST_SACH co xoa duoc hay khong
	/// </summary>
	/// <returns>bool</returns>
	bool CanDelete();

	/// <summary>
	/// Kiem tra SACH cho muon duoc
	/// </summary>
	/// <returns>bool</returns>
	bool IsChoMuonDuoc();
};

/// <summary>
/// Su dung ham Split de loc bo phan duoi Ma SACH de lay Ma DAUSACH
/// </summary>
/// <param name="maSach"> Ma SACH can de lay MADAUSACH</param>
/// <returns>string</returns>
string GetMaDauSach(string maSach);
