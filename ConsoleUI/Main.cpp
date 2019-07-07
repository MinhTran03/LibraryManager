#include "FunctionMethods.h"

int main()
{
	SetupConsole();
	MYPOINT locationDS = { 1, 3 };

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
				HienThiDauSach(listDS, locationDS);
			}
			// CAP NHAT DAU SACH
			else if (func[1] == 1)
			{
				CapNhatDauSach(listDS, locationDS);
				//_getch();
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