#include "DauSach.h"

#pragma region ----------------------------------------------------TOPSACH

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns>void</returns>
void TOPSACH::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << TOPSACH::info;
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns>void</returns>
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

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns>void</returns>
int RemoveDuplicatesInSortedTopSach(TOPSACH* sortedArr, int sizeOfArr)
{
	// Return, if array is empty
	// or contains a single element
	if (sizeOfArr == 0 || sizeOfArr == 1)
		return sizeOfArr;

	TOPSACH* newArr = new TOPSACH[sizeOfArr];

	// Start traversing elements
	int newSize = 0;
	for (int i = 0; i < sizeOfArr - 1; i++)
	{
		// If current element is not equal
		// to next element then store that
		// current element
		if (sortedArr[i].soSachMuon != sortedArr[i + 1].soSachMuon)
		{
			newArr[newSize++] = sortedArr[i];
		}
	}
	// Store the last element as whether
	// it is unique or repeated, it hasn't
	// stored previously
	newArr[newSize++] = sortedArr[sizeOfArr - 1];

	int result;
	if (newSize > 9)
		result = newArr[9].soSachMuon;
	else
		result = newArr[newSize - 1].soSachMuon;
	delete[] newArr;
	return result;
}

#pragma endregion

#pragma region ----------------------------------------------------DAUSACH

/// <summary>
/// Lấy ToString của đầu sách và in ra màn hình
/// </summary>
/// <param name="location">Vị trí in</param>
/// <param name="backColor">Màu nền</param>
/// <param name="textColor">Màu chữ</param>
/// <returns>void</returns>
void DAUSACH::Print(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DAUSACH::ToString();
}

/// <summary>
/// Lấy ToString của đầu sách cùng số lần mượn và in ra màn hình
/// </summary>
/// <param name="location">Vị trí in</param>
/// <param name="backColor">Màu nền</param>
/// <param name="textColor">Màu chữ</param>
/// <returns>void</returns>
void DAUSACH::PrintMuonTra(MYPOINT location, Color backColor, Color textColor)
{
	GoToXY(location.x, location.y);
	SetTextColor(textColor);
	SetBGColor(backColor);
	cout << DAUSACH::ToStringMuonTra();
}

/// <summary>
/// Chuyển obj DAUSACH thành line string để in dưới dạng List
/// </summary>
/// <returns>DAUSACH as string in List</returns>
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

/// <summary>
/// Chuyển obj DAUSACH và SOLUOTMUON thành line string để in dưới dạng List
/// </summary>
/// <returns>DAUSACH as string in List</returns>
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

/// <summary>
/// Chuyển obj DAUSACH thành line string để lưu vô file text
/// </summary>
/// <returns>DAUSACH as string in File</returns>
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

#pragma region --------------------PRINT

/// <summary>
/// Selection sort danh sách DAUSACH dựa vào tên sách
/// </summary>
/// <param name="listDauSach">List string</param>
/// <param name="size">Kích cỡ của danh sách</param>
/// <returns>void</returns>
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

/// <summary>
/// In labels cho danh sách đầu sách
/// </summary>
/// <param name="location">Location</param>
/// <param name="row">Số đầu sách có trong danh sách</param>
/// <param name="headerText">Tiêu để của LIST đầu sách</param>
/// <returns>void</returns>
void PrintLabelDauSach(MYPOINT location, int row)
{
	string labels[] = { "ISBN", "TEN SACH", "SO TRANG", "TEN TAC GIA", "NXB", "TEN THE LOAI" };
	auto lstBorder = LISTBORDERTEXT(labels, 6);
	lstBorder.Draw(location, { ISBN_WIDTH, TENSACH_WIDTH, SOTRANG_WIDTH, TENTACGIA_WIDTH, NAMXUATBAN_WIDTH, TENTHELOAI_WIDTH },
		row, BORDER_COLOR);
	/*SetTextColor(headerTextColor);
	GoToXY(location.x + DAUSACH_TOTAL_WIDTH / 2 - headerText.size() / 2 + 1, location.y - 1);
	cout << headerText;*/
}

/// <summary>
/// In danh sách DAUSACH của thể loại và sắp xếp theo tên
/// </summary>
/// <param name="location">Location</param>
/// <param name="theLoai">Tên thể loại cần in</param>
/// <returns>Phím người dùng ấn as string</returns>
string LIST_DAUSACH::PrintByTheLoai(MYPOINT location, string theLoai)
{
	// Create Empty Line
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	int totalLine = 0;
	int currentPage = 0;
	int totalPage = 0;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// Lấy tất cả sách thuộc thể loại
	DAUSACH* listISBN = GetDauSachByTheLoai(theLoai, totalLine);

	// Sắp xếp theo tên sách
	SortByTenSach(listISBN, totalLine);

	// Tính tổng số page
	totalPage = totalLine / MAX_ROW_PER_PAGE;
	if (totalLine % MAX_ROW_PER_PAGE != 0)totalPage++;

	location.y += 3;
	backUpLocation = location;

	// In Đầu sách lấy được
	ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < MAX_ROW_PER_PAGE; i++)
	{
		if (i < totalLine && i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			listISBN[i].Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);
		}
		// Xóa line dư của page trước
		else
		{
			GoToXY(location.x, location.y + (int)(i % MAX_ROW_PER_PAGE));
			cout << emptyTemplate;
		}
	}

	// Bắt phím
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
				delete[] listISBN;
				return "RIGHT";
			}
			else if (inputKey == Key::LEFT)
			{
				delete[] listISBN;
				return "LEFT";
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
			{
				currentPage++;
				ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					// In trang không phải cuối cùng
					if (currentPage < totalPage - 1 || (currentPage == totalPage - 1 && totalLine % MAX_ROW_PER_PAGE == 0))
					{
						listISBN[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
						continue;
					}
					// In trang cuối cùng
					if (currentPage == totalPage - 1 && totalLine % MAX_ROW_PER_PAGE != 0
						&& i < totalLine % MAX_ROW_PER_PAGE)
					{
						listISBN[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
					}
					// Xóa line dư của page trước
					else
					{
						GoToXY(backUpLocation.x, backUpLocation.y + i);
						cout << emptyTemplate;
					}
				}
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0)
			{
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

/// <summary>
/// In danh sách DAUSACH của tất cả thể loại chia thánh nhiều trang
/// </summary>
/// <param name="location">Location</param>
/// <returns>Phím người dùng ấn as string</returns>
string LIST_DAUSACH::PrintAllTheLoai(MYPOINT location)
{
	int currentPage = 0;
	int totalPages = this->soTheLoai;

	// In mũi tên qua phải
	SetBGColor(Color::Gray);
	SetTextColor(Color::Bright_White);
	GoToXY(location.x + DAUSACH_TOTAL_WIDTH + 1, location.y + MAX_ROW_PER_PAGE / 2);
	cout << char(62);

	// print label
	PrintLabelDauSach(location, MAX_ROW_PER_PAGE);

	while (true)
	{
		// In Đầu sách theo từng thể loại và bắt phím qua trái phải
		string inputKey = PrintByTheLoai(location, this->dsTheLoai[currentPage]);

		// Qua page bên phải
		if (inputKey == "RIGHT")
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
		// Qua page bên trái
		else if (inputKey == "LEFT")
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
		// Trả về phím được nhấn
		else
		{
			return inputKey;
		}
	}
}

/// <summary>
/// In danh sách DAUSACH
/// </summary>
/// <param name="location">Location</param>
/// <param name="page">Trang muốn hiển thị</param>
/// <param name="mode">
/// 	<para>Show_Only: Chỉ hiện</para>
/// 	<para>Both: Hiện và bắt phím</para>
/// </param>
/// <returns>Phím người dùng ấn as string</returns>
string LIST_DAUSACH::PrintAll(MYPOINT location, int& showPage, Menu_Mode mode)
{
	// Create Empty Line Đầu sách
	string emptyStringDauSach = "";
	{
		emptyStringDauSach = emptyStringDauSach + char(179) + string(ISBN_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179) + string(TENSACH_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179) + string(SOTRANG_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179) + string(TENTACGIA_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179) + string(NAMXUATBAN_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179) + string(TENTHELOAI_WIDTH, ' ');
		emptyStringDauSach = emptyStringDauSach + char(179);
	}
	
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int currentPage = showPage;
	int totalPages = this->size / (int)MAX_ROW_PER_PAGE + (this->size % (int)MAX_ROW_PER_PAGE == 0 ? 0 : 1);

	// Đưa về trang cuối nếu showPage >= totalPages
	if (currentPage >= totalPages)
	{
		showPage = totalPages - 1;
		return "";
	}

	// Kiểm tra size
	if (this->size == 0) return "";

	string** dauSach_AsString = new string * [totalPages];
	int* rowsOfPage = NULL;

	// Tính số line của từng page cần cấp phát cho ds 2 chiều
	if(mode == Both)
	{
		int countTemp = 0;
		int soDongConDu = this->size % MAX_ROW_PER_PAGE;
		for (int i = 0; i < totalPages - 1; i++)
		{
			dauSach_AsString[i] = new string[MAX_ROW_PER_PAGE];
			PushBack(rowsOfPage, (int)(MAX_ROW_PER_PAGE), countTemp);
		}
		dauSach_AsString[totalPages - 1] = new string[soDongConDu == 0 ? (int)MAX_ROW_PER_PAGE : soDongConDu];
		PushBack(rowsOfPage, (soDongConDu == 0 ? (int)MAX_ROW_PER_PAGE : soDongConDu), countTemp);
	}

	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		location.y += 3;

		// In LIST_DAUSACH ra màn hình
		ShowPageNumber(showPage, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
		for (int i = 0; i < this->size; i++)
		{
			if (i >= (int)MAX_ROW_PER_PAGE * showPage && i < (showPage + 1) * (int)MAX_ROW_PER_PAGE)
			{
				this->nodes[i]->Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);

				// HL dòng đầu tiên nếu có ở chế độ Bắt phím
				if (WhereY() == location.y && mode == Menu_Mode::Both)
				{
					this->nodes[i]->Print(location, hlBGColor, hlTextColor);
				}
			}

			// Lưu lại vị trí dòng và lấy toString
			if (mode == Both)
			{
				int line = i % MAX_ROW_PER_PAGE;
				currentPage = i / MAX_ROW_PER_PAGE;
				dauSach_AsString[currentPage][line] = this->nodes[i]->ToString();
			}
		}

		// Xóa Line dư của trang trước nếu là trang cuối
		if (showPage == totalPages - 1 && this->size % MAX_ROW_PER_PAGE != 0 && showPage != 0)
		{
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (int i = this->size % MAX_ROW_PER_PAGE; i < MAX_ROW_PER_PAGE; i++)
			{
				GoToXY(location.x, location.y + i);
				cout << emptyStringDauSach;
			}
		}

		if (mode == Show_Only)
		{
			delete[] dauSach_AsString;
		}
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
						HightLight(dauSach_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + --currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = (rowsOfPage[currentPage]) - 1;
						GoToXY(location.x, location.y + currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (rowsOfPage != NULL && currentLine < (rowsOfPage[currentPage]) - 1)
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, location.y + ++currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, location.y + currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, location.y + currentLine);
						HightLight(dauSach_AsString[currentPage][currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				showPage = currentPage;
				string temp = "";
				if (this->size != 0)
					temp = this->nodes[currentLine + MAX_ROW_PER_PAGE * currentPage]->isbn;
				delete[] dauSach_AsString;
				delete[] rowsOfPage;
				return temp;
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPages - 1 && currentPage < MAX_PAGE_DAUSACH)
			{
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);

				// In next page
				currentPage++;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				for (int i = 0; i < (int)MAX_ROW_PER_PAGE; i++)
				{
					if (rowsOfPage != NULL && i < (rowsOfPage[currentPage]))
					{
						GoToXY(location.x, location.y + i);
						cout << dauSach_AsString[currentPage][i];
					}
					else
					{
						GoToXY(location.x, location.y + i);
						cout << emptyStringDauSach;
					}
				}

				// HL dòng đầu tiên
				this->nodes[MAX_ROW_PER_PAGE * currentPage]->Print(location, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::PAGE_UP && currentPage > 0 && currentPage < MAX_PAGE_DAUSACH)
			{
				currentLine = 0;
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);

				// In previous page
				currentPage--;
				ShowPageNumber(currentPage, totalPages, location.x, location.y + MAX_ROW_PER_PAGE + 1);
				for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
				{
					GoToXY(location.x, location.y + i);
					cout << dauSach_AsString[currentPage][i];
				}

				// HL dòng đầu tiên
				this->nodes[MAX_ROW_PER_PAGE * currentPage]->Print(location, hlBGColor, hlTextColor);
			}
			else if (inputKey == Key::TAB)
			{
				GoToXY(location.x, location.y + currentLine);
				HightLight(dauSach_AsString[currentPage][currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				showPage = currentPage;
				delete[] dauSach_AsString;
				delete[] rowsOfPage;
				return "TAB";
			}
			else if (inputKey == Key::ESC)
			{
				showPage = currentPage;
				delete[] dauSach_AsString;
				delete[] rowsOfPage;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}

// ...
string LIST_DAUSACH::PrintAllSearch(MYPOINT location, string tenSach, Menu_Mode mode)
{
	int pageSach = 0;
	int page = 0;
	int currentPage = 0;
	int totalPages;
	int count = 0;
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int x = location.x + (int)DAUSACH_TOTAL_WIDTH + 1;
	int y = location.y;

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine = 0;
	// dua vao vector
	auto listISBN = FindBooks(tenSach, totalLine);
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
			datas[currentPage][i % MAX_ROW_PER_PAGE] = (listISBN[i].ToString());
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
				else if (inputKey == Key::DOWN && currentPage < MAX_PAGE_DAUSACH)
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
				RECTANGLE rect = { { location.x + (int)DAUSACH_TOTAL_WIDTH + 1, y } , {DMS_TOTAL_WIDTH, 20} };
				ClearArea(rect.location.x, rect.location.y, rect.size.width, rect.size.height);

				string temp = listISBN[currentLine].dsSach.PrintAll({ location.x + (int)DAUSACH_TOTAL_WIDTH + 1, y }, pageSach, Menu_Mode::Show_Only);
			}
			else if (inputKey == Key::PAGE_DOWN && currentPage < totalPages - 1 && currentPage < MAX_PAGE_DAUSACH)
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

#pragma endregion

#pragma region --------------------DOC GHI FILE

/// <summary>
/// Đọc LIST_DAUSACH từ file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu file tồn tại</returns>
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
			*dauSach = ParseVectorStringDS(lstDauSachVector[i], 1);
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

/// <summary>
/// Ghi LIST_DAUSACH ra file text
/// </summary>
/// <param name="path">Đường dẫn tới file</param>
/// <returns>true nếu ghi file thành công</returns>
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

#pragma endregion

/// <summary>
/// Hàm hủy toàn bộ DAUSACH khỏi RAM
/// </summary>
void LIST_DAUSACH::Deconstructor()
{
	for (int i = 0; i < this->size; i++)
	{
		delete this->nodes[i];
		this->nodes[i] = NULL;
	}
}

/// <summary>
/// In danh sách DAUSACH của toàn bộ DAUSACH
/// </summary>
/// <param name="location">Location</param>
/// <returns>true nếu Thể loại đó tồn tại</returns>
bool LIST_DAUSACH::IsContainTheLoai(string theLoai)
{
	string theLoaiAsLower = ToLowerString(theLoai);
	for (int i = 0; i < this->size; i++)
	{
		if (ToLowerString(this->nodes[i]->tenTheLoai) == theLoaiAsLower) return true;
	}
	return false;
}

/// <summary>
/// Lấy danh sách DAUSACH dựa vào Thể Loại
/// </summary>
/// <param name="tenTheLoai">Tên thể loại cần lấy</param>
/// <param name="count">Tham trị đếm số DAUSACH lấy được</param>
/// <returns>Danh sách DAUSACH</returns>
DAUSACH* LIST_DAUSACH::GetDauSachByTheLoai(string tenTheLoai, int& count)
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

/// <summary>
/// Lấy DAUSACH dựa vào ISBN
/// </summary>
/// <param name="isbn">ISBN cần lấy</param>
/// <returns>NULL nếu không có DAUSACH thuộc ISBN</returns>
DAUSACH* LIST_DAUSACH::GetDauSach(char isbn[ISBN_MAXSIZE + 1])
{
	for (DAUSACH* dauSach : this->nodes)
	{
		if (strcmp(dauSach->isbn, isbn) == 0)
			return dauSach;
	}
	return NULL;
}

/// <summary>
/// Kiểm tra LIST_DAUSACH đầy chưa (1000)
/// </summary>
/// <returns>true nếu đầy</returns>
bool LIST_DAUSACH::IsFull()
{
	return this->size == SODAUSACH_MAX;
}

/// <summary>
/// Kiểm tra LIST_DAUSACH rỗng
/// </summary>
/// <returns>true nếu rỗng</returns>
bool LIST_DAUSACH::IsEmpty()
{
	return this->size == 0;
}

/// <summary>
/// Kiểm tra LIST_DAUSACH đã tồn tại ISBN hay chưa
/// </summary>
/// <param name="isbn">ISBN cần kiểm tra</param>
/// <returns>true nếu tồn tại</returns>
bool LIST_DAUSACH::IsContainISBN(char isbn[ISBN_MAXSIZE + 1])
{
	for (int i = 0; i < this->size; i++)
	{
		if (strcmp(this->nodes[i]->isbn, isbn) == 0)
			return true;
	}
	return false;
}

/// <summary>
/// Thêm DAUSACH vào LIST_DAUSACH
/// DAUSACH phải dùng tham biến (&) vì nếu dùng tham trị thì node sẽ mất sau khi ra khỏi hàm
/// </summary>
/// <param name="node">DAUSACH cần thêm</param>
/// <param name="index">Vị trí cần thêm</param>
/// <returns>true nếu Insert thành công</returns>
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
		PushBack(this->dsTheLoai, node.tenTheLoai, this->soTheLoai);
	}
	nodes[index] = &node;
	size++;
	return true;
}

// ...
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

/// <summary>
/// Tìm index của DAUSACH theo ISBN
/// </summary>
/// <param name="isbn">ISBN cần tìm</param>
/// <returns>-1 nếu ISBN không tồn tại</returns>
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

/// <summary>
/// Cập nhật danh sách thể loại khi Thêm, Xóa và Sửa DAUSACH
/// </summary>
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

/// <summary>
/// Xóa DAUSACH dựa vào ISBN
/// </summary>
/// <param name="isbn">ISBN của DAUSACH cần xóa</param>
/// <returns>true nếu xóa thành công</returns>
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

/// <summary>
/// Chuyển list string thành object DAUSACH
/// </summary>
/// <param name="data">List string</param>
/// <param name="mode">Mode = 1: Thêm field SoLuotMuon</param>
/// <returns>DAUSACH</returns>
DAUSACH ParseVectorStringDS(string* data, int mode)
{
	DAUSACH dauSach;
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

/// <summary>
/// Hiện form nhập DAUSACH
/// </summary>
/// <param name="listDS">Kiểm tra ISBN xem có trùng không</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DAUSACH</returns>
DAUSACH InputDauSach(LIST_DAUSACH listDS, RECTANGLE rect)
{
	// Setup Form Input
	string labels[] = { "ISBN:","Ten sach:","So trang:","Tac gia:", "Nam xuat ban:","The loai:" };
	string inputTitle = "NHAP THONG TIN DAU SACH";
	CONDITION conditions[] = { {Number_Only, ISBN_MAXSIZE, ISBN_MAXSIZE}, {All, 1, TENSACH_MAXSIZE},{Number_Only, 1, SOTRANG_MAXKYTU},
													{Name, 1, TENTACGIA_MAXSIZE},{Year, 4, 4},{Word_Only, 1, TENTHELOAI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle, 6);
	string guilds[] = { "DAY SO CO 6 CHU SO", "TAT CA KY TU", "SO TRANG TU [1, 999999]", "CHI NHAP CHU CAI",
													"PHAI NHO HON NAM HIEN TAI", "CHI NHAP CHU CAI" };
	form.Guilds = guilds;

	// Tạo DAUSACH mới
	DAUSACH dauSach = DAUSACH();
	string* tempData = form.OutputResults;

	while (true)
	{
		form.OutputResults = tempData;
		// SAVE DAUSACH
		if (form.Show())
		{
			// Chuyển dữ liệu string người dùng nhập thành obj DAUSACH
			dauSach = ParseVectorStringDS(form.OutputResults);

			// Kiểm tra ISBN có trùng
			if (listDS.IsContainISBN(dauSach.isbn))
			{
				GoToXY(form.cols[0] - 6, form.rows[0] + 1);
				SetTextColor(WARNING_TEXT_COLOR);
				cout << "ISBN da bi trung";
				form.currentLine = 0;
				tempData = form.OutputResults;
			}
			// ISBN không trùng
			else
			{
				delete[] tempData;
				return dauSach;
			}
		}
		// CANCEL DAUSACH
		else
		{
			form.ResetOutput();
			delete[] tempData;
			break;
		}
	}
	return dauSach;
}

/// <summary>
///  Hiện form sửa thông tin DAUSACH
/// </summary>
/// <param name="listDS">Kiểm tra ISBN xem có trùng không</param>
/// <param name="dauSach">DAUSACH cần chỉnh sửa</param>
/// <param name="rect">Khung nhập sách</param>
/// <returns>DAUSACH</returns>
DAUSACH InputFixDauSach(LIST_DAUSACH listDS, RECTANGLE rect, DAUSACH dauSach)
{
	LIST_SACH backupDSSach = dauSach.dsSach;
	int backupSoLuotMuon = dauSach.soLuotMuon;

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
			auto newSach = ParseVectorStringDS(form.OutputResults);
			newSach.dsSach = backupDSSach;
			newSach.soLuotMuon = backupSoLuotMuon;
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

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns>void</returns>
string PrintTopDauSach(LIST_DAUSACH listDS, MYPOINT location)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOLUOTMUON_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int soDauSach = listDS.size;

	TOPSACH* top10 = nullptr;

	// nhap thong tin vao mang.
	int count = 0;
	for (int i = 0; i < soDauSach; i++)
	{
		TOPSACH top = TOPSACH();
		top.soSachMuon = listDS.nodes[i]->soLuotMuon;
		top.info = listDS.nodes[i]->ToStringMuonTra();
		PushBack(top10, top, count);
	}

	if (count != 0)
		SortTop10(top10, 0, count - 1);
	int minOfTop10 = RemoveDuplicatesInSortedTopSach(top10, count);
	int sizeOfTop10 = 0;
	for (int i = 0; i < count; i++)
	{
		if (minOfTop10 <= top10[i].soSachMuon) sizeOfTop10++;
	}

	// Print Label
	string labels[] = { "ISBN", "TEN SACH", "SO TRANG", "TEN TAC GIA", "NXB", "TEN THE LOAI", "SO LAN MUON" };
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, { ISBN_WIDTH, TENSACH_WIDTH, SOTRANG_WIDTH, TENTACGIA_WIDTH, NAMXUATBAN_WIDTH, TENTHELOAI_WIDTH, SOLUOTMUON_WIDTH },
		MAX_ROW_PER_PAGE, BORDER_COLOR);
	location.y += 3;
	int totalLine = sizeOfTop10;
	int currentPage = 0;
	int totalPage = 0;
	totalPage = totalLine / MAX_ROW_PER_PAGE;
	if (totalLine % MAX_ROW_PER_PAGE != 0)totalPage++;
	ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
	for (int i = 0; i < MAX_ROW_PER_PAGE; i++)
	{
		//Sleep(10);
		if (i < totalLine && i >= (int)MAX_ROW_PER_PAGE * currentPage && i < (currentPage + 1) * (int)MAX_ROW_PER_PAGE)
		{
			top10[i].Print({ location.x, location.y + (int)(i % MAX_ROW_PER_PAGE) }, BG_COLOR, TEXT_INPUT_COLOR);
		}
		else
		{
			GoToXY(location.x, location.y + (int)(i % MAX_ROW_PER_PAGE));
			cout << emptyTemplate;
		}
	}

	char inputKey = NULL;
	HidePointer();
	do
	{
		inputKey = _getch();
		if (inputKey == -32) inputKey = _getch();
		if (inputKey == Key::PAGE_DOWN && currentPage < totalPage - 1)
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
					top10[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
					continue;
				}
				// in trang cuoi cung
				if (currentPage == totalPage - 1 && totalLine % MAX_ROW_PER_PAGE != 0
					&& i < totalLine % MAX_ROW_PER_PAGE)
				{
					top10[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
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
			ShowPageNumber(currentPage, totalPage, location.x, location.y + MAX_ROW_PER_PAGE + 1);
			SetBGColor(BG_COLOR);
			SetTextColor(TEXT_INPUT_COLOR);
			for (size_t i = 0; i < MAX_ROW_PER_PAGE; i++)
			{
				top10[i + MAX_ROW_PER_PAGE * currentPage].Print({ location.x, location.y + (int)i }, BG_COLOR, TEXT_INPUT_COLOR);
			}
		}
		if (inputKey == Key::ESC)
		{
			delete[] top10;
			return "ESC";
		}
	} while (!_kbhit());
	return "";
}