#pragma once
#include "DauSach.h"
#include "DocGia.h"

bool LoadDauSach(LIST_DAUSACH& listDS);
bool LoadSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1]);
bool LoadDocGia(LIST_DOCGIA& listDocGia);