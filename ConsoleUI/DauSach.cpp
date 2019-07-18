 #include "DauSach.h"

#pragma region ----------------------------------------------------DAUSACH
// chuyen vector<string> vo obj DAUSACH
DAUSACH ParseVectorString(std::vector<std::string> data)
{
	DAUSACH dauSach;// = new DAUSACH;
	StringToCharArray(data[0], dauSach.isbn);
	dauSach.tenSach = data[1];
	dauSach.soTrang = std::stoi(data[2]);
	dauSach.tenTacGia = data[3];
	dauSach.namXuatBan = std::stoi(data[4]);
	dauSach.tenTheLoai = data[5];
	FormatWord(dauSach.tenTheLoai);
	return dauSach;
}
// hien form nhap DAUSACH / truyen listDS de kiem tra du lieu co trung khong
DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect)
{
	std::vector<std::string> labels = { "ISBN:","Ten sach:","So trang:","Tac gia:", "Nam xuat ban:","The loai:" };
	std::string inputTitle = "NHAP THONG TIN DAU SACH";
	std::vector<CONDITION> conditions = { {Number_Only, ISBN_MAXSIZE, ISBN_MAXSIZE}, {All, 1, TENSACH_MAXSIZE},{Number_Only, 1, SOTRANG_MAXKYTU},
													{Name, 1, TENTACGIA_MAXSIZE},{Year, 4, 4},{Word_Only, 1, TENTHELOAI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle);
	std::vector<std::string> guilds = { "DAY SO CO 5 CHU SO", "TAT CA KY TU", "SO TRANG TU [1, 999999]", "CHI NHAP CHU CAI", 
													"PHAI NHO HON NAM HIEN TAI", "CHI NHAP CHU CAI" };
	form.Guilds = guilds;
	DAUSACH dauSach = DAUSACH();
	std::vector<std::string> tempData = form.OutputResults;

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
				std::cout << "ISBN da bi trung";
				form.currentLine = 0;
				tempData = form.OutputResults;
			}
			else
			{
				return dauSach;
			}
		}
		else
		{
			form.ResetOutput();
			break;
		}
	}
	return dauSach;
}
DAUSACH InputFixDauSach(LIST_DAUSACH listDS, RECTANGLE rect, DAUSACH dauSach)
{
	auto tempDSSach = dauSach.dsSach;

	std::vector<std::string> labels = { "ISBN:","Ten sach:","So trang:","Tac gia:", "Nam xuat ban:","The loai:" };
	std::string inputTitle = "NHAP THONG TIN DAU SACH";
	std::vector<CONDITION> conditions = { {Number_Only, ISBN_MAXSIZE, ISBN_MAXSIZE, Default}, {All, 1, TENSACH_MAXSIZE},{Number_Only, 1, SOTRANG_MAXKYTU},
													{Name, 1, TENTACGIA_MAXSIZE},{Year, 4, 4},{Word_Only, 1, TENTHELOAI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle);
	//DAUSACH dauSach = DAUSACH();
	std::vector<std::string> guilds = { "DAY SO CO 5 CHU SO", "TAT CA KY TU", "SO TRANG TU [1, 999999]", "CHI NHAP CHU CAI",
													"PHAI NHO HON NAM HIEN TAI", "CHI NHAP CHU CAI" };
	form.Guilds = guilds;
	form.ParseData({ std::string(dauSach.isbn), dauSach.tenSach, std::to_string(dauSach.soTrang),
				dauSach.tenTacGia, std::to_string(dauSach.namXuatBan), dauSach.tenTheLoai });
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
	std::cout << DAUSACH::ToString();
}
// chen | giua cac field
std::string DAUSACH::ToString()
{
	int temp;
	// ISBN
	std::string result = "";
	result += char(179);
	result += this->isbn;
	//result += " ";
	// TENSACH
	result += char(179);
	result += this->tenSach;
	temp = TENSACH_WIDTH - this->tenSach.size();
	result += std::string(temp, ' ');
	// SOTRANG
	result += char(179);
	result += std::to_string(this->soTrang);
	temp = SOTRANG_WIDTH - NumberLength(this->soTrang);
	result += std::string(temp, ' ');
	// TENTACGIA
	result += char(179);
	result += this->tenTacGia;
	temp = TENTACGIA_WIDTH - this->tenTacGia.size();
	result += std::string(temp, ' ');
	// NAMXUATBAN
	result += char(179);
	result += std::to_string(this->namXuatBan);
	temp = NAMXUATBAN_WIDTH - NumberLength(this->namXuatBan);
	result += std::string(temp, ' ');
	// TENTHELOAI
	result += char(179);
	result += this->tenTheLoai;
	temp = TENTHELOAI_WIDTH - this->tenTheLoai.size();
	result += std::string(temp, ' ');
	result += char(179);
	return result;
}
// chuyen object dau sach thanh string luu file
std::string DAUSACH::ToStringFile()
{
	std::string result = "";
	result = std::string(this->isbn);
	result += '-';
	result += this->tenSach + '-';
	result += std::to_string(this->soTrang) + '-';
	result += this->tenTacGia + '-';
	result += std::to_string(this->namXuatBan) + '-';
	result += this->tenTheLoai;
	//result += '\n';
	return result;
}
#pragma endregion

#pragma region ----------------------------------------------------LIST_DAUSACH
#pragma region Graphics
// selection sort dua vao ten sach
void SortByTenSach(std::vector<DAUSACH>& listDauSach)
{
	DAUSACH min;
	int posMin;
	for (size_t i = 0; i < listDauSach.size() - 1; i++)
	{
		min = listDauSach[i];
		posMin = i;
		for (size_t j = i + 1; j < listDauSach.size(); j++)
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
	std::vector<std::string> labels = { "ISBN", "TEN SACH", "SO TRANG", "TEN TAC GIA", "NXB", "TEN THE LOAI" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { ISBN_WIDTH, TENSACH_WIDTH, SOTRANG_WIDTH, TENTACGIA_WIDTH, NAMXUATBAN_WIDTH, TENTHELOAI_WIDTH },
		row, BORDER_COLOR);
}
// Print list DAUSACH theo the loai (Sap xep theo ten)
std::string LIST_DAUSACH::PrintByTheLoai(MYPOINT location, std::string theLoai)
{
	std::string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + std::string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	/*Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;*/
	// tim ISBN theo the loai
	auto listISBN = GetTheLoai(theLoai);
	// sap xep theo ten sach
	SortByTenSach(listISBN);
	int totalLine = listISBN.size();
	/*std::vector<std::string> datas;
	std::vector<int> rows;*/
	MYPOINT backUpLocation = MYPOINT(0, 0);
	int currentPage = 0;
	int totalPage = 0;
	totalPage = totalLine / MAX_ROW_PER_PAGE;
	if (totalLine % MAX_ROW_PER_PAGE != 0)totalPage++;
	// print label
	PrintLabelDauSach(location, MAX_ROW_PER_PAGE);
	location.y += 3;
	backUpLocation = location;
	// print data
	for (int i = 0; i < totalLine; i++)
	{
		Sleep(10);
		ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
		if (i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			listISBN[i].Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);
		}

		// neu la dong dau tien thi hight light len
		/*if (location.y == backUpLocation.y)
			listISBN[i].Print(location, hlBGColor, hlTextColor);*/
			// luu lai vi tri dong
			/*rows.push_back(location.y++);
			datas.push_back(listISBN[i].ToString());*/
	}

	// bat phim
	//currentLine = 0;
	char inputKey = NULL;
	HidePointer();
	do
	{
		inputKey = _getch();
		if (inputKey == Key::_NULL) inputKey = _getch();
		if (inputKey == -32)
		{
			inputKey = _getch();
			/*if (inputKey == Key::UP)
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
			else */if (inputKey == Key::RIGHT)
			{
				ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				return "RIGHT";
			}
			else if (inputKey == Key::LEFT)
			{
				ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
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
						std::cout << emptyTemplate;
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
		/*if (inputKey == Key::ENTER)
		{
			return listISBN[currentLine].isbn;
		}
		else */if (inputKey == Key::ESC)
		{
			ClearArea(location.x - 3, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH + 6, MAX_ROW_PER_PAGE + 5);
			return "ESC";
		}
	} while (!_kbhit());
	return "";
}
// In tat ca the loai thanh nhieu page
std::string LIST_DAUSACH::PrintAllTheLoai(MYPOINT location)
{
	int currentPage = 0;
	int totalPages = this->dsTheLoai.size();
	SetBGColor(Color::Gray);
	SetTextColor(Color::Bright_White);
	GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
	std::cout << char(62);
	while (true)
	{
		std::string outPut = PrintByTheLoai(location, this->dsTheLoai[currentPage]);
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
					std::cout << char(60);
				}
				currentPage++;
				if (currentPage == totalPages - 1)
				{
					SetBGColor(BG_COLOR);
					SetTextColor(BG_COLOR);
					GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
					std::cout << " ";
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
					std::cout << char(62);
				}
				currentPage--;
				if (currentPage == 0)
				{
					SetBGColor(BG_COLOR);
					SetTextColor(BG_COLOR);
					GoToXY(location.x - 2, location.y + MAX_ROW_PER_PAGE / 2);
					std::cout << " ";
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
std::string LIST_DAUSACH::PrintAll(MYPOINT location, int& page, Menu_Mode mode)
{
	std::string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + std::string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + std::string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int currentPage = page;
	// dua vao vector de sort
	std::vector<DAUSACH> listISBN;
	for (int i = 0; i < this->size; i++)
	{
		listISBN.push_back(*this->nodes[i]);
	}
	// sap xep theo ten sach
	//SortByTenSach(listISBN);
	int totalLine = this->size;
	std::vector<std::vector<std::string>> datas;
	std::vector<std::vector<int>> rows;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// them page
	for (int i = 0; i < totalLine / (int)MAX_ROW_PER_PAGE; i++)
	{
		datas.push_back({});
		rows.push_back({});
	}
	if (totalLine % (int)MAX_ROW_PER_PAGE != 0)
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
		PrintLabelDauSach(location, MAX_ROW_PER_PAGE);
		location.y += 3;
		backUpLocation = location;
		// print data
		for (int i = 0; i < totalLine; i++)
		{
			//Sleep(1);
			ShowPageNumber(page, datas.size(), location.x, location.y + MAX_ROW_PER_PAGE + 1);
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
			rows[currentPage].push_back(i % MAX_ROW_PER_PAGE + location.y);
			datas[currentPage].push_back(this->nodes[i]->ToString());
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
				return listISBN[currentLine + MAX_ROW_PER_PAGE * currentPage].isbn;
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < (int)datas.size() - 1)
			{
				// in next page
				currentPage++;
				ShowPageNumber(currentPage, datas.size(), location.x, location.y + MAX_ROW_PER_PAGE + 1);
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
				listISBN[MAX_ROW_PER_PAGE * currentPage].Print(backUpLocation, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
				// in next page
				currentPage--;
				ShowPageNumber(currentPage, datas.size(), location.x, location.y + MAX_ROW_PER_PAGE + 1);
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(backUpLocation.x, backUpLocation.y + i);
					std::cout << datas[currentPage][i];
				}
				listISBN[MAX_ROW_PER_PAGE * currentPage].Print(backUpLocation, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::TAB)
			{
				GoToXY(location.x, rows[currentPage][currentLine]);
				HightLight(datas[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				page = currentPage;
				return "TAB";
			}
			else if (inputKey == Key::ESC)
			{
				page = currentPage;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "Empty";
}
// CMT
void LIST_DAUSACH::PrintFindBooks(MYPOINT location, std::string tenSach)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	// tim ISBN theo the loai
	auto listISBN = FindBooks(tenSach);
	int totalLine = listISBN.size();
	std::vector<std::string> datas;
	std::vector<int> rows;
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
bool LIST_DAUSACH::IsContainTheLoai(std::string theLoai)
{
	std::string theLoaiAsLower = ToLowerString(theLoai);
	for (int i = 0; i < this->size; i++)
	{
		if (ToLowerString(this->nodes[i]->tenTheLoai) == theLoaiAsLower) return true;
	}
	return false;
}
// Lay dau sach dua vao ten the loai
std::vector<DAUSACH> LIST_DAUSACH::GetTheLoai(std::string tenTheLoai)
{
	std::vector<DAUSACH> result;
	for (int i = 0; i < this->size; i++)
	{
		if (this->nodes[i]->tenTheLoai == tenTheLoai)
		{
			result.push_back(*this->nodes[i]);
		}
	}
	return result;
}
// get dau sach theo isbn
DAUSACH* LIST_DAUSACH::GetDauSach(char isbn[ISBN_MAXSIZE + 1])
{
	for (auto dauSach : this->nodes)
	{		if (strcmp(dauSach->isbn, isbn) == 0)
			return dauSach;
	}
	return NULL;
}
// Doc obj DAUSACH tu file
bool LIST_DAUSACH::ReadFromFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		auto lstDauSachVector = fileHandler.GetTokens();
		int size = lstDauSachVector.size();
		//DAUSACH* dauSach = new DAUSACH[size];
		for (int i = 0; i < size; i++)
		{
			DAUSACH* dauSach = new DAUSACH;
			*dauSach = ParseVectorString(lstDauSachVector[i]);
			Insert(*dauSach, this->size);
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
// Ghi du lieu dau sach ra file text
bool LIST_DAUSACH::WriteToFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		std::vector<std::string> data;
		for (auto i = 0; i < this->size; i++)
		{
			auto temp = this->nodes[i]->ToStringFile();
			if (i < this->size - 1)
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
	if (!IsContainTheLoai(node.tenTheLoai)) dsTheLoai.push_back(node.tenTheLoai);
	nodes[index] = &node;
	size++;
	return true;
}
// tim theo ten sach
std::vector<DAUSACH> LIST_DAUSACH::FindBooks(std::string tenSach)
{
	std::vector<DAUSACH> result;
	if (tenSach != "")
	{
		std::string toLowerName = ToLowerString(tenSach);
		std::vector<std::string> listKey = Split(toLowerName, " ");

		for (int i = 0; i < this->size; i++)
		{
			std::string toLowerTenSach = ToLowerString(this->nodes[i]->tenSach);
			size_t found = toLowerTenSach.find(toLowerName);
			if (found != std::string::npos)
			{
				result.push_back(*this->nodes[i]);
			}
		}
		for (size_t j = 0; j < listKey.size(); j++)
		{
			for (int i = 0; i < this->size; i++)
			{
				std::string toLowerTenSach = ToLowerString(this->nodes[i]->tenSach);
				size_t found = toLowerTenSach.find(listKey[j]);
				if (found != std::string::npos || toLowerTenSach == listKey[j])
				{
					int dem = 0;
					for (size_t k = 0; k < result.size(); k++)
					{
						std::string temp = this->nodes[i]->isbn;
						if (result[k].isbn == temp)
						{
							dem++;
						}
					}
					if (dem == 0)
					{
						result.push_back(*this->nodes[i]);
					}
				}
			}
		}
	}
	return result;
}
// In tat ca Dau sach tim dc ra mh
std::string LIST_DAUSACH::PrintAllSearch(MYPOINT location, std::string tenSach, Menu_Mode mode)
{
	int x = location.x + (int)DAUSACH_TOTAL_WIDTH + 1;
	int y = location.y;

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	// dua vao vector
	std::vector<DAUSACH> listISBN = FindBooks(tenSach);
	int totalLine = listISBN.size();
	std::vector<std::string> datas;
	std::vector<int> rows;
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

			for (int i = 0; i < totalLine; i++)
			{
				listISBN[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
				// neu la dong dau tien thi hight light len
				if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
				{
					listISBN[i].Print(location, hlBGColor, hlTextColor);
				}
				// luu lai vi tri dong
				rows.push_back(location.y++);
				datas.push_back(listISBN[i].ToString());
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

					std::string temp = listISBN[currentLine].dsSach.PrintAll({ location.x + (int)DAUSACH_TOTAL_WIDTH + 1, y }, Menu_Mode::Show_Only);
					//return listISBN[currentLine].isbn;

				}
				else if (inputKey == Key::ESC)
				{
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
	for (size_t i = 0; i < this->dsTheLoai.size(); i++)
	{
		if (this->IsContainTheLoai(this->dsTheLoai[i]) == false)
		{
			this->dsTheLoai.erase(this->dsTheLoai.begin() + i);
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
#pragma endregion