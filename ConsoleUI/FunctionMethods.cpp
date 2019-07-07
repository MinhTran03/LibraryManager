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
		{"HIEN THI DAU SACH", "CAP NHAT DAU SACH", "CAP NHAT DANH MUC SACH"},
		{"CHUA LAM", "CHUA LAM", "CHUA LAM"} }, menu);
	auto selection = slide.Show(rootLine, childLine);
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
// Fun 1 1
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
			*newDauSach = newDauSach->Input({ {DAUSACH_TOTAL_WIDTH + 2, 3}, {50, 18} });
			// nguoi dung an CANCEL
			if (newDauSach->isbn[0] == '\0')
			{
				delete newDauSach;
			}
			// ng dung Luu dau sach
			else
			{
				listDS.Insert(*newDauSach, listDS.size);
				listDS.PrintAll(location);
				menu.location.y++;
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