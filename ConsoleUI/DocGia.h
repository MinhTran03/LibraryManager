#pragma once
#include "MuonTra.h"

enum GioiTinh
{
	Nam,
	Nu
};
enum TrangThaiTheDG
{
	TheBiKhoa = 0,
	DangHoatDong = 1
};

struct DOCGIA
{
	// 0001 ... 9999
	char maDocGia[MADOCGIA_MAXKYTU + 1];
	std::string ho;
	std::string ten;
	GioiTinh gioiTinh;
	TrangThaiTheDG trangThai;

	LIST_MUONTRA listMuonTra;
};

struct NODE_DOCGIA
{
	DOCGIA data;

	NODE_DOCGIA* pLeft;
	NODE_DOCGIA* pRight;
};
typedef NODE_DOCGIA* tree;

void FreeMemory(NODE_DOCGIA* root)
{
	if (root == NULL)
		return;
	FreeMemory(root->pLeft);
	FreeMemory(root->pRight);
	FreeMemory(root);
}
// khoi toa cay
void init(tree& cay)
{
	cay = NULL;
}

void insert(tree& cay, DOCGIA input)
{
	if (cay == NULL)
	{
		NODE_DOCGIA* p = new NODE_DOCGIA;
		p->data = input;
		p->pLeft = p->pRight = NULL;
		cay = p;
	}
	else
	{
		if (cay->data.maDocGia > input.maDocGia)
		{
			insert(cay->pLeft, input);
		}
		else if (cay->data.maDocGia < input.maDocGia)
		{
			insert(cay->pRight, input);
		}
	}
}

void NLR(tree cay)
{
	if (cay != NULL)
	{
		NLR(cay->pLeft);
		NLR(cay->pRight);
	}
}

NODE_DOCGIA* search(tree cay, DOCGIA input)
{
	if (cay == NULL)
	{
		return NULL;
	}
	else
	{
		if (cay->data.maDocGia > input.maDocGia)
		{
			search(cay->pLeft, input);
		}
		else if (cay->data.maDocGia < input.maDocGia)
		{
			search(cay->pRight, input);
		}
		else
		{
			return cay;
		}
	}
}

void TimPhanTuTheMangTraiNhatCayConPhai(tree& p, tree& q)
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

void TimpPhanTuTheMangPhaiNhatCayConTrai(tree& p, tree& q)
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
void DeleteNode(tree& t, DOCGIA input)
{
	if (t == NULL)
	{
		return;
	}
	else
	{
		if (t->data.maDocGia > input.maDocGia)
		{
			DeleteNode(t->pLeft, input);
		}
		else if (t->data.maDocGia < input.maDocGia)
		{
			DeleteNode(t->pRight, input);
		}
		else
		{
			NODE_DOCGIA* p = t;
			if (t->pLeft == NULL)
			{
				t = t->pRight;
			}
			else if (t->pRight == NULL)
			{
				t = t->pLeft;
			}
			else
			{
				// cach 1 tim phan tu trai nhat cay con phai 
				//timphantuthemangtrainhatcayconphai(p, t->pright);
				//cach 2 tìm phan tu tha mang phai nhat cay con trai
				TimpPhanTuTheMangPhaiNhatCayConTrai(p, t->pLeft);
			}
			delete p;
		}
	}

}

void Add(tree& cay, DOCGIA input)
{
	if (cay == NULL)
	{
		NODE_DOCGIA* p = new NODE_DOCGIA;
		p->data = input;
		p->pLeft = p->pRight = NULL;
		cay = p;
	}
	else
	{
		if (cay->data.maDocGia > input.maDocGia)
		{
			Add(cay->pLeft, input);
		}
		else if (cay->data.maDocGia < input.maDocGia)
		{
			Add(cay->pRight, input);
		}
		else
		{
			NODE_DOCGIA* l = new NODE_DOCGIA;
			if (cay->pLeft == NULL)
			{
				cay->data = input;
				cay = cay->pRight;

			}
			else if (cay->pRight == NULL)
			{
				cay->data = input;
				cay = cay->pLeft;
			}
		}
	}
}
