#include "DocGia.h"

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
#pragma endregion

#pragma region -------------------------------------------LIST_DOCGIA
// so node cua cay
int Size(LIST_DOCGIA listDG)
{
	if (listDG == NULL)
		return 0;
	else
		return 1 + Size(listDG->pLeft) + Size(listDG->pLeft);
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
		NODE_DOCGIA* p = new NODE_DOCGIA;
		p->data = input;
		p->pLeft = p->pRight = NULL;
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
	DOCGIA docGia = DOCGIA();
	form.ParseData({ std::to_string(maThe), "","","0","1" });
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
// row la so dong data
void PrintLabelDocGia(MYPOINT location, int row)
{
	std::vector<std::string> labels = { "MA DOC GIA", "HO", "TEN", "GIOI TINH", "TRANG THAI THE" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { MADOCGIA_WIDTH, HODOCGIA_WIDTH, TENDOCGIA_WIDTH, GIOITINH_WIDTH, TRANGTHAIDG_WIDTH },
		row, BORDER_COLOR);
}
// in content theo maDG
void PrintContentSortMaDG(LIST_DOCGIA lstDG, MYPOINT& location)
{
	if (lstDG != NULL)
	{
		PrintContentSortMaDG(lstDG->pLeft, location);
		lstDG->data.Print({ location.x,location.y++ }, BG_COLOR, TEXT_INPUT_COLOR);
		PrintContentSortMaDG(lstDG->pRight, location);
	}
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
// ...
void PrintContentSortTen(LIST_DOCGIA lstDG, MYPOINT location)
{
	std::vector<std::string> listData = GetAllStringNode(lstDG);
	size_t size = listData.size();
	std::string deli = "";
	deli += char(179);

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
	// In ra mh
	for (size_t i = 0; i < size; i++)
	{
		GoToXY(location.x, location.y + i);
		std::cout << listData[i];
	}
}
// In ds doc gia: mode = 1 (Sort theo maDG)
//                mode = 2 (Sort theo hoTen)
void PrintSortMaDG(LIST_DOCGIA lstDG, MYPOINT location, int mode)
{
	PrintLabelDocGia(location, MAX_ROW_PER_PAGE);
	auto loc = location;
	loc.y += 3;
	if (mode == 1)
	{
		PrintContentSortMaDG(lstDG, loc);
	}
	else
	{
		PrintContentSortTen(lstDG, loc);
	}
}
#pragma endregion