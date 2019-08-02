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
	/// In ra SACH dưới dạng list
	/// </summary>
	/// <returns>SACH as string in List</returns>
	string ToString();
	/// <summary>
	/// Chuyển obj SACH thành line string để lưu vơ file text
	/// </summary>
	/// <returns>SACH as string in File</returns>
	string ToStringFile();
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
	// Duyet lay kich co cua ds Sach
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
	// constructor Init ds moi

	LIST_SACH();
	// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
	bool ReadFromFile(string path);
	// Doc obj SACH tu file
	bool WriteToFile(string path);
	// Thuat toan tu sinh ma sach
	string AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1]);
	// Them vao cuoi ds sach
	void AddTail(NODE_SACH& node);
	// Tim sach theo ma
	NODE_SACH* Search(string maSach);
	// Xoa node dau tien trong dslk
	bool DeleteFirst();
	// Xoa node sau 1 node p
	bool DeleteAfter(NODE_SACH* beforeNode);
	// Xoa 1 sach dua vao ma sach
	bool Delete(string maSach);
	// Kiem tra LIST_SACH co xoa duoc hay khong
	bool CanDelete();
	// kiem tra sach cho muon duoc
	bool IsChoMuonDuoc();
};

string GetMaDauSach(string maSach);
