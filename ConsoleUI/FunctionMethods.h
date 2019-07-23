#pragma once
#include "SlideMenu.h"
#include "Database.h"
#include "DauSach.h"
#include "MuonTra.h"
#include "DocGia.h"

using namespace std;

void SetupConsole();
void FormClosing(LIST_DOCGIA listDG, LIST_DAUSACH listDS);
int* SelectionFuntion(int rootLine = -1, int childLine = -1);
void QuanLiDocGia(LIST_DOCGIA& listDS, MYPOINT location);
void InDanhSachDG(LIST_DOCGIA listDG, MYPOINT location);
void HienThiDauSach(LIST_DAUSACH& listDS, MYPOINT location);
void CapNhatDauSach(LIST_DAUSACH& listDS, MYPOINT location);
void CapNhatDanhMucSach(LIST_DAUSACH& listDS);
void TimSach(LIST_DAUSACH& listDS, MYPOINT location);
void MuonTraSach(LIST_DOCGIA& listDG, LIST_DAUSACH& listDS, MYPOINT location);