#include "Database.h"

using namespace std;

void demo(LIST_DAUSACH& listDS)
{
	auto rect = RECTANGLE({ 30, 5 }, { 50, 20 });
	DAUSACH* ds1 = new DAUSACH;
	*ds1 = ds1->Input(rect);
	listDS.Insert(*ds1, 0);
	string temp = ds1->ToString();
	GoToXY(0, 0);
	cout << temp << endl;
	//_getch();
}

int main()
{
	ClearScreen(BG_COLOR);
	//fullscreen();
	
	LIST_DAUSACH listDS;
	LoadDauSach(listDS);
	char tl[] = "Ky nang song";
	//listDS.PrintFindBooks({10, 3}, "Dac nhan tam");

	LIST_SACH dsSach = LIST_SACH();
	auto isbn = listDS.nodes[0]->isbn;
	LoadSach(dsSach, isbn);
	std::string ma = dsSach.AutoGenerateMaSach(isbn);

	SACH* s = new SACH;
	*s = s->Input({ {10, 3}, {40, 12} }, ma);
	auto nodeSach = NODE_SACH(*s);
	dsSach.AddTail(nodeSach);

	listDS.nodes[0]->dsSach = dsSach;
	
	delete s;
	dsSach.Deconstructor();
	listDS.Deconstructor();
	SetTextColor(Color::White);
	SetBGColor(Color::Black);
	GoToXY(0, 50);
	system("pause");
	return 0;
}