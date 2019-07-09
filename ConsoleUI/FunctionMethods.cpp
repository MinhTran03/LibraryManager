#include "FunctionMethods.h"

void SetupConsole()
{
	MaximizeWindow();
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	ClearScreen(BG_COLOR);
}

vector<int> SelectionFuntion(int rootLine, int childLine)
{
	MENU menu = MENU({ "QUAN LY DOC GIA", "QUAN LY DAU SACH", "QUAN LY SACH" }, { 0, 3 });
	vector<vector<string>> temp;
	SLIDEMENUS slide = SLIDEMENUS({ {"chua lam", "chua lam", "chua lam"},
		{"HIEN THI DAU SACH", "CAP NHAT DAU SACH", "CAP NHAT DANH MUC SACH", "TIM SACH"},
		{"CHUA LAM", "CHUA LAM", "CHUA LAM"} }, menu);
	auto selection = slide.Show(rootLine, childLine);
	//slide.Clear();
	/*GoToXY(0, 0);
	cout << menu.labels[selection[0]] << " ==> " << slide.childLabels[selection[0]][selection[1]];*/
	return selection;
}
// Func 1 0
void HienThiDauSach(LIST_DAUSACH& listDS, MYPOINT location)
{
	string result = listDS.PrintAllTheLoai(location);
	if (result == "ESC")
	{
		ClearScreen(BG_COLOR);
	}
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
				//else
				//{
				//	GoToXY(0, 0);
				//	SetTextColor(WARNING_TEXT_COLOR);
				//	cout << "ISBN da ton tai";
				//	/*auto tempLoc = location;
				//	tempLoc.x += 10;
				//	tempLoc.y += 5;
				//	auto messageBox = CONFIRMDIALOG(tempLoc);
				//	messageBox.Show("ISBN da ton tai", DialogResult::OK_Cancel);*/
				//	// load lai form
				//}
			}
		}
		// Xoa
		else if (selected == 1)
		{
			while (true)
			{
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
				// ng dung an enter de xoa
				else
				{
					auto confirm = CONFIRMDIALOG({ 30, 7 });
					confirm.Show("Ban chac chan muon xoa?", Yes_No);
					confirm.Clear();
					// dong y xoa
					if (confirm.result == Yes)
					{
						listDS.DeleteDauSach(isbnAsArr);
						SetBGColor(BG_COLOR);
						GoToXY(location.x, listDS.size + location.y + 3);
						cout << emptyTemplate;
					}
				}
			}
		}
		// Sua
		else if (selected == 2)
		{
			while (true)
			{
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
	MYPOINT locationDS = { 41,3 };
	auto locationBtn = locationDS;
	locationBtn.x = 46;

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
			if (maSach == "ESC")
			{
				continue;
			}

			// hien button
			int selectionMenu = menu.ShowInHorizontal(Both);
			// them
			if (selectionMenu == 0)
			{
				// Form nhap sach moi
				SACH* newSach = new SACH();
				StringToCharArray(isbn, isbnAsChar);
				string maSachAuto = listSach->AutoGenerateMaSach(isbnAsChar);
				*newSach = newSach->Input({ {90, 3},{44,13} }, maSachAuto);
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

			}
			// SUa
			else if (selectionMenu == 2)
			{

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