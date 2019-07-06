#include "SlideMenu.h"

using namespace std;

int main()
{
	ClearScreen(BG_COLOR);
	MENU menu = MENU({ "QUAN LY DOC GIA", "QUAN LY DAU SACH", "QUAN LY SACH" }, {0, 3});
	vector<vector<string>> temp;
	SLIDEMENUS slide = SLIDEMENUS({ {"chua lam", "chua lam", "chua lam"},
		{"HIEN THI DAU SACH", "CAP NHAT DAU SACH", "CAP NHAT DANH MUC SACH"},
		{"CHUA LAM", "CHUA LAM", "CHUA LAM"}}, menu);
	auto te = slide.Show();
	GoToXY(0, 0);
	cout << te[0] << te[1];
	




	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 50);
	system("pause");
	return 0;
}