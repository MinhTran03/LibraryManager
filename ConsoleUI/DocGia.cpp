#include "DocGia.h"

int *maDocGiaArr = NULL;
int newPos;

#pragma region-- -----------------------------------------DOCGIA

/// <summary>
/// Chuyển list string lấy từ file thành obj DOCGIA
/// </summary>
/// <param name="data">List string lấy từ file</param>
/// <returns>DOCGIA</returns>
DOCGIA ParseVectorStringFileDG(string *data)
{
	DOCGIA docGia; // = new DOCGIA;
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
	if (this->trangThai == TheBiKhoa)
		return BiKhoaThe;
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
	if (soSachChuaTra >= 3)
		return MuonDuSach;
	return Accept;
}

/// <summary>
/// Chuyển obj DOCGIA mượn sách quá hạn thành line string để in dưới dạng List
/// </summary>
/// <returns>DOCGIA quá hạn as string in List</returns>
string *DOCGIA::ToStringQuaHan(LIST_DAUSACH listSach, int &count)
{
	string *output = NULL;
	for (auto p = this->listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.IsQuaHan())
		{
			string *isbn = Split(p->data.maSach, "_");
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

/// <summary>
/// Kiểm tra độc giả mượn sách quá 30 ngày
/// </summary>
/// <returns>true nếu mượn quá 30 ngày</returns>
bool DOCGIA::IsQua30Ngay()
{
	for (auto p = this->listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.GetSoNgayQuaHan() > 23)
		{
			return true;
		}
	}
	return false;
}

#pragma endregion

#pragma region-- -----------------------------------------NODE_DOCGIA

/// <summary>
/// Constructor
/// </summary>
NODE_DOCGIA::NODE_DOCGIA(DOCGIA &data)
{
	this->data = data;
	this->pLeft = NULL;
	this->pRight = NULL;
}

#pragma endregion

#pragma region-- -----------------------------------------LIST_DOCGIA

/// <summary>
/// Kiểm tra DOCGIA được phép xóa không
/// </summary>
/// <param name="docGia">DOCGIA cần kiểm tra</param>
/// <returns>true nếu được xóa</returns>
bool IsDelete(DOCGIA &docGia)
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
void GetMaDG(LIST_DOCGIA lstDG, int *&dsMaDocGia)
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
string *GetDGToListString(DOCGIA docGia)
{
	string *docGiaInfo = NULL;
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
	string soLuotMuon = to_string(docGia.listMuonTra.DuyetDSSachDaTra());
	PushBack(docGiaInfo, soLuotMuon,c);

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
	int soDG = Size(listDG);
	newPos = rand() % (MAX_DOCGIA - soDG);
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
/// <para>Khi xóa độc giả phải thêm lại mã của ng đó vô mảng</para>
/// </summary>
/// <param name="tongDocGia">Tổng số Độc giả trước khi xóa</param>
/// <param name="ma">mã của độc giả đó</param>
/// <returns>void</returns>
void InsertMaDocGia(int tongDocGia, int ma)
{
	int pos = MAX_DOCGIA - tongDocGia;
	PushBack(maDocGiaArr, ma, pos);
}

/// <summary>
/// Hàm hủy toàn bộ DOCGIA khỏi RAM
/// </summary>
void FreeMemory(NODE_DOCGIA *root)
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
void Init(LIST_DOCGIA &lstDG)
{
	lstDG = NULL;
}

/// <summary>
/// Thêm DOCGIA vào LIST_DOCGIA
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần thêm Node</param>
/// <param name="input">DOCGIA cần thêm</param>
void Insert(LIST_DOCGIA &lstDG, DOCGIA input)
{
	if (lstDG == NULL)
	{
		NODE_DOCGIA *p = new NODE_DOCGIA(input);
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
NODE_DOCGIA *Search(LIST_DOCGIA lstDG, int maDocGia)
{
	while (lstDG != NULL && lstDG->data.maDocGia != maDocGia)
	{
		if (maDocGia < lstDG->data.maDocGia)
		{
			lstDG = lstDG->pLeft;
		}
		else
			lstDG = lstDG->pRight;
	}
	return (lstDG);
}

// Tim thg nho nhat
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

// Tim thg lon nhat
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
/// <para>Xóa 1 DOCGIA khỏi cây LIST_DOCGIA co 3 truong hop:</para>
/// <para>TH1: Nut can xoa la nut la. Delete luon.</para>
/// <para>TH2: Nut can xoa co 1 cay con. Cho p tro toi lstDG roi tao lien ket nut cha lstDG vs nut p sau do tien hanh Delete</para>
/// <para>TH3: Nut can xoa co 2 cay con. Dua tren nut trai nhat cua cay con ben phai (tim node lon nhat)</para>
/// </summary>
/// <param name="lstDG">LIST_DOCGIA chứa DOCGIA cần xóa</param>
/// <param name="docGia">DOCGIA cần xóa</param>
/// <returns>false xóa thất bại</returns>
bool DeleteNode(LIST_DOCGIA &lstDG, DOCGIA docGia)
{
	if (lstDG == NULL)
	{
		return false;
	}
	else
	{
		if (docGia.maDocGia < lstDG->data.maDocGia)
		{
			DeleteNode(lstDG->pLeft, docGia);
		}
		else if (docGia.maDocGia > lstDG->data.maDocGia)
		{
			DeleteNode(lstDG->pRight, docGia);
		}
		else
		{
			NODE_DOCGIA* p = lstDG;
			// p la nut la hoac la nut co cay con ben trai
			if (lstDG->pLeft == NULL)
			{
				lstDG = lstDG->pRight;
			}
			// p la nut la hoac la nut co cay con ben phai
			else if (lstDG->pRight == NULL)
			{
				lstDG = lstDG->pLeft;
			}
			else
			{
				// cach 1 tim phan tu trai nhat cay con phai
				//TimPhanTuTheMangTraiNhatCayConPhai(p, t->pright);
				// cach 2 tìm phan tu tha mang phai nhat cay con trai
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
void InorderGetString(LIST_DOCGIA lstDG, string *&result, int &count)
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
string *GetAllStringNode(LIST_DOCGIA listDG, int &count)
{
	string *result = NULL;
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
	string labels[] = {"MA DOC GIA", "HO", "TEN", "GIOI TINH", "TRANG THAI THE"};
	auto lstBorder = LISTBORDERTEXT(labels, 5);
	lstBorder.Draw(location, {MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, GIOITINH_WIDTH, TRANGTHAIDG_WIDTH},
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
	// Create Empty Line DG
	string emptyStringDG = "";
	{
		emptyStringDG = emptyStringDG + char(179) + string(MADOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(HODOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TENDOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(GIOITINH_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179);
	}

	int currentPages = 0;
	int totalPage = 0;
	int soDocGia = 0;
	int sleepTime = 1;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	// Get theo NLR => mã độc giả tự tăng => không cần sort
	string *listData = GetAllStringNode(listDG, soDocGia);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPage = soDocGia / MAX_ROW_PER_PAGE;
	if (soDocGia % MAX_ROW_PER_PAGE != 0)
		totalPage++;

	// Ký tự phân cách '|' as string
	string deli = "";
	deli += char(179);

	// In danh sách độc giả ra màn hình
	ShowPageNumber(currentPages, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < soDocGia; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPages && i < (currentPages + 1) * (int)MAX_ROW_PER_PAGE)
		{
			Sleep(sleepTime);
			GoToXY(location.x, location.y + i);
			cout << listData[i];
		}
	}

	if (mode == Show_Only)
		return;

	// Bắt phím
	char inputKey = NULL;
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL || inputKey == -32)
			inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPages < totalPage - 1)
		{
			currentPages++;
			ShowPageNumber(currentPages, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(sleepTime);
				// In trang không phải cuối cùng
				if (currentPages < totalPage - 1 || (currentPages == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPages];
					continue;
				}
				// In data trang cuối cùng
				if (currentPages == totalPage - 1 && soDocGia % MAX_ROW_PER_PAGE != 0 && i < soDocGia % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPages];
				}
				// In empty line xóa line dư của page trước đó
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyStringDG;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPages > 0)
		{
			currentPages--;
			ShowPageNumber(currentPages, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			// In data ra màn hình
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(sleepTime);
				GoToXY(location.x, location.y + (int)i);
				cout << listData[i + MAX_ROW_PER_PAGE * currentPages];
			}
		}
		else if (inputKey == Key::ESC)
		{
			delete[] listData;
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
void SortStringDocGiaTheoTen(string *&listDG, string *&listName, int q, int r)
{
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	string x = listName[(q + r) / 2];
	do
	{ // Phân đoạn dãy con a[q],..., a[r]
		while (listName[i].compare(x) < 0)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (listName[j].compare(x) > 0)
			j--; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j) // Hoan vi
		{
			Swap(listName[i], listName[j]);
			Swap(listDG[i], listDG[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (q < j) // phần thứ nhất có từ 2 phần tử trở lên
		SortStringDocGiaTheoTen(listDG, listName, q, j);
	if (i < r) // phần thứ ba có từ 2 phần tử trở lên
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
	// Create Empty Line DG
	string emptyStringDG = "";
	{
		emptyStringDG = emptyStringDG + char(179) + string(MADOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(HODOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TENDOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(GIOITINH_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179);
	}

	int currentPages = 0;
	int totalPages = 0;
	int soDocGia = 0;
	int sleepTime = 1;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	string *listDG_AsString = GetAllStringNode(lstDG, soDocGia);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPages = soDocGia / MAX_ROW_PER_PAGE;
	if (soDocGia % MAX_ROW_PER_PAGE != 0)
		totalPages++;

	// Ký tự phân cách '|' as string
	string deli = "";
	deli += char(179);

	// Tách list name từ ToString của độc giả
	string *listName = new string[soDocGia];
	for (int i = 0; i < soDocGia; i++)
	{
		string *tokens = Split(listDG_AsString[i], deli);
		listName[i] = Trim(tokens[3]) + Trim(tokens[2]);
		delete[] tokens;
	}

	// Sort listData theo listName được tách sẵn
	SortStringDocGiaTheoTen(listDG_AsString, listName, 0, soDocGia - 1);
	delete[] listName;

	// In danh sách độc giả ra màn hình
	ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < soDocGia; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPages && i < (currentPages + 1) * (int)MAX_ROW_PER_PAGE)
		{
			Sleep(sleepTime);
			GoToXY(location.x, location.y + i);
			cout << listDG_AsString[i];
		}
	}

	if (mode == Show_Only)
		return;

	// bat phim
	char inputKey = NULL;
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL || inputKey == -32)
			inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPages < totalPages - 1)
		{
			currentPages++;
			ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(sleepTime);
				// In trang không phải cuối cùng
				if (currentPages < totalPages - 1 || (currentPages == totalPages - 1 && soDocGia % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listDG_AsString[i + MAX_ROW_PER_PAGE * currentPages];
					continue;
				}
				// In data trang cuối cùng
				if (currentPages == totalPages - 1 && soDocGia % MAX_ROW_PER_PAGE != 0 && i < soDocGia % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listDG_AsString[i + MAX_ROW_PER_PAGE * currentPages];
				}
				// In empty line xóa line dư của page trước đó
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyStringDG;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPages > 0)
		{
			currentPages--;
			ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			// In data ra màn hình
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(sleepTime);
				GoToXY(location.x, location.y + (int)i);
				cout << listDG_AsString[i + MAX_ROW_PER_PAGE * currentPages];
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

	if (Size(lstDG) == 0)
		return;

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
string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int &showPage, Menu_Mode mode)
{
	// Create Empty Line Độc Giả
	string emptyStringDG = "";
	{
		emptyStringDG = emptyStringDG + char(179) + string(MADOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(HODOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TENDOCGIA_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(GIOITINH_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
		emptyStringDG = emptyStringDG + char(179);
	}

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int currentPage = showPage;
	int totalLines = 0;
	int totalPages = 0;
	string *dsDocGia = NULL;

	// Chuyển List độc giả về string array
	dsDocGia = GetAllStringNode(listDG, totalLines);
	totalPages = totalLines / (int)MAX_ROW_PER_PAGE + (totalLines % (int)MAX_ROW_PER_PAGE == 0 ? 0 : 1);

	// Đưa về trang cuối nếu showPage >= totalPages
	if (currentPage >= totalPages)
	{
		showPage = totalPages - 1;
		return "";
	}

	// Kiểm tra size
	if (totalLines == 0)
		return "";

	string **docGia_AsString = new string *[totalPages];
	int *rowsOfPage = NULL;

	// Tính số line của từng page cần cấp phát cho ds 2 chiều
	if (mode == Both)
	{
		int countTemp = 0;
		int soDongConDu = totalLines % MAX_ROW_PER_PAGE;
		for (int i = 0; i < totalPages - 1; i++)
		{
			docGia_AsString[i] = new string[MAX_ROW_PER_PAGE];
			PushBack(rowsOfPage, (int)MAX_ROW_PER_PAGE, countTemp);
		}
		docGia_AsString[totalPages - 1] = new string[soDongConDu == 0 ? (int)MAX_ROW_PER_PAGE : soDongConDu];
		PushBack(rowsOfPage, (soDongConDu == 0 ? (int)MAX_ROW_PER_PAGE : soDongConDu), countTemp);
	}

	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		location.y += 3;

		// In LIST_DAUSACH ra màn hình
		ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
		for (int i = 0; i < totalLines; i++)
		{
			if (i >= (int)MAX_ROW_PER_PAGE * showPage && i < (showPage + 1) * (int)MAX_ROW_PER_PAGE)
			{
				PrintStringDocGia(dsDocGia[i], {location.x, location.y + (int)(i % MAX_ROW_PER_PAGE)});

				// HL dòng đầu tiên nếu có ở chế độ Bắt phím
				if (WhereY() == location.y && mode == Menu_Mode::Both)
				{
					GoToXY(location.x, location.y + (int)(i % MAX_ROW_PER_PAGE));
					HightLight(dsDocGia[i], hlBGColor, hlTextColor);
					NormalColor();
				}
			}

			// Lưu lại vị trí dòng và lấy toString
			if (mode == Both)
			{
				int line = i % MAX_ROW_PER_PAGE;
				currentPage = i / MAX_ROW_PER_PAGE;
				docGia_AsString[currentPage][line] = (dsDocGia[i]);
			}
		}

		// Xóa Line dư của trang trước nếu là trang cuối
		if (showPage == totalPages - 1 && totalLines % MAX_ROW_PER_PAGE != 0 && showPage != 0)
		{
			NormalColor();
			for (int i = totalLines % MAX_ROW_PER_PAGE; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, location.y + i);
				cout << emptyStringDG;
			}
		}

		if (mode == Show_Only)
		{
			delete[] docGia_AsString;
		}
		delete[] dsDocGia;
	}

	if (mode == Menu_Mode::Both)
	{
		currentPage = showPage;
		currentLine = 0;
		HidePointer();

		// Bắt phím
		char inputKey = NULL;
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL)
				inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP)
				{
					if (currentLine > 0)
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + --currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = (rowsOfPage[currentPage]) - 1;
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < (rowsOfPage[currentPage]) - 1)
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + ++currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, location.y + currentLine);
						HightLight(docGia_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				string deli = "";
				deli += char(179);
				auto temp = Split(docGia_AsString[currentPage][currentLine], deli);
				temp[1] = Trim(temp[1]);
				showPage = currentPage;
				delete[] rowsOfPage;
				delete[] docGia_AsString;
				return temp[1];
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPages - 1 && currentPage < MAX_PAGE_DAUSACH)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				NormalColor();
				for (int i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					if (i < (rowsOfPage[currentPage]))
					{
						GoToXY(location.x, location.y + i);
						cout << docGia_AsString[currentPage][i];
					}
					else
					{
						GoToXY(location.x, location.y + i);
						cout << emptyStringDG;
					}
				}
				GoToXY(location.x, location.y);
				HightLight(dsDocGia[MAX_ROW_PER_PAGE * currentPage], hlBGColor, hlTextColor);
				NormalColor();
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
				// in prev page
				currentPage--;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				NormalColor();
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(location.x, location.y + i);
					cout << docGia_AsString[currentPage][i];
				}
				GoToXY(location.x, location.y);
				HightLight(dsDocGia[MAX_ROW_PER_PAGE * currentPage], hlBGColor, hlTextColor);
				NormalColor();
			}
			else if (inputKey == Key::ESC && currentPage < MAX_PAGE_DAUSACH)
			{
				showPage = currentPage;
				GoToXY(location.x, location.y + currentLine);
				HightLight(docGia_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				delete[] rowsOfPage;
				delete[] docGia_AsString;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}

/// <summary>
/// In labels cho danh sách Độc giả mượn sách quá hạn
/// </summary>
/// <param name="location">Location</param>
/// <param name="row">Số độc giả có trong danh sách</param>
/// <returns>void</returns>
void PrintLabelQuaHan(MYPOINT location, int row)
{
	string labels[] = {"MA DOC GIA", "HO", "TEN", "MA SACH", "TEN SACH", "NGAY MUON", "SO NGAY QUA HAN"};
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, {MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH, 17},
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
void SortQuaHanString(int *&soNgayQH, string *&quaHanString, int q, int r)
{
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = soNgayQH[(q + r) / 2];
	do
	{ // Phân đoạn dãy con a[q],..., a[r]
		while (soNgayQH[i] > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (soNgayQH[j] < x)
			j--; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j) // Hoan vi
		{
			Swap(soNgayQH[i], soNgayQH[j]);
			Swap(quaHanString[i], quaHanString[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (q < j) // phần thứ nhất có từ 2 phần tử trở lên
		SortQuaHanString(soNgayQH, quaHanString, q, j);
	if (i < r) // phần thứ ba có từ 2 phần tử trở lên
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
void InorderGetStringQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG, string *&result, int &count)
{
	if (lstDG != NULL)
	{
		InorderGetStringQuaHan(listDS, lstDG->pLeft, result, count);
		int countMTQuaHan = 0;
		string *mtQuaHanAsString = lstDG->data.ToStringQuaHan(listDS, countMTQuaHan);
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
	// Create Empty Line DG Quá Hạn
	string emptyStringQH = "";
	{
		emptyStringQH = emptyStringQH + char(179) + string(MADOCGIA_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(HODOCGIA_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(TENDOCGIA_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(MASACH_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(TENSACH_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(NGAY_WIDTH, ' ');
		emptyStringQH = emptyStringQH + char(179) + string(17, ' ');
		emptyStringQH = emptyStringQH + char(179);
	}

	MYPOINT location = {20, 3};
	string *quaHanString = NULL;
	int currentPages = 0;
	int totalPages = 0;
	int totalQuaHan = 0;

	// Lấy ra List độc giả dưới dạng String để in ra màn hình
	InorderGetStringQuaHan(listDS, lstDG, quaHanString, totalQuaHan);

	// Tính tổng page dựa vào MAX_ROW_PER_PAGE
	totalPages = totalQuaHan / MAX_ROW_PER_PAGE;
	if (totalQuaHan % MAX_ROW_PER_PAGE != 0)
		totalPages++;

	// Tách ToString lấy số ngày quá hạn
	int *soNgayQH = new int[totalQuaHan];
	string deli = "";
	deli += char(179);
	for (int i = 0; i < totalQuaHan; i++)
	{
		string *arr = Split(quaHanString[i], deli);
		arr[7] = Trim(arr[7]);
		soNgayQH[i] = stoi(arr[7]);
	}

	// Quick Sort list ToString theo soNgayQuaHan
	SortQuaHanString(soNgayQH, quaHanString, 0, totalQuaHan - 1);
	delete[] soNgayQH;

	// In ra màn hình
	PrintLabelQuaHan(location, MAX_ROW_PER_PAGE);
	ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 4);
	for (int i = 0; i < totalQuaHan; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPages && i < (currentPages + 1) * (int)MAX_ROW_PER_PAGE)
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
		if (inputKey == Key::_NULL || inputKey == -32)
			inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPages < totalPages - 1)
		{
			currentPages++;
			ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(3);
				// in trang not cuoi cung
				if (currentPages < totalPages - 1 || (currentPages == totalPages - 1 && totalQuaHan % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPages];
					continue;
				}
				// in trang cuoi cung
				if (currentPages == totalPages - 1 && totalQuaHan % MAX_ROW_PER_PAGE != 0 && i < totalQuaHan % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPages];
				}
				else
				{
					GoToXY(location.x, location.y + i);
					cout << emptyStringQH;
				}
			}
		}
		else if (inputKey == Key::PAGE_UP && currentPages > 0)
		{
			currentPages--;
			ShowPageNumber(currentPages, totalPages, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				Sleep(3);
				GoToXY(location.x, location.y + (int)i);
				cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPages];
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

/// <summary>
/// <para>Kiểm tra Độc giả mượn sách quá 30 ngày => khóa thẻ</para>
/// Duyệt LNR
/// </summary>
/// <param name="listDS">LIST_DAUSACH để tính số ngày quá hạn</param>
/// <returns>void</returns>
void InorderCheckKhoaThe(LIST_DOCGIA& listDG)
{
	if (listDG != NULL)
	{
		InorderCheckKhoaThe(listDG->pLeft);

		if (listDG->data.IsQua30Ngay())
		{
			listDG->data.trangThai = TheBiKhoa;
		}

		InorderCheckKhoaThe(listDG->pRight);
	}
}

#pragma region-- ------------------DOC GHI FILE

/// <summary>
/// <para>Chuyển LIST_DOCGIA thành list string để lưu vô file text</para>
/// Duyệt LRN
/// </summary>
/// <param name="lstDG">LIST_DOCGIA cần lưu</param>
/// <param name="result">List string sau khi convert</param>
/// <param name="count">Số DOCGIA sau khi lưu (ban đầu gán = 0)</param>
/// <returns>void</returns>
void PosorderGetStringFile(LIST_DOCGIA lstDG, string *&result, int &count)
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
string *GetAllStringFileNodeLRN(LIST_DOCGIA listDG)
{
	string *result = NULL;
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
void InorderGetStringFile(LIST_DOCGIA lstDG, string *&result, int &count)
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
string *GetAllStringFileNodeLNR(LIST_DOCGIA listDG)
{
	string *result = NULL;
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
bool ReadFromFile(LIST_DOCGIA &listDG, string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = 0;
		auto lstDocGia = fileHandler.GetTokens(size);
		for (int i = 0; i < size; i++)
		{
			DOCGIA *docGia = new DOCGIA;
			*docGia = ParseVectorStringFileDG(lstDocGia[i]);
			Insert(listDG, *docGia);
		}
		delete[] lstDocGia;
	}
	catch (const exception &ex)
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
	catch (const exception &ex)
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
		string *data = GetAllStringFileNodeLRN(lstDG);
		for (auto i = 0; i < size; i++)
		{
			if (i < size - 1)
				data[i] += '\n';
		}
		fileHandler.WriteToFile(data, Replace, size);
		delete[] data;
	}
	catch (const exception &ex)
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
		int soDG = Size(listDG);
		int size = MAX_DOCGIA - soDG;
		string *data = NULL;
		for (auto i = 0; i < size; i++)
		{
			string temp = "";
			temp += to_string(maDocGiaArr[i]);
			if (i < size - 1)
				temp += '\n';
			PushBack(data, temp, c);
		}
		fileHandler.WriteToFile(data, Replace, size);
		delete[] data;
	}
	catch (const exception &ex)
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
bool WriteMuonTraToFile(LIST_MUONTRA &listMT, string maDG, string defaultPath)
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
bool ReadMuonTraFromFile(LIST_MUONTRA &listMT, string maDG, string path)
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
void DuyetDocFileMuonTra(LIST_DOCGIA &lstDG, string path)
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
DOCGIA ParseVectorStringDG(string *data)
{
	DOCGIA docGia; // = new DOCGIA;
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
	string labels[] = {"Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:"};
	string inputTitle = "NHAP THONG TIN DOC GIA";
	CONDITION conditions[] = {{Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH}, {Name, 1, TENDOCGIA_WIDTH}, {Enum, 1, 2}, {Enum2, 1, 2, Default}};
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 5);
	string guilds[] = {"MA DOC GIA LA TU DONG", "CHI NHAP CHU CAI", "CHI NHAP CHU CAI", "0: NAM\n1: NU", "0: THE BI KHOA\n1: DANG HOAT DONG"};
	form.Guilds = guilds;
	DOCGIA docGia = DOCGIA();
	string datas[] = {to_string(maThe), "", "", "0", "1"};
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
	string labels[] = {"Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:"};
	string inputTitle = "NHAP THONG TIN DOC GIA";
	CONDITION conditions[] = {{Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH}, {Name, 1, TENDOCGIA_WIDTH}, {Enum, 1, 2}, {Enum2, 1, 2}};
	string guilds[] = {"MA DOC GIA LA TU DONG", "CHI NHAP CHU CAI", "CHI NHAP CHU CAI", "0: NAM\n1: NU", "0: THE BI KHOA\n1: DANG HOAT DONG"};
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
	string datas[5] = {to_string(docGia.maDocGia), docGia.ho, docGia.ten, temp1, temp2};
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