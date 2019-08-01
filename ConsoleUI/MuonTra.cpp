#include "MuonTra.h"

void MUONTRA::Print(DAUSACH dauSach, MYPOINT location, Color bgColor, Color textColor)
{
	SetTextColor(TEXT_INPUT_COLOR);
	SetBGColor(BG_COLOR);
	GoToXY(location.x, location.y);
	cout << this->ToString(dauSach);
}
// can dau sach de tim ten sach
string MUONTRA::ToString(DAUSACH dauSach)
{
	int temp;
	// MA SACH
	string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += string(temp, ' ');
	// TENSACH
	result += char(179);
	result += dauSach.tenSach;
	temp = TENSACH_WIDTH - dauSach.tenSach.size();
	result += string(temp, ' ');
	// NGAY MUON
	result += char(179);
	result += this->ngayMuon.ToStringDate();
	temp = NGAY_WIDTH - 10;
	result += string(temp, ' ');
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
	result += string(temp, ' ');
	// SO NGAY MUON
	result += char(179);
	if (this->trangThai != TrangThaiMuonTra::SachDaTra)
	{
		auto today = DATETIME();
		today.SetDateTimeNow();
		int subDay = today.SubDate(this->ngayMuon);
		result += to_string(subDay);
		temp = SONGAYMUON_WIDTH - NumberLength(subDay);
	}
	else
	{
		int subDay = this->ngayTra.SubDate(this->ngayMuon);
		result += to_string(subDay);
		temp = SONGAYMUON_WIDTH - NumberLength(subDay);
	}
	result += string(temp, ' ');
	// VI TRI
	result += char(179);
	result += dauSach.dsSach.Search(this->maSach)->data.viTri;
	temp = VITRI_WIDTH - VITRI_MAXSIZE;
	result += string(temp, ' ');
	// TRANG THAI MUON TRA
	result += char(179);
	string tem = "";
	if (this->trangThai == TrangThaiMuonTra::LamMatSach)
		tem += "Lam mat sach";
	else if (this->trangThai == TrangThaiMuonTra::SachChuaTra)
		tem += "Sach chua tra";
	else if (this->trangThai == TrangThaiMuonTra::SachDaTra)
		tem += "Sach da tra";
	result += tem;
	temp = TENTHELOAI_WIDTH - tem.size();
	result += string(temp, ' ');
	result += char(179);
	return result;
}
// can dau sach de tim ten sach
string MUONTRA::ToStringMuonSach(DAUSACH dauSach)
{
	int temp;
	// MA SACH
	string result = "";
	result += char(179);
	result += this->maSach;
	temp = MASACH_WIDTH - this->maSach.size();
	result += string(temp, ' ');
	// TENSACH
	result += char(179);
	result += dauSach.tenSach;
	temp = TENSACH_WIDTH - dauSach.tenSach.size();
	result += string(temp, ' ');
	// NGAY MUON
	result += char(179);
	result += this->ngayMuon.ToStringDate();
	temp = NGAY_WIDTH - 10;
	result += string(temp, ' ');
	result += char(179);
	return result;
}
// tao line string de ghi ra file
string MUONTRA::ToStringFile()
{
	string result = "";
	result = string(this->maSach);
	result += '-';
	result += this->ngayMuon.ToStringDate();
	result += '-';
	if (this->ngayTra.SubToDefaultDate() == 0)
	{
		result += "NULL";
		result += '-';
	}
	else
	{
		result += this->ngayTra.ToStringDate();
		result += '-';
	}
	switch (this->trangThai)
	{
	case TrangThaiMuonTra::LamMatSach:
		result += "Lam mat sach";
		break;
	case TrangThaiMuonTra::SachChuaTra:
		result += "Sach chua tra";
		break;
	case TrangThaiMuonTra::SachDaTra:
		result += "Sach da tra";
		break;
	default:
		break;
	}
	return result;
}
// ...
bool MUONTRA::IsQuaHan()
{
	if (this->trangThai == SachDaTra) return false;
	auto today = DATETIME();
	today.SetDateTimeNow();
	if (today.SubDate(this->ngayMuon) > 7)
	{
		return true;
	}
	return false;
}
// ...
int MUONTRA::GetSoNgayQuaHan()
{
	auto today = DATETIME();
	today.SetDateTimeNow();
	return today.SubDate(this->ngayMuon) - SONGAYMUON_TOIDA;
}

MUONTRA ParseVectorStringFile(string* data)
{
	DATETIME dt = DATETIME();
	MUONTRA mt;
	mt.maSach = data[0];
	if (data[2] == "NULL")
	{
		mt.ngayTra = dt;
	}
	else
	{
		dt.ParseStringDate(data[2]);
		mt.ngayTra = dt;
	}
	dt.ParseStringDate(data[1]);
	mt.ngayMuon = dt;
	if (ToLowerString(data[3]) == "sach chua tra")
		mt.trangThai = SachChuaTra;
	else if (ToLowerString(data[3]) == "sach da tra")
		mt.trangThai = SachDaTra;
	else
		mt.trangThai = LamMatSach;
	return mt;
}

// kiem tra trung key [maSach, ngayMuon] co trung khong
bool LIST_MUONTRA::IsLoopKey(string maSach)
{
	DATETIME now = DATETIME();
	now.SetDateTimeNow();
	string nowAsString = now.ToStringDate();
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		if (p->data.maSach == maSach && nowAsString == p->data.ngayMuon.ToStringDate())
			return true;
	}
	return false;
}
// ...
LIST_MUONTRA::LIST_MUONTRA()
{
	this->pHead = NULL;
	this->pTail = NULL;
}
// row la so dong data
void PrintLabelMuonSach(MYPOINT location, int row)
{
	string labels[] = { "MA SACH", "TEN SACH", "NGAY MUON" };
	auto lstBorder = LISTBORDERTEXT(labels, 3);
	lstBorder.Draw(location, { MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH },
		row, BORDER_COLOR);
}
// row la so dong data
void PrintLabelMuonTra(MYPOINT location, int row)
{
	string labels[] = { "MA SACH", "TEN SACH", "NGAY MUON", "NGAY TRA", "SO NGAY MUON", "VI TRI", "TRANG THAI" };
	auto lstBorder = LISTBORDERTEXT(labels, 7);
	lstBorder.Draw(location, { MASACH_WIDTH, TENSACH_WIDTH, NGAY_WIDTH, NGAY_WIDTH,
		SONGAYMUON_WIDTH, VITRI_WIDTH, TRANGTHAI_MUONTRA_WIDTH },
		row, BORDER_COLOR);
}
// hien form muon sach
string LIST_MUONTRA::ShowFormMuonSach(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode, int totalLineKhung)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MASACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NGAY_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	HidePointer();
	MYPOINT backUpLocation = location;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine;

	totalLine = 0;
	string* datas = this->GetAllNodeStringMuonSach(listDS, totalLine);
	int* rows = NULL;

	int count = 0;
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelMuonSach(location, totalLineKhung);
		location.y += 3;
		backUpLocation = location;
		for (int i = 0; i < totalLineKhung; i++)
		{
			if (i < totalLine)
			{
				GoToXY(location.x, location.y);
				if (mode == Both && i == 0)
				{
					SetTextColor(hlTextColor);
					SetBGColor(hlBGColor);
					cout << datas[i];
					PushBack(rows, location.y++, count);
					//rows.push_back(location.y++);
					SetTextColor(TEXT_INPUT_COLOR);
					SetBGColor(BG_COLOR);
					continue;
				}
				cout << datas[i];
				//rows.push_back(location.y++);
				PushBack(rows, location.y++, count);
			}
			// in khoang trang
			else
			{
				GoToXY(location.x, location.y++);
				cout << emptyTemplate;
			}
		}
	}
	if (mode == Show_Only)
	{
		delete[] datas;
		delete[] rows;
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
					else if (totalLine != 1)
					{
						GoToXY(location.x, rows[currentLine]);
						HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
						currentLine = count - 1;
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
					else if (totalLine != 1)
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
				string d = "";
				d += char(179);
				auto data = Split(datas[currentLine], d);
				delete[] datas;
				delete[] rows;
				return data[1];
			}
			else if (inputKey == Key::TAB)
			{
				delete[] datas;
				delete[] rows;
				return "TAB";
			}
			else if (inputKey == Key::ESC)
			{
				delete[] datas;
				delete[] rows;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}
// hien thi cac sach doc gia dang muon
string LIST_MUONTRA::Show(LIST_DAUSACH listDS, MYPOINT location, Menu_Mode mode)
{
	string emptyTemplate = "";
	emptyTemplate = emptyTemplate + char(179) + string(MASACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TENSACH_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NGAY_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(NGAY_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(SONGAYMUON_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(VITRI_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179) + string(TRANGTHAI_MUONTRA_WIDTH, ' ');
	emptyTemplate = emptyTemplate + char(179);

	HidePointer();
	MYPOINT backUpLocation = location;
	Color hlBGColor = Color::Cyan;
	Color hlTextColor = Color::White;
	int currentLine = 0;
	int totalLine;

	totalLine = 0;
	string* datas = this->GetAllNodeString(listDS, totalLine);
	int* rows = NULL;

	int count = 0;
	if (mode == Menu_Mode::Show_Only || mode == Menu_Mode::Both)
	{
		PrintLabelMuonTra(location, 3);
		location.y += 3;
		backUpLocation = location;
		
		for (int i = 0; i < 3; i++)
		{
			GoToXY(location.x, location.y);
			if (i < totalLine)
			{
				if (mode == Both && i == 0)
				{
					SetTextColor(hlTextColor);
					SetBGColor(hlBGColor);
					cout << datas[i];
					PushBack(rows, location.y++, count);
					//rows.push_back(location.y++);
					SetTextColor(TEXT_INPUT_COLOR);
					SetBGColor(BG_COLOR);
					continue;
				}
				cout << datas[i];
				PushBack(rows, location.y++, count);
			}
			else
			{
				cout << emptyTemplate;
			}
			//rows.push_back(location.y++);
		}
	}
	if (mode == Show_Only)
	{
		delete[] datas;
		delete[] rows;
	}
	if (totalLine == 0) return "ESC";
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
						currentLine = count - 1;
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
				
				std::string key = "";
				key += char(179);
				auto temp = Split(datas[currentLine], key);
				std::string keyTrim = Trim(temp[1]);
				delete[] datas;
				delete[] rows;
				return keyTrim;
			}
			else if (inputKey == Key::ESC)
			{
				GoToXY(location.x, rows[currentLine]);
				HightLight(datas[currentLine], BG_COLOR, TEXT_INPUT_COLOR);
				delete[] datas;
				delete[] rows;
				return "ESC";
			}
		} while (!_kbhit());
	}
	return "";
}
// duyet list lay data
string* LIST_MUONTRA::GetAllNodeStringMuonSach(LIST_DAUSACH listDS, int& count)
{
	string* result = NULL;
	//int count = 0;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai != SachDaTra)
		{
			auto isbn = Split(p->data.maSach, "_");
			auto isbnAsChar = StringToCharArray(isbn[0]);
			auto dauSach = listDS.GetDauSach(isbnAsChar);
			delete[] isbnAsChar;
			PushBack(result, p->data.ToStringMuonSach(*dauSach), count);
			//result.push_back(p->data.ToStringMuonSach(*dauSach));
		}
	}
	return result;
}
// duyet list lay data
string* LIST_MUONTRA::GetAllNodeString(LIST_DAUSACH listDS, int& count)
{
	string* result = NULL;
	//int count = 0;
	for (auto p = this->pHead; p != NULL; p = p->pNext)
	{
		if (p->data.trangThai != SachDaTra)
		{
			auto isbn = Split(p->data.maSach, "_");
			auto isbnAsChar = StringToCharArray(isbn[0]);
			auto dauSach = listDS.GetDauSach(isbnAsChar);
			PushBack(result, p->data.ToString(*dauSach), count);
			//result.push_back(p->data.ToString(*dauSach));
		}
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
// Tim muon tra theo ma sach
NODE_MUONTRA* LIST_MUONTRA::Search(string maSach)
{
	for (auto node = this->pTail; node != NULL; node = node->pPrev)
	{
		if (node->data.maSach == maSach)
		{
			return node;
		}
	}
	return NULL;
}
// xoa o dau
void LIST_MUONTRA::DeleteAtHead()
{
	if (pHead == NULL)
	{
		return;
	}
	// ds chi co 1 ptu
	if (this->pHead->pNext == NULL)
	{
		this->pHead = NULL;
		this->pTail = NULL;
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
// xoa muon tra dua vao ma sach
bool LIST_MUONTRA::Delete(string maSach)
{
	if (this->IsEmpty())
	{
		return false;
	}
	else
	{
		NODE_MUONTRA* p;
		NODE_MUONTRA* q;
		p = this->Search(maSach);
		if (p == NULL)
		{
			return false;
		}
		else
		{
			if (p == this->pHead)
			{
				this->DeleteAtHead();
			}
			else
			{
				q = this->pHead;
				while (q->pNext != p)
				{
					q = q->pNext;
				}
				if (q->pNext == this->pTail)
					this->DeleteAtTail();
				else
					this->DeleteAfter(q);
			}
		}
	}
	return true;
}
// xoa sau node before
bool LIST_MUONTRA::DeleteAfter(NODE_MUONTRA* beforeNode)
{
	NODE_MUONTRA* afterNode;
	NODE_MUONTRA* deleteNode;
	if (beforeNode == NULL || beforeNode->pNext == NULL)
	{
		return false;
	}

	deleteNode = beforeNode->pNext;
	afterNode = deleteNode->pNext;
	beforeNode->pNext = afterNode;
	afterNode->pPrev = beforeNode;
	delete deleteNode;

	return true;
}
// ghi ra filr text
bool LIST_MUONTRA::WriteToFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int c = 0;
		string* data = NULL;
		for (auto p = this->pHead; p != NULL; p = p->pNext)
		{
			auto temp = p->data.ToStringFile();
			if (p != this->pTail)
				temp += '\n';
			//data.push_back(temp);
			PushBack(data, temp, c);
		}
		fileHandler.WriteToFile(data, IosMode::WriteNext, c);
		delete[] data;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}
// doc file
bool LIST_MUONTRA::ReadFromFile(string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		int size = 0;
		auto lstMTVector = fileHandler.GetTokens(size);
		for (int i = 0; i < size; i++)
		{
			MUONTRA mt = ParseVectorStringFile(lstMTVector[i]);
			this->InsertAtTail(mt);
		}
		delete[] lstMTVector;
	}
	catch (const exception& ex)
	{
		GoToXY(0, 0);
		cout << ex.what();
		return false;
	}
	return true;
}
// dem so sach doc gia muon
int LIST_MUONTRA::DuyetDSSachChuaTra()
{
	int count = 0;
	for (auto p = this->pHead;  p != NULL; p = p->pNext)
	{
		p->data.trangThai = SachChuaTra;
		count++;
	}
	return count;
}