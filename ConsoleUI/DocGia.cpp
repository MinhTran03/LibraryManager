#include "DocGia.h"

int* maDocGiaArr = NULL;
int newPos;

#pragma region -------------------------------------------DOCGIA

/// <summary>
/// Chuyển list string lấy từ file thành obj DOCGIA
/// </summary>
/// <param name="data">List string lấy từ file</param>
/// <returns>DOCGIA</returns>
DOCGIA ParseVectorStringFileDG(string* data)
{
	DOCGIA docGia;// = new DOCGIA;
	auto maAsChar = StringToCharArray(data[0]);
	docGia.maDocGia = atoi(maAsChar);
	delete[] maAsChar;
	docGia.ho = data[1];
	FormatName(docGia.ho);
	docGia.ten = data[2];
	FormatName(docGia.ten);
	if (ToLowerString(data[3]) == "nam")
	{
		docGia.gioiTinh = Nam;
	}
	else
	{
		docGia.gioiTinh = Nu;
	}
	if (ToLowerString(data[4]) == "dang hoat dong")
	{
		docGia.trangThai = DangHoatDong;
	}
	else
	{
		docGia.trangThai = TrangThaiTheDG::TheBiKhoa;
	}
	return docGia;
}

/// <summary>
/// Lấy ToString của DOCGIA và in ra màn hình
/// </summary>
/// <param name="location">Vị trí in</param>
/// <param name="backColor">Màu nền</param>
/// <param name="textColor">Màu chữ</param>
/// <returns>void</returns>
void DOCGIA::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DOCGIA::ToString();
}

/// <summary>
/// Chuyển obj DOCGIA thành line string để in dưới dạng List
/// </summary>
/// <returns>DOCGIA as string in List</returns>
string DOCGIA::ToString()
{
	string tempStr = "";
	MergeWordWithNumber(tempStr, this->maDocGia, 4);
	int temp;
	// ma doc gia
	string result = "";
	result += char(179);
	result += tempStr;
	temp = MADOCGIA_WIDTH - tempStr.size();
	result += string(temp, ' ');
	// ho
	result += char(179);
	result += this->ho;
	temp = HODOCGIA_WIDTH - this->ho.size();
	result += string(temp, ' ');
	// ten
	result += char(179);
	result += this->ten;
	temp = TENDOCGIA_WIDTH - this->ten.size();
	result += string(temp, ' ');
	// gioi tinh
	result += char(179);
	if (this->gioiTinh == Nam)
	{
		tempStr = "Nam";
	}
	else
	{
		tempStr = "Nu";
	}
	result += tempStr;
	temp = GIOITINH_WIDTH - tempStr.size();
	result += string(temp, ' ');
	// NAMXUATBAN
	result += char(179);
	if (this->trangThai == TheBiKhoa)
	{
		tempStr = "The bi khoa";
	}
	else
	{
		tempStr = "Dang hoat dong";
	}
	result += tempStr;
	temp = TRANGTHAIDG_WIDTH - tempStr.size();
	result += string(temp, ' ');
	result += char(179);
	return result;
}

/// <summary>
/// Chuyển obj DOCGIA thành line string để lưu vô file text
/// </summary>
/// <returns>DOCGIA as string in File</returns>
string DOCGIA::ToStringFile()
{
	string result = "";
	result = to_string(this->maDocGia);
	result += '-';
	result += this->ho + '-';
	result += this->ten + '-';
	if (this->gioiTinh == Nam)
	{
		result += "Nam-";
	}
	else
	{
		result += "Nu-";
	}
	if (this->trangThai == TheBiKhoa)
	{
		result += "The bi khoa";
	}
	else
	{
		result += "Dang hoat dong";
	}
	return result;
}

/// <summary>
/// <para>Kiểm tra xem DOCGIA đủ điều kiện mượn sách</para>
/// <para>0> Không làm mất sách</para>
/// <para>1> Không giữ sách quá 7 ngày</para>
/// <para>2> Thẻ độc giả đang hoạt động</para>
/// <para>3> Mượn tối đa 3 sách</para>
/// </summary>
/// <returns>Accept nếu đủ điều kiện mượn sách</returns>
ExeptionMuonSach DOCGIA::IsMuonSach()
{
	// 2> the doc gia dang hoat dong
	if (this->trangThai == TheBiKhoa) return BiKhoaThe;
	auto toDay = DATETIME();
	toDay.SetDateTimeNow();
	//1 > khong muon sach qua 7 ngay
	int soSachChuaTra = 0;
	for (auto p = this->listMuonTra.pHead; p != NULL && p->data.trangThai != SachDaTra; p = p->pNext)
	{
		if (p->data.trangThai == LamMatSach)
		{
			return SachBiMat;
		}
		if (toDay.SubDate(p->data.ngayMuon) > SONGAYMUON_TOIDA)
		{
			return GiuQua7Ngay;
		}
		soSachChuaTra++;
	}
	// 3> muon toi da 3 sach
	if (soSachChuaTra >= 3) return MuonDuSach;
	return Accept;
}

/// <summary>
/// Chuyển obj DOCGIA mượn sách quá hạn thành line string để in dưới dạng List
/// </summary>
/// <returns>DOCGIA quá hạn as string in List</returns>
string* DOCGIA::ToStringQuaHan(LIST_DAUSACH listSach, int& count)
{
	string* output = NULL;
	for (auto p = this->listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.IsQuaHan())
		{
			string* isbn = Split(p->data.maSach, "_");
			auto isbnAsChar = StringToCharArray(isbn[0]);
			string tenSach = listSach.GetDauSach(isbnAsChar)->tenSach;
			delete[] isbnAsChar;
			string tempStr = "";
			MergeWordWithNumber(tempStr, this->maDocGia, 4);
			int temp;
			// ma doc gia
			string result = "";
			result += char(179);
			result += tempStr;
			temp = MADOCGIA_WIDTH - tempStr.size();
			result += string(temp, ' ');
			// ho
			result += char(179);
			result += this->ho;
			temp = HODOCGIA_WIDTH - this->ho.size();
			result += string(temp, ' ');
			// ten
			result += char(179);
			result += this->ten;
			temp = TENDOCGIA_WIDTH - this->ten.size();
			result += string(temp, ' ');
			// ma sach
			result += char(179);
			result += p->data.maSach;
			temp = MASACH_WIDTH - p->data.maSach.size();
			result += string(temp, ' ');
			// ten sach
			result += char(179);
			result += tenSach;
			temp = TENSACH_WIDTH - tenSach.size();
			result += string(temp, ' ');
			// NGAY MUON
			result += char(179);
			result += p->data.ngayMuon.ToStringDate();
			temp = NGAY_WIDTH - 10;
			result += string(temp, ' ');
			// so ngay qua han
			result += char(179);
			result += string(7, ' ');
			int nqh = p->data.GetSoNgayQuaHan();
			result += to_string(nqh);
			result += string(10 - NumberLength(nqh), ' ');
			result += char(179);
			PushBack(output, result, count);
			delete[] isbn;
		}
	}
	return output;
}

#pragma endregion

#pragma region -------------------------------------------NODE_DOCGIA

/// <summary>
/// Constructor
/// </summary>
NODE_DOCGIA::NODE_DOCGIA(DOCGIA& data)
{
	this->data = data;
	this->pLeft = NULL;
	this->pRight = NULL;
}

#pragma endregion

#pragma region -------------------------------------------LIST_DOCGIA

/// <summary>
/// Kiểm tra DOCGIA được phép xóa không
/// </summary>
/// <param name="docGia">DOCGIA cần kiểm tra</param>
/// <returns>true nếu được xóa</returns>
bool IsDelete(DOCGIA& docGia)
{
	for (auto p = docGia.listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai == SachChuaTra)
			return false;
	}
	return true;
}

/// <summary>
/// Tính số DOCGIA có trong LIST_DOCGIA
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần tính size</param>
/// <returns>Số DOCGIA</returns>
int Size(LIST_DOCGIA listDG)
{
	if (listDG == NULL)
		return 0;
	else
		return 1 + Size(listDG->pLeft) + Size(listDG->pRight);
}

/// <summary>
/// Duyệt LNR lấy danh sách maDocGia
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần tính size</param>
/// <param name="dsMaDocGia">dsMaDocGia để lưu</param>
/// <returns>void</returns>
void GetMaDG(LIST_DOCGIA lstDG, int*& dsMaDocGia)
{
	if (lstDG != NULL)
	{
		GetMaDG(lstDG->pLeft, dsMaDocGia);
		int c = 0;
		PushBack(dsMaDocGia, lstDG->data.maDocGia, c);
		GetMaDG(lstDG->pRight, dsMaDocGia);
	}
}

/// <summary>
/// Lấy info DOCGIA lưu vô list String
/// </summary>
/// <param name="docGia">DOCGIA cần lưu</param>
/// <returns>List string</returns>
string* GetDGToListString(DOCGIA docGia)
{
	string* docGiaInfo = NULL;
	int c = 0;

	PushBack(docGiaInfo, to_string(docGia.maDocGia), c);
	PushBack(docGiaInfo, docGia.ho, c);
	PushBack(docGiaInfo, docGia.ten, c);

	if (docGia.gioiTinh == Nam)
	{
		string temp = "Nam";
		PushBack(docGiaInfo, temp, c);
	}
	else
	{
		string temp = "Nu";
		PushBack(docGiaInfo, temp, c);
	}
	if (docGia.trangThai == DangHoatDong)
	{
		string temp = "Dang hoat dong";
		PushBack(docGiaInfo, temp, c);
	}
	else
	{
		string temp = "The bi khoa";
		PushBack(docGiaInfo, temp, c);
	}

	return docGiaInfo;
}

/// <summary>
/// <para>Sinh mã độc giả ngẫu nhiên</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA để lấy Size</param>
/// <returns>Mã độc giả</returns>
int GetRandomMaDG(LIST_DOCGIA listDG)
{
	srand((unsigned int)time((time_t)NULL));
	int t = Size(listDG);
	newPos = rand() % (MAX_DOCGIA - Size(listDG));
	return maDocGiaArr[newPos];
}

/// <summary>
/// <para>Remove msDocGia vừa random khỏi maDocGiaArr khi thêm DOCGIA</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA để lấy Size</param>
/// <returns>void</returns>
void RemoveMaDG(LIST_DOCGIA listDG)
{
	Erase(maDocGiaArr, newPos, MAX_DOCGIA - Size(listDG));
}

/// <summary>
/// Hàm hủy toàn bộ DOCGIA khỏi RAM
/// </summary>
void FreeMemory(NODE_DOCGIA* root)
{
	if (root == NULL)
		return;
	FreeMemory(root->pLeft);
	FreeMemory(root->pRight);
	delete root;
	root = NULL;
}

/// <summary>
/// Khởi tạo Cây Nhị Phân DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần khởi tạo</param>
void Init(LIST_DOCGIA& lstDG)
{
	lstDG = NULL;
}

/// <summary>
/// Thêm DOCGIA vào LIST_DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần thêm Node</param>
/// <param name="input">DOCGIA cần thêm</param>
void Insert(LIST_DOCGIA& lstDG, DOCGIA input)
{
	if (lstDG == NULL)
	{
		NODE_DOCGIA* p = new NODE_DOCGIA(input);
		lstDG = p;
	}
	else
	{
		if (lstDG->data.maDocGia > input.maDocGia)
		{
			Insert(lstDG->pLeft, input);
		}
		else if (lstDG->data.maDocGia < input.maDocGia)
		{
			Insert(lstDG->pRight, input);
		}
	}
}

/// <summary>
/// Tìm DOCGIA dựa vào maDocGia
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần thêm Node</param>
/// <param name="maDocGia">mã DOCGIA cần tìm</param>
/// <returns>NULL nếu không tìm thấy</returns>
NODE_DOCGIA* Search(LIST_DOCGIA lstDG, int maDocGia)
{
	while (lstDG != NULL && lstDG->data.maDocGia != maDocGia)
	{
		if (maDocGia < lstDG->data.maDocGia)
		{
			lstDG = lstDG->pLeft;
		}
		else lstDG = lstDG->pRight;
	}
	return (lstDG);
}

// ...
void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q)
{
	if (q->pLeft != NULL)
	{
		TimPhanTuTheMangTraiNhatCayConPhai(p, q->pLeft);
	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pRight;
	}
}

// ...
void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q)
{
	if (q->pRight != NULL)
	{
		TimpPhanTuTheMangPhaiNhatCayConTrai(p, q->pRight);
	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pLeft;
	}
}

/// <summary>
/// Xóa 1 DOCGIA khỏi cây LIST_DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa DOCGIA cần xóa</param>
/// <param name="docGia">DOCGIA cần xóa</param>
/// <returns>false xóa thất bại</returns>
bool DeleteNode(LIST_DOCGIA& lstDG, DOCGIA docGia)
{
	if (lstDG == NULL)
	{
		return false;
	}
	else
	{
		if (lstDG->data.maDocGia > docGia.maDocGia)
		{
			DeleteNode(lstDG->pLeft, docGia);
		}
		else if (lstDG->data.maDocGia < docGia.maDocGia)
		{
			DeleteNode(lstDG->pRight, docGia);
		}
		else
		{
			NODE_DOCGIA* p = lstDG;
			if (lstDG->pLeft == NULL)
			{
				lstDG = lstDG->pRight;
			}
			else if (lstDG->pRight == NULL)
			{
				lstDG = lstDG->pLeft;
			}
			else
			{
				// cach 1 tim phan tu trai nhat cay con phai 
				//timphantuthemangtrainhatcayconphai(p, t->pright);
				//cach 2 tìm phan tu tha mang phai nhat cay con trai
				TimpPhanTuTheMangPhaiNhatCayConTrai(p, lstDG->pLeft);
			}
			delete p;
			return true;
		}
	}
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để in ra màn hình</para>
/// Duyệt LNR
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần chuyển</param>
/// <param name="result">List string sau khi convert</param>
/// <param name="count">Số DOCGIA sau khi lưu (ban đầu gán = 0)</param>
/// <returns>void</returns>
void InorderGetString(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetString(lstDG->pLeft, result, count);
		PushBack(result, lstDG->data.ToString(), count);
		InorderGetString(lstDG->pRight, result, count);
	}
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để in ra màn hình</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần convert</param>
/// <param name="count">Số độc giả đếm được (ban đầu = 0)</param>
/// <returns>List string sau khi convert</returns>
string* GetAllStringNode(LIST_DOCGIA listDG, int& count)
{
	string* result = NULL;
	InorderGetString(listDG, result, count);
	return result;
}

/// <summary>
/// In labels cho danh sách Độc giả
/// </summary>
/// <param name="location">Location</param>
/// <param name="row">Số độc giả có trong danh sách</param>
/// <returns>void</returns>
void PrintLabelDocGia(MYPOINT location, int row)
{
	string labels[] = { "MA DOC GIA", "HO", "TEN", "GIOI TINH", "TRANG THAI THE" };
	auto lstBorder = LISTBORDERTEXT(labels, 5);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, GIOITINH_WIDTH, TRANGTHAIDG_WIDTH },
		row, BORDER_COLOR);
}

/// <summary>
/// In DOCGIA sắp xếp theo mã độc giả
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <param name="location">Location</param>
/// <param name="mode"><para>Show_Only: Chỉ hiện</para><para>Both: Hiện và bắt phím</para></param>
/// <returns>Phím được nhấn As String</returns>
void PrintContentSortMaDG(LIST_DOCGIA listDG, MYPOINT location, Menu_Mode mode)
{
	// Create Empty Line
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	int currentPage = 0;
	int totalPage = 0;
	int soDocGia = 0;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	// Get theo NLR => mã độc giả tự tăng => không cần sort
	string* listData = GetAllStringNode(listDG, soDocGia);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPage = soDocGia / MAX_ROW_PER_PAGE;
	if (soDocGia % MAX_ROW_PER_PAGE != 0) totalPage++;

	// Ký tự phân cách '|' as string
	string deli = ""; deli += char(179);

	// In danh sách độc giả ra màn hình
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < soDocGia; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			Sleep(2);
			GoToXY(location.x, location.y + i);
			cout << listData[i];
		}
	}

	if (mode == Show_Only) return;

	// Bắt phím
	char inputKey = NULL;
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL || inputKey == -32) inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
		{
			currentPage++;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(2);
				// In trang không phải cuối cùng
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// In data trang cuối cùng
				if (currentPage == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE != 0
					&& i < soDocGia % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
				}
				// In empty line xóa line dư của page trước đó
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyTemplate;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPage > 0)
		{
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			// In data ra màn hình
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(2);
				GoToXY(location.x, location.y + (int)i);
				cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
			}
		}
		else if (inputKey == Key::ESC)
		{
			return;
		}
	} while (!_kbhit());
	return;
}

/// <summary>
/// Quick Sort ToString của LIST_DOCGIA theo tên
/// </summary>
/// <param name="listDG">LIST_DOCGIA as String cần sắp xếp</param>
/// <param name="listName">List name tách ra từ ToString</param>
/// <param name="q">Index đầu mảng</param>
/// <param name="r">Index cuối mảng</param>
/// <returns>void</returns>
void SortStringDocGiaTheoTen(string*& listDG, string*& listName, int q, int r)
{
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	string x = listName[(q + r) / 2];
	do
	{  // Phân đoạn dãy con a[q],..., a[r]
		while (listName[i].compare(x) < 0)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (listName[j].compare(x) > 0)
			j--;   //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j)   // Hoan vi
		{
			Swap(listName[i], listName[j]);
			Swap(listDG[i], listDG[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (q < j) 	// phần thứ nhất có từ 2 phần tử trở lên
		SortStringDocGiaTheoTen(listDG, listName, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		SortStringDocGiaTheoTen(listDG, listName, i, r);
}

/// <summary>
/// In DOCGIA sắp xếp theo tên độc giả
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <param name="location">Location</param>
/// <param name="mode"><para>Show_Only: Chỉ hiện</para><para>Both: Hiện và bắt phím</para></param>
/// <returns>Phím được nhấn As String</returns>
void PrintContentSortTen(LIST_DOCGIA lstDG, MYPOINT location, Menu_Mode mode)
{
	// Create Empty Line
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	int currentPage = 0;
	int totalPage = 0;
	int soDocGia = 0;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	string* listData = GetAllStringNode(lstDG, soDocGia);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPage = soDocGia / MAX_ROW_PER_PAGE;
	if (soDocGia % MAX_ROW_PER_PAGE != 0) totalPage++;

	// Ký tự phân cách '|' as string
	string deli = ""; deli += char(179);

	// Tách list name từ ToString của độc giả
	string* listName = new string[soDocGia];
	for (int i = 0; i < soDocGia; i++)
	{
		auto tokens = Split(listData[i], deli);
		listName[i] = Trim(tokens[3]) + Trim(tokens[2]);
	}

	// Sort listData theo listName được tách sẵn
	SortStringDocGiaTheoTen(listData, listName, 0, soDocGia - 1);
	delete[] listName;

	// In danh sách độc giả ra màn hình
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < soDocGia; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			Sleep(2);
			GoToXY(location.x, location.y + i);
			cout << listData[i];
		}
	}

	if (mode == Show_Only) return;

	// bat phim
	char inputKey = NULL;
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL || inputKey == -32) inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
		{
			currentPage++;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(2);
				// In trang không phải cuối cùng
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// In data trang cuối cùng
				if (currentPage == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE != 0
					&& i < soDocGia % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
				}
				// In empty line xóa line dư của page trước đó
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyTemplate;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPage > 0)
		{
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			// In data ra màn hình
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(2);
				GoToXY(location.x, location.y + (int)i);
				cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
			}
		}
		else if (inputKey == Key::ESC)
		{
			return;
		}
	} while (!_kbhit());
	return;
}

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
/// <returns>Phím được nhấn As String</returns>
void PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int sortMode, Menu_Mode mode)
{
	PrintLabelDocGia(location, MAX_ROW_PER_PAGE);
	location.y += 3;

	// Độc giả sắp theo Mã
	if (sortMode == 1)
	{
		PrintContentSortMaDG(lstDG, location, mode);
	}
	// Độc giả sắp theo Họ Tên
	else
	{
		PrintContentSortTen(lstDG, location, mode);
	}
}

/// <summary>
/// In string tại vị trí truyền vào
/// </summary>
/// <param name="data">string cần in</param>
/// <param name="location">Location</param>
/// <returns>void</returns>
void PrintStringDocGia(string data, MYPOINT location)
{
	GoToXY(location.x, location.y);
	cout << data;
}

/// <summary>
/// In LIST_DOCGIA ra màn hình
/// </summary>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <param name="location">Location</param>
/// <param name="page">Lưu lại vị trí page đang đứng</param>
/// <param name="line">Dòng cần highLight</param>
/// <param name="mode">
///	<para>Show_Only: Chỉ hiện</para>
///	<para>Both: Hiện và bắt phím</para>
/// </param>
/// <returns>Phím được nhấn As String</returns>
string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int& page, Menu_Mode mode, int line)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	MYPOINT backUpLocation = MYPOINT(0, 0);
	MYPOINT loc = MYPOINT(0, 0);
	string* dsDocGia = NULL;
	string** datas = NULL;
	int* rowsOfPage = NULL;
	int** rows = NULL;
	int currentLine = 0;
	int currentPage = page;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int totalLine = 0;

	// chuyen list doc gia ve mang string
	if (listDG != NULL)
	{
		dsDocGia = GetAllStringNode(listDG, totalLine);
	}
	int totalPages = totalLine / (int)MAX_ROW_PER_PAGE + (totalLine % (int)MAX_ROW_PER_PAGE == 0 ? 0 : 1);;
	//int totalLine = SizeOfT(dsDocGia);
	// them page
	datas = new string * [totalPages];
	rows = new int* [totalPages];
	// tranh vuot qua so trang MAX
	if (currentPage >= totalPages)
	{
		//currentPage = datas.size() - 1;
		page = totalPages - 1;
		return "";
	}
	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelDocGia(location, MAX_ROW_PER_PAGE);
		if (totalPages == 0) return "";
		ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 4);
		location.y += 3;
		backUpLocation = location;
		//print data
		int c = 0;
		for (int i = 0; i < totalPages - 1; i++)
		{
			rows[i] = new int[MAX_ROW_PER_PAGE];
			datas[i] = new string[MAX_ROW_PER_PAGE];
			PushBack(rowsOfPage, (int)MAX_ROW_PER_PAGE, c);
		}
		rows[totalPages - 1] = new int[totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)];
		datas[totalPages - 1] = new string[totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)];
		PushBack(rowsOfPage, (int)(totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)), c);
		for (int i = 0; i < totalLine; i++)
		{
			//Sleep(1);
			if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
			{
				PrintStringDocGia(dsDocGia[i], { location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) });
				if (/*backUpLocation.y == WhereY()*/i == line + page * MAX_ROW_PER_PAGE && mode == Menu_Mode::Both)
				{
					SetBGColor(hlBGColor);
					SetTextColor(hlTextColor);
					PrintStringDocGia(dsDocGia[i], { location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) });
					SetBGColor(BG_COLOR);
					SetTextColor(TEXT_INPUT_COLOR);
				}
			}
			// luu lai vi tri dong
			currentPage = i / MAX_ROW_PER_PAGE;
			rows[currentPage][i % MAX_ROW_PER_PAGE] = (i % MAX_ROW_PER_PAGE + location.y);
			datas[currentPage][i % MAX_ROW_PER_PAGE] = (dsDocGia[i]);
		}
		// xoa nhung line du cua trang truoc do
		if (page == totalPages - 1 && totalLine % MAX_ROW_PER_PAGE != 0 && page != 0)
		{
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (int i = totalLine % MAX_ROW_PER_PAGE; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, rows[page - 1][i]);
				cout << emptyTemplate;
			}
		}
	}
	if (mode == Show_Only)
	{
		delete[] dsDocGia;
		delete[] rows;
		delete[] datas;
	}
	currentPage = page;
	// bat phim
	if (mode == Menu_Mode::Both)
	{
		currentLine = line;

		char inputKey = NULL;
		HidePointer();
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP)
				{
					if (currentLine > 0)
					{
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[currentPage][--currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = (rowsOfPage[currentPage]) - 1;
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < (rowsOfPage[currentPage]) - 1)
					{
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[currentPage][++currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				string deli = "";
				deli += char(179);
				auto temp = Split(datas[currentPage][currentLine], deli);
				temp[1] = Trim(temp[1]);
				page = currentPage;
				delete[] dsDocGia;
				return temp[1];
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPages - 1)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (int i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					if (i < (rowsOfPage[currentPage]))
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						cout << datas[currentPage][i];
					}
					else
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						cout << emptyTemplate;
					}
				}
				SetBGColor(hlBGColor);
				SetTextColor(hlTextColor);
				PrintStringDocGia(dsDocGia[MAX_ROW_PER_PAGE * currentPage], location);
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
				// in prev page
				currentPage--;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(backUpLocation.x, backUpLocation.y + i);
					cout << datas[currentPage][i];
				}
				SetBGColor(hlBGColor);
				SetTextColor(hlTextColor);
				PrintStringDocGia(dsDocGia[MAX_ROW_PER_PAGE * currentPage], location);
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
			}
			else if (inputKey == Key::ESC)
			{
				page = currentPage;
				GoToXY(location.x, rows[currentPage][currentLine]);
				HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				delete[] dsDocGia;
				delete[] rows;
				delete[] datas;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "Empty";
}

/// <summary>
/// In labels cho danh sách Độc giả mượn sách quá hạn
/// </summary>
/// <param name="location">Location</param>
/// <param name="row">Số độc giả có trong danh sách</param>
/// <returns>void</returns>
void PrintLabelQuaHan(MYPOINT location, int row)
{
	string labels[] = { "MA DOC GIA", "HO", "TEN", "MA SACH", "TEN SACH", "NGAY MUON", "SO NGAY QUA HAN" };
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH, 17 },
		row, BORDER_COLOR);
}

/// <summary>
/// Quick Sort Số ngày quá hạn của LIST_DOCGIA
/// </summary>
/// <param name="soNgayQH">List Số ngày quá hạn tách ra từ string quá hạn</param>
/// <param name="quaHanString">List string DOCGIA quá hạn</param>
/// <param name="q">Index đầu mảng</param>
/// <param name="r">Index cuối mảng</param>
/// <returns>void</returns>
void SortQuaHanString(int*& soNgayQH, string*& quaHanString, int q, int r)
{
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = soNgayQH[(q + r) / 2];
	do
	{  // Phân đoạn dãy con a[q],..., a[r]
		while (soNgayQH[i] > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (soNgayQH[j] < x)
			j--;   //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j)   // Hoan vi
		{
			Swap(soNgayQH[i], soNgayQH[j]);
			Swap(quaHanString[i], quaHanString[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (q < j) 	// phần thứ nhất có từ 2 phần tử trở lên
		SortQuaHanString(soNgayQH, quaHanString, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		SortQuaHanString(soNgayQH, quaHanString, i, r);
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA quá hạn thành list string để in ra màn hình</para>
/// Duyệt LNR
/// </summary>
/// <param name="listDS">LIST_DAUSACH để tính số ngày quá hạn</param>
/// <param name="lstDG">LIST_DOCGIA cần chuyển</param>
/// <param name="result">List string sau khi convert</param>
/// <param name="count">Số DOCGIA sau khi lưu (ban đầu gán = 0)</param>
/// <returns>void</returns>
void InorderGetStringQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetStringQuaHan(listDS, lstDG->pLeft, result, count);
		int countMTQuaHan = 0;
		string* mtQuaHanAsString = lstDG->data.ToStringQuaHan(listDS, countMTQuaHan);
		for (int i = 0; i < countMTQuaHan; i++)
		{
			PushBack(result, mtQuaHanAsString[i], count);
		}
		delete[] mtQuaHanAsString;
		InorderGetStringQuaHan(listDS, lstDG->pRight, result, count);
	}
}

/// <summary>
/// In LIST_DOCGIA quá hạn ra màn hình
/// </summary>
/// <param name="listDS">LIST_DAUSACH để tính số ngày quá hạn</param>
/// <param name="listDG">LIST_DOCGIA cần in</param>
/// <returns>void</returns>
void PrintListQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG)
{
	// Create Empty Line
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(MASACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NGAY_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(17, ' ');
	emptyTemplate = emptyTemplate + char(179);

	MYPOINT location = { 20, 3 };
	string* quaHanString = NULL;
	int currentPage = 0;
	int totalPage = 0;
	int totalQuaHan = 0;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	InorderGetStringQuaHan(listDS, lstDG, quaHanString, totalQuaHan);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPage = totalQuaHan / MAX_ROW_PER_PAGE;
	if (totalQuaHan % MAX_ROW_PER_PAGE != 0) totalPage++;

	// Tách ToString lấy số ngày quá hạn
	int* soNgayQH = new int[totalQuaHan];
	string deli = ""; deli += char(179);
	for (int i = 0; i < totalQuaHan; i++)
	{
		string* arr = Split(quaHanString[i], deli);
		arr[7] = Trim(arr[7]);
		soNgayQH[i] = stoi(arr[7]);
	}

	// Quick Sort list ToString theo soNgayQuaHan
	SortQuaHanString(soNgayQH, quaHanString, 0, totalQuaHan - 1);
	delete[] soNgayQH;

	// In ra màn hình
	PrintLabelQuaHan(location, MAX_ROW_PER_PAGE);
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 4);
	for (int i = 0; i < totalQuaHan; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			Sleep(3);
			GoToXY(location.x, location.y + i + 3);
			cout << quaHanString[i];
		}
	}

	// Bắt phím
	char inputKey = NULL;
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL || inputKey == -32) inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
		{
			currentPage++;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(3);
				// in trang not cuoi cung
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && totalQuaHan % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && totalQuaHan % MAX_ROW_PER_PAGE != 0
					&& i < totalQuaHan % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPage];
				}
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyTemplate;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPage > 0)
		{
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(3);
				GoToXY(location.x, location.y + (int)i);
				cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPage];
			}
		}
		else if (inputKey == Key::ESC)
		{
			delete[] quaHanString;
			ClearScreen(BG_COLOR);
			return;
		}
	} while (!_kbhit());
	return;
}

#pragma region --------------------DOC GHI FILE

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LRN
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu</param>
/// <param name="result">List string sau khi convert</param>
/// <param name="count">Số DOCGIA sau khi lưu (ban đầu gán = 0)</param>
/// <returns>void</returns>
void PosorderGetStringFile(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		PosorderGetStringFile(lstDG->pLeft, result, count);
		PosorderGetStringFile(lstDG->pRight, result, count);
		PushBack(result, lstDG->data.ToStringFile(), count);
	}
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LRN
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần convert</param>
/// <returns>List string sau khi convert</returns>
string* GetAllStringFileNodeLRN(LIST_DOCGIA listDG)
{
	string* result = NULL;
	int count = 0;
	PosorderGetStringFile(listDG, result, count);
	return result;
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LNR
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu</param>
/// <param name="result">List string sau khi convert</param>
/// <param name="count">Số DOCGIA sau khi lưu (ban đầu gán = 0)</param>
/// <returns>void</returns>
void InorderGetStringFile(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetStringFile(lstDG->pLeft, result, count);
		PushBack(result, lstDG->data.ToStringFile(), count);
		InorderGetStringFile(lstDG->pRight, result, count);
	}
}

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LNR
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần convert</param>
/// <returns>List string sau khi convert</returns>
string* GetAllStringFileNodeLNR(LIST_DOCGIA listDG)
{
	string* result = NULL;
	int count = 0;
	InorderGetStringFile(listDG, result, count);
	return result;
}

/// <summary>
/// Đọc LIST_DOCGIA từ file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <param name="listDG">LIST_DOCGIA để lưu data</param>
/// <returns>true nếu file tồn tại</returns>
bool ReadFromFile(LIST_DOCGIA& listDG, string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = 0;
		auto lstDocGia = fileHandler.GetTokens(size);
		for (int i = 0; i < size; i++)
		{
			DOCGIA* docGia = new DOCGIA;
			*docGia = ParseVectorStringFileDG(lstDocGia[i]);
			Insert(listDG, *docGia);
		}
		delete[] lstDocGia;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}

/// <summary>
/// Đọc maDocGia từ file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu file tồn tại</returns>
bool ReadMaDGFromFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		maDocGiaArr = fileHandler.GetLinesInt();
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}

/// <summary>
/// Ghi LIST_DOCGIA ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu</param>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu ghi file thành công</returns>
bool WriteToFile(LIST_DOCGIA lstDG, string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = Size(lstDG);
		string* data = GetAllStringFileNodeLRN(lstDG);
		for (auto i = 0; i < size; i++)
		{
			if (i < size - 1)
				data[i] += '\n';
		}
		fileHandler.WriteToFile(data, Replace, size);
		delete[] data;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}

/// <summary>
/// Ghi maDocGia ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu mã</param>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu ghi file thành công</returns>
bool WriteMaDGToFile(string path, LIST_DOCGIA listDG)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int c = 0;
		int size = MAX_DOCGIA - Size(listDG);
		string* data = NULL;
		for (auto i = 0; i < size; i++)
		{
			string temp = "";
			temp += to_string(maDocGiaArr[i]);
			if (i < size - 1)
				temp += '\n';
			PushBack(data, temp, c);
		}
		fileHandler.WriteToFile(data, Replace, c);
		delete[] data;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}

/// <summary>
/// Thực hiện ghi LIST_MUONTRA của từng DOCGIA ra file text
/// </summary>
/// <param name="listMT">LIST_MUONTRA cần lưu</param>
/// <param name="maDG">Mã DOCGIA làm tên file</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>true nếu ghi thành công</returns>
bool WriteMuonTraToFile(LIST_MUONTRA& listMT, string maDG, string defaultPath)
{
	defaultPath += MUONTRA_FILE_PATH;
	defaultPath += maDG;
	defaultPath += ".txt";
	return listMT.WriteToFile(defaultPath);
}

/// <summary>
/// Duyệt cây DOCGIA ghi LIST_MUONTRA của từng DOCGIA ra file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa LIST_MUONTRA cần lưu</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>void</returns>
void DuyetLuuFileMuonTra(LIST_DOCGIA lstDG, string defaultPath)
{
	if (lstDG != NULL)
	{
		if (lstDG->data.listMuonTra.IsEmpty() == false)
		{
			string maAsString = to_string(lstDG->data.maDocGia);
			//MergeWordWithNumber(maAsString, lstDG->data.maDocGia, 4);
			WriteMuonTraToFile(lstDG->data.listMuonTra, maAsString, defaultPath);
		}
		DuyetLuuFileMuonTra(lstDG->pLeft, defaultPath);
		DuyetLuuFileMuonTra(lstDG->pRight, defaultPath);
	}
}

/// <summary>
/// Thực hiện đọc LIST_MUONTRA của từng DOCGIA trong file text
/// </summary>
/// <param name="listMT">LIST_MUONTRA cần lưu</param>
/// <param name="maDG">Mã DOCGIA để lấy tên file</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>true nếu đọc thành công</returns>
bool ReadMuonTraFromFile(LIST_MUONTRA& listMT, string maDG, string path)
{
	path += MUONTRA_FILE_PATH;
	path += maDG;
	path += ".txt";
	return listMT.ReadFromFile(path);
}

/// <summary>
/// Duyệt cây DOCGIA đọc LIST_MUONTRA của từng DOCGIA trong file text
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa LIST_MUONTRA cần đọc</param>
/// <param name="defaultPath">Đường dẫn mặc định file debug</param>
/// <returns>void</returns>
void DuyetDocFileMuonTra(LIST_DOCGIA& lstDG, string path)
{
	if (lstDG != NULL)
	{
		DuyetDocFileMuonTra(lstDG->pLeft, path);
		string maAsString = to_string(lstDG->data.maDocGia);
		//MergeWordWithNumber(maAsString, lstDG->data.maDocGia, 4);
		ReadMuonTraFromFile(lstDG->data.listMuonTra, maAsString, path);
		DuyetDocFileMuonTra(lstDG->pRight, path);
	}
}

#pragma endregion

#pragma endregion

/// <summary>
/// Chuyển list string từ form thành obj DOCGIA
/// </summary>
/// <param name="data">List string người dùng nhập</param>
/// <returns>DOCGIA</returns>
DOCGIA ParseVectorStringDG(string* data)
{
	DOCGIA docGia;// = new DOCGIA;
	auto maAsChar = StringToCharArray(data[0]);
	docGia.maDocGia = atoi(maAsChar);
	delete[] maAsChar;
	docGia.ho = Trim(data[1]);
	docGia.ten = Trim(data[2]);
	if (data[3] == "0")
	{
		docGia.gioiTinh = Nam;
	}
	else
	{
		docGia.gioiTinh = Nu;
	}
	if (data[4] == "1")
	{
		docGia.trangThai = DangHoatDong;
	}
	else
	{
		docGia.trangThai = TrangThaiTheDG::TheBiKhoa;
	}
	return docGia;
}

/// <summary>
///  Hiện form nhập thông tin DOCGIA
/// </summary>
/// <param name="maThe">mã DOCGIA đã được random</param>
/// <param name="rect">Khung nhập DOCGIA</param>
/// <returns>DOCGIA</returns>
DOCGIA InputDocGia(int maThe, RECTANGLE rect)
{
	string labels[] = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	string inputTitle = "NHAP THONG TIN DOC GIA";
	CONDITION conditions[] = { {Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH},{Name, 1, TENDOCGIA_WIDTH},
													{Enum, 1, 2 },{Enum2, 1, 2, Default} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 5);
	string guilds[] = { "MA DOC GIA LA TU DONG", "CHI NHAP CHU CAI", "CHI NHAP CHU CAI", "0: NAM\n1: NU", "0: THE BI KHOA\n1: DANG HOAT DONG" };
	form.Guilds = guilds;
	DOCGIA docGia = DOCGIA();
	string datas[] = { to_string(maThe), "","","0","1" };
	form.ParseData(datas);
	form.currentLine = 1;
	if (form.Show(1, 4))
	{
		return ParseVectorStringDG(form.OutputResults);
	}
	else
	{
		form.ResetOutput();
	}
	return docGia;
}

/// <summary>
///  Hiện form sửa thông tin DOCGIA
/// </summary>
/// <param name="docGia">DOCGIA cần chỉnh sửa</param>
/// <param name="rect">Khung nhập DOCGIA</param>
/// <returns>DOCGIA</returns>
DOCGIA InputFixDocGia(RECTANGLE rect, DOCGIA docGia)
{
	auto listMTBackUp = docGia.listMuonTra;
	string labels[] = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	string inputTitle = "NHAP THONG TIN DOC GIA";
	CONDITION conditions[] = { {Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH},{Name, 1, TENDOCGIA_WIDTH},
									{Enum, 1, 2 },{Enum2, 1, 2} };
	string guilds[] = { "MA DOC GIA LA TU DONG", "CHI NHAP CHU CAI", "CHI NHAP CHU CAI", "0: NAM\n1: NU", "0: THE BI KHOA\n1: DANG HOAT DONG" };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 5);
	form.Guilds = guilds;
	//DOCGIA docGia = DOCGIA();
	string temp1, temp2;
	if (docGia.gioiTinh == Nam)
	{
		temp1 = "0";
	}
	else
	{
		temp1 = "1";
	}
	if (docGia.trangThai == TheBiKhoa)
	{
		temp2 = "0";
	}
	else
	{
		temp2 = "1";
	}
	string datas[5] = { to_string(docGia.maDocGia) , docGia.ho, docGia.ten, temp1, temp2 };
	form.ParseData(datas);
	form.currentLine = 1;
	while (true)
	{
		if (form.Show(1, 4))
		{
			DOCGIA newDocGia = ParseVectorStringDG(form.OutputResults);
			newDocGia.listMuonTra = listMTBackUp;
			return newDocGia;
		}
		else
		{
			form.ResetOutput();
			break;
		}
	}
	return docGia;
}