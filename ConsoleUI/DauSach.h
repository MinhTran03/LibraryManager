#pragma once
#include "Sach.h"

struct TOPSACH
{
	string info;
	int soSachMuon;

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns>void</returns>
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);
};

struct DAUSACH
{
	char isbn[ISBN_MAXSIZE + 1];
	string tenSach;
	int soTrang = NULL;
	string tenTacGia;
	int namXuatBan = NULL;
	string tenTheLoai;
	int soLuotMuon = 0;

	LIST_SACH dsSach;

	/// <summary>
	/// Lấy ToString của đầu sách và in ra màn hình
	/// </summary>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
	void Print(MYPOINT location, Color bgSelectColor, Color textColor);

	/// <summary>
	/// Lấy ToString của đầu sách cùng số lần mượn và in ra màn hình
	/// </summary>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
	void PrintMuonTra(MYPOINT location, Color backColor, Color textColor);
	
	/// <summary>
	/// In ra DAUSACH dưới dạng list
	/// </summary>
	/// <returns>DAUSACH as string in List</returns>
	string ToString();

	/// <summary>
	/// In ra DAUSACH cùng số lượt mượn dưới dạng list
	/// </summary>
	/// <returns>DAUSACH as string in List</returns>
	string ToStringMuonTra();

	/// <summary>
	/// Chuyển obj DAUSACH thành line string để lưu vơ file text
	/// </summary>
	/// <returns>DAUSACH as string in File</returns>
	string ToStringFile();
};

struct LIST_DAUSACH
{
	int size = 0;
	DAUSACH* nodes[SODAUSACH_MAX];
	string* dsTheLoai;
	int soTheLoai = 0;

	#pragma region --------------------PRINT

	/// <summary>
	/// In danh sách DAUSACH của thể loại và sắp xếp theo tên
	/// </summary>
	/// <param name="location">Location</param>
	/// <param name="theLoai">Tên thể loại cần in</param>
	/// <returns>Phím người dùng ấn as string</returns>
	string PrintByTheLoai(MYPOINT location, string tenTheLoai);

	/// <summary>
	/// In danh sách DAUSACH của tất cả thể loại chia thánh nhiều trang
	/// </summary>
	/// <param name="location">Location</param>
	/// <returns>Phím người dùng ấn as string</returns>
	string PrintAllTheLoai(MYPOINT location);

	/// <summary>
	/// In danh sách DAUSACH của toàn bộ DAUSACH
	/// </summary>
	/// <param name="location">Location</param>
	/// <param name="page">Trang</param>
	/// <param name="mode">Show_Only: Chỉ hiện \n Both: Hiện và bắt phím</param>
	/// <returns>Phím người dùng ấn as string</returns>
	string PrintAll(MYPOINT location, int& page, Menu_Mode mode = Menu_Mode::Show_Only);

	// ...
	void PrintFindBooks(MYPOINT location, string tenSach);

	// ...
	string PrintAllSearch(MYPOINT location, string tenSach, Menu_Mode mode);

	#pragma endregion

	#pragma region --------------------DOC GHI FILE

	/// <summary>
	/// Đọc LIST_DAUSACH từ file text
	/// </summary>
	/// <param name="path">Đường dẫn tới file</param>
	/// <returns>true nếu file tồn tại</returns>
	bool ReadFromFile(string path);

	/// <summary>
	/// Ghi LIST_DAUSACH ra file text
	/// </summary>
	/// <param name="path">Đường dẫn tới file</param>
	/// <returns>true nếu ghi file thành công</returns>
	bool WriteToFile(string path);

	#pragma endregion

	/// <summary>
	/// Hàm hủy toàn bộ DAUSACH khỏi RAM
	/// </summary>
	void Deconstructor();

	/// <summary>
	/// In danh sách DAUSACH của toàn bộ DAUSACH
	/// </summary>
	/// <param name="location">Location</param>
	/// <returns>true nếu Thể loại đó tồn tại</returns>
	bool IsContainTheLoai(string theLoai);

	/// <summary>
	/// Lấy danh sách DAUSACH dựa vào Thể Loại
	/// </summary>
	/// <param name="tenTheLoai">Tên thể loại cần lấy</param>
	/// <param name="count">Tham trị đếm số DAUSACH lấy được</param>
	/// <returns>Danh sách DAUSACH</returns>
	DAUSACH* GetDauSachByTheLoai(string tenTheLoai, int& count);

	/// <summary>
	/// Lấy DAUSACH dựa vào ISBN
	/// </summary>
	/// <param name="isbn">ISBN cần lấy</param>
	/// <returns>NULL nếu không có DAUSACH thuộc ISBN</returns>
	DAUSACH* GetDauSach(char isbn[ISBN_MAXSIZE + 1]);

	/// <summary>
	/// Kiểm tra LIST_DAUSACH đầy chưa (1000)
	/// </summary>
	/// <returns>true nếu đầy</returns>
	bool IsFull();

	/// <summary>
	/// Kiểm tra LIST_DAUSACH rỗng
	/// </summary>
	/// <returns>true nếu rỗng</returns>
	bool IsEmpty();

	/// <summary>
	/// Kiểm tra LIST_DAUSACH đã tồn tại ISBN hay chưa
	/// </summary>
	/// <param name="isbn">ISBN cần kiểm tra</param>
	/// <returns>true nếu tồn tại</returns>
	bool IsContainISBN(char isbn[ISBN_MAXSIZE + 1]);

	/// <summary>
	/// Thêm DAUSACH vào LIST_DAUSACH
	/// DAUSACH phải dùng tham biến (&) vì nếu dùng tham trị thì node sẽ mất sau khi ra khỏi hàm
	/// </summary>
	/// <param name="node">DAUSACH cần thêm</param>
	/// <param name="index">Vị trí cần thêm</param>
	/// <returns>true nếu Insert thành công</returns>
	bool Insert(DAUSACH& node, int index);

	// ...
	DAUSACH* FindBooks(string tenSach, int& count);
	
	/// <summary>
	/// Tìm index của DAUSACH theo ISBN
	/// </summary>
	/// <param name="isbn">ISBN cần tìm</param>
	/// <returns>-1 nếu ISBN không tồn tại</returns>
	int GetLocateDauSach(char isbn[ISBN_MAXSIZE + 1]);

	/// <summary>
	/// Cập nhật danh sách thể loại khi Thêm, Xóa và Sửa DAUSACH
	/// </summary>
	void INotifyDSTheLoai();

	/// <summary>
	/// Xóa DAUSACH dựa vào ISBN
	/// </summary>
	/// <param name="isbn">ISBN của DAUSACH cần xóa</param>
	/// <returns>true nếu xóa thành công</returns>
	bool DeleteDauSach(char isbn[ISBN_MAXSIZE + 1]);

};

/// <summary>
/// Hiện form nhập DAUSACH
/// </summary>
/// <param name="listDS">Kiểm tra ISBN xem có trùng không</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DAUSACH</returns>
DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect);

/// <summary>
///  Hiện form sửa thông tin DAUSACH
/// </summary>
/// <param name="listDS">Kiểm tra ISBN xem có trùng không</param>
/// <param name="dauSach">DAUSACH cần chỉnh sửa</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DAUSACH</returns>
DAUSACH InputFixDauSach(LIST_DAUSACH listDS, RECTANGLE rect, DAUSACH dauSach);

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns>void</returns>
string PrintTopDauSach(LIST_DAUSACH listDS, MYPOINT location);