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
	GioiTinh gioiTinh = Nam;
	TrangThaiTheDG trangThai = DangHoatDong;

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

/// <summary>
/// Kiểm tra DOCGIA được phép xóa không
/// </summary>
/// <param name="docGia">DOCGIA cần kiểm tra</param>
/// <returns>true nếu được xóa</returns>
bool IsDelete(DOCGIA& docGia);

/// <summary>
/// Tính số DOCGIA có trong LIST_DOCGIA
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần tính size</param>
/// <returns>Số DOCGIA</returns>
int Size(LIST_DOCGIA listDG);

/// <summary>
/// Lấy info DOCGIA lưu vô list String
/// </summary>
/// <param name="docGia">DOCGIA cần lưu</param>
/// <returns>List string</returns>
string* GetDGToListString(DOCGIA docGia);

/// <summary>
/// <para>Sinh mã độc giả ngẫu nhiên</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA để lấy Size</param>
/// <returns>Mã độc giả</returns>
int GetRandomMaDG(LIST_DOCGIA listDG);

/// <summary>
/// <para>Remove msDocGia vừa random khỏi maDocGiaArr khi thêm DOCGIA</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA để lấy Size</param>
/// <returns>void</returns>
void RemoveMaDG(LIST_DOCGIA listDG);

/// <summary>
/// Hàm hủy toàn bộ DOCGIA khỏi RAM
/// </summary>
void FreeMemory(NODE_DOCGIA* root);

/// <summary>
/// Khởi tạo Cây Nhị Phân DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần khởi tạo</param>
void Init(LIST_DOCGIA& listDG);

/// <summary>
/// Thêm DOCGIA vào LIST_DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần thêm Node</param>
/// <param name="input">DOCGIA cần thêm</param>
void Insert(LIST_DOCGIA& listDG, DOCGIA docGia);

/// <summary>
/// Tìm DOCGIA dựa vào maDocGia
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần thêm Node</param>
/// <param name="maDocGia">mã DOCGIA cần tìm</param>
/// <returns>NULL nếu không tìm thấy</returns>
NODE_DOCGIA* Search(LIST_DOCGIA listDG, int maDocGia);

// ...
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q);

// ...
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q);

/// <summary>
/// Xóa 1 DOCGIA khỏi cây LIST_DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa DOCGIA cần xóa</param>
/// <param name="docGia">DOCGIA cần xóa</param>
/// <returns>false xóa thất bại</returns>
bool DeleteNode(LIST_DOCGIA& listDG, DOCGIA docGia);

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để in ra màn hình</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần convert</param>
/// <param name="count">Số độc giả đếm được (ban đầu = 0)</param>
/// <returns>List string sau khi convert</returns>
string* GetAllStringNode(LIST_DOCGIA listDG, int& count);

/// <summary>
/// In LIST_DOCGIA ra màn hình
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <param name="location">Location</param>
/// <param name="mode">
///	<para>Show_Only: Chỉ hiện</para>
///	<para>Both: Hiện và bắt phím</para>
/// </param>
/// <param name = "sortMode">
///	<para>1: Sort theo mã độc giả</para>
///	<para>0: Sort theo tên độc giả</para>
/// </param>
/// <returns>void</returns>
void PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode = 1, Menu_Mode m = Both);

/// <summary>
/// In string tại vị trí truyền vào
/// </summary>
/// <param name="data">string cần in</param>
/// <param name="location">Location</param>
/// <returns>void</returns>
void PrintStringDocGia(string data, MYPOINT location);

/// <summary>
/// In LIST_DOCGIA ra màn hình
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <param name="location">Location</param>
/// <param name="page">Lưu lại vị trí page đang đứng</param>
/// <param name="mode">
///	<para>Show_Only: Chỉ hiện</para>
///	<para>Both: Hiện và bắt phím</para>
/// </param>
/// <returns>Phím được nhấn As String</returns>
string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int& showPage, Menu_Mode mode);

/// <summary>
/// In LIST_DOCGIA quá hạn ra màn hình
/// </summary>
/// <param name="listDS">LIST_DAUSACH để tính số ngày quá hạn</param>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <returns>void</returns>
void PrintListQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG);

#pragma region --------------------DOC GHI FILE

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LRN
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần convert</param>
/// <returns>List string sau khi convert</returns>
string* GetAllStringFileNodeLRN(LIST_DOCGIA listDG);

/// <summary>
/// Đọc LIST_DOCGIA từ file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <param name="listDG">LIST_DOCGIA để lưu data</param>
/// <returns>true nếu file tồn tại</returns>
bool ReadFromFile(LIST_DOCGIA& listDG, string path);

/// <summary>
/// Đọc maDocGia từ file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu file tồn tại</returns>
bool ReadMaDGFromFile(string path);

/// <summary>
/// Ghi LIST_DOCGIA ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu</param>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu ghi file thành công</returns>
bool WriteToFile(LIST_DOCGIA lstDG, string path);

/// <summary>
/// Ghi maDocGia ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu mã</param>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu ghi file thành công</returns>
bool WriteMaDGToFile(string path, LIST_DOCGIA listDG);

/// <summary>
/// Duyệt cây DOCGIA ghi LIST_MUONTRA của từng DOCGIA ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa LIST_MUONTRA cần lưu</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>void</returns>
void DuyetLuuFileMuonTra(LIST_DOCGIA lstDG, string defaultPath);

/// <summary>
/// Duyệt cây DOCGIA đọc LIST_MUONTRA của từng DOCGIA trong file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa LIST_MUONTRA cần đọc</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>void</returns>
void DuyetDocFileMuonTra(LIST_DOCGIA& lstDG, string path);

#pragma endregion

#pragma endregion

/// <summary>
/// Chuyển list string từ form thành obj DOCGIA
/// </summary>
/// <param name="data">List string người dùng nhập</param>
/// <returns>DOCGIA</returns>
DOCGIA ParseVectorStringDG(string* data);

/// <summary>
///  Hiện form nhập thông tin DOCGIA
/// </summary>
/// <param name="maThe">mã DOCGIA đã được random</param>
/// <param name="rect">Khung nhập DOCGIA</param>
/// <returns>DOCGIA</returns>
DOCGIA InputDocGia(int maThe, RECTANGLE rect);

/// <summary>
///  Hiện form sửa thông tin DOCGIA
/// </summary>
/// <param name="docGia">DOCGIA cần chỉnh sửa</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DOCGIA</returns>
DOCGIA InputFixDocGia(RECTANGLE rect, DOCGIA docGia);

/// <summary>
/// In labels cho danh sách Độc giả
/// </summary>
/// <param name="location">Location</param>
/// <param name="row">Số độc giả có trong danh sách</param>
/// <returns>void</returns>
void PrintLabelDocGia(MYPOINT location, int row);