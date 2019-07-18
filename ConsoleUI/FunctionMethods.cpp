#include "FunctionMethods.h"
#include "Displays.h"
#include "FormInfo.h"

void SaveAll(LIST_DOCGIA listDG, LIST_DAUSACH listDS)
{
	// luu dau sach
	WriteDauSach(listDS);
	// luu sach
	for (int i = 0; i < listDS.size; i++)
	{
		if (listDS.nodes[i]->dsSach.IsEmpty())
			continue;
		WriteSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}
	// luu doc gia
	WriteDocGia(listDG);
	// luu ma doc gia arr
	WriteMaDGToFile(MADOCGIA_FILE_PATH);
}

void FormClosing(LIST_DOCGIA listDG, LIST_DAUSACH listDS)
{
	GoToXY(0, 0);
	std::cout << "Saving...";
	SaveAll(listDG, listDS);
	//Sleep(1000);
	// Huy
	for (int i = 0; i < listDS.size; i++)
	{
		listDS.nodes[i]->dsSach.Deconstructor();
	}
	listDS.Deconstructor();
	FreeMemory(listDG);
	GoToXY(0, 0);
	std::cout << "Done       ";
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

void MakeFlickWarning(MYPOINT location, std::string text)
{
	int x = location.x;
	int y = location.y;

	GoToXY(x, y);
	SetBGColor(BG_COLOR);
	SetTextColor(WARNING_TEXT_COLOR);
	cout << text;
	//ClearArea(location.x, location.y, text.size(), 1);
}

vector<int> SelectionFuntion(int rootLine, int childLine)
{
	MENU menu = MENU({ "QUAN LY DOC GIA", "QUAN LY DAU SACH", "QUAN LY SACH" }, { 0, 3 });
	vector<vector<string>> temp;
	SLIDEMENUS slide = SLIDEMENUS({ {"QUAN LY DOC GIA", "IN DANH SACH DOC GIA", "chua lam"},
		{"HIEN THI DAU SACH", "CAP NHAT DAU SACH", "CAP NHAT DANH MUC SACH", "TIM SACH"},
		{"MUON & TRA SACH", "CHUA LAM", "CHUA LAM"} }, menu);
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
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	string selectedMaDocGia;
	int page = 0;
	string tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
	std::string MaDocGia = StringToCharArray(selectedMaDocGia);

	//int maThe;
	auto locationBtn = location;
	locationBtn.x += 22;
	locationBtn.y += 25;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
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
			int newMaDG = GetRandomMaDG(listDG);
			*newDocGia = InputDocGia(newMaDG, { {location.x + (int)DOCGIA_TOTAL_WIDTH + 2, location.y}, {50, 18} });
			if (newDocGia->ho == "")
			{
				delete newDocGia;
			}
			else
			{
				RemoveMaDG();
				Insert(listDG, *newDocGia);
				tem = PrintAllDocGia(listDG, location, 1, Show_Only);
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
				ClearLine(1);
				MaDocGia = StringToCharArray(selectedMaDocGia);
				if (selectedMaDocGia == "ESC")
				{
					// load lai data
					std::vector<std::string> dsDocGia;
					if (listDG != NULL)
					{
						dsDocGia = GetAllStringNode(listDG);
					}
					int totalLine = dsDocGia.size();
					auto tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < totalLine; i++)
					{
						if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
						{
							PrintStringDocGia(dsDocGia[i], tempLoc);
							tempLoc.y++;
						}
					}
					break;
				}
				// ng dung an enter de xoa
				else
				{
					auto confirm = CONFIRMDIALOG({ 30, 7 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();
					// dong y xoa
					if (confirm.result == Yes)
					{
						int MaDG = std::stoi(MaDocGia);
						auto temp = Search(listDG, MaDG);
						// chua kiem tra co duoc xoa hay khong???
						// ...
						// D khong duoc phep xoa
						if (DeleteNode(listDG, temp->data) == false)
						{
							MakeFlickWarning({ locationBtn.x - 5, 1 }, WARNING_CANT_DELETE_DS);
						}
						else
						{
							//DeleteNode(listDG, temp->data);
							SetBGColor(BG_COLOR);
							GoToXY(location.x, Size(listDG) + location.y + 3);
							cout << emptyTemplate;
							// da cap nhat ds the loai trong DeleteDauSach
							tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
						}
					}
				}
			}
		}
		// Sua
		else if (selected == 2)
		{
			while (true)
			{
				if (Size(listDG) == 0)
				{
					break;
				}
				selectedMaDocGia = PrintAllDGWithHL(listDG, location, page, Menu_Mode::Both);
				ClearLine(1);
				MaDocGia = StringToCharArray(selectedMaDocGia);
				if (selectedMaDocGia == "ESC")
				{
					// load lai data
					std::vector<std::string> dsDocGia;
					if (listDG != NULL)
					{
						dsDocGia = GetAllStringNode(listDG);
					}
					int totalLine = dsDocGia.size();
					auto tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < totalLine; i++)
					{
						if (i >= (int)MAX_ROW_PER_PAGE * page && i < (page + 1) * (int)MAX_ROW_PER_PAGE)
						{
							PrintStringDocGia(dsDocGia[i], tempLoc);
							tempLoc.y++;
						}
					}
					break;
				}
				else
				{
					// cap nhat dsDocGia
					int MaDG = std::stoi(MaDocGia);
					auto temp = Search(listDG, MaDG);
					temp->data = InputFixDocGia({ {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} }, temp->data);
					tem = PrintAllDGWithHL(listDG, location, page, Show_Only);
					//break;
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
void InDanhSachDG(LIST_DOCGIA listDG, MYPOINT location)
{
	auto locationMenu = location;
	std::string temp;
	locationMenu.x = 62;
	location.y += 3;
	MENU menu = MENU({ "SAP XEP THEO HO TEN", "SAP XEP THEO MA" }, locationMenu);
	menu.btnSize = { 25, 3 };
	while (true)
	{
		auto result = menu.ShowInHorizontal(Menu_Mode::Both);
		//menu.ShowDisableModeInHorizontal();
		if (result == 0)
		{
			temp = PrintAllDocGia(listDG, location, 2);
		}
		else if (result == 1)
		{
			temp = PrintAllDocGia(listDG, location, 1);
		}
		else
		{
			ClearScreen(BG_COLOR);
			break;
		}
	}
}
// Func 1 0
void HienThiDauSach(LIST_DAUSACH& listDS, MYPOINT location)
{
	string result = listDS.PrintAllTheLoai(location);
}
// Func 1 1
void CapNhatDauSach(LIST_DAUSACH& listDS, MYPOINT location)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(ISBN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SOTRANG_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTACGIA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NAMXUATBAN_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENTHELOAI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);
	int page = 0;
	string selectedISBN = listDS.PrintAll(location, page, Show_Only);
	char* isbnAsArr = StringToCharArray(selectedISBN);
	auto locationBtn = location;
	// xem = mat
	locationBtn.x += 30;
	locationBtn.y += 25;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	while (true)
	{
		int selected = menu.ShowInHorizontal(Menu_Mode::Both);

		if (selected == Key::PAGE_UP && page > 0)
		{
			page--;
			selectedISBN = listDS.PrintAll(location, page, Show_Only);
		}
		else if (selected == Key::PAGE_DOWN)
		{
			page++;
			selectedISBN = listDS.PrintAll(location, page, Show_Only);
		}
		// Them
		else if (selected == 0)
		{
			//menu.ShowDisableModeInHorizontal();
			auto newDauSach = new DAUSACH();
			*newDauSach = InputDauSach(listDS, { {(int)DAUSACH_TOTAL_WIDTH + 2 + location.x, location.y}, {60, 18} });
			// nguoi dung an CANCEL
			if (newDauSach->isbn[0] == '\0')
			{
				delete newDauSach;
			}
			// ng dung Luu dau sach
			else
			{
				if (listDS.Insert(*newDauSach, listDS.size))
				{
					selectedISBN = listDS.PrintAll(location, page);
				}
			}
		}
		// Xoa
		else if (selected == 1)
		{
			//menu.ShowDisableModeInHorizontal();
			while (true)
			{
				// Het dau sach
				if (listDS.size == 0)
				{
					selectedISBN = listDS.PrintAll(location, page, Show_Only);
					break;
				}

				selectedISBN = listDS.PrintAll(location, page, Menu_Mode::Both);
				ClearLine(1);
				isbnAsArr = StringToCharArray(selectedISBN);
				if (selectedISBN == "ESC")
				{
					// load lai data
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
				// ng dung an enter de xoa
				else
				{
					auto confirm = CONFIRMDIALOG({ 30, 7 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();
					// dong y xoa
					if (confirm.result == Yes)
					{
						// chua kiem tra co duoc xoa hay khong???
						// ...
						// Dau sach khong duoc phep xoa
						if (listDS.GetDauSach(isbnAsArr)->dsSach.CanDelete() == false)
						{
							MakeFlickWarning({ locationBtn.x - 5, 1 }, WARNING_CANT_DELETE_DS);
						}
						else
						{
							// da cap nhat ds the loai trong DeleteDauSach
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
		// Sua
		else if (selected == 2)
		{
			//menu.ShowDisableModeInHorizontal();
			while (true)
			{
				if (listDS.size == 0)
				{
					break;
				}
				selectedISBN = listDS.PrintAll(location, page, Menu_Mode::Both);
				isbnAsArr = StringToCharArray(selectedISBN);
				if (selectedISBN == "ESC")
				{
					// load lai data
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
				else
				{
					auto fixDauSach = listDS.GetDauSach(isbnAsArr);

					*fixDauSach = InputFixDauSach(listDS, { {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} }, *fixDauSach);

					// cap nhat dsDauSach
					listDS.INotifyDSTheLoai();
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
// Func 1 2
void CapNhatDanhMucSach(LIST_DAUSACH& listDS)
{
	string emptyTemplate = "";
	emptyTemplate += string(MASACH_WIDTH + TRANGTHAISACH_WIDTH + VITRI_WIDTH + 4, ' ');

	MYPOINT locationDS = { 38,2 };
	auto locationBtn = locationDS;
	locationBtn.x = 46;
	//locationBtn.y += 37;

	auto locationListSach = locationDS;
	locationListSach.x = 40;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };

	int page = 0;

	while (true)
	{
		// List Dau sach can cap nhat
		string isbn = listDS.PrintAll(locationDS, page, Both);
		ClearScreen(BG_COLOR);
		if (isbn == "ESC")
		{
			return;
		}

		auto isbnAsChar = StringToCharArray(isbn);
		auto listSach = &listDS.GetDauSach(isbnAsChar)->dsSach;

		menu.location.y = locationBtn.y + listSach->Size() + 4;
		while (true)
		{
			// List danh muc sach
			string maSach = listSach->PrintAll(locationListSach, Show_Only);

			// hien button
			int selectionMenu = menu.ShowInHorizontal(Both);

			// them
			if (selectionMenu == 0)
			{
				//menu.ShowDisableModeInHorizontal();
				// Form nhap sach moi
				SACH* newSach = new SACH();
				StringToCharArray(isbn, isbnAsChar);
				string maSachAuto = listSach->AutoGenerateMaSach(isbnAsChar);
				*newSach = newSach->Input({ {90, locationDS.y},{44,13} }, maSachAuto);
				// nguoi dung an CANCEL
				if (newSach->viTri[0] == '\0')
				{
					delete newSach;
				}
				// ng dung Luu dau sach
				else
				{
					auto node = new NODE_SACH(*newSach);
					listSach->AddTail(*node);
					maSach = listSach->PrintAll(locationListSach, Show_Only);
					menu.location.y++;
				}
			}
			// Xoa
			else if (selectionMenu == 1)
			{
				while (true)
				{
					// Het sach
					if (listSach->Size() == 0)
						break;
					//menu.ShowDisableModeInHorizontal();
					maSach = listSach->PrintAll(locationListSach, Both);
					ClearLine(1);
					if (maSach == "ESC")
					{
						break;
					}
					auto confirm = CONFIRMDIALOG({ locationListSach.x + 3, locationListSach.y + 2 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();
					// dong y xoa
					if (confirm.result == Yes)
					{
						// chua kiem tra dieu kien xoa sach
						// ...
						// khong duoc xoa
						if (listSach->Search(maSach)->data.CanDelete() == false)
						{
							MakeFlickWarning({ locationBtn.x, 1 }, WARNING_CANT_DELETE_SACH);
						}
						else
						{
							if (listSach->Delete(maSach))
							{
								// xoa dong cuoi
								SetTextColor(BG_COLOR);
								SetBGColor(BG_COLOR);
								//GoToXY(locationListSach.x, menu.location.y - 1);
								//cout << emptyTemplate;
								ClearArea(locationListSach.x, menu.location.y - 1, DMS_TOTAL_WIDTH, 1);
								// xoa menu
								menu.ClearInHorizontal();
								// show menu
								menu.location.y--;

							}
						}
					}
				}
			}
			// Sua
			else if (selectionMenu == 2)
			{
				while (true)
				{
					// Het sach
					if (listSach->Size() == 0)
						break;
					//menu.ShowDisableModeInHorizontal();
					maSach = listSach->PrintAll(locationListSach, Both);
					if (maSach == "ESC")
					{
						break;
					}
					else
					{
						auto nodeFix = listSach->Search(maSach);
						// khong duoc xoa
						if (nodeFix->data.CanDelete() == false)
						{
							MakeFlickWarning({ locationBtn.x, 1 }, WARNING_CANT_FIX_SACH);
						}
						else
						{
							nodeFix->data = nodeFix->data.InputFix({ {90, locationDS.y},{44,13} });
						}
					}
				}
			}
			// thoat
			else if (selectionMenu == Key::ESC)
			{
				ClearScreen(BG_COLOR);
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
	std::string searchKey = "";
	DrawMessageBox(point, "NHAP TEN SACH CAN TIM", searchKey, isEnter, isCancel, char(219), Show_Only);
	while (true)
	{
		isEnter = false;
		isCancel = false;
		isTrue = false;
		DrawMessageBox(point, "NHAP TEN SACH CAN TIM", searchKey, isEnter, isCancel, char(219), GetKey_Only);
		if (isEnter)
		{
			ClearArea(0, point.y + 8, 168, SCREEN_HEIGHT - FOOTER_HEIGHT - point.y - 10);
			ClearLine(1);

			string selectedDauSach = listDS.PrintAllSearch({ location.x + 10, location.y + 10 }, searchKey, Menu_Mode::Both);
			if (selectedDauSach == "Empty")
			{
				MakeFlickWarning({ point.x + 20 - (((int)searchKey.size() + 26) / 2), point.y - 1 }, "KHONG TIM THAY DAU SACH: " + searchKey);
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
void MuonTraSach(LIST_DOCGIA& listDG, LIST_DAUSACH& listDS, MYPOINT location)
{
	MYPOINT point = { 66, 2 };
	bool isEnter = false;
	bool isCancel = false;
	bool isTrue = false;
	std::string searchKey = "";
	DrawMessageBox(point, "NHAP MA DOC GIA", searchKey, isEnter, isCancel, char(219), Show_Only);
	while (true)
	{
		isEnter = false;
		isCancel = false;
		isTrue = false;
		DrawMessageBox(point, "NHAP MA DOC GIA", searchKey, isEnter, isCancel, char(219), GetKey_Only, 4);
		if (isEnter)
		{
			ClearArea(0, point.y + 8, 168, SCREEN_HEIGHT - FOOTER_HEIGHT - point.y - 10);
			ClearLine(1);

			auto docGiaSearch = Search(listDG, stoi(searchKey));
			// khong tim thay
			if (docGiaSearch == NULL)
			{
				MakeFlickWarning({ point.x + 20 - (((int)searchKey.size() + 25) / 2), point.y - 1 }, "KHONG TIM THAY DOC GIA: " + searchKey);
			}
			// tiim thay
			else
			{
				// hien thi thong tin doc gia
				RECTANGLE rect = { {location.x + 63, location.y + 10}, {40, 11} };
				DocGiaInfo(rect, docGiaSearch->data);

				// hien thi cac sach doc gia muon


				// menu
				auto locationBtn = location;
				locationBtn.x += 22;
				locationBtn.y += 25;
				MENU menu = MENU({ "MUON SACH", "TRA SACH" }, locationBtn);
				menu.btnSize = { 10,3 };

				int selected = menu.ShowInHorizontal(Menu_Mode::Both);
				// muon sach
				if(selected == 0)
				{

				}
				// tra sach
				else
				{

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