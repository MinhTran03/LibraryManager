#include "FunctionMethods.h"

int main()
{
	SetupConsole();
	MYPOINT locationDS = { 1, 2 };

	// load dau sach
	auto listDS = LIST_DAUSACH();
	LoadDauSach(listDS);

	// load sach
	for (size_t i = 0; i < 5; i++)
	{
		LoadSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}

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
				HienThiDauSach(listDS, locationDS);
			}
			// CAP NHAT DAU SACH
			else if (func[1] == 1)
			{
				CapNhatDauSach(listDS, locationDS);
				//_getch();
			}
			// CAP NHAT DANH MUC SACH
			else if(func[1] == 2)
			{
				CapNhatDanhMucSach(listDS);
				break;
			}
			else if (func[1] == 3)
			{
				TimSach(listDS, locationDS);
				break;
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

	for (int i = 0; i < listDS.size; i++)
	{
		listDS.nodes[i]->dsSach.Deconstructor();
	}
	listDS.Deconstructor();

	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 35);
	system("pause");
	return 0;
}