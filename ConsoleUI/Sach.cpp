#include "Sach.h"

#pragma region -------------------------------------------SACH
// chuyen vector<string> vo obj Sach
SACH ParseVectorString(std::vector<std::string> data)
{
	SACH sach;
	sach.maSach = data[0];
	if (data[1] == "0")
		sach.trangThai = ChoMuonDuoc;
	else if (data[1] == "1")
		sach.trangThai = DaMuon;
	else
		sach.trangThai = DaThanhLy;
	sach.viTri = data[2];
	return sach;
}
// hien form nhap SACH
SACH SACH::Input(RECTANGLE rect, std::string maSach)
{
	std::string title = "Nhap Sach";
	std::vector<std::string> labels = { "Ma sach", "Trang thai:", "Vi tri:" };
	std::vector<CONDITION> conditions = { {All, 6, 6, Default}, {Enum, 1, 3, Default}, {Mix, 1, VITRI_MAXSIZE} };
	auto form = FORMINPUT(labels, conditions, rect, title);
	form.ParseData({ maSach, "0", "" });
	form.currentLine = 2;
	if (form.Show(2))
	{
		return ParseVectorString(form.OutputResults);
	}
	else
	{
		form.ResetOutput();
	}
	return *this;
}

#pragma endregion

#pragma region -------------------------------------------NODE_SACH
NODE_SACH::NODE_SACH()
{
	
}
// Khoi tao 1 node sach moi
NODE_SACH::NODE_SACH(SACH& data)
{
	this->data = data;
	this->pNext = NULL;
}

#pragma endregion

#pragma region -------------------------------------------LIST_SACH
void LIST_SACH::Deconstructor()
{
	while (this->pHead->pNext != NULL && this->pHead != NULL)
	{
		NODE_SACH* old = this->pHead;
		this->pHead = this->pHead->pNext;
		delete old;
	}
	this->pHead = this->pTail = NULL;
}
// constructor Init ds moi
LIST_SACH::LIST_SACH()
{
	this->pHead = NULL;
	this->pTail = NULL;
}
// Doc ds danh muc sach tu file. Moi file chua 1 dms cua 1 dau sach
bool LIST_SACH::ReadFromFile(std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		auto lstSachVector = fileHandler.GetTokens();
		int size = lstSachVector.size();
		SACH* dauSach = new SACH[size];
		for (int i = 0; i < size; i++)
		{
			dauSach[i] = ParseVectorString(lstSachVector[i]);
			auto nodeSach = new NODE_SACH(dauSach[i]);
			AddTail(*nodeSach);
		}
	}
	catch (const std::exception& ex)
	{
		GoToXY(0, 0);
		std::cout << ex.what();
		return false;
	}
	return true;
}
// Thuat toan tu sinh ma sach
std::string LIST_SACH::AutoGenerateMaSach(char isbn[ISBN_MAXSIZE + 1])
{
	std::string maSach = isbn;
	maSach += "_";
	// kiem tra ds sach rong
	if (this->pHead == NULL)
	{
		maSach += "0001";
	}
	else
	{
		std::string oldMax = Split(this->pTail->data.maSach, "_")[1];
		int newNum = std::stoi(oldMax) + 1;
		MergeWordWithNumber(maSach, newNum, MASACH_MAXSIZE);
	}
	return maSach;
}
// Them vao cuoi ds sach
void LIST_SACH::AddTail(NODE_SACH& node)
{
	if (this->pHead == NULL)
	{
		this->pHead = this->pTail = &node;
	}
	else
	{
		this->pTail->pNext = &node;
		this->pTail = &node;
	}
}
#pragma endregion