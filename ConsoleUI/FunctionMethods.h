#pragma once
#include "SlideMenu.h"
#include "DauSach.h"
#include "Database.h"

using namespace std;

void SetupConsole();
vector<int> SelectionFuntion(int rootLine = -1, int childLine = -1);
void HienThiDauSach(LIST_DAUSACH& listDS, MYPOINT location);
void CapNhatDauSach(LIST_DAUSACH& listDS, MYPOINT location);
void CapNhatDanhMucSach(LIST_DAUSACH& listDS, LIST_SACH& listSach);