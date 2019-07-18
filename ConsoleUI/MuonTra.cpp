#include "MuonTra.h"

void MUONTRA::Print(DAUSACH dauSach, MYPOINT location, Color bgColor, Color textColor)
{
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(location.x, location.y);
	std::cout << this->ToString(dauSach);
}
// can dau sach de tim ten sach
std::string MUONTRA::ToString(DAUSACH dauSach)
{
	int temp;
	// MA SACH
	std::string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += std::string(temp, ' ');
	// TENSACH
	result += char(179);
	result += dauSach.tenSach;
	temp = TENSACH_WIDTH - dauSach.tenSach.size();
	result += std::string(temp, ' ');
	// NGAY MUON
	result += char(179);
	result += this->ngayMuon.ToStringDate();
	temp = NGAY_WIDTH - 10;
	result += std::string(temp, ' ');
	// NGAY TRA
	result += char(179);
	if (this->trangThai != TrangThaiMuonTra::SachDaTra)
	{
		result += "NULL";
		temp = NGAY_WIDTH - 4;
	}
	else
	{
		result += this->ngayTra.ToStringDate();
		temp = NGAY_WIDTH - 10;
	}
	result += std::string(temp, ' ');
	// SO NGAY MUON
	result += char(179);
	if (this->trangThai != TrangThaiMuonTra::SachDaTra)
	{
		result += "NULL";
		temp = SONGAYMUON_WIDTH - 4;
	}
	else
	{
		int subDay = this->ngayTra.SubDate(this->ngayMuon);
		result += subDay;
		temp = SONGAYMUON_WIDTH - NumberLength(subDay);
	}
	result += std::string(temp, ' ');
	// VI TRI
	result += char(179);
	result += dauSach.dsSach.Search(this->maSach)->data.viTri;
	temp = VITRI_WIDTH - VITRI_MAXSIZE;
	result += std::string(temp, ' ');
	// TRANG THAI MUON TRA
	result += char(179);
	std::string tem = "";
	if(this->trangThai == TrangThaiMuonTra::LamMatSach)
		tem += "Lam mat sach";
	else if (this->trangThai == TrangThaiMuonTra::SachChuaTra)
		tem += "Sach chua tra";
	else if (this->trangThai == TrangThaiMuonTra::SachDaTra)
		tem += "Sach da tra";
	result += tem;
	temp = TENTHELOAI_WIDTH - tem.size();
	result += std::string(temp, ' ');
	result += char(179);
	return result;
}
// can dau sach de tim ten sach
std::string MUONTRA::ToStringMuonSach(DAUSACH dauSach)
{
	int temp;
	// MA SACH
	std::string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += std::string(temp, ' ');
	// TENSACH
	result += char(179);
	result += dauSach.tenSach;
	temp = TENSACH_WIDTH - dauSach.tenSach.size();
	result += std::string(temp, ' ');
	// NGAY MUON
	result += char(179);
	result += this->ngayMuon.ToStringDate();
	temp = NGAY_WIDTH - 10;
	result += std::string(temp, ' ');
	result += char(179);
	return result;
}

LIST_MUONTRA::LIST_MUONTRA()
{
	this->pHead = NULL;
	this->pTail = NULL;
}
// row la so dong data
void PrintLabelMuonSach(MYPOINT location, int row)
{
	std::vector<std::string> labels = { "MA SACH", "TEN SACH", "NGAY MUON" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH },
		row, BORDER_COLOR);
}
// row la so dong data
void PrintLabelMuonTra(MYPOINT location, int row)
{
	std::vector<std::string> labels = { "MA SACH", "TEN SACH", "NGAY MUON", "NGAY TRA", "SO NGAY MUON", "VI TRI", "TRANG THAI" };
	auto lstBorder = LISTBORDERTEXT(labels);
	lstBorder.Draw(location, { MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH, NGAY_WIDTH, 
		SONGAYMUON_WIDTH, VITRI_WIDTH, TRANGTHAI_MUONTRA_WIDTH },
		row, BORDER_COLOR);
}
// hien form muon sach
std::string LIST_MUONTRA::ShowFormMuonSach(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode)
{
	HidePointer();
	MYPOINT backUpLocation = location;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine;

	std::vector<std::string> datas = this->GetAllNodeStringMuonSach(listDS);
	std::vector<int> rows;

	totalLine = (int)datas.size();

	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelMuonSach(location, 3);
		location.y += 3;
		backUpLocation = location;
		for (int i = 0; i < totalLine; i++)
		{
			GoToXY(location.x, location.y);
			if (mode == Both && i == 0)
			{
				SetTextColor(hlTextColor);
				SetBGColor(hlBGColor);
				std::cout << datas[i];
				continue;
			}
			std::cout << datas[i];
			rows.push_back(location.y++);
		}
	}
	if (mode == Menu_Mode::Both)
	{
		currentLine = 0;
		char inputKey = NULL;
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP)
				{
					if (currentLine > 0)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[--currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else if(totalLine != 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = rows.size() - 1;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < totalLine - 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[++currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else if(totalLine != 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				auto data = Split(datas[currentLine], "-");
				return data[1];
			}
			else if (inputKey == Key::TAB)
			{
				return "TAB";
			}
			else if (inputKey == Key::ESC)
			{
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}
// hien thi cac sach doc gia dang muon
std::string LIST_MUONTRA::Show(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode)
{
	HidePointer();
	MYPOINT backUpLocation = location;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine;

	std::vector<std::string> datas = this->GetAllNodeString(listDS);
	std::vector<int> rows;

	totalLine = (int)datas.size();

	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelMuonTra(location, 3);
		location.y += 3;
		backUpLocation = location;
		for (int i = 0; i < totalLine; i++)
		{
			GoToXY(location.x, location.y);
			if (mode == Both && i == 0)
			{
				SetTextColor(hlTextColor);
				SetBGColor(hlBGColor);
				std::cout << datas[i];
				continue;
			}
			std::cout << datas[i];
			rows.push_back(location.y++);
		}
	}
	if (mode == Menu_Mode::Both)
	{
		currentLine = 0;
		char inputKey = NULL;
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP)
				{
					if (currentLine > 0)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[--currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = rows.size() - 1;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
				else if (inputKey == Key::DOWN)
				{
					if (currentLine < totalLine - 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						GoToXY(location.x, rows[++currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
					else
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = 0;
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], hlBGColor, hlTextColor);
					}
				}
			}
			if (inputKey == Key::ENTER)
			{
				auto data = Split(datas[currentLine], "-");
				return data[1];
			}
			else if (inputKey == Key::ESC)
			{
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}
// duyet list lay data
std::vector<std::string> LIST_MUONTRA::GetAllNodeStringMuonSach(LIST_DAUSACH listDS)
{
	std::vector<std::string> result;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		auto isbn = Split(p->data.maSach, "_");
		auto dauSach = listDS.GetDauSach(StringToCharArray(isbn[0]));
		result.push_back(p->data.ToStringMuonSach(*dauSach));
	}
	return result;
}
// duyet list lay data
std::vector<std::string> LIST_MUONTRA::GetAllNodeString(LIST_DAUSACH listDS)
{
	std::vector<std::string> result;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		auto isbn = Split(p->data.maSach, "_");
		auto dauSach = listDS.GetDauSach(StringToCharArray(isbn[0]));
		result.push_back(p->data.ToString(*dauSach));
	}
	return result;
}
// kiem tra rong
bool LIST_MUONTRA::IsEmpty()
{
	if (pHead == NULL)
	{
		return true;
	}
	return false;
}
// tao moi 1 node
NODE_MUONTRA* LIST_MUONTRA::MakeNode(MUONTRA muonTra) //tao 1 Node P chua thong tin la x 
{
	//Cap phat vung nho cho temp
	NODE_MUONTRA* temp = new NODE_MUONTRA;
	temp->data = muonTra; //Ghi du lieu vao Data
	temp->pNext = NULL;
	temp->pPrev = NULL;
	return temp;
}
// them o dau
void LIST_MUONTRA::InsertAtHead(MUONTRA muonTra) 
{
	NODE_MUONTRA* newNode = MakeNode(muonTra);
	if (pHead == NULL) {
		pHead = newNode;
		pTail = newNode;
		return;
	}
	pHead->pPrev = newNode;
	newNode->pNext = pHead;
	pHead = newNode;
}
// them o cuoi
void LIST_MUONTRA::InsertAtTail(MUONTRA muonTra) 
{
	NODE_MUONTRA* newNode = MakeNode(muonTra);
	if (pHead == NULL) 
	{
		pHead = newNode;
		pTail = newNode;
		return;
	}
	pTail->pNext = newNode;
	newNode->pPrev = pTail;
	pTail = newNode;
}
// xoa o dau
void LIST_MUONTRA::DeleteAtHead() 
{
	if (pHead == NULL) 
	{
		return;
	}
	pHead = pHead->pNext;
	pHead->pPrev = NULL;
}
// xoa o cuoi
void LIST_MUONTRA::DeleteAtTail() 
{
	if (pHead == NULL) 
	{
		return;
	}
	pTail = pTail->pPrev;
	pTail->pNext = NULL;
}
//void LIST_MUONTRA::Print() {
//	struct NODE_MUONTRA* temp = pHead;
//	printf("\nForward: ");
//	while (temp != NULL) {
//		printf("%d ", temp->data);
//		temp = temp->pNext;
//	}
//	printf("\n");
//}
//
//void LIST_MUONTRA::ReversePrint() {
//	struct NODE_MUONTRA* temp = pTail;
//	if (temp == NULL) return; // empty list, exit
//	// Traversing backward using prev pointer
//	printf("\nReverse: ");
//	while (temp != NULL) {
//		printf("%d ", temp->data);
//		temp = temp->pPrev;
//	}
//	printf("\n");
//}
