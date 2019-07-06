#include "SlideMenu.h"
#include "DauSach.h"
#include "Database.h"

using namespace std;

vector<int> SelectionFuntion(int rootLine = -1, int childLine = -1)
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

void SetupDisplay()
{
	//MaximizeWindow();
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	ClearScreen(BG_COLOR);
}

int main()
{
	SetupDisplay();
	MYPOINT locationDS = { 0, 3 };

	auto listDS = LIST_DAUSACH();
	LoadDauSach(listDS);
	vector<int> func = { -1,-1 };
	while (true)
	{
		func = SelectionFuntion(func[0], func[1]);
		ClearScreen(BG_COLOR);
		if (func[0] == 0)
		{
			if (func[1] == 0)
			{

			}
			else if (func[1] == 1)
			{

			}
			else
			{

			}
		}
		else if (func[0] == 1)
		{
			// HIEN THI DAU SACH
			if (func[1] == 0)
			{
				string result = listDS.PrintAllTheLoai(locationDS);
				if (result == "ESC")
				{
					continue;
				}
			}
			// CAP NHAT DAU SACH
			else if (func[1] == 1)
			{

			}
			// CAP NHAT DANH MUC SACH
			else
			{

			}
		}
		else
		{
			if (func[1] == 0)
			{

			}
			else if (func[1] == 1)
			{

			}
			else
			{

			}
		}

	}
	listDS.Deconstructor();

	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 35);
	system("pause");
	return 0;
}