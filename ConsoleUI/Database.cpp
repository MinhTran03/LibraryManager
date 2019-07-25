#include "Database.h"

string GetPath()
{
	wchar_t buffer[MAX_PATH];
	auto path = GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring ws(buffer);
	string str(ws.begin(), ws.end());
	auto at = str.find_last_of('\\');
	str.erase(str.begin() + at, str.end());
	str += "\\Data";
	return str;
}

bool LoadDauSach(LIST_DAUSACH& listDS)
{
	string path = GetPath();
	return listDS.ReadFromFile(path + "\\DauSachData.txt");
}
bool LoadSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1])
{
	string path = GetPath();
	path += "\\DanhMucSach\\";

	path += isbn;
	path += ".txt";
	return listSach.ReadFromFile(path);
}
bool LoadDocGia(LIST_DOCGIA& listDocGia)
{
	string path = GetPath();
	path += "\\DocGiaData.txt";

	return ReadFromFile(listDocGia, path);
}
bool LoadMaDG(LIST_DOCGIA listDocGia)
{
	string path = GetPath();
	path += MADOCGIA_FILE_PATH;

	return ReadMaDGFromFile(path);
}

bool WriteDauSach(LIST_DAUSACH& listDS)
{
	string path = GetPath();
	path += "\\DauSachData.txt";
	return listDS.WriteToFile(path);
}
bool WriteSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1])
{
	string path = GetPath();
	path += "\\DanhMucSach\\";
	path += isbn;
	path += ".txt";
	return listSach.WriteToFile(path);
}
bool WriteDocGia(LIST_DOCGIA& listDocGia)
{
	string path = GetPath();
	path += "\\DocGiaData.txt";
	return WriteToFile(listDocGia, path);
}
bool WriteMuonTra(LIST_MUONTRA& listMT, string maDG)
{
	string path = GetPath();
	path += "\\MuonTra\\";
	path += maDG;
	path += ".txt";
	return listMT.WriteToFile(path);
}