#include "DauSach.h"

#pragma region ----------------------------------------------------TOPSACH
void TOPSACH::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << TOPSACH::info;
}

#pragma region ----------------------------------------------------DAUSACH
// chuyen vector<string> vo obj DAUSACH
DAUSACH ParseVectorString(string* data, int mode = 0)
{
	DAUSACH dauSach;// = new DAUSACH;
	StringToCharArray(data[0], dauSach.isbn);
	dauSach.tenSach = data[1];
	FormatWord(dauSach.tenSach);
	dauSach.soTrang = stoi(data[2]);
	dauSach.tenTacGia = data[3];
	FormatName(dauSach.tenTacGia);
	dauSach.namXuatBan = stoi(data[4]);
	dauSach.tenTheLoai = data[5];
	FormatWord(dauSach.tenTheLoai);
	if (mode == 1)
		dauSach.soLuotMuon = stoi(data[6]);
	return dauSach;
}
// hien form nhap DAUSACH / truyen listDS de kiem tra du lieu co trung khong
DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect)
{
	string labels[] = { "ISBN:","Ten sach:","So trang:","Tac gia:", "Nam xuat ban:","The loai:" };
	string inputTitle = "NHAP THONG TIN DAU SACH";
	CONDITION conditions[] = { {Number_Only, ISBN_MAXSIZE, ISBN_MAXSIZE}, {All, 1, TENSACH_MAXSIZE},{Number_Only, 1, SOTRANG_MAXKYTU},
													{Name, 1, TENTACGIA_MAXSIZE},{Year, 4, 4},{Word_Only, 1, TENTHELOAI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 6);
	string guilds[] = { "DAY SO CO 6 CHU SO", "TAT CA KY TU", "SO TRANG TU [1, 999999]", "CHI NHAP CHU CAI",
													"PHAI NHO HON NAM HIEN TAI", "CHI NHAP CHU CAI" };
	form.Guilds = guilds;
	DAUSACH dauSach = DAUSACH();
	string* tempData = form.OutputResults;

	while (true)
	{
		form.OutputResults = tempData;
		if (form.Show())
		{
			dauSach = ParseVectorString(form.OutputResults);
			if (listDS.IsContainISBN(dauSach.isbn))
			{
				GoToXY(form.cols[0] - 6, form.rows[0] + 1);
				SetTextColor(WARNING_TEXT_COLOR);
				cout << "ISBN da bi trung";
				form.currentLine = 0;
				tempData = form.OutputResults;
			}
			else
			{
				delete[] tempData;
				return dauSach;
			}
		}
		else
		{
			form.ResetOutput();
			delete[] tempData;
			break;
		}
	}
	return dauSach;
}
DAUSACH InputFixDauSach(LIST_DAUSACH listDS, RECTANGLE rect, DAUSACH dauSach)
{
	auto tempDSSach = dauSach.dsSach;

	string labels[] = { "ISBN:","Ten sach:","So trang:","Tac gia:", "Nam xuat ban:","The loai:" };
	string inputTitle = "NHAP THONG TIN DAU SACH";
	CONDITION conditions[] = { {Number_Only, ISBN_MAXSIZE, ISBN_MAXSIZE, Default}, {All, 1, TENSACH_MAXSIZE},{Number_Only, 1, SOTRANG_MAXKYTU},
													{Name, 1, TENTACGIA_MAXSIZE},{Year, 4, 4},{Word_Only, 1, TENTHELOAI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 6);
	//DAUSACH dauSach = DAUSACH();
	string guilds[] = { "DAY SO CO 6 CHU SO", "TAT CA KY TU", "SO TRANG TU [1, 999999]", "CHI NHAP CHU CAI",
													"PHAI NHO HON NAM HIEN TAI", "CHI NHAP CHU CAI" };
	form.Guilds = guilds;
	string datas[] = { string(dauSach.isbn), dauSach.tenSach, to_string(dauSach.soTrang),
				dauSach.tenTacGia, to_string(dauSach.namXuatBan), dauSach.tenTheLoai };
	form.ParseData(datas);
	form.currentLine = 1;
	while (true)
	{
		if (form.Show())
		{
			auto newSach = ParseVectorString(form.OutputResults);
			newSach.dsSach = tempDSSach;
			return newSach;
		}
		else
		{
			form.ResetOutput();
			break;
		}
	}
	return dauSach;
}
// in ra node
void DAUSACH::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DAUSACH::ToString();
}
void DAUSACH::PrintFull(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DAUSACH::ToStringMuonTra();
}
// chen | giua cac field
string DAUSACH::ToString()
{
	int temp;
	// ISBN
	string result = "";
	result += char(179);
	result += this->isbn;
	//result += " ";
	// TENSACH
	result += char(179);
	result += this->tenSach;
	temp = TENSACH_WIDTH - this->tenSach.size();
	result += string(temp, ' ');
	// SOTRANG
	result += char(179);
	result += to_string(this->soTrang);
	temp = SOTRANG_WIDTH - NumberLength(this->soTrang);
	result += string(temp, ' ');
	// TENTACGIA
	result += char(179);
	result += this->tenTacGia;
	temp = TENTACGIA_WIDTH - this->tenTacGia.size();
	result += string(temp, ' ');
	// NAMXUATBAN
	result += char(179);
	result += to_string(this->namXuatBan);
	temp = NAMXUATBAN_WIDTH - NumberLength(this->namXuatBan);
	result += string(temp, ' ');
	// TENTHELOAI
	result += char(179);
	result += this->tenTheLoai;
	temp = TENTHELOAI_WIDTH - this->tenTheLoai.size();
	result += string(temp, ' ');
	result += char(179);
	return result;
}

string DAUSACH::ToStringMuonTra()
{
	int temp;
	// ISBN
	string result = "";
	result += char(179);
	result += this->isbn;
	//result += " ";
	// TENSACH
	result += char(179);
	result += this->tenSach;
	temp = TENSACH_WIDTH - this->tenSach.size();
	result += string(temp, ' ');
	// SOTRANG
	result += char(179);
	result += to_string(this->soTrang);
	temp = SOTRANG_WIDTH - NumberLength(this->soTrang);
	result += string(temp, ' ');
	// TENTACGIA
	result += char(179);
	result += this->tenTacGia;
	temp = TENTACGIA_WIDTH - this->tenTacGia.size();
	result += string(temp, ' ');
	// NAMXUATBAN
	result += char(179);
	result += to_string(this->namXuatBan);
	temp = NAMXUATBAN_WIDTH - NumberLength(this->namXuatBan);
	result += string(temp, ' ');
	// TENTHELOAI
	result += char(179);
	result += this->tenTheLoai;
	temp = TENTHELOAI_WIDTH - this->tenTheLoai.size();
	result += string(temp, ' ');
	// SOLANMUON
	result += char(179);
	result += to_string(this->soLuotMuon);
	temp = SOLUOTMUON_WIDTH - NumberLength(this->soLuotMuon);
	result += string(temp, ' ');
	result += char(179);

	return result;
}
// chuyen object dau sach thanh string luu file
string DAUSACH::ToStringFile()
{
	string result = "";
	result = string(this->isbn);
	result += '-';
	result += this->tenSach + '-';
	result += to_string(this->soTrang) + '-';
	result += this->tenTacGia + '-';
	result += to_string(this->namXuatBan) + '-';
	result += this->tenTheLoai + '-';
	result += to_string(this->soLuotMuon);
	//result += '\n';
	return result;
}
#pragma endregion

#pragma region ----------------------------------------------------LIST_DAUSACH
#pragma region Graphics
// selection sort dua vao ten sach
void SortByTenSach(DAUSACH*& listDauSach, int size)
{
	DAUSACH min;
	int posMin;
	//int size = SizeOfT(listDauSach);
	for (int i = 0; i < size - 1; i++)
	{
		min = listDauSach[i];
		posMin = i;
		for (int j = i + 1; j < size; j++)
		{
			if (listDauSach[j].tenSach.compare(min.tenSach) < 0)
			{
				min = listDauSach[j];
				posMin = j;
			}
		}
		listDauSach[posMin] = listDauSach[i];
		listDauSach[i] = min;
	}
}
// row la so dong data
void PrintLabelDauSach(MYPOINT location, int row)
{
	string labels[] = { "ISBN", "TEN SACH", "SO TRANG", "TEN TAC GIA", "NXB", "TEN THE LOAI" };
	auto lstBorder = LISTBORDERTEXT(labels, 6);
	lstBorder.Draw(location, { ISBN_WIDTH, TENSACH_WIDTH, SOTRANG_WIDTH, TENTACGIA_WIDTH, NAMXUATBAN_WIDTH, TENTHELOAI_WIDTH },
		row, BORDER_COLOR);
}
// Print list DAUSACH theo the loai (Sap xep theo ten)
string LIST_DAUSACH::PrintByTheLoai(MYPOINT location, string theLoai)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	int totalLine = 0;
	// tim ISBN theo the loai
	auto listISBN = GetTheLoai(theLoai, totalLine);
	// sap xep theo ten sach
	SortByTenSach(listISBN, totalLine);
	MYPOINT backUpLocation = MYPOINT(0, 0);
	int currentPage = 0;
	int totalPage = 0;
	totalPage = totalLine / MAX_ROW_PER_PAGE;
	if (totalLine % MAX_ROW_PER_PAGE != 0)totalPage++;
	
	location.y += 3;
	backUpLocation = location;
	// print data
	ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < MAX_ROW_PER_PAGE; i++)
	{
		//Sleep(10);
		if (i < totalLine && i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			listISBN[i].Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);
		}
		else
		{
			GoToXY(location.x, location.y + (int)(i % MAX_ROW_PER_PAGE));
			cout << emptyTemplate;
		}
	}

	// bat phim
	char inputKey = NULL;
	HidePointer();
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL) inputKey = _getch();
		if (inputKey == -32)
		{
			inputKey = _getch();
			if (inputKey == Key::RIGHT)
			{
				//ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				delete[] listISBN;
				return "RIGHT";
			}
			else if (inputKey == Key::LEFT)
			{
				//ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				delete[] listISBN;
				return "LEFT";
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					// in trang not cuoi cung
					if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && totalLine % MAX_ROW_PER_PAGE == 0))
					{
						listISBN[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
						continue;
					}
					// in trang cuoi cung
					if (currentPage == totalPage - 1 && totalLine % MAX_ROW_PER_PAGE != 0
						&& i < totalLine % MAX_ROW_PER_PAGE)
					{
						listISBN[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
					}
					else
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						cout << emptyTemplate;
					}
				}
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
				// in prev page
				currentPage--;
				ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					listISBN[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
				}
			}
		}
		if (inputKey == Key::ESC)
		{
			ClearArea(location.x - 3, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH + 6, MAX_ROW_PER_PAGE + 5);
			delete[] listISBN;
			return "ESC";
		}
	} while (!_kbhit());
	return "";
}
// In tat ca the loai thanh nhieu page
string LIST_DAUSACH::PrintAllTheLoai(MYPOINT location)
{
	int currentPage = 0;
	int totalPages = this->soTheLoai;
	SetBGColor(Color::Gray);
	SetTextColor(Color::Bright_White);
	GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
	cout << char(62);
	// print label
	PrintLabelDauSach(location, MAX_ROW_PER_PAGE);
	while (true)
	{
		string outPut = PrintByTheLoai(location, this->dsTheLoai[currentPage]);
		// go to next page
		if (outPut == "RIGHT")
		{
			if (currentPage < totalPages - 1)
			{
				if (currentPage == 0)
				{
					SetBGColor(Color::Gray);
					SetTextColor(Color::Bright_White);
					GoToXY(location.x - 2, location.y + MAX_ROW_PER_PAGE / 2);
					cout << char(60);
				}
				currentPage++;
				if (currentPage == totalPages - 1)
				{
					SetBGColor(BG_COLOR);
					SetTextColor(BG_COLOR);
					GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
					cout << " ";
				}
			}
		}
		// go to previous page
		else if (outPut == "LEFT")
		{
			if (currentPage > 0)
			{
				if (currentPage == totalPages - 1)
				{
					SetBGColor(Color::Gray);
					SetTextColor(Color::Bright_White);
					GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
					cout << char(62);
				}
				currentPage--;
				if (currentPage == 0)
				{
					SetBGColor(BG_COLOR);
					SetTextColor(BG_COLOR);
					GoToXY(location.x - 2, location.y + MAX_ROW_PER_PAGE / 2);
					cout << " ";
				}
			}
		}
		// ESC hitted
		else if (outPut == "ESC")
		{
			return outPut;
		}
		// enter hitted
		else
		{
			return outPut;
		}
	}
}
// In tat ca dau sach
// DO NOT CHANGE ANYTHINGS IN THIS FUNC. IT'S WORKING
string LIST_DAUSACH::PrintAll(MYPOINT location, int& page, Menu_Mode mode)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int currentPage = page;
	// dua vao vector de sort
	DAUSACH* listISBN = NULL;
	int totalLine = this->size;
	int totalPages = 0;
	int count = 0;
	for (int i = 0; i < this->size; i++)
	{
		PushBack(listISBN, *this->nodes[i], count);
	}
	// sap xep theo ten sach
	string** datas = NULL;
	int** rows = NULL;
	int* rowsOfPage = NULL;
	MYPOINT backUpLocation = MYPOINT(0, 0);
	totalPages = totalLine / (int)MAX_ROW_PER_PAGE + (totalLine % (int)MAX_ROW_PER_PAGE == 0 ? 0 : 1);

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
		count = 0;
		PrintLabelDauSach(location, MAX_ROW_PER_PAGE);
		location.y += 3;
		backUpLocation = location;
		// print data
		int c = 0;
		for (int i = 0; i < totalPages - 1; i++)
		{
			rows[i] = new int[MAX_ROW_PER_PAGE];
			datas[i] = new string[MAX_ROW_PER_PAGE];
			PushBack(rowsOfPage, (int)(MAX_ROW_PER_PAGE), c);
		}
		rows[totalPages - 1] = new int[totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)];
		datas[totalPages - 1] = new string[totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)];
		PushBack(rowsOfPage, (int)(totalLine % MAX_ROW_PER_PAGE == 0 ? MAX_ROW_PER_PAGE : (totalLine % MAX_ROW_PER_PAGE)), c);
		for (int i = 0; i < totalLine; i++)
		{
			//Sleep(1);
			ShowPageNumber(page, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
			if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
			{
				listISBN[i].Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);
				// neu la dong dau tien thi hight light len
				if (WhereY() == backUpLocation.y && mode == Menu_Mode::Both)
				{
					listISBN[i].Print(location, hlBGColor, hlTextColor);
				}
			}
			// luu lai vi tri dong
			currentPage = i / MAX_ROW_PER_PAGE;
			rows[currentPage][i % MAX_ROW_PER_PAGE] = (i % MAX_ROW_PER_PAGE + location.y);
			datas[currentPage][i % MAX_ROW_PER_PAGE] = (this->nodes[i]->ToString());
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
		delete[] listISBN;
		delete[] datas;
		delete[] rows;
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
						//currentLine = rows[currentPage].size() - 1;
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
				page = currentPage;
				string temp = listISBN[currentLine + MAX_ROW_PER_PAGE * currentPage].isbn;
				delete[] listISBN;
				return temp;
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPages - 1)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (int i = 0; i < (int)MAX_ROW_PER_PAGE; i++)
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
				listISBN[MAX_ROW_PER_PAGE * currentPage].Print(backUpLocation, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
				// in next page
				currentPage--;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(backUpLocation.x, backUpLocation.y + i);
					cout << datas[currentPage][i];
				}
				listISBN[MAX_ROW_PER_PAGE * currentPage].Print(backUpLocation, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::TAB)
			{
				GoToXY(location.x, rows[currentPage][currentLine]);
				HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				page = currentPage;
				delete[] listISBN;
				delete[] datas;
				delete[] rows;
				return "TAB";
			}
			else if (inputKey == Key::ESC)
			{
				page = currentPage;
				delete[] listISBN;
				delete[] datas;
				delete[] rows;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "Empty";
}
// ...
void LIST_DAUSACH::PrintFindBooks(MYPOINT location, string tenSach)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int totalLine = 0;
	// tim ISBN theo the loai
	auto listISBN = FindBooks(tenSach, totalLine);

	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	PrintLabelDauSach(location, totalLine);
	location.y += 3;
	backUpLocation = location;
	int found = 0;
	// print data
	for (int i = 0; i < totalLine; i++)
	{
		listISBN[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
		location.y++;
	}
	delete[] listISBN;
}
#pragma endregion

// Huy
void LIST_DAUSACH::Deconstructor()
{
	for (int i = 0; i < this->size; i++)
	{
		delete this->nodes[i];
		this->nodes[i] = NULL;
	}
}
// kiem tra theLoai sach da ton tai hay chua
bool LIST_DAUSACH::IsContainTheLoai(string theLoai)
{
	string theLoaiAsLower = ToLowerString(theLoai);
	for (int i = 0; i < this->size; i++)
	{
		if (ToLowerString(this->nodes[i]->tenTheLoai) == theLoaiAsLower) return true;
	}
	return false;
}
// Lay dau sach dua vao ten the loai
DAUSACH* LIST_DAUSACH::GetTheLoai(string tenTheLoai, int& count)
{
	DAUSACH* result = NULL;
	for (int i = 0; i < this->size; i++)
	{
		if (this->nodes[i]->tenTheLoai == tenTheLoai)
		{
			PushBack(result, *this->nodes[i], count);
		}
	}
	return result;
}
// get dau sach theo isbn
DAUSACH* LIST_DAUSACH::GetDauSach(char isbn[ISBN_MAXSIZE + 1])
{
	for (auto dauSach : this->nodes)
	{
		if (strcmp(dauSach->isbn, isbn) == 0)
			return dauSach;
	}
	return NULL;
}
// Doc obj DAUSACH tu file
bool LIST_DAUSACH::ReadFromFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = 0;
		auto lstDauSachVector = fileHandler.GetTokens(size);
		for (int i = 0; i < size; i++)
		{
			DAUSACH* dauSach = new DAUSACH;
			*dauSach = ParseVectorString(lstDauSachVector[i], 1);
			Insert(*dauSach, this->size);
		}
		delete[] lstDauSachVector;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}
// Ghi du lieu dau sach ra file text
bool LIST_DAUSACH::WriteToFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int c = 0;
		string* data = NULL;
		for (auto i = 0; i < this->size; i++)
		{
			auto temp = this->nodes[i]->ToStringFile();
			if (i < this->size - 1)
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
// Return true if list full (1000)
bool LIST_DAUSACH::IsFull()
{
	return this->size == SODAUSACH_MAX;
}
// Return true if list empty
bool LIST_DAUSACH::IsEmpty()
{
	return this->size == 0;
}
// kiem tra dau sach da ton tai isbn hay chua
bool LIST_DAUSACH::IsContainISBN(char isbn[ISBN_MAXSIZE + 1])
{
	for (int i = 0; i < this->size; i++)
	{
		if (strcmp(this->nodes[i]->isbn, isbn) == 0)
			return true;
	}
	return false;
}
// DAUSACH phai dung tham bien (&) vi neu dung tham tri thi node se mat sau khi ra khoi ham
// Do dac tinh cua tham tri la copy vo node
bool LIST_DAUSACH::Insert(DAUSACH& node, int index)
{
	if (index < 0 || index > SODAUSACH_MAX || IsFull() || IsContainISBN(node.isbn))
	{
		return false;
	}
	for (int pos = size - 1; pos >= index; pos--)
	{
		nodes[pos + 1] = nodes[pos];
	}
	if (!IsContainTheLoai(node.tenTheLoai))
	{
		//dsTheLoai.push_back(node.tenTheLoai);
		PushBack(this->dsTheLoai, node.tenTheLoai, this->soTheLoai);
	}
	nodes[index] = &node;
	size++;
	return true;
}
// tim theo ten sach
DAUSACH* LIST_DAUSACH::FindBooks(string tenSach, int& count)
{
	DAUSACH* result = NULL;
	if (tenSach != "")
	{
		string toLowerName = ToLowerString(tenSach);
		string* listKey = Split(toLowerName, " ");

		for (int i = 0; i < this->size; i++)
		{
			string toLowerTenSach = ToLowerString(this->nodes[i]->tenSach);
			size_t found = toLowerTenSach.find(toLowerName);
			if (found != string::npos)
			{
				PushBack(result, *this->nodes[i], count);
			}
		}
		auto tenSachAsChar = StringToCharArray(tenSach);
		int wordCount = WordCount(tenSachAsChar);
		delete[] tenSachAsChar;
		for (int j = 0; j < wordCount; j++)
		{
			for (int i = 0; i < this->size; i++)
			{
				string toLowerTenSach = ToLowerString(this->nodes[i]->tenSach);
				size_t found = toLowerTenSach.find(listKey[j]);
				if (found != string::npos || toLowerTenSach == listKey[j])
				{
					int dem = 0;
					for (int k = 0; k < count; k++)
					{
						string temp = this->nodes[i]->isbn;
						if (result[k].isbn == temp)
						{
							dem++;
						}
					}
					if (dem == 0)
					{
						PushBack(result, *this->nodes[i], count);
					}
				}
			}
		}
		delete[] listKey;
	}
	return result;
}
// In tat ca Dau sach tim dc ra mh
string LIST_DAUSACH::PrintAllSearch(MYPOINT location, string tenSach, Menu_Mode mode)
{
	int x = location.x + (int)DAUSACH_TOTAL_WIDTH + 1;
	int y = location.y;

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine = 0;
	// dua vao vector
	auto listISBN = FindBooks(tenSach, totalLine);
	string* datas = NULL;
	int* rows = NULL;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	if (tenSach == "")
	{
		PrintLabelDauSach(location, totalLine);
		location.y += 3;
		backUpLocation = location;
	}
	else
	{
		if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
		{
			if (totalLine == 0) return "Empty";

			PrintLabelDauSach(location, totalLine);
			location.y += 3;
			backUpLocation = location;
			// print data
			int c1 = 0;
			int c2 = 0;
			for (int i = 0; i < totalLine; i++)
			{
				listISBN[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
				// neu la dong dau tien thi hight light len
				if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
				{
					listISBN[i].Print(location, hlBGColor, hlTextColor);
				}
				// luu lai vi tri dong
				//rows.push_back(location.y++);
				//datas.push_back(listISBN[i].ToString());
				PushBack(rows, location.y++, c1);
				PushBack(datas, listISBN[i].ToString(), c2);
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
					RECTANGLE rect = { { location.x + (int)DAUSACH_TOTAL_WIDTH + 1, y } , {DMS_TOTAL_WIDTH, 20} };
					ClearArea(rect.location.x, rect.location.y, rect.size.width, rect.size.height);

					string temp = listISBN[currentLine].dsSach.PrintAll({ location.x + (int)DAUSACH_TOTAL_WIDTH + 1, y }, Menu_Mode::Show_Only);
				}
				else if (inputKey == Key::ESC)
				{
					delete[] listISBN;
					delete[] rows;
					delete[] datas;
					return "ESC";
				}
			} while (!_kbhit());
		}
	}
	return "";
}
// tim vi tri cua dau sach theo ISBN
int LIST_DAUSACH::GetLocateDauSach(char isbn[ISBN_MAXSIZE + 1])
{
	for (int i = 0; i < this->size; i++)
	{
		if (strcmp(this->nodes[i]->isbn, isbn) == 0)
		{
			return i;
		}
	}
	return -1;
}
// cap nhat dsTheLoai moi khi xoa 1 dau sach
void LIST_DAUSACH::INotifyDSTheLoai()
{
	int c = this->soTheLoai;
	for (int i = 0; i < c; i++)
	{
		if (this->IsContainTheLoai(this->dsTheLoai[i]) == false)
		{
			//this->dsTheLoai.erase(this->dsTheLoai.begin() + i);
			Erase(this->dsTheLoai, i, c);
			this->soTheLoai--;
			return;
		}
	}
}
// xoa dau sach theo isbn
bool LIST_DAUSACH::DeleteDauSach(char isbn[ISBN_MAXSIZE + 1])
{
	int position = this->GetLocateDauSach(isbn);
	if (position == -1) return false;
	else
	{
		// xoa phan tu cuoi cung => ko can duyet lai vi tri
		if (position == this->size - 1)
		{
			delete this->nodes[position];
			this->size--;
			this->nodes[this->size] = NULL;
		}
		else
		{
			delete this->nodes[position];
			for (int i = position + 1; i <= this->size; i++)
			{
				this->nodes[i - 1] = this->nodes[i];
			}
			this->size--;
			delete this->nodes[this->size];
			this->nodes[this->size] = NULL;
		}
	}
	// cap nhat dsTheLoai
	this->INotifyDSTheLoai();
	return true;
}
// Quick Sort
void SortTop10(TOPSACH* top10, int q, int r)
{
	TOPSACH temp;
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = top10[(q + r) / 2].soSachMuon;

	do
	{  // Phân đoạn dãy con a[q],..., a[r]
		while (top10[i].soSachMuon > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x 
		while (top10[j].soSachMuon < x)
			j--; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j)   // Hoan vi
		{
			temp = top10[i];
			top10[i] = top10[j];
			top10[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (q < j) 	// phần thứ nhất có từ 2 phần tử trở lên
		SortTop10(top10, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		SortTop10(top10, i, r);
}
// Heap Sort
void Heapify(TOPSACH* top10, int r, int n)
{
	int j = 2 * r + 1;	// vi tri nut ben trai
	int x = top10[r].soSachMuon;
	int cont = TRUE;

	while (j <= n - 1 && cont)
	{
		if (j < n - 1)
		{
			if (top10[j].soSachMuon < top10[j + 1].soSachMuon)
			{
				j++;
			}
		}
		if (top10[j].soSachMuon <= x)
		{
			cont = FALSE;
		}
		else
		{
			top10[r].soSachMuon = top10[j].soSachMuon;
			r = j;
			j = 2 * r + 1;
		}
	}
	top10[r].soSachMuon = x;
}

void HeapSort(TOPSACH* top10, int n)
{
	int i;
	TOPSACH	temp;
	//Tao Heap
	for (i = n/2 - 1; i >= 0; i--)
	{
		Heapify(top10, i, n);
	}
	for (i = n - 2; i >= 0; i--)
	{
		temp = top10[0];	// cho ve cuoi Heap
		top10[0] = top10[i + 1];
		top10[i + 1] = temp;
		Heapify(top10, 0, i + 1);	//Dieu chinh laij Heap tai vi tri 0, vi tri 1 2 da la Heap
	}
}

string PrintTopDauSach(LIST_DAUSACH listDS, MYPOINT location)
{
	DAUSACH* temp;
	int soDauSach = listDS.size;

	// Interchange Sort
	//for (int i = 0; i < totalLine - 1; i++)
	//{
	//	for (int j = i + 1; j < totalLine; j++)
	//	{
	//		if (listDS.nodes[i]->soLuotMuon < listDS.nodes[j]->soLuotMuon)
	//		{
	//			// Hoan vi 2 so a[i] va a[j]
	//			temp = listDS.nodes[i];
	//			listDS.nodes[i] = listDS.nodes[j];
	//			listDS.nodes[j] = temp;
	//		}
	//	}
	//}

	TOPSACH* top10 = nullptr;

	// nhap thong tin vao mang.
	int count = 0;
	for (int i = 0; i < soDauSach; i++)
	{
		if (listDS.nodes[i]->soLuotMuon != 0)
		{
			TOPSACH top = TOPSACH();
			top.soSachMuon = listDS.nodes[i]->soLuotMuon;
			top.info = listDS.nodes[i]->ToStringMuonTra();
			PushBack(top10, top, count);
		}
	}

	if(count != 0)
		SortTop10(top10, 0, count - 1);
	//HeapSort(top10, totalLine);

	// Print Label
	string labels[] = { "ISBN", "TEN SACH", "SO TRANG", "TEN TAC GIA", "NXB", "TEN THE LOAI", "SO LAN MUON" };
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, { ISBN_WIDTH, TENSACH_WIDTH, SOTRANG_WIDTH, TENTACGIA_WIDTH, NAMXUATBAN_WIDTH, TENTHELOAI_WIDTH, SOLUOTMUON_WIDTH },
		10, BORDER_COLOR);
	location.y += 3;

	for (int i = 0; i < count; i++)
	{
		top10[i].Print({ location.x, location.y }, BG_COLOR, TEXT_INPUT_COLOR);
		location.y++;
	}

	char inputKey = NULL;
	HidePointer();
	do
	{
		inputKey = _getch();
		if (inputKey == -32) inputKey = _getch();
		if (inputKey == Key::ESC)
		{
			delete[] top10;
			return "ESC";
		}
	} while (!_kbhit());
}
#pragma endregion