#include "DocGia.h"

std::vector<int> maDocGiaArr;
int newPos;

#pragma region -------------------------------------------DOCGIA
// Chuyen vector string trong file thanh doc gia
DOCGIA ParseVectorStringFile(std::vector<std::string> data)
{
	DOCGIA docGia;// = new DOCGIA;
	docGia.maDocGia = atoi(StringToCharArray(data[0]));
	docGia.ho = data[1];
	docGia.ten = data[2];
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
		docGia.trangThai = TheBiKhoa;
	}
	return docGia;
}
// Chuyen vector string thanh doc gia
DOCGIA ParseVectorString(std::vector<std::string> data)
{
	DOCGIA docGia;// = new DOCGIA;
	docGia.maDocGia = atoi(StringToCharArray(data[0]));
	docGia.ho = data[1];
	docGia.ten = data[2];
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
		docGia.trangThai = TheBiKhoa;
	}
	return docGia;
}
// in ra node
void DOCGIA::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	std::cout << DOCGIA::ToString();
}
// chen | vao giua field
std::string DOCGIA::ToString()
{
	std::string tempStr = "";
	MergeWordWithNumber(tempStr, this->maDocGia, 4);
	int temp;
	// ma doc gia
	std::string result = "";
	result += char(179);
	result += tempStr;
	temp = MADOCGIA_WIDTH - tempStr.size();
	result += std::string(temp, ' ');
	// ho
	result += char(179);
	result += this->ho;
	temp = HODOCGIA_WIDTH - this->ho.size();
	result += std::string(temp, ' ');
	// ten
	result += char(179);
	result += this->ten;
	temp = TENDOCGIA_WIDTH - this->ten.size();
	result += std::string(temp, ' ');
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
	result += std::string(temp, ' ');
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
	result += std::string(temp, ' ');
	result += char(179);
	return result;
}
// chuyen object dau sach thanh string luu file
std::string DOCGIA::ToStringFile()
{
	std::string result = "";
	result = std::to_string(this->maDocGia);
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
	std::vector<std::string> labels = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	std::string inputTitle = "NHAP THONG TIN DOC GIA";
	std::vector<CONDITION> conditions = { {Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH},{Name, 1, TENDOCGIA_WIDTH},
									{Enum, 1, 2 },{Enum2, 1, 2, Default} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle);
	//DOCGIA docGia = DOCGIA();
	std::string temp1, temp2;
	if (docGia.gioiTinh == Nam)
	{
		temp1 = "0";
	}
	else
	{
		temp1 = "1";
	}
	if (docGia.trangThai)
	{
		temp2 = "0";
	}
	else
	{
		temp2 = "1";
	}
	form.ParseData({ std::to_string(docGia.maDocGia) , docGia.ho, docGia.ten, temp1, temp2 });
	form.currentLine = 1;
	while (true)
	{
		if (form.Show(1, 4))
		{
			auto newDocGia = ParseVectorString(form.OutputResults);
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
bool ReadFromFile(LIST_DOCGIA& listDG, std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		auto lstDocGia = fileHandler.GetTokens();
		int size = lstDocGia.size();
		//DAUSACH* dauSach = new DAUSACH[size];
		for (int i = 0; i < size; i++)
		{
			DOCGIA* docGia = new DOCGIA;
			*docGia = ParseVectorStringFile(lstDocGia[i]);
			Insert(listDG, *docGia);
		}
	}
	catch (const std::exception& ex)
	{
		GoToXY(0, 0);
		std::cout << ex.what();
		return false;
	}
	return true;
}
// Lay ds maDocGia
void GetMaDGtoVector(LIST_DOCGIA lstDG, std::vector<int>& dsMaDocGia)
{
	if (lstDG != NULL)
	{
		GetMaDGtoVector(lstDG->pLeft, dsMaDocGia);
		dsMaDocGia.push_back(lstDG->data.maDocGia);
		GetMaDGtoVector(lstDG->pRight, dsMaDocGia);
	}
}
// Doc mang MADOCGIA tu file
bool ReadMaDGFromFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		maDocGiaArr = fileHandler.GetLinesInt();
	}
	catch (const std::exception& ex)
	{
		GoToXY(0, 0);
		std::cout << ex.what();
		return false;
	}
	return true;
}
// duyet cay lay data string file
void InorderGetStringFile(LIST_DOCGIA lstDG, std::vector<std::string>& result)
{
	if (lstDG != NULL)
	{
		InorderGetStringFile(lstDG->pLeft, result);
		result.push_back(lstDG->data.ToStringFile());
		InorderGetStringFile(lstDG->pRight, result);
	}
}
// duyet cay lay ToStringFile cua node doc gia
std::vector<std::string> GetAllStringFileNode(LIST_DOCGIA listDG)
{
	std::vector<std::string> result;
	InorderGetStringFile(listDG, result);
	return result;
}
// Ghi du lieu doc gia ra file text
bool WriteToFile(LIST_DOCGIA lstDG, std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = Size(lstDG);
		std::vector<std::string> data = GetAllStringFileNode(lstDG);
		for (auto i = 0; i < size; i++)
		{
			if (i < size - 1)
				data[i] += '\n';
		}
		fileHandler.WriteToFile(data, Replace);
	}
	catch (const std::exception& ex)
	{
		GoToXY(0, 0);
		std::cout << ex.what();
		return false;
	}
	return true;
}
// Ghi du lieu ma doc gia ra file text
bool WriteMaDGToFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = maDocGiaArr.size();
		std::vector<std::string> data;
		for (auto i = 0; i < size; i++)
		{
			std::string temp = "";
			temp += std::to_string(maDocGiaArr[i]);
			if (i < size - 1)
				temp += '\n';
			data.push_back(temp);
		}
		fileHandler.WriteToFile(data, Replace);
	}
	catch (const std::exception& ex)
	{
		GoToXY(0, 0);
		std::cout << ex.what();
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
void RemoveMaDG()
{
	maDocGiaArr.erase(maDocGiaArr.begin() + newPos);
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
	std::vector<std::string> labels = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	std::string inputTitle = "NHAP THONG TIN DOC GIA";
	std::vector<CONDITION> conditions = { {Number_Only, 1, 4, Default}, {Name, 1, HODOCGIA_WIDTH},{Name, 1, TENDOCGIA_WIDTH},
													{Enum, 1, 2 },{Enum2, 1, 2, Default} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle);
	std::vector<std::string> guilds = {"MA DOC GIA LA TU DONG", "CHI NHAP CHU CAI", "CHI NHAP CHU CAI", "0: NAM\n1: NU", "0: THE BI KHOA\n1: DANG HOAT DONG"};
	form.Guilds = guilds;
	DOCGIA docGia = DOCGIA();
	form.ParseData({ std::to_string(maThe), "","","0","1" });
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
void InorderGetString(LIST_DOCGIA lstDG, std::vector<std::string>& result)
{
	if (lstDG != NULL)
	{
		InorderGetString(lstDG->pLeft, result);
		result.push_back(lstDG->data.ToString());
		InorderGetString(lstDG->pRight, result);
	}
}
// duyet cay lay ToString cua node doc gia
std::vector<std::string> GetAllStringNode(LIST_DOCGIA listDG)
{
	std::vector<std::string> result;
	InorderGetString(listDG, result);
	return result;
}
// row la so dong data
void PrintLabelDocGia(MYPOINT location, int row)
{
	std::vector<std::string> labels = { "MA DOC GIA", "HO", "TEN", "GIOI TINH", "TRANG THAI THE" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, GIOITINH_WIDTH, TRANGTHAIDG_WIDTH },
		row, BORDER_COLOR);
}
// in content theo maDG
std::string PrintContentSortMaDG(LIST_DOCGIA listDG, MYPOINT location, Menu_Mode m)
{
	std::string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + std::string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int currentPage = 0;

	std::vector<std::string> listData = GetAllStringNode(listDG);
	size_t size = listData.size();

	int totalPage = size / MAX_ROW_PER_PAGE;
	if (size % MAX_ROW_PER_PAGE != 0) totalPage++;
	std::string deli = "";
	deli += char(179);

	// In ra mh
	for (size_t i = 0; i < size; i++)
	{
		if (i >= MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * MAX_ROW_PER_PAGE)
		{
			GoToXY(location.x, location.y + i);
			std::cout << listData[i];
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
					std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE != 0
					&& i < size % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
				}
				else
				{
					GoToXY(location.x, location.y + i);
					std::cout << emptyTemplate;
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
				std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
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
std::string PrintContentSortTen(LIST_DOCGIA lstDG, MYPOINT location, Menu_Mode m)
{
	std::string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + std::string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int currentPage = 0;

	std::vector<std::string> listData = GetAllStringNode(lstDG);
	size_t size = listData.size();

	int totalPage = size / MAX_ROW_PER_PAGE;
	if (size % MAX_ROW_PER_PAGE != 0) totalPage++;
	std::string deli = "";
	deli += char(179);

	// sort
	std::string minHT;
	std::string min;
	int posMin;
	for (size_t i = 0; i < size - 1; i++)
	{
		if (i == 6)
		{
			GoToXY(0, 0);
		}
		min = listData[i];
		auto temp = Split(listData[i], deli);
		minHT = Trim(temp[3]) + Trim(temp[2]);
		posMin = i;
		for (size_t j = i + 1; j < size; j++)
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
	for (size_t i = 0; i < size; i++)
	{
		if (i >= MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * MAX_ROW_PER_PAGE)
		{
			GoToXY(location.x, location.y + i);
			std::cout << listData[i];
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
					std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && size % MAX_ROW_PER_PAGE != 0
					&& i < size % MAX_ROW_PER_PAGE)
				{
					GoToXY(location.x, location.y + (int)i);
					std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
				}
				else
				{
					GoToXY(location.x, location.y + i);
					std::cout << emptyTemplate;
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
				std::cout << listData[i + MAX_ROW_PER_PAGE * currentPage];
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
std::string PrintAllDocGia(LIST_DOCGIA lstDG, MYPOINT location, int mode, Menu_Mode m)
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
void PrintStringDocGia(std::string data, MYPOINT location)
{
	GoToXY(location.x, location.y);
	cout << data;
}

// in danh sach de quan ly doc gia co highLight
std::string PrintAllDGWithHL(LIST_DOCGIA listDG, MYPOINT location, int& page, Menu_Mode mode)
{
	std::string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + std::string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	MYPOINT backUpLocation = MYPOINT(0, 0);
	MYPOINT loc = MYPOINT(0, 0);
	std::vector<std::string> dsDocGia;
	std::vector<std::vector<std::string>> datas;
	std::vector<std::vector<int>> rows;
	int currentLine = 0;
	int currentPage = page;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;

	// chuyen list doc gia ve mang string
	if (listDG != NULL)
	{
		dsDocGia = GetAllStringNode(listDG);
	}
	int totalLine = dsDocGia.size();
	// them page
	for (int i = 0; i < totalLine / (int)MAX_ROW_PER_PAGE; i++)
	{
		datas.push_back({});
		rows.push_back({});
	}
	if (totalLine % MAX_ROW_PER_PAGE != 0)
	{
		datas.push_back({});
		rows.push_back({});
	}
	// tranh vuot qua so trang MAX
	if (currentPage >= (int)datas.size())
	{
		//currentPage = datas.size() - 1;
		page = datas.size() - 1;
		return "";
	}
	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelDocGia(location, MAX_ROW_PER_PAGE);
		ShowPageNumber(currentPage, datas.size(),location.x, location.y + (int)MAX_ROW_PER_PAGE + 4);
		location.y += 3;
		backUpLocation = location;
		//print data
		for (int i = 0; i < totalLine; i++)
		{
			Sleep(1);
			if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
			{
				PrintStringDocGia(dsDocGia[i], { location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) });
				if (backUpLocation.y == WhereY() && mode == Menu_Mode::Both)
				{
					SetBGColor(hlBGColor);
					SetTextColor(hlTextColor);
					PrintStringDocGia(dsDocGia[i], location);
					SetBGColor(BG_COLOR);
					SetTextColor(TEXT_INPUT_COLOR);
				}
			}
			// luu lai vi tri dong
			currentPage = i / MAX_ROW_PER_PAGE;
			rows[currentPage].push_back(i % MAX_ROW_PER_PAGE + location.y);
			datas[currentPage].push_back(dsDocGia[i]);
		}
		// xoa nhung line du cua trang truoc do
		if (page == datas.size() - 1 && totalLine % MAX_ROW_PER_PAGE != 0 && page != 0)
		{
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (int i = totalLine % MAX_ROW_PER_PAGE; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, rows[page - 1][i]);
				std::cout << emptyTemplate;
			}
		}
	}
	currentPage = page;
	// bat phim
	if (mode == Menu_Mode::Both)
	{
		currentLine = 0;
		
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
						currentLine = rows[currentPage].size() - 1;
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < (int)rows[currentPage].size() - 1)
					{
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[currentPage][++currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, (int)rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, rows[currentPage][currentLine]);
						HightLight(datas[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				std::string deli = ""; deli += char(179);
				auto temp = Split(datas[currentPage][currentLine], deli);
				temp[1] = Trim(temp[1]);
				page = currentPage;
				return temp[1];
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < (int)datas.size() - 1)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, datas.size(), location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					if (i < rows[currentPage].size())
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						std::cout << datas[currentPage][i];
					}
					else
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						std::cout << emptyTemplate;
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
				ShowPageNumber(currentPage, datas.size(), location.x, location.y + (int)MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(backUpLocation.x, backUpLocation.y + i);
					std::cout << datas[currentPage][i];
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
				//ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "Empty";
}
#pragma endregion