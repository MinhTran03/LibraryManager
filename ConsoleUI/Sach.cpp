#include "Sach.h"

#pragma region -------------------------------------------SACH
// in ra node
void SACH::Print(MYPOINT location, Color bgSelectColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(bgSelectColor);
	cout << SACH::ToString();
}
// chen | giua cac field
string SACH::ToString()
{
	int temp;
	// Ma sach
	string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += string(temp, ' ');
	// Trang thai
	result += char(179);
	string str = "";
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
	result += string(temp, ' ');
	// Vi tri
	result += char(179);
	result += this->viTri;
	temp = VITRI_WIDTH - this->viTri.size();
	result += string(temp, ' ');
	result += char(179);
	return result;
}
// chuyen object sach sach thanh string luu file
string SACH::ToStringFile()
{
	string result = "";
	result = string(this->maSach);
	result += '-';
	string str = "";
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
	result += str + '-';
	result += this->viTri;
	return result;
}
//c chuyen vector<string> vo obj Sach
SACH ParseVectorString(string* data)
{
	SACH sach;
	sach.maSach = data[0];
	if (data[1] == "0")
		sach.trangThai = ChoMuonDuoc;
	else if (data[1] == "1")
		sach.trangThai = DaMuon;
	else
		sach.trangThai = DaThanhLy;
	sach.viTri = ToUpperString(data[2]);
	return sach;
}
SACH ParseVectorStringFile(string* data)
{
	SACH sach;
	sach.maSach = data[0];
	if (ToLowerString(data[1]) == "cho muon duoc")
		sach.trangThai = ChoMuonDuoc;
	else if (ToLowerString(data[1]) == "da muon")
		sach.trangThai = DaMuon;
	else
		sach.trangThai = DaThanhLy;
	sach.viTri = data[2];
	return sach;
}
// hien form nhap SACH
SACH SACH::Input(RECTANGLE rect, string maSach)
{
	string title = "NHAP THONG TIN SACH";
	string labels[] = { "Ma sach", "Trang thai:", "Vi tri:" };
	CONDITION conditions[] = { {All, 6, 6, Default}, {Enum, 1, 3, Default}, {Mix, VITRI_MAXSIZE, VITRI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, title, 3);
	string guilds[] = { "MA SACH LA TU DONG", "0: CHO MUON DUOC\n1: DA MUON\n2: DA THANH LY", "BAO GOM CHU VA SO" };
	form.Guilds = guilds;
	string datas[3] = { maSach, "0", "" };
	form.ParseData(datas);
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
SACH SACH::InputFix(RECTANGLE rect)
{
	string title = "CAP NHAT THONG TIN SACH";
	string labels[] = { "Ma sach", "Trang thai:", "Vi tri:" };
	CONDITION conditions[] = { {All, 6, 6, Default}, {Enum, 1, 3}, {Mix, VITRI_MAXSIZE, VITRI_MAXSIZE} };

	auto form = FORMINPUT(labels, conditions, rect, title, 3);
	string datas[3] = { this->maSach, to_string(this->trangThai), this->viTri };
	form.ParseData(datas);
	form.currentLine = 1;
	string guilds[] = { "MA SACH LA TU DONG", "0: CHO MUON DUOC\n1: DA MUON\n2: DA THANH LY", "BAO GOM CHU VA SO" };
	form.Guilds = guilds;
	if (form.Show(2))
	{
		return ParseVectorString(form.OutputResults);
	}
	else
	{
		//form.ResetOutput();
	}
	return *this;
}
// kiem tra sach co xoa duoc khong
bool SACH::CanDelete()
{
	return this->trangThai != DaMuon;
}
#pragma endregion

#pragma region -------------------------------------------NODE_SACH
// Khoi tao 1 node sach moi
NODE_SACH::NODE_SACH(SACH& data)
{
	this->data = data;
	this->pNext = NULL;
}
#pragma endregion

#pragma region -------------------------------------------LIST_SACH
bool LIST_SACH::IsEmpty()
{
	return this->pHead == NULL;
}
// row la so dong data
void PrintLabelSach(MYPOINT location, int row)
{
	string labels[] = { "MA SACH", "TRANG THAI", "VI TRI" };
	auto lstBorder = LISTBORDERTEXT(labels, 3);
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
// In ra mh
string LIST_SACH::PrintAll(MYPOINT location, Menu_Mode mode)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine = 0;
	// dua vao vector de sort
	SACH* listSach = NULL;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		PushBack(listSach, p->data, totalLine);
	}
	// sap xep theo ten sach
	//SortByTenSach(listISBN);
	string* datas = NULL;
	int* rows = NULL;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelSach(location, totalLine);
		location.y += 3;
		backUpLocation = location;
		// print data
		int c1 = 0;
		int c2 = 0;
		for (int i = 0; i < totalLine; i++)
		{
			listSach[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
			// neu la dong dau tien thi hight light len
			if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
			{
				listSach[i].Print(location, hlBGColor, hlTextColor);
			}
			// luu lai vi tri dong
			PushBack(rows, location.y++, c2);
			PushBack(datas, listSach[i].ToString(), c1);
		}
	}
	if (mode == Show_Only)
	{
		delete[] listSach;
		delete[] rows;
		delete[] datas;
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
				auto temp = listSach[currentLine].maSach;
				delete[] listSach;
				delete[] rows;
				delete[] datas;
				return temp;
			}
			else if (inputKey == Key::ESC)
			{
				delete[] rows;
				delete[] datas;
				delete[] listSach;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "NULL";
}
// In ra mh
string LIST_SACH::PrintAllChoMuonDuoc(MYPOINT location, Menu_Mode mode)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine = 0;
	// dua vao vector de sort
	SACH* listSach = NULL;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai == ChoMuonDuoc)
		{
			PushBack(listSach, p->data, totalLine);
		}
	}
	// sap xep theo ten sach
	//SortByTenSach(listISBN);
	string* datas = NULL;
	int* rows = NULL;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelSach(location, totalLine);
		location.y += 3;
		backUpLocation = location;
		// print data
		int c1 = 0;
		int c2 = 0;
		for (int i = 0; i < totalLine; i++)
		{
			listSach[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
			// neu la dong dau tien thi hight light len
			if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
			{
				listSach[i].Print(location, hlBGColor, hlTextColor);
			}
			// luu lai vi tri dong
			PushBack(rows, location.y++, c2);
			PushBack(datas, listSach[i].ToString(), c1);
		}
	}
	if (mode == Show_Only)
	{
		delete[] listSach;
		delete[] rows;
		delete[] datas;
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
				auto temp = listSach[currentLine].maSach;
				delete[] listSach;
				delete[] rows;
				delete[] datas;
				return temp;
			}
			else if (inputKey == Key::ESC)
			{
				delete[] listSach;
				delete[] rows;
				delete[] datas;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "NULL";
}
// Delete sach
void LIST_SACH::Deconstructor()
{
	while (this->pHead != NULL && this->pHead->pNext != NULL)
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
bool LIST_SACH::ReadFromFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = 0;
		auto lstSachVector = fileHandler.GetTokens(size);
		SACH* dauSach = new SACH[size];
		for (int i = 0; i < size; i++)
		{
			dauSach[i] = ParseVectorStringFile(lstSachVector[i]);
			auto nodeSach = new NODE_SACH(dauSach[i]);
			AddTail(*nodeSach);
		}
		delete[] lstSachVector;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}
// Doc obj SACH tu file
bool LIST_SACH::WriteToFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int c = 0;
		string* data = NULL;
		for (auto p = this->pHead; p != NULL; p = p->pNext)
		{
			auto temp = p->data.ToStringFile();
			if (p != this->pTail)
				temp += '\n';
			//data.push_back(temp);
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
// Thuat toan tu sinh ma sach
string LIST_SACH::AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1])
{
	string maSach = isbn;
	maSach += "_";
	// kiem tra ds sach rong
	if (this->pHead == NULL)
	{
		maSach += "0001";
	}
	else
	{
		string oldMax = Split(this->pTail->data.maSach, "_")[1];
		int newNum = stoi(oldMax) + 1;
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
// Tim sach theo ma
NODE_SACH* LIST_SACH::Search(string maSach)
{
	for (auto node = this->pHead; node != NULL; node = node->pNext)
	{
		if (node->data.maSach == maSach)
		{
			return node;
		}
	}
	return NULL;
}
// Xoa ptu dau tien trong dslk
bool LIST_SACH::DeleteFirst()
{
	if (this->IsEmpty()) return false;
	NODE_SACH* pNode;
	pNode = this->pHead;
	this->pHead = pNode->pNext;
	delete pNode;
	return true;
}
// Xoa node sau 1 node p
bool LIST_SACH::DeleteAfter(NODE_SACH* beforeNode)
{
	NODE_SACH* deleteNode;
	if (beforeNode == NULL || beforeNode->pNext == NULL)
	{
		return false;
	}

	deleteNode = beforeNode->pNext;
	beforeNode->pNext = deleteNode->pNext;
	delete deleteNode;

	return true;
}
// Delete sach dua vao ma sach
bool LIST_SACH::Delete(string maSach)
{
	if (this->IsEmpty())
	{
		return false;
	}
	else
	{
		NODE_SACH* p;
		NODE_SACH* q;
		p = this->Search(maSach);
		if (p == NULL)
		{
			return false;
		}
		else
		{
			if (p == this->pHead)
			{
				this->DeleteFirst();
			}
			else
			{
				q = this->pHead;
				while (q->pNext != p)
				{
					q = q->pNext;
				}
				this->DeleteAfter(q);
			}
		}
	}
	return true;
}
// Kiem tra LIST_SACH co xoa duoc hay khong
bool LIST_SACH::CanDelete()
{
	for (auto node = this->pHead; node != NULL; node = node->pNext)
	{
		if (node->data.CanDelete() == false)
		{
			return false;
		}
	}
	return true;
}
std::string GetMaDauSach(std::string maSach)
{
	auto temp = Split(maSach, "_");
	return temp[0];
}
#pragma endregion