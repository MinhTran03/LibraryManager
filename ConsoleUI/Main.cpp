#include "DauSach.h"

using namespace std;

void demo(LIST_DAUSACH& listDS)
{
	auto rect = RECTANGLE({ 30, 5 }, { 50, 20 });
	DAUSACH* ds1 = new DAUSACH[1];
	*ds1 = ds1->Input(rect);
	listDS.Insert(*ds1, 0);
	string temp = ds1->ToString();
	GoToXY(0, 0);
	cout << temp << endl;
	_getch();
}

void demo2(LIST_DAUSACH& listDS)
{
	listDS.ReadFromFile("D:\\C++\\LibraryManager\\ConsoleUI\\DauSachData.txt");
}

int main()
{
	fullscreen();
	
	LIST_DAUSACH listDS;
	demo2(listDS);
	char tl[] = "Ky nang song";
	string temp = listDS.PrintFindBooks({10, 3}, "Dac nhan tam");
	

	SetTextColor(Color::White);
	SetBGColor(Color::Black);
	GoToXY(0, 50);
	cout << temp;
	system("pause");
	return 0;
}