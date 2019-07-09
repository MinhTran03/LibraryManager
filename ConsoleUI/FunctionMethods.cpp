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
	string selectedDauSach = listDS.PrintAll(location, Show_Only);
	auto locationBtn = location;
	locationBtn.x += 30;
	locationBtn.y += listDS.size + 4;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	while (true)
	{
		int selected = menu.ShowInHorizontal(Menu_Mode::Both);
		// Them
		if (selected == 0)
		{
			auto newDauSach = new DAUSACH();
			*newDauSach = InputDauSach(listDS, { {DAUSACH_TOTAL_WIDTH + 2, 3}, {50, 18} });
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
					selectedDauSach = listDS.PrintAll(location);
					menu.location.y++;
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
			selectedDauSach = listDS.PrintAll(location, Menu_Mode::Both);
			if (selectedDauSach == "ESC")
			{
				// load lai data
				auto tempLoc = location;
				tempLoc.y += 3;
				for (int i = 0; i < listDS.size; i++)
				{
					listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
					tempLoc.y++;
				}
			}
		}
		// Sua
		else if (selected == 2)
		{
			selectedDauSach = listDS.PrintAll(location, Menu_Mode::Both);
			if (selectedDauSach == "ESC")
			{
				// load lai data
				auto tempLoc = location;
				tempLoc.y += 3;
				for (int i = 0; i < listDS.size; i++)
				{
					listDS.nodes[i]->Print(tempLoc, BG_COLOR, TEXT_INPUT_COLOR);
					tempLoc.y++;
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
void CapNhatDanhMucSach(LIST_DAUSACH& listDS, LIST_SACH& listSach)
{
	MYPOINT location = { 50,3 };
	auto locationBtn = location;
	locationBtn.x += 30;
	locationBtn.y += listSach.Size() + 4;
	MENU menu = MENU({ "THEM", "XOA", "SUA" }, locationBtn);
	menu.btnSize = { 10,3 };
	while (true)
	{
		// List Dau sach can cap nhat
		string isbn = listDS.PrintAll(location, Both);
		ClearScreen(BG_COLOR);
		if (isbn == "ESC")
		{
			return;
		}
		// List danh muc sach
		string maSach = listSach.PrintAll({ 1,3 }, Show_Only);
		menu.ShowInHorizontal(Both);
		if (maSach == "ESC")
		{
			continue;
		}
		// Form nhap sach moi
		SACH* sach = new SACH();
		char isbnAsChar[ISBN_MAXSIZE + 1];
		StringToCharArray(isbn, isbnAsChar);
		string maSachAuto = listSach.AutoGenerateMaSach(isbnAsChar);
		*sach = sach->Input({ {90, 3},{44,13} }, maSachAuto);
		auto node = new NODE_SACH(*sach);
		listSach.AddTail(*node);
	}
}