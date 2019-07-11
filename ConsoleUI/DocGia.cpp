#include "DocGia.h"

void FreeMemory(NODE_DOCGIA* root)
{
	if (root == NULL)
		return;
	FreeMemory(root->pLeft);
	FreeMemory(root->pRight);
	FreeMemory(root);
}
// khoi toa cay
void init(LIST_DOCGIA& cay)
{
	cay = NULL;
}

void insert(LIST_DOCGIA& cay, DOCGIA input)
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

void NLR(LIST_DOCGIA cay)
{
	if (cay != NULL)
	{
		NLR(cay->pLeft);
		NLR(cay->pRight);
	}
}

NODE_DOCGIA* search(LIST_DOCGIA cay, DOCGIA input)
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
void DeleteNode(LIST_DOCGIA& t, DOCGIA input)
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

void Add(LIST_DOCGIA& cay, DOCGIA input)
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