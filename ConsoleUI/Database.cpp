#include "Database.h"

bool LoadDauSach(LIST_DAUSACH& listDS)
{
	return listDS.ReadFromFile("DauSachData.txt");

}
bool LoadSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1])
{
	std::string path = "DanhMucSach\\";

	path += isbn;
	path += ".txt";
	return listSach.ReadFromFile(path);
}
bool LoadDocGia(LIST_DOCGIA& listDocGia)
{
	std::string path = "DocGiaData.txt";

	return ReadFromFile(listDocGia, path);
}
bool LoadMaDG(LIST_DOCGIA listDocGia)
{
	std::string path = MADOCGIA_FILE_PATH;

	return ReadMaDGFromFile(path);
}

bool WriteDauSach(LIST_DAUSACH& listDS)
{
	std::string path = "DauSachData.txt";
	return listDS.WriteToFile(path);
}
bool WriteSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1])
{
	std::string path = "DanhMucSach\\";
	path += isbn;
	path += ".txt";
	return listSach.WriteToFile(path);
}
bool WriteDocGia(LIST_DOCGIA& listDocGia)
{
	std::string path = "DocGiaData.txt";
	return WriteToFile(listDocGia, path);
}
bool WriteMuonTra(LIST_MUONTRA& listMT, std::string maDG)
{
	std::string path = "MuonTra\\";
	path += maDG;
	path += ".txt";
	return listMT.WriteToFile(path);
}