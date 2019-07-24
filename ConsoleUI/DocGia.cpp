#include "DocGia.h"

int* maDocGiaArr = NULL;
int newPos;

#pragma region -------------------------------------------DOCGIA
// Chuyen vector string trong file thanh doc gia
DOCGIA ParseVectorStringFile(string* data)
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
// Chuyen vector string thanh doc gia
DOCGIA ParseVectorString(string* data)
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
// in ra node
void DOCGIA::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DOCGIA::ToString();
}
// chen | vao giua field
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
// chuyen object dau sach thanh string luu file
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
// ...
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
			auto newDocGia = ParseVectorString(form.OutputResults);
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
// kiem tra xem doc gia co duoc muon sach
// 0> lam mat sach
// 1> khong muon sach qua 7 ngay
// 2> the doc gia dang hoat dong
// 3> muon toi da 3 sach
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
// ...
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

NODE_DOCGIA::NODE_DOCGIA(DOCGIA& data)
{
	this->data = data;
	this->pLeft = NULL;
	this->pRight = NULL;
}

#pragma region -------------------------------------------LIST_DOCGIA
// so node cua cay
int Size(LIST_DOCGIA listDG)
{
	if (listDG == NULL)
		return 0;
	else
		return 1 + Size(listDG->pLeft) + Size(listDG->pRight);
}
// Doc tu file txt
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
			*docGia = ParseVectorStringFile(lstDocGia[i]);
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
// Lay ds maDocGia
void GetMaDGtoVector(LIST_DOCGIA lstDG, int*& dsMaDocGia)
{
	if (lstDG != NULL)
	{
		GetMaDGtoVector(lstDG->pLeft, dsMaDocGia);
		int c = 0;
		PushBack(dsMaDocGia, lstDG->data.maDocGia, c);
		//dsMaDocGia.push_back(lstDG->data.maDocGia);
		GetMaDGtoVector(lstDG->pRight, dsMaDocGia);
	}
}
// ...
string* GetDGtoVector(DOCGIA docGia)
{
	string* docGiaInfo = NULL;
	int c = 0;

	PushBack(docGiaInfo, to_string(docGia.maDocGia), c);
	PushBack(docGiaInfo, docGia.ho, c);
	PushBack(docGiaInfo, docGia.ten, c);
	//docGiaInfo.push_back(to_string(docGia.maDocGia));
	//docGiaInfo.push_back(docGia.ho);
	//docGiaInfo.push_back(docGia.ten);

	if (docGia.gioiTinh == Nam)
	{
		string temp = "Nam";
		PushBack(docGiaInfo, temp, c);
		//docGiaInfo.push_back("Nam");
	}
	else
	{
		string temp = "Nu";
		PushBack(docGiaInfo, temp, c);
		//docGiaInfo.push_back("Nu");
	}
	if (docGia.trangThai == DangHoatDong)
	{
		string temp = "Dang hoat dong";
		PushBack(docGiaInfo, temp, c);
		//docGiaInfo.push_back("Dang hoat dong");
	}
	else
	{
		string temp = "The bi khoa";
		PushBack(docGiaInfo, temp, c);
		//docGiaInfo.push_back("The bi khoa");
	}

	return docGiaInfo;
}
// Doc mang MADOCGIA tu file
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
// duyet cay lay data string file
void PreorderGetStringFile(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		PreorderGetStringFile(lstDG->pLeft, result, count);
		PreorderGetStringFile(lstDG->pRight, result, count);
		PushBack(result, lstDG->data.ToStringFile(), count);
	}
}
// duyet cay lay ToStringFile cua node doc gia
string* GetAllStringFileNodePre(LIST_DOCGIA listDG)
{
	string* result = NULL;
	int count = 0;
	PreorderGetStringFile(listDG, result, count);
	return result;
}
// duyet cay lay data string file
void InorderGetStringFile(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetStringFile(lstDG->pLeft, result, count);
		PushBack(result, lstDG->data.ToStringFile(), count);
		//result.push_back(lstDG->data.ToStringFile());
		InorderGetStringFile(lstDG->pRight, result, count);
	}
}
// duyet cay lay ToStringFile cua node doc gia
string* GetAllStringFileNode(LIST_DOCGIA listDG)
{
	string* result = NULL;
	int count = 0;
	InorderGetStringFile(listDG, result, count);
	return result;
}
// Ghi du lieu doc gia ra file text
bool WriteToFile(LIST_DOCGIA lstDG, string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = Size(lstDG);
		string* data = GetAllStringFileNodePre(lstDG);
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
// Ghi du lieu ma doc gia ra file text
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
// Sinh ma DG ngau nhien
int GetRandomMaDG(LIST_DOCGIA listDG)
{
	srand((unsigned int)time((time_t)NULL));
	int t = Size(listDG);
	newPos = rand() % (MAX_DOCGIA - Size(listDG));
	return maDocGiaArr[newPos];
}
// Doi vi tri 2 ma trong MADOCGIAARR
void SwapMaDG(int pos1, int pos2)
{
	Swap(maDocGiaArr[pos1], maDocGiaArr[pos2]);
}
// Remove ma doc gia from array khi them moi doc gia
void RemoveMaDG(LIST_DOCGIA listDG)
{
	//maDocGiaArr.erase(maDocGiaArr.begin() + newPos);
	Erase(maDocGiaArr, newPos, MAX_DOCGIA - Size(listDG));
}
// Giai phong vung nho
void FreeMemory(NODE_DOCGIA* root)
{
	if (root == NULL)
		return;
	FreeMemory(root->pLeft);
	FreeMemory(root->pRight);
	delete root;
	root = NULL;
}
// khoi toa cay
void Init(LIST_DOCGIA& lstDG)
{
	lstDG = NULL;
}
// them node
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
// duyet cay
void NLR(LIST_DOCGIA lstDG)
{
	if (lstDG != NULL)
	{
		NLR(lstDG->pLeft);
		NLR(lstDG->pRight);
	}
}
// tim doc gia dua vao maDocGia
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
// xoa 1 doc gia
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
// form nhap doc gia moi
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
		return ParseVectorString(form.OutputResults);
	}
	else
	{
		form.ResetOutput();
	}
	return docGia;
}
// duyet cay lay data string
void InorderGetString(LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetString(lstDG->pLeft, result, count);
		PushBack(result, lstDG->data.ToString(), count);
		InorderGetString(lstDG->pRight, result, count);
	}
}
// duyet cay lay ToString cua node doc gia
string* GetAllStringNode(LIST_DOCGIA listDG, int& count)
{
	string* result = NULL;
	//int count = 0;
	InorderGetString(listDG, result, count);
	return result;
}
// row la so dong data
void PrintLabelDocGia(MYPOINT location, int row)
{
	string labels[] = { "MA DOC GIA", "HO", "TEN", "GIOI TINH", "TRANG THAI THE" };
	auto lstBorder = LISTBORDERTEXT(labels, 5);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, GIOITINH_WIDTH, TRANGTHAIDG_WIDTH },
		row, BORDER_COLOR);
}
// in content theo maDG
string PrintContentSortMaDG(LIST_DOCGIA listDG, MYPOINT location, Menu_Mode m)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int currentPage = 0;

	int size = 0;
	string* listData = GetAllStringNode(listDG, size);

	int totalPage = size / MAX_ROW_PER_PAGE;
	if (size % MAX_ROW_PER_PAGE != 0) totalPage++;
	string deli = "";
	deli += char(179);

	// In ra mh
	for (int i = 0; i < size; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			GoToXY(location.x, location.y + i);
			cout << listData[i];
		}
	}
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	if (m == Show_Only) return "";
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
				// in trang not cuoi cung
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE != 0
					&& i < size % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
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
			// in prev page
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, location.y + (int)i);
				cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
			}
		}
		else if (inputKey == Key::ESC)
		{
			return "ESC";
		}
	} while (!_kbhit());
	return "";
}
// In ds doc gia theo ten
string PrintContentSortTen(LIST_DOCGIA lstDG, MYPOINT location, Menu_Mode m)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int currentPage = 0;

	int size = 0;
	string* listData = GetAllStringNode(lstDG, size);

	int totalPage = size / MAX_ROW_PER_PAGE;
	if (size % MAX_ROW_PER_PAGE != 0) totalPage++;
	string deli = "";
	deli += char(179);

	// sort
	string minHT;
	string min;
	int posMin;
	for (int i = 0; i < size - 1; i++)
	{
		if (i == 6)
		{
			GoToXY(0, 0);
		}
		min = listData[i];
		auto temp = Split(listData[i], deli);
		minHT = Trim(temp[3]) + Trim(temp[2]);
		posMin = i;
		for (int j = i + 1; j < size; j++)
		{
			temp = Split(listData[j], deli);
			auto t = (Trim(temp[3]) + Trim(temp[2]));
			if (t.compare(minHT) < 0)
			{
				min = listData[j];
				posMin = j;

				temp = Split(listData[j], deli);
				minHT = Trim(temp[3]) + Trim(temp[2]);
			}
		}
		listData[posMin] = listData[i];
		listData[i] = min;
	}
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
	// In ra mh
	for (int i = 0; i < size; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			GoToXY(location.x, location.y + i);
			cout << listData[i];
		}
	}

	if (m == Show_Only) return "";
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
				// in trang not cuoi cung
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE != 0
					&& i < size % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
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
			// in prev page
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, location.y + (int)i);
				cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
			}
		}
		else if (inputKey == Key::ESC)
		{
			return "ESC";
		}
	} while (!_kbhit());
	return "";
}
// In ds doc gia: mode = 1 (Sort theo maDG)
//                mode = 2 (Sort theo hoTen)
string PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode, Menu_Mode m)
{
	PrintLabelDocGia(location, MAX_ROW_PER_PAGE);
	auto loc = location;
	loc.y += 3;
	if (mode == 1)
	{
		return PrintContentSortMaDG(lstDG, loc, m);
	}
	else
	{
		return PrintContentSortTen(lstDG, loc, m);
	}
}
// ...
void PrintStringDocGia(string data, MYPOINT location)
{
	GoToXY(location.x, location.y);
	cout << data;
}
// in danh sach de quan ly doc gia co highLight
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
				if (/*backUpLocation.y == WhereY()*/i == line + page*MAX_ROW_PER_PAGE && mode == Menu_Mode::Both)
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
// luu list muontra vo file
bool WriteMuonTraToFile(LIST_MUONTRA& listMT, string maDG)
{
	string path = MUONTRA_FILE_PATH;
	path += maDG;
	path += ".txt";
	return listMT.WriteToFile(path);
}
void DuyetLuuFile(LIST_DOCGIA lstDG)
{
	if (lstDG != NULL)
	{
		if (lstDG->data.listMuonTra.IsEmpty() == false)
		{
			string maAsString = to_string(lstDG->data.maDocGia);
			//MergeWordWithNumber(maAsString, lstDG->data.maDocGia, 4);
			WriteMuonTraToFile(lstDG->data.listMuonTra, maAsString);
		}
		DuyetLuuFile(lstDG->pLeft);
		DuyetLuuFile(lstDG->pRight);
	}
}
bool ReadMuonTraFromFile(LIST_MUONTRA& listMT, string maDG, string path)
{
	path += MUONTRA_FILE_PATH;
	path += maDG;
	path += ".txt";
	return listMT.ReadFromFile(path);
}
void DuyetDocFile(LIST_DOCGIA& lstDG, string path)
{
	if (lstDG != NULL)
	{
		DuyetDocFile(lstDG->pLeft, path);
		string maAsString = to_string(lstDG->data.maDocGia);
		//MergeWordWithNumber(maAsString, lstDG->data.maDocGia, 4);
		ReadMuonTraFromFile(lstDG->data.listMuonTra, maAsString, path);
		DuyetDocFile(lstDG->pRight, path);
	}
}
#pragma endregion

// print label qua han
void PrintLabelQuaHan(MYPOINT location, int row)
{
	string labels[] = { "MA DOC GIA", "HO", "TEN", "MA SACH", "TEN SACH", "NGAY MUON", "SO NGAY QUA HAN" };
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH, 17 },
		row, BORDER_COLOR);
}
// sort qua han string
void SortQuaHanString(int*& soNgayQH, string*& quaHanString, int q, int r)
{
	int temp;
	string tempStr;

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
// get tostring qua han
void InorderGetStringQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG, string*& result, int& count)
{
	if (lstDG != NULL)
	{
		InorderGetStringQuaHan(listDS, lstDG->pLeft, result, count);
		int c = 0;
		string* temp = lstDG->data.ToStringQuaHan(listDS, c);
		for (int i = 0; i < c; i++)
		{
			PushBack(result, temp[i], count);
		}
		InorderGetStringQuaHan(listDS, lstDG->pRight, result, count);
	}
}
// Show ds qua han
void ShowListQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG)
{
	MYPOINT location = { 20, 3 };
	string* quaHanString = NULL;
	int size = 0;
	InorderGetStringQuaHan(listDS, lstDG, quaHanString, size);

	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(MASACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NGAY_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(17, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int currentPage = 0;

	int totalPage = size / MAX_ROW_PER_PAGE;
	if (size % MAX_ROW_PER_PAGE != 0) totalPage++;

	// sap xep
	int* soNgayQH = new int[size];
	string deli = ""; deli += char(179);
	for (int i = 0; i < size; i++)
	{
		auto temp = Split(quaHanString[i], deli);
		temp[7] = Trim(temp[7]);
		soNgayQH[i] = stoi(temp[7]);
	}
	SortQuaHanString(soNgayQH, quaHanString, 0, size - 1);
	delete[] soNgayQH;
	
	PrintLabelQuaHan(location, MAX_ROW_PER_PAGE);
	ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 4);
	// In ra mh
	for (int i = 0; i < size; i++)
	{
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			GoToXY(location.x, location.y + i + 3);
			cout << quaHanString[i];
		}
	}
	
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
				// in trang not cuoi cung
				if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE == 0))
				{
					GoToXY(location.x, location.y + (int)i);
					cout << quaHanString[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE != 0
					&& i < size % MAX_ROW_PER_PAGE)
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
			// in prev page
			currentPage--;
			ShowPageNumber(currentPage, totalPage, location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
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