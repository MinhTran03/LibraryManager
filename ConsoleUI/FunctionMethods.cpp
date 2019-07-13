#include "FunctionMethods.h"
#include "Displays.h"

void SetupConsole()
{
	MaximizeWindow();
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	ClearScreen(BG_COLOR);
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
		{"CHUA LAM", "CHUA LAM", "CHUA LAM"} }, menu);
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
	PrintDocGia(listDG, location);
	//int maThe;
	auto locationBtn = location;
	locationBtn.x += 30;
	locationBtn.y += 37;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	while (true)
	{
		int selected = menu.ShowInHorizontal(Menu_Mode::Both);
		menu.ShowDisableModeInHorizontal();
		// Them
		if (selected == 0)
		{
			auto newDocGia = new DOCGIA();
			int backUpPos;
			int newMaDG = GetRandomMaDG(listDG, backUpPos);
			*newDocGia = InputDocGia(newMaDG, { {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} });
			if (newDocGia->ho == "")
			{
				delete newDocGia;
			}
			else
			{
				SwapMaDG(Size(listDG), backUpPos);
				Insert(listDG, *newDocGia);
				PrintDocGia(listDG, location);
			}
		}
		// Xoa
		else if (selected == 1)
		{
			while (true)
			{
				// Het doc gia
				if (true)
				{
					break;
				}
				ClearLine(1);
				if (true)
				{
					// load lai data
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
						// D khong duoc phep xoa
						if (true)
						{
							MakeFlickWarning({ locationBtn.x - 5, 1 }, WARNING_CANT_DELETE_DS);
						}
						else
						{
							// da cap nhat ds the loai trong DeleteDauSach

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
				if (true)
				{
					break;
				}

				if (true)
				{
					// load lai data
					break;
				}
				else
				{
					// cap nhat dsDauSach
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
	locationMenu.x = 62;
	location.y += 3;
	MENU menu = MENU({ "SAP XEP THEO HO TEN", "SAP XEP THEO MA" }, locationMenu);
	menu.btnSize = { 25, 3 };
	while (true)
	{
		auto result = menu.ShowInHorizontal(Menu_Mode::Both);
		if (result == 0)
		{
			PrintAllDocGia(listDG, location, 2);
		}
		else if (result == 1)
		{
			PrintAllDocGia(listDG, location, 1);
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

	string selectedISBN = listDS.PrintAll(location, Show_Only);
	char* isbnAsArr = StringToCharArray(selectedISBN);
	auto locationBtn = location;
	// xem = mat
	locationBtn.x += 30;
	locationBtn.y += 37;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	while (true)
	{
		int selected = menu.ShowInHorizontal(Menu_Mode::Both);
		menu.ShowDisableModeInHorizontal();
		// Them
		if (selected == 0)
		{
			auto newDauSach = new DAUSACH();
			*newDauSach = InputDauSach(listDS, { {DAUSACH_TOTAL_WIDTH + 2, location.y}, {50, 18} });
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
					selectedISBN = listDS.PrintAll(location);
				}
			}
		}
		// Xoa
		else if (selected == 1)
		{
			while (true)
			{
				// Het dau sach
				if (listDS.size == 0)
				{
					selectedISBN = listDS.PrintAll(location, Show_Only);
					break;
				}

				selectedISBN = listDS.PrintAll(location, Menu_Mode::Both);
				ClearLine(1);
				isbnAsArr = StringToCharArray(selectedISBN);
				if (selectedISBN == "ESC")
				{
					// load lai data
					auto tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < listDS.size; i++)
					{
						listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
						tempLoc.y++;
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
							SetBGColor(BG_COLOR);
							GoToXY(location.x, listDS.size + location.y + 3);
							cout << emptyTemplate;
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
				if (listDS.size == 0)
				{
					break;
				}
				selectedISBN = listDS.PrintAll(location, Menu_Mode::Both);
				isbnAsArr = StringToCharArray(selectedISBN);
				if (selectedISBN == "ESC")
				{
					// load lai data
					auto tempLoc = location;
					tempLoc.y += 3;
					for (int i = 0; i < listDS.size; i++)
					{
						listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
						tempLoc.y++;
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

	MYPOINT locationDS = { 41,2 };
	auto locationBtn = locationDS;
	locationBtn.x = 46;
	//locationBtn.y += 37;

	auto locationListSach = locationDS;
	locationListSach.x = 40;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };

	while (true)
	{
		// List Dau sach can cap nhat
		string isbn = listDS.PrintAll(locationDS, Both);
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
				menu.ShowDisableModeInHorizontal();
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
					menu.ShowDisableModeInHorizontal();
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
					menu.ShowDisableModeInHorizontal();
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
			ClearScreen(BG_COLOR);
			DrawMessageBox(point, "NHAP TEN SACH CAN TIM", searchKey, isEnter, isCancel, char(219), Show_Only);
			//listDS.PrintFindBooks({ location.x + 10, location.y + 10 }, searchKey);
			string selectedDauSach = listDS.PrintAllSearch({ location.x + 10, location.y + 10 }, searchKey, Menu_Mode::Both);
			if (selectedDauSach == "Empty")
			{
				MakeFlickWarning({ 70,1 }, "KHONG TIM THAY DAU SACH: " + searchKey);
			}
		}
		if (isCancel)
		{
			ClearScreen(BG_COLOR);
			return;
		}
	}
}