#pragma once
#include "DauSach.h"
#include "DocGia.h"
#include "FileHandler.h"

string GetPath();
bool LoadDauSach(LIST_DAUSACH& listDS);
bool LoadSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1]);
bool LoadDocGia(LIST_DOCGIA& listDocGia);
bool LoadMaDG(LIST_DOCGIA listDocGia);

bool WriteDauSach(LIST_DAUSACH& listDS);
bool WriteSach(LIST_SACH& listDS, char isbn[ISBN_MAXSIZE + 1]);
bool WriteDocGia(LIST_DOCGIA& listDocGia);
bool WriteMuonTra(LIST_MUONTRA& listMT, std::string maDG);
bool WriteLog(string* log);