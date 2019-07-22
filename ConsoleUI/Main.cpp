#include "FunctionMethods.h"

int main()
{
	SetupConsole();
	MYPOINT locationDS = { 2, 2 };

	// Load Doc gia
	LIST_DOCGIA listDG = LIST_DOCGIA();
	LoadMaDG(listDG);
	LoadDocGia(listDG);
	DuyetDocFile(listDG, GetPath());
	
	// load dau sach
	auto listDS = LIST_DAUSACH();
	LoadDauSach(listDS);
	// load sach
	for (int i = 0; i < listDS.size; i++)
	{
		LoadSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}
	ClearLine(0);

	int t1 = -1;
	int t2 = -1;
	while (true)
	{
		auto func = SelectionFuntion(t1, t2);
		if (func[0] == 0)
		{
			if (func[1] == 0)
			{
				QuanLiDocGia(listDG, { locationDS.x + 23, locationDS.y });
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
				HienThiDauSach(listDS, { locationDS.x + 30, locationDS.y });
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
			// MUON SACH
			if (func[1] == 0)
			{
				MuonTraSach(listDG, listDS, locationDS);
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
		t1 = func[0];
		t2 = func[1];
	}

	FormClosing(listDG, listDS);

	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 38);
	system("pause");
	return 0;
}