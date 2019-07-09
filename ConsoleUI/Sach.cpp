#include "Sach.h"

#pragma region -------------------------------------------SACH
// in ra node
void SACH::Print(MYPOINT location, Color bgSelectColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(bgSelectColor);
	std::cout << SACH::ToString();
}
// chen | giua cac field
std::string SACH::ToString()
{
	int temp;
	// Ma sach
	std::string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += std::string(temp, ' ');
	// Trang thai
	result += char(179);
	std::string str = "";
	switch (this->trangThai)
	{
	case 0:
		str = "Cho muon duoc";
		break;
	case 1:
		str = "Da muon";
		break;
	case 2:
		str = "Da thanh ly";
		break;
	default:
		break;
	}
	result += str;
	temp = TRANGTHAISACH_WIDTH - str.size();
	result += std::string(temp, ' ');
	// Vi tri
	result += char(179);
	result += this->viTri;
	temp = VITRI_WIDTH - this->viTri.size();
	result += std::string(temp, ' ');
	result += char(179);
	return result;
}
// chuyen vector<string> vo obj Sach
SACH ParseVectorString(std::vector<std::string> data)
{
	SACH sach;
	sach.maSach = data[0];
	if (data[1] == "0")
		sach.trangThai = ChoMuonDuoc;
	else if (data[1] == "1")
		sach.trangThai = DaMuon;
	else
		sach.trangThai = DaThanhLy;
	sach.viTri = data[2];
	return sach;
}
// hien form nhap SACH
SACH SACH::Input(RECTANGLE rect, std::string maSach)
{
	std::string title = "Nhap Sach";
	std::vector<std::string> labels = { "Ma sach", "Trang thai:", "Vi tri:" };
	std::vector<CONDITION> conditions = { {All, 6, 6, Default}, {Enum, 1, 3, Default}, {Mix, 1, VITRI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, title);
	form.ParseData({ maSach, "0", "" });
	form.currentLine = 2;
	if (form.Show(2))
	{
		return ParseVectorString(form.OutputResults);
	}
	else
	{
		form.ResetOutput();
	}
	return *this;
}

#pragma endregion

#pragma region -------------------------------------------NODE_SACH
NODE_SACH::NODE_SACH()
{
	
}
// Khoi tao 1 node sach moi
NODE_SACH::NODE_SACH(SACH& data)
{
	this->data = data;
	this->pNext = NULL;
}

#pragma endregion

#pragma region -------------------------------------------LIST_SACH
// row la so dong data
void PrintLabelSach(MYPOINT location, int row)
{
	std::vector<std::string> labels = { "MA SACH", "TRANG THAI", "VI TRI" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { MASACH_WIDTH, TRANGTHAISACH_WIDTH, VITRI_WIDTH }, row, BORDER_COLOR);
}
// tinh kich co cua dslk
int LIST_SACH::Size()
{
	int count = 0;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		count++;
	}
	return count;
}
std::string LIST_SACH::PrintAll(MYPOINT location, Menu_Mode mode)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine = 0;
	// dua vao vector de sort
	std::vector<SACH> listSach;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		listSach.push_back(p->data);
		totalLine++;
	}
	// sap xep theo ten sach
	//SortByTenSach(listISBN);
	std::vector<std::string> datas;
	std::vector<int> rows;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelSach(location, totalLine);
		location.y += 3;
		backUpLocation = location;
		// print data
		for (int i = 0; i < totalLine; i++)
		{
			listSach[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
			// neu la dong dau tien thi hight light len
			if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
			{
				listSach[i].Print(location, hlBGColor, hlTextColor);
			}
			// luu lai vi tri dong
			rows.push_back(location.y++);
			datas.push_back(listSach[i].ToString());
		}
	}
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
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[--currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = totalLine - 1;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < totalLine - 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[++currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				return listSach[currentLine].maSach;
			}
			else if (inputKey == Key::ESC)
			{
				return "ESC";
			}
		} while (!_kbhit());
	}
	return listSach[currentLine].maSach;
}
void LIST_SACH::Deconstructor()
{
	while (this->pHead->pNext != NULL && this->pHead != NULL)
	{
		NODE_SACH* old = this->pHead;
		this->pHead = this->pHead->pNext;
		delete old;
	}
	this->pHead = this->pTail = NULL;
}
// constructor Init ds moi
LIST_SACH::LIST_SACH()
{
	this->pHead = NULL;
	this->pTail = NULL;
}
// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
bool LIST_SACH::ReadFromFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		auto lstSachVector = fileHandler.GetTokens();
		int size = lstSachVector.size();
		SACH* dauSach = new SACH[size];
		for (int i = 0; i < size; i++)
		{
			dauSach[i] = ParseVectorString(lstSachVector[i]);
			auto nodeSach = new NODE_SACH(dauSach[i]);
			AddTail(*nodeSach);
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
// Thuat toan tu sinh ma sach
std::string LIST_SACH::AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1])
{
	std::string maSach = isbn;
	maSach += "_";
	// kiem tra ds sach rong
	if (this->pHead == NULL)
	{
		maSach += "0001";
	}
	else
	{
		std::string oldMax = Split(this->pTail->data.maSach, "_")[1];
		int newNum = std::stoi(oldMax) + 1;
		MergeWordWithNumber(maSach, newNum, MASACH_MAXSIZE);
	}
	return maSach;
}
// Them vao cuoi ds sach
void LIST_SACH::AddTail(NODE_SACH& node)
{
	if (this->pHead == NULL)
	{
		this->pHead = this->pTail = &node;
	}
	else
	{
		this->pTail->pNext = &node;
		this->pTail = &node;
	}
}
#pragma endregion