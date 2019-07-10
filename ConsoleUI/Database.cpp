#include "Database.h"

bool LoadDauSach(LIST_DAUSACH& listDS)
{
	return listDS.ReadFromFile("D:\\WorkSpace\\LibraryManager\\ConsoleUI\\DauSachData.txt");
}
bool LoadSach(LIST_SACH& listSach, char isbn[ISBN_MAXSIZE + 1])
{
	std::string path = "D:\\WorkSpace\\LibraryManager\\ConsoleUI\\DanhMucSach\\";
	path += isbn;
	path += ".txt";
	return listSach.ReadFromFile(path);
}