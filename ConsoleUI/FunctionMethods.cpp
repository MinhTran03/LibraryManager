#include "FunctionMethods.h"
#include "Displays.h"
#include "FormInfo.h"

static bool isSaving = true;

void ShowLogoText()
{
	HidePointer();
	MaximizeWindow();
	ClearScreen(BG_COLOR, SCREEN_HEIGHT);
	SetTextColor(Color::Light_Blue);

	GoToXY(60, 0 + 1); cout << string(2, char(219)) << char(187) << "     " << string(2, char(219)) << char(187) << string(6, char(219)) << char(187) << " " << string(6, char(219)) << char(187) << "  " << string(5, char(219)) << char(187) << " " << string(6, char(219)) << char(187) << " " << string(2, char(219)) << char(187) << "   " << string(2, char(219)) << char(187) << '\n';
	GoToXY(60, 1 + 1); cout << string(2, char(219)) << char(186) << "     " << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << char(200) << string(2, char(219)) << char(187) << " " << string(2, char(219)) << char(201) << char(188) << '\n';
	GoToXY(60, 2 + 1); cout << string(2, char(219)) << char(186) << "     " << string(2, char(219)) << char(186) << string(6, char(219)) << char(201) << char(188) << string(6, char(219)) << char(201) << char(188) << string(7, char(219)) << char(186) << string(6, char(219)) << char(201) << char(188) << " " << char(200) << string(4, char(219)) << char(201) << char(188) << '\n';
	GoToXY(60, 3 + 1); cout << string(2, char(219)) << char(186) << "     " << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << "  " << char(200) << string(2, char(219)) << char(201) << char(188) << '\n';
	GoToXY(60, 4 + 1); cout << string(7, char(219)) << char(187) << string(2, char(219)) << char(186) << string(6, char(219)) << char(201) << char(188) << string(2, char(219)) << char(186) << "  " << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << "  " << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << "  " << string(2, char(219)) << char(186) << "   " << string(2, char(219)) << char(186) << '\n';
	GoToXY(60, 5 + 1); cout << char(200) << string(6, char(205)) << char(188) << char(200) << char(205) << char(188) << char(200) << string(5, char(205)) << char(188) << " " << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << "   " << char(200) << char(205) << char(188) << '\n';

	GoToXY(40, 7 + 1); cout << string(3, char(219)) << char(187) << "   " << string(3, char(219)) << char(187) << " " << string(5, char(219)) << char(187) << " " << string(3, char(219)) << char(187) << "   " << string(2, char(219)) << char(187) << " " << string(5, char(219)) << char(187) << "  " << string(6, char(219)) << char(187) << " " << string(7, char(219)) << char(187) << string(3, char(219)) << char(187) << "   " << string(3, char(219)) << char(187) << string(7, char(219)) << char(187) << string(3, char(219)) << char(187) << "   " << string(2, char(219)) << char(187) << string(8, char(219)) << char(187) << '\n';
	GoToXY(40, 8 + 1); cout << string(4, char(219)) << char(187) << " " << string(4, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(4, char(219)) << char(187) << "  " << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(187) << string(2, char(219)) << char(201) << string(4, char(205)) << char(188) << " " << string(2, char(219)) << char(201) << string(4, char(205)) << char(188) << string(4, char(219)) << char(187) << " " << string(4, char(219)) << char(186) << string(2, char(219)) << char(201) << string(4, char(205)) << char(188) << string(4, char(219)) << char(187) << "  " << string(2, char(219)) << char(186) << char(200) << string(2, char(205)) << string(2, char(219)) << char(201) << string(2, char(205)) << char(188) << '\n';
	GoToXY(40, 9 + 1); cout << string(2, char(219)) << char(201) << string(4, char(219)) << char(201) << string(2, char(219)) << char(186) << string(7, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(219)) << char(187) << " " << string(2, char(219)) << char(186) << string(7, char(219)) << char(186) << string(2, char(219)) << char(186) << "  " << string(3, char(219)) << char(187) << string(5, char(219)) << char(187) << "  " << string(2, char(219)) << char(201) << string(4, char(219)) << char(201) << string(2, char(219)) << char(186) << string(5, char(219)) << char(187) << "  " << string(2, char(219)) << char(201) << string(2, char(219)) << char(187) << " " << string(2, char(219)) << char(186) << "   " << string(2, char(219)) << char(186) << '\n';
	GoToXY(40, 10 + 1); cout << string(2, char(219)) << char(186) << char(200) << string(2, char(219)) << char(201) << char(188) << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << char(200) << string(2, char(219)) << char(187) << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << "   " << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << char(188) << "  " << string(2, char(219)) << char(186) << char(200) << string(2, char(219)) << char(201) << char(188) << string(2, char(219)) << char(186) << string(2, char(219)) << char(201) << string(2, char(205)) << char(188) << "  " << string(2, char(219)) << char(186) << char(200) << string(2, char(219)) << char(187) << string(2, char(219)) << char(186) << "   " << string(2, char(219)) << char(186) << '\n';
	GoToXY(40, 11 + 1); cout << string(2, char(219)) << char(186) << " " << char(200) << char(205) << char(188) << " " << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << "  " << string(2, char(219)) << char(186) << string(2, char(219)) << char(186) << " " << char(200) << string(4, char(219)) << char(186) << string(2, char(219)) << char(186) << "  " << string(2, char(219)) << char(186) << char(200) << string(6, char(219)) << char(201) << char(188) << string(7, char(219)) << char(187) << string(2, char(219)) << char(186) << " " << char(200) << char(205) << char(188) << " " << string(2, char(219)) << char(186) << string(7, char(219)) << char(187) << string(2, char(219)) << char(186) << " " << char(200) << string(4, char(219)) << char(186) << "   " << string(2, char(219)) << char(186) << '\n';
	GoToXY(40, 12 + 1); cout << char(200) << char(205) << char(188) << "     " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << string(3, char(205)) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << " " << char(200) << string(5, char(205)) << char(188) << " " << char(200) << string(6, char(205)) << char(188) << char(200) << char(205) << char(188) << "     " << char(200) << char(205) << char(188) << char(200) << string(6, char(205)) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << string(3, char(205)) << char(188) << "   " << char(200) << char(205) << char(188) << '\n';
}

void ShowInfoStudent()
{
	MYPOINT location = { 40, 16 };
	MYSIZE size = { 93, 15 };
	auto border = BORDER(location, size);
	border.Draw1Line(TEXT_INPUT_COLOR);
	GoToXY(location.x + 32, location.y + 2);
	cout << "CAU TRUC DU LIEU & GIAI THUAT";
	GoToXY(location.x + 5, location.y + 6);
	cout << "GIANG VIEN HUONG DAN: LUU NGUYEN KY THU";
	GoToXY(location.x + 5, location.y + 8);
	cout << "SINH VIEN THUC HIEN:";
	GoToXY(location.x + 10, location.y + 10);
	cout << "Ho va ten: Vu Dang Khoa";
	GoToXY(location.x + 40, location.y + 10);
	cout << "MSSV: N16DCCN076";
	GoToXY(location.x + 10, location.y + 12);
	cout << "Ho va ten: Tran Cong Minh";
	GoToXY(location.x + 40, location.y + 12);
	cout << "MSSV: N16DCCN095";
}

void ShowMainScreen()
{
	HidePointer();
	ShowLogoText();
	ShowInfoStudent();
	GoToXY(71, 32);
	system("pause");
}

void SavingAnimation(void)
{
	GoToXY(0, 0);
	SetTextColor(TEXT_INPUT_COLOR);
	while (isSaving)
	{
		GoToXY(0, 0);
		cout << "Saving   ";
		Sleep(300);
		GoToXY(0, 0);
		cout << "Saving.  ";
		Sleep(300);
		GoToXY(0, 0);
		cout << "Saving.. ";
		Sleep(300);
		GoToXY(0, 0);
		cout << "Saving...";
		Sleep(300);
	}
	GoToXY(0, 0);
	cout << "Done       ";
}

void SaveAll(LIST_DOCGIA listDG, LIST_DAUSACH listDS)
{
	thread saving(SavingAnimation);

	// luu dau sach
	WriteDauSach(listDS);
	Sleep(400);
	// luu sach
	for (int i = 0; i < listDS.size; i++)
	{
		if (listDS.nodes[i]->dsSach.IsEmpty())
			continue;
		WriteSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}
	Sleep(400);
	// luu doc gia
	WriteDocGia(listDG);
	Sleep(400);
	// luu ma doc gia arr
	WriteMaDGToFile(GetPath() + MADOCGIA_FILE_PATH, listDG);
	Sleep(400);
	// luu muon tra
	DuyetLuuFileMuonTra(listDG, GetPath());
	Sleep(400);

	isSaving = false;
	saving.join();
}

void FormClosing(LIST_DOCGIA listDG, LIST_DAUSACH listDS, bool isSaveFile)
{
	if (isSaveFile)
	{
		SaveAll(listDG, listDS);
	}
	// Huy
	for (int i = 0; i < listDS.size; i++)
	{
		listDS.nodes[i]->dsSach.Deconstructor();
	}
	listDS.Deconstructor();
	FreeMemory(listDG);
}

void ShowFooter()
{
	int y = SCREEN_HEIGHT - FOOTER_HEIGHT + FOOTER_HEIGHT / 2;

	FOOTER_CHILD footer1 = FOOTER_CHILD({ 5, y }, "ENTER", "CHON");
	footer1.Draw(Color::Blue, Color::Light_Blue);

	FOOTER_CHILD footer2 = FOOTER_CHILD({ footer1.location.x + footer1.size + 5, y }, "ESC", "QUAY LAI");
	footer2.Draw(Color::Red, Color::Light_Red);

	FOOTER_CHILD footer3 = FOOTER_CHILD({ footer2.location.x + footer2.size + 5, y }, "PG_UP", "QUA TRANG MOI");
	footer3.Draw(Color::Magenta, Color::Light_Magenta);

	FOOTER_CHILD footer4 = FOOTER_CHILD({ footer3.location.x + footer3.size + 5, y }, "PG_DOWN", "QUAY LAI TRANG CU");
	footer4.Draw(Color::Cyan, Color::Light_Cyan);
}

void SetupConsole()
{
	HidePointer();
	MaximizeWindow();
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);

	ClearScreen(Color::Gray, SCREEN_HEIGHT);
	ClearScreen(BG_COLOR);

	ShowFooter();
}

void NormalColor()
{
	SetTextColor(BG_COLOR);
	SetBGColor(BG_COLOR);
}

void MakeFlickWarning(MYPOINT location, string text)
{
	int x = location.x;
	int y = location.y;
	GoToXY(x, y);
	SetBGColor(BG_COLOR);
	SetTextColor(WARNING_TEXT_COLOR);
	int distance = (text.size() - 29) / 2;
	cout << text;
	GoToXY(x + distance, y + 1);
	cout << "An phim bat ky de tiep tuc...";
	ShowPointer();
	_getch();
	HidePointer();
	ClearLine(y);
	ClearLine(y + 1);
	//ClearArea(location.x, location.y, text.size(), 1);
}

int* SelectionFuntion(int rootLine, int childLine)
{
	MENU menu = MENU({ "QUAN LY DOC GIA", "QUAN LY DAU SACH", "QUAN LY SACH" }, { 0, 3 });
	vector<vector<string>> temp;
	SLIDEMENUS slide = SLIDEMENUS({ {"QUAN LY DOC GIA", "IN DANH SACH DOC GIA", "DANH SACH DOC GIA MUON QUA HAN"},
		{"HIEN THI DAU SACH", "CAP NHAT DAU SACH", "CAP NHAT DANH MUC SACH", "TIM SACH"},
		{"MUON & TRA SACH", "TOP 10 DAU SACH"} }, menu);
	auto selection = slide.Show(rootLine, childLine);
	slide.Clear();
	//slide.Clear();
	/*GoToXY(0, 0);
	cout << menu.labels[selection[0]] << " ==> " << slide.childLabels[selection[0]][selection[1]];*/
	return selection;
}

// Func 0 0
void QuanLiDocGia(LIST_DOCGIA& listDG, MYPOINT location)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MADOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(HODOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENDOCGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(GIOITINH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAIDG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	string selectedMaDocGia;
	int page = 0;
	string tem = PrintAllDGWithHL(listDG, location, page, Show_Only);

	//int maThe;
	auto locationBtn = location;
	locationBtn.x += 20;
	locationBtn.y += 25;
	// Menu button
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	// in Data Doc Gia voi Hightlight
	tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
	while (true)
	{
		int selected = menu.ShowInHorizontal(Menu_Mode::Both);
		if (selected == Key::PAGE_UP && page > 0)
		{
			page--;
			tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
		}
		else if (selected == Key::PAGE_DOWN)
		{
			page++;
			tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
		}
		// Them
		if (selected == 0)
		{
			auto newDocGia = new DOCGIA();
			//Random Ma Doc Gia
			int newMaDG = GetRandomMaDG(listDG);
			// Show Input tao moi Doc Gia
			*newDocGia = InputDocGia(newMaDG, { {location.x + (int)DOCGIA_TOTAL_WIDTH + 2, location.y}, {50, 18} });
			// Xoa newDocGia neu ho de trong
			if (newDocGia->ho == "")
			{
				delete newDocGia;
			}
			else
			{
				// Xoa MaDG vua lay ra khoi mang
				RemoveMaDG(listDG);
				// Them Doc Gia vao ListDG
				Insert(listDG, *newDocGia);
				tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
			}
		}
		// Xoa
		else if (selected == 1)
		{
			while (true)
			{
				// Het doc gia
				if (Size(listDG) == 0)
				{
					tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
					break;
				}
				selectedMaDocGia = PrintAllDGWithHL(listDG, location, page, Menu_Mode::Both);
				//ClearLine(1);
				if (selectedMaDocGia == "ESC")
				{
					break;
				}
				// ng dung an enter de xoa
				else
				{
					// Show dialog button select
					auto confirm = CONFIRMDIALOG({ 45, 7 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();
					// dong y xoa
					if (confirm.result == Yes)
					{

						int MaDG = stoi(selectedMaDocGia);
						// Tim Doc Gia dua tren MaDG
						auto docGiaDelete = Search(listDG, MaDG);
						// DS khong duoc phep xoa neu dang muon Sach
						if (IsDelete(docGiaDelete->data) == false)
						{
							selectedMaDocGia = PrintAllDGWithHL(listDG, location, page, Menu_Mode::Show_Only);
							MakeFlickWarning({ locationBtn.x - 5, 0 }, "DOC GIA DANG MUON SACH. KHONG DUOC PHEP XOA");
						}
						else
						{
							// Xoa Node
							DeleteNode(listDG, docGiaDelete->data);
							int temp = 0;
							int size = Size(listDG);
							if (size % MAX_ROW_PER_PAGE != 0) temp = 1;
							else if (size % MAX_ROW_PER_PAGE == 0 && page == size / MAX_ROW_PER_PAGE)
							{
								page--;
							}
							if (page == size / MAX_ROW_PER_PAGE + temp - 1)
							{
								SetBGColor(BG_COLOR);
								SetTextColor(TEXT_INPUT_COLOR);
								GoToXY(location.x, size % MAX_ROW_PER_PAGE + location.y + 3);
								cout << emptyTemplate;
							}
						}
					}
				}
			}
		}
		// Sua
		else if (selected == 2)
		{
			int line = 0;
			while (true)
			{
				if (Size(listDG) == 0)
				{
					break;
				}
				// In Doc Gia co Hightlight
				selectedMaDocGia = PrintAllDGWithHL(listDG, location, page, Menu_Mode::Both, line);
				line = WhereY() - location.y - 3;
				//ClearLine(1);
				if (selectedMaDocGia == "ESC")
				{
					break;
				}
				else
				{
					// cap nhat dsDocGia
					int MaDG = stoi(selectedMaDocGia);
					// Tim kiem Doc Gia bang Ma Doc Gia
					auto temp = Search(listDG, MaDG);
					// ...
					temp->data = InputFixDocGia({ {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} }, temp->data);
					tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
				}
			}
		}
		else if (selected == Key::ESC)
		{
			ClearScreen(BG_COLOR);
			break;
		}
	}
}

// Func 0 1
void InDanhSachDG(LIST_DOCGIA listDG)
{
	// Location của Menu
	MYPOINT locationMenu = { 62, 2 };

	// Location của Danh sách độc giả
	MYPOINT locationList = { 52, locationMenu.y + 3 };

	// Tạo Menu Select
	MENU menu = MENU({ "SAP XEP THEO HO TEN", "SAP XEP THEO MA" }, locationMenu);
	menu.btnSize = { 25, 3 };
	while (true)
	{
		int result = menu.ShowInHorizontal(Menu_Mode::Both);

		// Độc giả sắp theo Họ Tên
		if (result == 0)
		{
			PrintAllDocGia(listDG, locationList, 2);
			ClearArea(locationList.x, locationList.y, DOCGIA_TOTAL_WIDTH, MAX_ROW_PER_PAGE + 5);
		}
		// Độc giả sắp theo Mã
		else if (result == 1)
		{
			PrintAllDocGia(listDG, locationList, 1);
			ClearArea(locationList.x, locationList.y, DOCGIA_TOTAL_WIDTH, MAX_ROW_PER_PAGE + 5);
		}
		else
		{
			ClearScreen(BG_COLOR);
			break;
		}
	}
}

// Func 0 2
void InDanhSachQuaHan(LIST_DAUSACH listDS, LIST_DOCGIA lstDG)
{
	PrintListQuaHan(listDS, lstDG);
}

// Func 1 0
void HienThiDauSach(LIST_DAUSACH& listDS, MYPOINT location)
{
	string result = listDS.PrintAllTheLoai(location);
}

// Func 1 1
void CapNhatDauSach(LIST_DAUSACH& listDS, MYPOINT location)
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

	int page = 0;
	MYPOINT locationBtn = location;

	// In tất cả đầu sách, trả về ISBN người dùng chọn
	string selectedISBN = listDS.PrintAll(location, page, Show_Only);
	char* isbnAsArr = StringToCharArray(selectedISBN);

	// Tinh chỉnh vị trí button = mắt
	locationBtn.x += 30;
	locationBtn.y += 25;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };

	while (true)
	{
		// Hiện menu button
		int selectedButton = menu.ShowInHorizontal(Menu_Mode::Both);

		if (selectedButton == Key::PAGE_UP && page > 0)
		{
			page--;
			selectedISBN = listDS.PrintAll(location, page, Show_Only);
		}
		else if (selectedButton == Key::PAGE_DOWN)
		{
			page++;
			selectedISBN = listDS.PrintAll(location, page, Show_Only);
		}

		// Thêm
		else if (selectedButton == 0)
		{
			auto newDauSach = new DAUSACH();

			// Hiện form tạo đầu sách mới
			*newDauSach = InputDauSach(listDS, { {(int)DAUSACH_TOTAL_WIDTH + 2 + location.x, location.y}, {60, 18} });

			// CANCEL nhập DAUSACH
			if (newDauSach->isbn[0] == '\0')
			{
				delete newDauSach;
			}
			// SAVE DAUSACH
			else
			{
				if (listDS.Insert(*newDauSach, listDS.size))
				{
					selectedISBN = listDS.PrintAll(location, page);
				}
			}
		}
		// Xóa
		else if (selectedButton == 1)
		{
			while (true)
			{
				// Kiểm tra nếu LIST_DAUSACH rỗng => chỉ Show
				if (listDS.IsEmpty())
				{
					selectedISBN = listDS.PrintAll(location, page, Show_Only);
					break;
				}

				// Hiện toàn bộ DAUSACH và bắt phím trả về ISBN người dùng chọn
				selectedISBN = listDS.PrintAll(location, page, Menu_Mode::Both);
				isbnAsArr = StringToCharArray(selectedISBN);

				if (selectedISBN == "ESC")
				{
					// In lại danh sách để xóa HighLight
					MYPOINT tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < listDS.size; i++)
					{
						if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
						{
							listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
							tempLoc.y++;
						}
					}
					break;
				}
				// Người dùng ấn Enter để xóa
				else if (selectedISBN != "TAB")
				{
					auto confirm = CONFIRMDIALOG({ 30, 7 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();

					// Đồng ý xóa
					if (confirm.result == Yes)
					{
						// Đầu sách không được phép xóa
						if (listDS.GetDauSach(isbnAsArr)->dsSach.CanDelete() == false)
						{
							selectedISBN = listDS.PrintAll(location, page, Menu_Mode::Show_Only);
							MakeFlickWarning({ locationBtn.x - 5, 0 }, WARNING_CANT_DELETE_DS);
						}
						// Đầu sách được phép xóa
						else
						{
							listDS.DeleteDauSach(isbnAsArr);

							int temp = 0;
							if (listDS.size % MAX_ROW_PER_PAGE != 0) temp = 1;
							else if (listDS.size % MAX_ROW_PER_PAGE == 0 && page == listDS.size / MAX_ROW_PER_PAGE)
							{
								page--;
							}
							if (page == listDS.size / MAX_ROW_PER_PAGE + temp - 1)
							{
								SetBGColor(BG_COLOR);
								GoToXY(location.x, listDS.size % MAX_ROW_PER_PAGE + location.y + 3);
								cout << emptyTemplate;
							}
						}
					}
				}
			}
		}
		// Sửa
		else if (selectedButton == 2)
		{
			while (true)
			{
				// Kiểm tra nếu LIST_DAUSACH rỗng => chỉ Show
				if (listDS.IsEmpty())
				{
					break;
				}

				// Hiện toàn bộ DAUSACH và bắt phím trả về ISBN người dùng chọn
				selectedISBN = listDS.PrintAll(location, page, Menu_Mode::Both);
				isbnAsArr = StringToCharArray(selectedISBN);

				if (selectedISBN == "ESC")
				{
					// In lại danh sách để xóa HighLight
					auto tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < listDS.size; i++)
					{
						if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
						{
							listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
							tempLoc.y++;
						}

					}
					break;
				}
				// Người dùng ấn Enter để xóa
				else
				{
					// Lấy ra DAUSACH cần sửa
					DAUSACH* fixDauSach = listDS.GetDauSach(isbnAsArr);

					// Hiện form sửa DAUSACH
					*fixDauSach = InputFixDauSach(listDS, { {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} }, *fixDauSach);

					// cap nhat dsDauSach
					listDS.INotifyDSTheLoai();
				}
			}
		}
		// Thoát
		else if (selectedButton == Key::ESC)
		{
			ClearScreen(BG_COLOR);
			break;
		}
	}
}

// Func 1 2
void CapNhatDanhMucSach(LIST_DAUSACH& listDS)
{
	// Create Empty Line
	string emptyTemplate = "";
	emptyTemplate += string(DMS_TOTAL_WIDTH, ' ');

	int page = 0;
	MYPOINT locationDS = { 38,3 };
	MYPOINT locationListSach = locationDS;
	locationListSach.x = 40;

	// Setup menu
	MYPOINT locationBtn = locationDS;
	locationBtn.x = 41;
	MENU menu = MENU({ "THEM", "XOA", "SUA", "THANH LY" }, locationBtn);
	menu.btnSize = { 10,3 };

	while (true)
	{
		// Print LIST_DAUSACH và bắt phím lấy ISBN ng dùng chọn
		string isbn = listDS.PrintAll(locationDS, page, Both);
		ClearScreen(BG_COLOR);

		if (isbn == "ESC") return;

		// Lấy LIST_SACH của đầu sách ng dùng chọn
		char* isbnAsChar = StringToCharArray(isbn);
		DAUSACH* dauSach = listDS.GetDauSach(isbnAsChar);
		LIST_SACH* listSach = &dauSach->dsSach;

		menu.location.y = locationBtn.y + listSach->Size() + 4;
		while (true)
		{
			// Print LIST_SACH
			string maSach = listSach->PrintAll(locationListSach, Show_Only);

			// Print tên sách
			{
				SetTextColor(Color::Blue);
				string text = "DAU SACH CAN CHINH SUA: " + ToUpperString(dauSach->tenSach);
				GoToXY(locationDS.x + DMS_TOTAL_WIDTH / 2 - text.size() / 2 + 1, locationDS.y - 1);
				cout << text;
			}

			// Show menu và bắt phím lấy button ng dùng ấn
			int selectionMenu = menu.ShowInHorizontal(Both);

			// Thêm sách
			if (selectionMenu == 0)
			{
				// Tạo sách mới
				SACH* newSach = new SACH();

				// Tạo mã sách mới tự động (dùng mã lớn nhất + 1)
				string maSachAuto = listSach->AutoGenerateMaSach(isbnAsChar);

				// Hiện form Input sách mới
				*newSach = newSach->Input({ {90, locationDS.y},{44,13} }, maSachAuto);

				// Hủy nhập sách mới
				if (newSach->viTri[0] == '\0')
				{
					delete newSach;
				}
				// Lưu thông tin sách mới
				else
				{
					NODE_SACH* node = new NODE_SACH(*newSach);
					listSach->AddTail(*node);

					// Load lại List sách
					maSach = listSach->PrintAll(locationListSach, Show_Only);
					menu.location.y++;
				}
			}
			// Xóa sách
			else if (selectionMenu == 1)
			{
				while (true)
				{
					// Hết sách
					if (listSach->Size() == 0) break;

					// Print LIST_SACH và bắt phím lấy mã sách ng dùng chọn
					maSach = listSach->PrintAll(locationListSach, Both);
					if (maSach == "ESC") break;

					// Xác nhận ng dùng trước khi xóa sách
					auto confirm = CONFIRMDIALOG({ locationListSach.x + 30, locationListSach.y + 13 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();

					// Ng dùng đồng ý xóa
					if (confirm.result == Yes)
					{
						// Nếu sách có độc giả mượn => không được xóa
						if (listSach->Search(maSach)->data.CanDelete() == false)
						{
							MakeFlickWarning({ locationListSach.x + (int)DMS_TOTAL_WIDTH / 2 - 20, locationListSach.y - 3 }, WARNING_CANT_DELETE_SACH);
						}
						// Sách được xóa (Đã thanh lý, Cho mượn được)
						else
						{
							if (listSach->Delete(maSach))
							{
								// Xóa trên giao diện
								menu.ClearInHorizontal();
								menu.location.y--;
								menu.ShowDisableModeInHorizontal();
							}
						}
					}
				}
			}
			// Sửa sách
			else if (selectionMenu == 2)
			{
				while (true)
				{
					// Hết sách
					if (listSach->Size() == 0) break;

					// Print LIST_SACH và bắt phím lấy mã sách ng dùng chọn
					maSach = listSach->PrintAll(locationListSach, Both);
					if (maSach == "ESC") break;

					// Lấy sách cần sửa
					NODE_SACH* nodeFix = listSach->Search(maSach);

					// Sách không được xóa => không được sửa (Có độc giả mượn)
					if (nodeFix->data.CanDelete() == false)
					{
						MakeFlickWarning({ locationListSach.x + (int)DMS_TOTAL_WIDTH / 2 - 20, locationListSach.y - 3 }, WARNING_CANT_FIX_SACH);
					}
					// Được sửa
					else
					{
						nodeFix->data = nodeFix->data.InputFix({ {90, locationDS.y},{44,13} });
					}
				}
			}
			// Thanh lý
			else if (selectionMenu == 3)
			{
				while (true)
				{
					// Hết sách
					if (listSach->Size() == 0) break;

					// Print LIST_SACH và bắt phím lấy mã sách ng dùng chọn
					maSach = listSach->PrintAll(locationListSach, Both);
					if (maSach == "ESC") break;

					// Xác nhận ng dùng trước khi thanh lý sách
					auto confirm = CONFIRMDIALOG({ locationListSach.x + 30, locationListSach.y + 13 });
					confirm.Show("Ban chac chan muon thanh ly sach?", Yes_No);
					confirm.Clear();

					// Ng dùng đồng ý thanh lý
					if (confirm.result == Yes)
					{
						NODE_SACH* sachThanhLy = listSach->Search(maSach);
						
						// Nếu sách có độc giả mượn => không được thanh lý
						if (sachThanhLy->data.CanDelete() == false)
						{
							MakeFlickWarning({ locationListSach.x + (int)DMS_TOTAL_WIDTH / 2 - 20, locationListSach.y - 3 }, "SACH DA CO DOC GIA MUON. KHONG DUOC THANH LY");
						}
						// Sửa trạng thái => Đã thanh lý
						else
						{
							sachThanhLy->data.trangThai = DaThanhLy;
						}
					}
				}
			}
			// thoat
			else if (selectionMenu == Key::ESC)
			{
				ClearScreen(BG_COLOR);
				delete[] isbnAsChar;
				break;
			}
		}
	}
}

// Func 1 3
void TimSach(LIST_DAUSACH& listDS, MYPOINT location)
{
	MYPOINT point = { 66, 2 };
	bool isEnter = false;
	bool isCancel = false;
	bool isTrue = false;
	string searchKey = "";
	DrawMessageBox(point, "NHAP TEN SACH CAN TIM", searchKey, isEnter, isCancel, char(219), Show_Only);
	while (true)
	{
		isEnter = false;
		isCancel = false;
		isTrue = false;
		ClearArea(0, point.y + 8, 170, SCREEN_HEIGHT - FOOTER_HEIGHT - point.y - 8);
		// Tim sach voi Key duoc truyen vao tu MessageBox
		DrawMessageBox(point, "NHAP TEN SACH CAN TIM", searchKey, isEnter, isCancel, char(219), GetKey_Only);
		ClearLine(1);
		if (isEnter)
		{
			string selectedDauSach = listDS.PrintAllSearch({ location.x + 10, location.y + 10 }, searchKey, Menu_Mode::Both);
			if (selectedDauSach == "Empty")
			{
				MakeFlickWarning({ point.x + 20 - (((int)searchKey.size() + 26) / 2), point.y - 2 }, "KHONG TIM THAY DAU SACH: " + searchKey);
			}
		}
		if (isCancel)
		{
			ClearScreen(BG_COLOR);
			return;
		}
	}
}

// Func 2 0
void MuonSach(NODE_DOCGIA& nodeDocGia, LIST_DAUSACH& listDS)
{
	ClearScreen(BG_COLOR);
	MYPOINT locationDS = { 0,3 };
	MYPOINT locationMuon = { locationDS.x + (int)DAUSACH_TOTAL_WIDTH, locationDS.y + 1 };
	LIST_MUONTRA tempMT = LIST_MUONTRA();

	// Show footer
	{
		MYPOINT locTab = { 70, SCREEN_HEIGHT - FOOTER_HEIGHT - 2 };
		FOOTER_CHILD footerTab = FOOTER_CHILD(locTab, "TAB", "CHUYEN QUA TAB SACH MUON THEM");
		footerTab.Draw(Color::Blue, Color::Light_Blue);

		FOOTER_CHILD footerEnter = FOOTER_CHILD({ locationMuon.x + 25, locationMuon.y + 12 }, "ENTER", "HUY MUON SACH");
		footerEnter.Draw(Color::Red, Color::Light_Red);
	}

	string* isbnDaMuon = NULL;
	int daMuon = 0;
	int tongMuon = 0;
	int page = 0;

	// Get những ISBN độc giả đang mượn
	for (auto p = nodeDocGia.data.listMuonTra.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai == SachChuaTra)
		{
			auto arr = Split(p->data.maSach, "_");
			PushBack(isbnDaMuon, arr[0], daMuon);
		}
	}

	// Sách đã mượn
	tongMuon = daMuon;

	// In label
	{
		GoToXY(locationMuon.x + 27, locationMuon.y - 1);
		SetTextColor(Color::Blue);
		cout << "SACH DA MUON";
		GoToXY(locationMuon.x + 26, locationMuon.y + 4 + daMuon);
		cout << "SACH MUON THEM";
		auto temp = nodeDocGia.data.listMuonTra.ShowFormMuonSach(listDS, locationMuon, Show_Only, daMuon);
	}

	// Tiến hành chọn sách mượn
	while (true)
	{
		// Show list sách dự định mượn
		auto cancelDS = tempMT.ShowFormMuonSach(listDS, { locationMuon.x, locationMuon.y + 5 + daMuon }, Show_Only, SOSACHMUON_TOIDA - daMuon);

		// Print tất cả đầu sách
		auto selectDS = listDS.PrintAll(locationDS, page, Menu_Mode::Both);

		// Thoát mượn sách
		if (selectDS == "ESC")
		{
			// Không có sách mượn thêm => không cần hỏi khi thoát
			if (tongMuon == daMuon)
			{
				ClearScreen(BG_COLOR);
				return;
			}

			// Hỏi trước khi lưu
			auto confirm = CONFIRMMODEVERSION("LUU SACH DA CHON?", { 65, 1 });
			confirm.ShowEnterConfirm();

			// Hủy lưu
			if (confirm.result == -1)
			{
				continue;
			}
			// Lưu sách chọn mượn thêm
			else if (confirm.result == 1)
			{
				for (auto p = tempMT.pHead; p != NULL; p = p->pNext)
				{
					string maSachMuon = p->data.maSach;

					// Thêm mượn trả vào NODE_DOCGIA
					nodeDocGia.data.listMuonTra.InsertAtTail(p->data);

					// Tách mã sách lấy ISBN
					string* arr = Split(maSachMuon, "_");

					// Tìm đầu sách dựa vào mã sách => tăng số lượt mượn lên
					DAUSACH* dauSach = listDS.GetDauSach(StringToCharArray(arr[0]));
					dauSach->soLuotMuon++;

					// Chuyển trạng thái sách chọn mượn => đã mượn
					NODE_SACH* sach = dauSach->dsSach.Search(maSachMuon);
					sach->data.trangThai = DaMuon;
				}
			}

			ClearScreen(BG_COLOR);
			return;
		}
		// Qua TAB sách mượn thêm
		else if (selectDS == "TAB")
		{
			while (true)
			{
				// Chưa có sách mượn thêm
				if (tempMT.IsEmpty()) break;

				// Qua TAB sách chọn mượn và bắt phím lấy Mã Sách cần hủy mượn
				cancelDS = tempMT.ShowFormMuonSach(listDS, { locationMuon.x, locationMuon.y + 5 + daMuon }, Menu_Mode::Both, 3 - daMuon);

				if (cancelDS == "ESC")
				{
					// do nothing
				}
				// Break về form mượn sách
				else if (cancelDS == "TAB")
				{
					break;
				}
				// Thực hiện hủy mượn sách
				else
				{
					// Xóa trong tempMT
					tempMT.Delete(cancelDS);

					// Tách mã sách lấy ISBN
					string* arr = Split(cancelDS, "_");

					// Xóa ISBN khỏi list ISBN mượn thêm
					for (int viTri = 0; viTri < tongMuon; viTri++)
					{
						if (isbnDaMuon[viTri] == arr[0])
						{
							Erase(isbnDaMuon, viTri, tongMuon--);
							break;
						}
					}
				}
			}
		}
		// Người dùng Enter chọn đầu sáchs
		else
		{
			// Kiểm tra đã mượn đủ 3 sách
			if (tongMuon == SOSACHMUON_TOIDA)
			{
				MakeFlickWarning({ locationDS.x + 31, locationDS.y - 2 }, "DOC GIA CHI DUOC MUON TOI DA 3 SACH");
				continue;
			}

			// Kiểm tra ISBN có bị trùng không
			// Nếu không trùng => viTri trả về MAGIC_NUMBER
			int viTri = MAGIC_NUMBER;
			for (int i = 0; i < tongMuon; i++)
			{
				if (isbnDaMuon[i] == selectDS)
				{
					viTri = i;
					break;
				}
			}

			// ISBN không trùng => cho mượn đầu sách này
			if (viTri == MAGIC_NUMBER)
			{
				// Lấy DAUSACH người dùng chọn để mượn
				DAUSACH* dauSach = listDS.GetDauSach(StringToCharArray(selectDS));

				// Kiểm tra DAUSACH này còn sách hay không
				if (dauSach->dsSach.IsChoMuonDuoc())
				{
					ClearArea(locationDS.x, locationDS.y, DAUSACH_TOTAL_WIDTH, MAX_ROW_PER_PAGE + 5);

					while (true)
					{
						// In tất cả Sách thuộc dauSach mà ChoMuonDuoc và bắt phím chọn sách cần mượn
						string maSach = dauSach->dsSach.PrintAllChoMuonDuoc(locationDS, Both);

						// ESC quay về trang LIST_DAUSACH
						if (maSach == "ESC")
						{
							ClearArea(locationDS.x, locationDS.y, DMS_TOTAL_WIDTH, MAX_ROW_PER_PAGE);
							break;
						}

						// Kiểm tra key [maSach, ngayMuon] có trùng không
						if (nodeDocGia.data.listMuonTra.IsLoopKey(maSach) == false)
						{
							// Lấy thời gian hiện tại
							DATETIME today = DATETIME();
							today.SetDateTimeNow();

							// Tạo thông tin mượn trả mới
							MUONTRA muonTra = MUONTRA();
							muonTra.maSach = maSach;
							muonTra.ngayMuon = today;
							muonTra.trangThai = TrangThaiMuonTra::SachChuaTra;

							// Thêm vào bộ nhớ tạm tempMT
							tempMT.InsertAtTail(muonTra);

							// Thêm ISBN vào ds ISBN đã mượn
							PushBack(isbnDaMuon, selectDS, tongMuon);

							ClearArea(locationDS.x, locationDS.y, DMS_TOTAL_WIDTH, MAX_ROW_PER_PAGE);
							break;
						}
						else
						{
							MakeFlickWarning({ locationDS.x + 1, locationDS.y - 2 }, "SACH BAN CHON BI TRUNG. VUI LONG CHON SACH KHAC");
						}
					}
				}
				else
				{
					MakeFlickWarning({ locationDS.x + 15, locationDS.y - 2 }, "DAU SACH BAN CHON DA HET SACH. VUI LONG CHON DAU SACH KHAC");
				}
			}
			// ISBN bị trùng => không cho mượn đầu sách này
			else
			{
				MakeFlickWarning({ locationDS.x + 27, locationDS.y - 2 }, "DAU SACH DA MUON. VUI LONG CHON DAU SACH KHAC");
			}
		}
	}
}
void MuonTraSach(LIST_DOCGIA& listDG, LIST_DAUSACH& listDS, MYPOINT location)
{
	MYPOINT point = { 66, 2 };
	bool isEnter = false;
	bool isCancel = false;
	bool isTrue = false;
	bool isReload = false;
	string searchKey = "";
	while (true)
	{
		isEnter = false;
		isCancel = false;
		isTrue = false;

		// Xóa thông tin DOCGIA trước đó
		ClearArea(0, point.y + 8, 170, SCREEN_HEIGHT - FOOTER_HEIGHT - point.y - 8);
		// Form nhập mã DOCGIA
		DrawMessageBox(point, "NHAP MA DOC GIA", searchKey, isEnter, isCancel, char(219), Both, 4);

		if (isEnter)
		{
			// Kiểm tra maDocGia truyền vô là số và không được để trống
			if (!IsNumber(searchKey) || searchKey == "")
			{
				MakeFlickWarning({ point.x + 21 - (((int)searchKey.size() + 25) / 2), point.y - 2 }, "MA DOC GIA KHONG HOP LE");
				continue;
			}

			NODE_DOCGIA* docGiaSearch = Search(listDG, stoi(searchKey));

			// Không tìm thấy
			if (docGiaSearch == NULL)
			{
				MakeFlickWarning({ point.x + 21 - (((int)searchKey.size() + 25) / 2), point.y - 2 }, "KHONG TIM THAY DOC GIA: " + searchKey);
			}
			// Tìm thấy
			else
			{
				DrawMessageBox(point, "NHAP MA DOC GIA", searchKey, isEnter, isCancel, char(219), Show_Only, 4);

				// Hiển thị thông tin DOCGIA
				RECTANGLE rect = { {location.x + 61, location.y + 8}, {45, 11} };
				DocGiaInfo(rect, docGiaSearch->data);

				// Hiển thị các sách DOCGIA mượn
				string maSachSelect = docGiaSearch->data.listMuonTra.Show(listDS, { 20, 23 }, Show_Only);

				// Setup menu
				MYPOINT locationBtn = location;
				locationBtn.x = point.x - 12;
				locationBtn.y += 31;
				MENU menu = MENU({ "MUON SACH", "TRA SACH", "BAO MAT SACH" }, locationBtn);
				menu.btnSize = { 20, 3 };

				while (true)
				{
					if (isReload)
					{
						DrawMessageBox(point, "NHAP MA DOC GIA", searchKey, isEnter, isCancel, char(219), Show_Only, 4);
						// hien thi thong tin doc gia
						DocGiaInfo(rect, docGiaSearch->data);

						// hien thi cac sach doc gia muon
						maSachSelect = docGiaSearch->data.listMuonTra.Show(listDS, { 20, 23 }, Show_Only);

						isReload = false;
					}

					// Hiện menu và bắt phím
					int selectedButton = menu.ShowInHorizontal(Menu_Mode::Both);

					// Mượn sách
					if (selectedButton == 0)
					{
						// Kiểm tra DOCGIA có được mượn sách
						auto result = docGiaSearch->data.IsMuonSach();

						// Được mượn
						if (result == Accept)
						{
							MuonSach(*docGiaSearch, listDS);
							isReload = true;
						}
						// Báo lỗi cụ thể không được mượn
						else
						{
							switch (result)
							{
							case BiKhoaThe:
								MakeFlickWarning({ 65, 21 }, "THE DOC GIA BI KHOA, KHONG THE MUON SACH");
								break;
							case SachBiMat:
								MakeFlickWarning({ 48, 21 }, "DOC GIA LAM MAT SACH, VUI LONG BOI THUONG LAI SACH DE TIEP TUC MUON SACH");
								break;
							case GiuQua7Ngay:
								MakeFlickWarning({ 40, 21 }, "DOC GIA GIU SACH QUA HAN QUY DINH, VUI LONG TRA LAI SACH DE TIEP DUC MUON SACH");
								break;
							case MuonDuSach:
								MakeFlickWarning({ 63, 21 }, "MOI DOC GIA CHI DUOC MUON TOI DA 3 CUON SACH");
								break;
							default:
								break;
							}
						}
					}
					// Trả sách
					else if (selectedButton == 1)
					{
						while (true)
						{
							maSachSelect = docGiaSearch->data.listMuonTra.Show(listDS, { 20, 23 }, Both);
							if (maSachSelect == "ESC")
							{
								break;
							}
							else if (maSachSelect != "")
							{
								// xac nhan truoc khi thay doi
								auto confirm = CONFIRMMODEVERSION("", { 72, 31 });
								confirm.ShowEnterConfirm();
								if (confirm.result == 1)
								{
									string temp = GetMaDauSach(maSachSelect);
									auto dauSach = StringToCharArray(temp);
									DAUSACH* listDauSach = listDS.GetDauSach(dauSach);
									DATETIME time = DATETIME();
									time.SetDateTimeNow();
									MUONTRA muonTra = MUONTRA();
									auto sachTra = docGiaSearch->data.listMuonTra.Search(maSachSelect);
									sachTra->data.ngayTra = time;
									sachTra->data.trangThai = SachDaTra;
									listDauSach->dsSach.Search(maSachSelect)->data.trangThai = ChoMuonDuoc;
								}
							}
						}
					}
					// Báo mất sách
					else if (selectedButton == 2)
					{
						while (true)
						{
							// Thực hiện bắt phím trên list mượn trả và chọn sách cần báo mất
							maSachSelect = docGiaSearch->data.listMuonTra.Show(listDS, { 20, 23 }, Both);

							if (maSachSelect == "ESC")
							{
								break;
							}
							else if (maSachSelect != "")
							{
								// Xác nhận báo mất sách
								auto confirm = CONFIRMMODEVERSION("", { 72, 31 });
								confirm.ShowEnterConfirm();

								// Đồng ý
								if (confirm.result == 1)
								{
									// Lấy ngày hiện tại
									DATETIME today = DATETIME();
									today.SetDateTimeNow();

									// Đổi trạng thái thành làm mất sách
									NODE_MUONTRA* nodeMT = docGiaSearch->data.listMuonTra.Search(maSachSelect);
									nodeMT->data.trangThai = LamMatSach;
								}
							}
						}
					}
					// Thoát
					else
					{
						break;
					}
				}
			}
		}
		if (isCancel)
		{
			ClearScreen(BG_COLOR);
			return;
		}
	}
}

// Func 2 1
void InDSDauSachMuonNhieuNhat(LIST_DAUSACH& listDS, MYPOINT location)
{
	string leaderBroad = PrintTopDauSach(listDS, location);

	while (true)
	{
		if (leaderBroad == "ESC")
		{

			ClearScreen(BG_COLOR);
			break;
		}
	}
}