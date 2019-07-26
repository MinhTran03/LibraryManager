#include "FunctionMethods.h"

void LoadDataAll(LIST_DOCGIA& listDG, LIST_DAUSACH& listDS)
{
	// Load Doc gia
	LoadMaDG(listDG);
	LoadDocGia(listDG);
	DuyetDocFile(listDG, GetPath());

	// load dau sach
	LoadDauSach(listDS);
	// load sach
	for (int i = 0; i < listDS.size; i++)
	{
		LoadSach(listDS.nodes[i]->dsSach, listDS.nodes[i]->isbn);
	}
	ClearLine(0);
}

bool Working(LIST_DOCGIA& listDG, LIST_DAUSACH& listDS)
{
	MYPOINT locationDS = { 2, 2 };
	bool isSave = false;
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
				InDanhSachQuaHan(listDS, listDG);
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
			else if (func[1] == 2)
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
			// TOP 10 DAU SACH
			else if (func[1] == 1)
			{
				InDSDauSachMuonNhieuNhat(listDS, { 26, 2 });
			}
		}
		else
		{
			// hoi luu file
			auto confirmSaveFile = CONFIRMDIALOG({ 65, 10 });
			confirmSaveFile.Show("LUU DU LIEU THAY DOI VO FILE?", DialogResult::Yes_No, Cyan, Green, Bright_White);
			if (confirmSaveFile.result == Yes)
			{
				isSave = true;
			}
			confirmSaveFile.Clear();
			break;
		}
		t1 = func[0];
		t2 = func[1];
	}
	return isSave;
}

int main()
{
	LIST_DOCGIA listDG = LIST_DOCGIA();
	LIST_DAUSACH listDS = LIST_DAUSACH();

	//ShowMainScreen();

	SetupConsole();

	LoadDataAll(listDG, listDS);

	bool isSave = Working(listDG, listDS);

	FormClosing(listDG, listDS, isSave);

	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(0, 38);
	system("pause");
	return 0;
}