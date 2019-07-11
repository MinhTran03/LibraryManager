#include "DocGia.h"

DOCGIA ParseVectorStringFile(std::vector<std::string> data)
{
	DOCGIA docGia;// = new DOCGIA;
	docGia.maDocGia = atoi(StringToCharArray(data[0]));
	docGia.ho = data[1];
	docGia.ten = data[2];
	if (ToLowerString(data[3]) == "nam")
	{
		docGia.gioiTinh = Nam;
	}
	else
	{
		docGia.gioiTinh = Nu;
	}
	if (ToLowerString(data[4]) == "dang hoat dong")
	{
		docGia.trangThai = DangHoatDong;
	}
	else
	{
		docGia.trangThai = TheBiKhoa;
	}
	return docGia;
}

bool ReadFromFile(LIST_DOCGIA& listDG, std::string path)
{
	auto fileHandler = FILEHANDLER(path);
	try
	{
		auto lstDocGia = fileHandler.GetTokens();
		int size = lstDocGia.size();
		//DAUSACH* dauSach = new DAUSACH[size];
		for (int i = 0; i < size; i++)
		{
			DOCGIA* docGia = new DOCGIA;
			*docGia = ParseVectorStringFile(lstDocGia[i]);
			Insert(listDG, *docGia);
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

DOCGIA ParseVectorString(std::vector<std::string> data)
{
	DOCGIA docGia;// = new DOCGIA;
	docGia.maDocGia = atoi(StringToCharArray(data[0]));
	docGia.ho = data[1];
	docGia.ten = data[2];
	if (data[3] == "0")
	{
		docGia.gioiTinh = Nam;
	}
	else
	{
		docGia.gioiTinh = Nu;
	}
	if (data[4] == "1")
	{
		docGia.trangThai = DangHoatDong;
	}
	else
	{
		docGia.trangThai = TheBiKhoa;
	}
	return docGia;
}

void FreeMemory(NODE_DOCGIA* root)
{
	if (root == NULL)
		return;
	FreeMemory(root->pLeft);
	FreeMemory(root->pRight);
	FreeMemory(root);
}
// khoi toa cay
void Init(LIST_DOCGIA& lstDG)
{
	lstDG = NULL;
}
// them node
void Insert(LIST_DOCGIA& lstDG, DOCGIA input)
{
	if (lstDG == NULL)
	{
		NODE_DOCGIA* p = new NODE_DOCGIA;
		p->data = input;
		p->pLeft = p->pRight = NULL;
		lstDG = p;
	}
	else
	{
		if (lstDG->data.maDocGia > input.maDocGia)
		{
			Insert(lstDG->pLeft, input);
		}
		else if (lstDG->data.maDocGia < input.maDocGia)
		{
			Insert(lstDG->pRight, input);
		}
	}
}

void NLR(LIST_DOCGIA lstDG)
{
	if (lstDG != NULL)
	{
		NLR(lstDG->pLeft);
		NLR(lstDG->pRight);
	}
}

NODE_DOCGIA* Search(LIST_DOCGIA lstDG, DOCGIA input)
{
	if (lstDG == NULL)
	{
		return NULL;
	}
	else
	{
		if (lstDG->data.maDocGia > input.maDocGia)
		{
			Search(lstDG->pLeft, input);
		}
		else if (lstDG->data.maDocGia < input.maDocGia)
		{
			Search(lstDG->pRight, input);
		}
		else
		{
			return lstDG;
		}
	}
	return NULL;
}

void TimPhanTuTheMangTraiNhatCayConPhai(LIST_DOCGIA& p, LIST_DOCGIA& q)
{
	if (q->pLeft != NULL)
	{
		TimPhanTuTheMangTraiNhatCayConPhai(p, q->pLeft);
	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pRight;
	}
}

void TimpPhanTuTheMangPhaiNhatCayConTrai(LIST_DOCGIA& p, LIST_DOCGIA& q)
{
	if (q->pRight != NULL)
	{
		TimpPhanTuTheMangPhaiNhatCayConTrai(p, q->pRight);
	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pLeft;
	}
}
// xoa 1 node la 
void DeleteNode(LIST_DOCGIA& lstDG, DOCGIA input)
{
	if (lstDG == NULL)
	{
		return;
	}
	else
	{
		if (lstDG->data.maDocGia > input.maDocGia)
		{
			DeleteNode(lstDG->pLeft, input);
		}
		else if (lstDG->data.maDocGia < input.maDocGia)
		{
			DeleteNode(lstDG->pRight, input);
		}
		else
		{
			NODE_DOCGIA* p = lstDG;
			if (lstDG->pLeft == NULL)
			{
				lstDG = lstDG->pRight;
			}
			else if (lstDG->pRight == NULL)
			{
				lstDG = lstDG->pLeft;
			}
			else
			{
				// cach 1 tim phan tu trai nhat cay con phai 
				//timphantuthemangtrainhatcayconphai(p, t->pright);
				//cach 2 t�m phan tu tha mang phai nhat cay con trai
				TimpPhanTuTheMangPhaiNhatCayConTrai(p, lstDG->pLeft);
			}
			delete p;
		}
	}

}

DOCGIA InputDocGia(int maThe, RECTANGLE rect)
{
	std::vector<std::string> labels = { "Ma doc gia:", "Ho:", "Ten:", "Gioi tinh:", "Trang thai the:" };
	std::string inputTitle = "NHAP THONG TIN DOC GIA";
	std::vector<CONDITION> conditions = { {Number_Only, 1, 4, Default}, {Name, 1, HO_MAXSIZE},{Name, 1, TENDOCGIA_MAXSIZE},
													{Enum, 1, 2 },{Enum2, 1, 2, Default} };
	auto form = FORMINPUT(labels, conditions, rect, inputTitle);
	DOCGIA docGia = DOCGIA();
	form.ParseData({ std::to_string(maThe), "","","0","1" });
	if (form.Show(1, 4))
	{
		return ParseVectorString(form.OutputResults);
	}
	else
	{
		form.ResetOutput();
	}
	return docGia;
}