#include "MuonTra.h"

bool LIST_MUONTRA::isEmpty()
{
	if (pHead == NULL)
	{
		return true;
	}
}

// tao moi 1 node
NODE_MUONTRA* LIST_MUONTRA::MakeNode(MUONTRA muonTra) //tao 1 Node P chua thong tin la x 
{
	//Cap phat vung nho cho temp
	NODE_MUONTRA* temp = (NODE_MUONTRA*)malloc(sizeof(NODE_MUONTRA));
	temp->data = muonTra; //Ghi du lieu vao Data
	temp->pNext = NULL;
	temp->pPrev = NULL;
	return temp;
}
// them o dau
void LIST_MUONTRA::InsertAtHead(MUONTRA muonTra) {
	struct NODE_MUONTRA* newNode = MakeNode(muonTra);
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
void LIST_MUONTRA::InsertAtTail(MUONTRA muonTra) {
	struct NODE_MUONTRA* newNode = MakeNode(muonTra);
	if (pHead == NULL) {
		pHead = newNode;
		pTail = newNode;
		return;
	}
	pTail->pNext = newNode;
	newNode->pPrev = pTail;
	pTail = newNode;
}
// xoa o dau
void LIST_MUONTRA::DeleteAtHead() {
	if (pHead == NULL) {
		return;
	}
	pHead = pHead->pNext;
	pHead->pPrev = NULL;
}
// xoa o cuoi
void LIST_MUONTRA::DeleteAtTail() {
	if (pHead == NULL) {
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
