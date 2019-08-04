#include "Sach.h"

#pragma region -------------------------------------------SACH

/// <summary>
	/// Lấy ToString của đầu sách và in ra màn hình
	/// </summary>
	/// <param name="location">Vị trí in</param>
	/// <param name="backColor">Màu nền</param>
	/// <param name="textColor">Màu chữ</param>
	/// <returns>void</returns>
void SACH::Print(MYPOINT location, Color bgSelectColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(bgSelectColor);
	cout << SACH::ToString();
}

/// <summary>
/// In ra SACH dưới dạng list bang cach chen | giua cac field
/// </summary>
/// <returns>SACH as string in List</returns>
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

/// <summary>
/// Chuyển obj SACH thành line string để lưu vơ file text
/// </summary>
/// <returns>SACH as string in File</returns>
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

/// <summary>
/// Chuyen con tro Data string obj Sach
/// </summary>
/// <param name="data">Data SACH can chuyen</param>
/// <returns>SACH</returns>
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

/// <summary>
/// Chuyen con tro Data string obj Sach cho file
/// </summary>
/// <param name="data">Data SACH can chuyen</param>
/// <returns>SACH</returns>
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

/// <summary>
/// Hien form nhap SACH
/// </summary>
/// <param name="rect">kích thước hình chữ nhật dựa trên tọa độ x, y và width height</param>
/// <param name="maSach">Mã sách truyền vào</param>
/// <returns>SACH</returns>
SACH SACH::Input(RECTANGLE rect, string maSach)
{
	string title = "NHAP THONG TIN SACH";
	string labels[] = { "Ma sach", "Trang thai:", "Vi tri:" };
	CONDITION conditions[] = { {All, 6, 6, Default}, {Enum, 1, 2, Default}, {Mix, VITRI_MAXSIZE, VITRI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, title, 3);
	string guilds[] = { "MA SACH LA TU DONG", "0: CHO MUON DUOC\n1: DA THANH LY", "BAO GOM CHU VA SO" };
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

/// <summary>
/// Hien form sua sach SACH
/// </summary>
/// <param name="rect">kích thước hình chữ nhật dựa trên tọa độ x, y và width height</param>
/// <returns>SACH</returns>
SACH SACH::InputFix(RECTANGLE rect)
{
	string title = "CAP NHAT THONG TIN SACH";
	string labels[] = { "Ma sach", "Trang thai:", "Vi tri:" };
	CONDITION conditions[] = { {All, 6, 6, Default}, {Enum, 1, 2, Default}, {Mix, VITRI_MAXSIZE, VITRI_MAXSIZE} };

	auto form = FORMINPUT(labels, conditions, rect, title, 3);
	string datas[3] = { this->maSach, to_string(this->trangThai), this->viTri };
	form.ParseData(datas);
	form.currentLine = 2;
	string guilds[] = { "MA SACH LA TU DONG", "0: CHO MUON DUOC\n1: DA THANH LY", "BAO GOM CHU VA SO" };
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

/// <summary>
/// Kiem tra SACH co xoa duoc khong 
/// </summary>
/// <returns>bool</returns>
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

/// <summary>
/// Kiem tra LIST SACH co rong khong
/// </summary>
/// <returns>bool</returns>
bool LIST_SACH::IsEmpty()
{
	return this->pHead == NULL;
}

/// <summary>
/// Duyet lay kich co cua ds Sach
/// </summary>
/// <returns>int</returns>
int LIST_SACH::Size()
{
	int count = 0;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		count++;
	}
	return count;
}

/// <summary>
/// Dung ham Draw ve khung va Menu
/// </summary>
/// <returns>void</returns>
void PrintLabelSach(MYPOINT location, int row)
{
	string labels[] = { "MA SACH", "TRANG THAI", "VI TRI" };
	auto lstBorder = LISTBORDERTEXT(labels, 3);
	lstBorder.Draw(location, { MASACH_WIDTH, TRANGTHAISACH_WIDTH, VITRI_WIDTH }, row, BORDER_COLOR);
}

/// <summary>
/// In string tại vị trí truyền vào
/// </summary>
/// <param name="data">string cần in</param>
/// <param name="location">Location</param>
/// <returns>void</returns>
void PrintStringDMS(string data, MYPOINT location)
{
	GoToXY(location.x, location.y);
	cout << data;
}

/// <summary>
/// In danh sách SACH của toàn bộ LIST SACH
/// </summary>
/// <param name="location">Location</param>
/// <param name="mode"> Lua chon giua cac che do hien thi</param>
/// <returns>Phím người dùng ấn as string</returns>
string LIST_SACH::PrintAll(MYPOINT location, int& showPage, Menu_Mode mode)
{
	// Create Empty Line Danh mục sách
	string emptyStringDMS = "";
	{
		emptyStringDMS = emptyStringDMS + char(179) + string(MASACH_WIDTH, ' ');
		emptyStringDMS = emptyStringDMS + char(179) + string(TRANGTHAISACH_WIDTH, ' ');
		emptyStringDMS = emptyStringDMS + char(179) + string(VITRI_WIDTH, ' ');
		emptyStringDMS = emptyStringDMS + char(179);
	}

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLines = 0;
	int totalPages = 0;
	int currentPage = 0;
	string* listSach = NULL;

	// Chuyển List độc giả về string array
	for (auto p = this->pHead; p != NULL; p = p->pNext) PushBack(listSach, p->data.ToString(), totalLines);
	totalPages = totalLines / (int)MAX_ROW_PER_PAGE + (totalLines % (int)MAX_ROW_PER_PAGE == 0 ? 0 : 1);

	// Đưa về trang cuối nếu showPage >= totalPages
	if (currentPage >= totalPages)
	{
		showPage = totalPages - 1;
		return "";
	}

	// Kiểm tra size
	if (totalLines == 0) return "";

	string** dms_AsString = new string * [totalPages];;
	int* rowsOfPage = NULL;

	// Tính số line của từng page cần cấp phát cho ds 2 chiều
	if (mode == Both)
	{
		int countTemp = 0;
		int soDongConDu = totalLines % MAX_ROW_PER_PAGE;
		for (int i = 0; i < totalPages - 1; i++)
		{
			dms_AsString[i] = new string[MAX_ROW_PER_PAGE];
			PushBack(rowsOfPage, (int)MAX_ROW_PER_PAGE, countTemp);
		}
		dms_AsString[totalPages - 1] = new string[soDongConDu == 0 ? (int)MAX_ROW_PER_PAGE : soDongConDu];
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
				PrintStringDMS(listSach[i], { location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) });

				// HL dòng đầu tiên nếu có ở chế độ Bắt phím
				if (WhereY() == location.y && mode == Menu_Mode::Both)
				{
					GoToXY(location.x, location.y + (int)(i % MAX_ROW_PER_PAGE));
					HightLight(listSach[i], hlBGColor, hlTextColor);
					NormalColor();
				}
			}

			// Lưu lại vị trí dòng và lấy toString
			if (mode == Both)
			{
				int line = i % MAX_ROW_PER_PAGE;
				currentPage = i / MAX_ROW_PER_PAGE;
				dms_AsString[currentPage][line] = (listSach[i]);
			}
		}

		// Xóa Line dư của trang trước nếu là trang cuối
		if (showPage == totalPages - 1 && totalLines % MAX_ROW_PER_PAGE != 0 && showPage != 0)
		{
			NormalColor();
			for (int i = totalLines % MAX_ROW_PER_PAGE; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, location.y + i);
				cout << emptyStringDMS;
			}
		}

		if (mode == Show_Only)
		{
			delete[] dms_AsString;
		}
		delete[] listSach;
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
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP)
				{
					if (currentLine > 0)
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + --currentLine);
						HightLight(dms_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = (rowsOfPage[currentPage]) - 1;
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < (rowsOfPage[currentPage]) - 1)
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + ++currentLine);
						HightLight(dms_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, location.y + currentLine);
						HightLight(dms_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				string deli = ""; deli += char(179);
				string* tokens = Split(dms_AsString[currentPage][currentLine], deli);
				tokens[1] = Trim(tokens[1]);
				string result = tokens[1];
				delete[] tokens;
				delete[] dms_AsString;
				delete[] rowsOfPage;
				showPage = currentPage;
				return result;
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
						GoToXY(location.x, location.y + i);
						cout << dms_AsString[currentPage][i];
					}
					else
					{
						GoToXY(location.x, location.y + i);
						cout << emptyStringDMS;
					}
				}
				GoToXY(location.x, location.y);
				HightLight(listSach[MAX_ROW_PER_PAGE * currentPage], hlBGColor, hlTextColor);
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
					cout << dms_AsString[currentPage][i];
				}
				GoToXY(location.x, location.y);
				HightLight(listSach[MAX_ROW_PER_PAGE * currentPage], hlBGColor, hlTextColor);
				NormalColor();
			}
			else if (inputKey == Key::ESC)
			{
				showPage = currentPage;
				GoToXY(location.x, location.y + currentLine);
				HightLight(dms_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				delete[] dms_AsString;
				delete[] rowsOfPage;
				return "ESC";
			}
		} while (!_kbhit());
	}

	return "";
}

/// <summary>
/// In ra man hinh SACH cho muon duoc
/// </summary>
/// <param name="location">Location</param>
/// <param name="mode"> Lua chon giua cac che do hien thi </param>
/// <returns>Phím người dùng ấn as string</returns>
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

/// <summary>
/// Delete SACH
/// </summary>
/// <returns>void</returns>
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

/// <summary>
/// Constructor Init ds moi
/// </summary>
LIST_SACH::LIST_SACH()
{
	this->pHead = NULL;
	this->pTail = NULL;
}

/// <summary>
/// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
/// </summary>
/// <param name="path"> Duong dan file </param>
/// <returns>bool</returns>
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

/// <summary>
/// Doc obj SACH tu file
/// </summary>
/// <param name="path"> Duong dan file </param>
/// <returns>bool</returns>
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

/// <summary>
/// Thuat toan tu sinh ma sach
/// </summary>
/// <param name="isbn"> Ma ISBN dua tren ma dang co + them  </param>
/// <returns>string</returns>
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

/// <summary>
/// Them vao cuoi ds sach
/// </summary>
/// <param name="node"> Node SACH chua </param>
/// <returns>void</returns>
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

/// <summary>
/// Tim sach theo Ma SACH
/// </summary>
/// <param name="maSach"> Ma SACH can tim </param>
/// <returns>NODE_SACH*</returns>
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

/// <summary>
/// Xoa Node dau tien trong dslk
/// </summary>
/// <returns>bool</returns>
bool LIST_SACH::DeleteFirst()
{
	if (this->IsEmpty()) return false;
	NODE_SACH* pNode;
	pNode = this->pHead;
	this->pHead = pNode->pNext;
	delete pNode;
	return true;
}

/// <summary>
/// Xoa Node ngay sau 1 Node
/// </summary>
/// <params name="beforeNode">Node phía trước node cần xóa</params>
/// <returns>bool</returns>
bool LIST_SACH::DeleteAfter(NODE_SACH* beforeNode)
{
	if (beforeNode == NULL || beforeNode->pNext == NULL)
	{
		return false;
	}
	NODE_SACH* deleteNode;
	deleteNode = beforeNode->pNext;
	if (deleteNode == this->pTail)
	{
		beforeNode->pNext = NULL;
		this->pTail = beforeNode;
	}
	else
	{
		beforeNode->pNext = deleteNode->pNext;
	}
	delete deleteNode;

	return true;
}

/// <summary>
/// Xoa 1 sach dua vao Ma SACH
/// </summary>
/// <returns>bool</returns>
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

/// <summary>
/// Kiem tra LIST_SACH co xoa duoc hay khong
/// </summary>
/// <returns>bool</returns>
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

/// <summary>
/// Kiem tra SACH cho muon duoc
/// </summary>
/// <returns>bool</returns>
bool LIST_SACH::IsChoMuonDuoc()
{
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai == ChoMuonDuoc)
			return true;
	}
	return false;
}

#pragma endregion

/// <summary>
/// Su dung ham Split de loc bo phan duoi Ma SACH de lay Ma DAUSACH
/// </summary>
/// <param name="maSach"> Ma SACH can de lay MADAUSACH</param>
/// <returns>string</returns>
string GetMaDauSach(string maSach)
{
	auto temp = Split(maSach, "_");
	return temp[0];
}