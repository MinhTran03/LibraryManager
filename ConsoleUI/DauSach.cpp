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
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	// tim ISBN theo the loai
	auto listISBN = GetTheLoai(theLoai);
	// sap xep theo ten sach
	SortByTenSach(listISBN);
	int totalLine = listISBN.size();
	std::vector<std::string> datas;
	std::vector<int> rows;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	PrintLabelDauSach(location, totalLine);
	location.y += 3;
	backUpLocation = location;
	// print data
	for (int i = 0; i < totalLine; i++)
	{
		listISBN[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
		// neu la dong dau tien thi hight light len
		if (location.y == backUpLocation.y)
			listISBN[i].Print(location, hlBGColor, hlTextColor);
		// luu lai vi tri dong
		rows.push_back(location.y++);
		datas.push_back(listISBN[i].ToString());
	}

	// bat phim
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
			else if (inputKey == Key::RIGHT)
			{
				ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				return "RIGHT";
			}
			else if (inputKey == Key::LEFT)
			{
				ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
				return "LEFT";
			}
		}
		if (inputKey == Key::ENTER)
		{
			return listISBN[currentLine].isbn;
		}
		else if (inputKey == Key::ESC)
		{
			ClearArea(location.x, backUpLocation.y - 3, DAUSACH_TOTAL_WIDTH, totalLine + 4);
			return "ESC";
		}
	} while (!_kbhit());
	return listISBN[currentLine].isbn;
}
// In tat ca the loai thanh nhieu page
std::string LIST_DAUSACH::PrintAllTheLoai(MYPOINT location)
{
	int currentPage = 0;
	int totalPages = this->dsTheLoai.size();
	while (true)
	{
		std::string outPut = PrintByTheLoai(location, this->dsTheLoai[currentPage]);
		// go to next page
		if (outPut == "RIGHT")
		{
			if (currentPage < totalPages - 1)
			{
				
				currentPage++;
			}
		}
		// go to previous page
		else if (outPut == "LEFT")
		{
			if (currentPage > 0)
			{
				//ClearScreen(BG_COLOR);
				currentPage--;
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
std::string LIST_DAUSACH::PrintAll(MYPOINT location, Menu_Mode mode)
{
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	// dua vao vector de sort
	std::vector<DAUSACH> listISBN;
	for (int i = 0; i < this->size; i++)
	{
		listISBN.push_back(*this->nodes[i]);
	}
	// sap xep theo ten sach
	//SortByTenSach(listISBN);
	int totalLine = this->size;
	std::vector<std::string> datas;
	std::vector<int> rows;
	MYPOINT backUpLocation = MYPOINT(0, 0);

	// print label
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelDauSach(location, 33);
		location.y += 3;
		backUpLocation = location;
		// print data
		for (int i = 0; i < totalLine; i++)
		{
			//Sleep(15);
			listISBN[i].Print(location, BG_COLOR, TEXT_INPUT_COLOR);
			// neu la dong dau tien thi hight light len
			if (location.y == backUpLocation.y && mode == Menu_Mode::Both)
			{
				listISBN[i].Print(location, hlBGColor, hlTextColor);
			}
			// luu lai vi tri dong
			rows.push_back(location.y++);
			datas.push_back(this->nodes[i]->ToString());
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
				return listISBN[currentLine].isbn;
			}
			else if (inputKey == Key::ESC)
			{
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
	{
		if (strcmp(dauSach->isbn, isbn) == 0)
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
	int y = location.y;

	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	// dua vao vector de sort
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