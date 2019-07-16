#include "FunctionMethods.h"

int main()
{
	SetupConsole();
	MYPOINT locationDS = { 1, 2 };

	// Load Doc gia
	LIST_DOCGIA listDG = LIST_DOCGIA();
	LoadDocGia(listDG);
	MakeRandomArrayMaDG(listDG);
	
	// load dau sach
	auto listDS = LIST_DAUSACH();
	LoadDauSach(listDS);

	// load sach
	for (int i = 0; i < listDS.size; i++)
	{
		LoadSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}

	vector<int> func = { -1,-1 };
	while (true)
	{
		func = SelectionFuntion(func[0], func[1]);
		//ClearScreen(BG_COLOR);
		if (func[0] == 0)
		{
			if (func[1] == 0)
			{
				QuanLiDocGia(listDG, locationDS);
			}
			else if (func[1] == 1)
			{
				InDanhSachDG(listDG, { locationDS.x + 50, locationDS.y });
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
			}
			// CAP NHAT DANH MUC SACH
			else if(func[1] == 2)
			{
				CapNhatDanhMucSach(listDS);
			}
			else if (func[1] == 3)
			{
				TimSach(listDS, locationDS);
				HidePointer();
			}
		}
		else if (func[0] == 2)
		{
			if (func[1] == 0)
			{

			}
			else if (func[1] == 1)
			{

			}
			else if (func[1] == 2)
			{

			}
		}
		else
		{
			break;
		}
	}


	FormClosing(listDG, listDS);

	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 35);
	system("pause");
	return 0;
}