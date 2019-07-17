#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mylib.h"
#include <time.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>

#define color 124
using namespace std;
enum LoiDauSach {
	maISBN = 1,
	maDSTrung,
	tenSach,
	tenTacGia,
	theLoaiBB,	// the loai bat buoc phai nhap	
	soTrangBB,		// so trang bat buoc phai nhap
	soTrangSo,  	//so trang pahi la so
	namXBanBB,
	namXBanSo,
	namXBanSai,
	maISBNSo,
	kiTuKhongHopLe,
	QuaDai
};
enum LoiDocGia {
	maDGBB = 1, // ma doc gia la bat buoc;
	maDGBiTrung,
	maDGSo,
	maQDai,
	hoBB,
	hoQDai,
	tenBB,
	tenQDai,
	phaiBB,
	phaiKhopLe,
	ttTheDGSo,
	ttTheBB,
	kiTuDocGia

};
enum LoiSach {
	maSachBB = 1,
	maSachBiTrung,
	maSachSo,
	ttTheSo,
	ttTheQDai,
	vTriSo,
	vTriQDai
};
enum ttThe {
	binhThuong,
	viPham,
};
enum ttSach {
	choMuonDuoc,
	daMuon,
	thanhLy
};
enum ttMuonTraSach {
	chuaTra,
	daTra,
	lamMatSach
};
using namespace std;
const int MaxDauSach = 300;

struct Date {
	int day;
	int month;
	int year;
};

//=====Danh Muc Muon Tra==
struct MuonTra {
	int maSach;
	Date ngayMuon;
	Date ngayTra;
	int trangThaiMuonTraSach;
};
struct NodeMuonTra {
	MuonTra muonTra;
	struct NodeMuonTra* next;
}; typedef NodeMuonTra* PTRMuonTra;

//=====Danh Muc Doc Gia====
struct DocGia {
	int maDG;
	string ho;
	string ten;
	int trangThaiThe;
	string phai;
	int soSachMuon;
	PTRMuonTra FirstMuonTra;
};
struct NodeDG {
	DocGia docGia;
	struct NodeDG* left;
	struct NodeDG* right;
}; typedef NodeDG* TreeDocGia;

//=====Danh Muc Sach====
struct MucSach {
	int maSach;
	int trangThaiSach;
	string viTri;
};
struct NodeDanhMucSach {		// danh muc sach
	MucSach mucSach;
	struct NodeDanhMucSach* next;
}; typedef NodeDanhMucSach* PTRDanhMucSach;

//=====Danh Muc Dau Sach==
struct DauSach {
	string ISBN;
	string tenSach;
	int soTrang;
	string tacGia;
	int namXuatBan;
	string theLoai;
	int soLanMuon;
	int soSach;
	PTRDanhMucSach FirstDanhMucSach;
};
struct ListDauSach {
	int soDauSach;
	DauSach sach[MaxDauSach];
};

TreeDocGia rootDocGia;
ListDauSach listDauSach;
void Menu(TreeDocGia& root, ListDauSach& list);

int So_Sanh_Chuoi(string s1, string s2)
{
	char temp[10];
	strcpy(temp, s1.c_str());
	char temp1[10];
	strcpy(temp1, s2.c_str());
	if (strcmp(strupr(temp1), strupr(temp)) == 0)   // strupr in hoa chu len roi so sanh
		return 1;
	return 0;
}

void Lay_Ngay_He_Thong(Date& d)
{
	int ngay, thang, nam, SoNgay;
	tm* today;
	time_t ltime;
	time(&ltime);
	today = localtime(&ltime);
	d.day = today->tm_mday;
	d.month = today->tm_mon + 1;
	d.year = today->tm_year + 1900;
}
int So_Ngay(Date n)
{
	int day = n.day;
	for (int i = 1; i < n.month; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			day += 31;
		else if (i == 4 || i == 6 || i == 9 || i == 11)
			day += 30;
		else
		{
			if (n.year % 4 == 0)
				day += 29;
			else
				day += 28;
		}
	}
	return day;
}
int Tinh_Ngay(Date muon, Date tra)
{
	return (tra.year - muon.year) * 365 + So_Ngay(tra) - So_Ngay(muon);
}

//=== BAT lOI ===
void Loi_Nhap_Dau_Sach(int k) {
	Del_Error();
	string s;
	switch (k)
	{
	case maISBN:
		s = "MA ISBN LA BAT BUOC!";
		break;
	case maDSTrung:
		s = "MA ISBN DA BI TRUNG!";
		break;
	case tenSach:
		s = "TEN SACH LA BAT BUOC!";
		break;
	case tenTacGia:
		s = "TEN TAC GIA LA BAT BUOC!";
		break;
	case  theLoaiBB:
		s = "THE LOAI LA BAT BUOC!";
		break;
	case soTrangBB:
		s = "NHAP SO TRANG LA BAT BUOC!";
		break;
	case soTrangSo:
		s = "SO TRANG PHAI LA SO!";
		break;
	case namXBanBB:
		s = "NHAP NAM XUAT BAN LA BAT BUOC!";
		break;
	case namXBanSo:
		s = "NAM XUAT BAN PHAI LA SO!";
		break;
	case namXBanSai:
		s = " NAM XUAT BAN TU 1800 -> 2017! ";
		break;
	case kiTuKhongHopLe:
		s = "CHUOI CO KI TU KHONG HOP LE";
		break;
	case maISBNSo:
		s = "MA ISBN PHAI LA SO!";
		break;
	case QuaDai:
		s = "CHUOI QUA DAI";
	}
	gotoxy(boxx + 15, 29); cout << "CANH BAO: " << s;
}
void Loi_Nhap_Doc_Gia(int k)
{
	Del_Error();
	string s;
	switch (k)
	{
	case maDGBB:
		s = "MA DOC GIA LA BAT BUOC!";
		break;
	case maDGBiTrung:
		s = "MA DOC GIA DA BI TRUNG!";
		break;
	case maQDai:
		s = "MA DOC GIA QUA DAI!";
		break;
	case maDGSo:
		s = "MA DOC GIA PHAI LA SO!";
		break;
	case hoBB:
		s = "HO DOC GIA LA BAT BUOC!";
		break;
	case hoQDai:
		s = "HO DOC GIA QUA DAI!";
		break;
	case tenBB:
		s = "TEN DOC GIA LA BAT BUOC!";
		break;
	case tenQDai:
		s = "TEN DOC GIA QUA DAI!";
		break;
	case phaiBB:
		s = "PHAI DOC GIA LA BAT BUOC!!";
		break;
	case phaiKhopLe:
		s = "PHAI DOC GIA KHONG HOP LE!";
		break;
	case ttTheDGSo:
		s = "TRANG THAI THE PHAI LA SO! (0/1)";
		break;
	case ttTheBB:
		s = "TRANG THAI THE LA BAT BUOC!";
		break;
	case kiTuDocGia:
		s = " CHUOI CO KY TU KHONG HOP LE!";
	}
	gotoxy(boxx + 15, 29); cout << "CANH BAO: " << s;
}
string Chuyen_So_Thanh_Chuoi(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
int Check_So(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i]<'0' || s[i]>'9')
			return 0;
	}
	return 1;
}
int Check_Chu(string s)
{
	if (s.length() != 0)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if ((s[i]<'A' || s[i]>'Z') && (s[i]<'a' || s[i]>'z') && s[i] != ' ')
				return 0;
		}
	}
	return 1;
}
int Check_Chu_So(string s)
{
	if (s.length() != 0)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if ((s[i]<'A' || s[i]>'Z') && (s[i]<'a' || s[i]>'z') && s[i] != ' ' && (s[i]<'0' || s[i]>'9') && s[i] != '+' && s[i] != '#')
				return 0;
		}
	}
	return 1;
}
string Sua_Ten_Chuoi(string s)
{
	if (s.length() != 0) // s co ki tu
	{
		while (s[0] == ' ')
			s.erase(0, 1); //Xoa 1 khoang trang o dau
		while (s[s.length() - 1] == ' ')
			s.erase(s.length() - 1, 1); //Xoa khoang trang o cuoi
		if (s.length() > 3) //Xoa khoang trang thua o giua , vi 4 ki tu tro len moi tao ra 2khoang trang thua`
		{
			for (int i = 1; i < s.length() - 2; i++)
			{
				if (s[i] == ' ' && s[i + 1] == ' ')
				{
					s.erase(i, 1);
					i--;
				}
			}
		}
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
				s[i] += 32; //Chuyen chu hoa thanh chu thuong
		}
		s[0] = s[0] - 32; //Chuyen ki tu dau thanh chu hoa
		for (int i = 1; i < s.length(); i++) // In hoa chu cai dau tien sau moi khoang trang
		{
			if (s[i] == ' ')
			{
				if (s[i + 1] >= 'a' && s[i + 1] <= 'z')
				{
					s[i + 1] -= 32;
					i = i + 1;
				}
			}
		}
	}
	return s;
}
//====DOC GIA====					
// phuc vu viec doc file, tim ma doc gia co trung khong trong qua trinh nhap, tim kiem doc gia							
TreeDocGia Tim_Doc_Gia_Theo_Ma(TreeDocGia root, int madgia)
{
	TreeDocGia p;
	p = root;
	while (p != NULL)
	{
		if (madgia < p->docGia.maDG)
			p = p->left;
		else if (madgia > p->docGia.maDG)
			p = p->right;
		else
			return p;
	}
	return NULL;
}
//===Dem So Luong Doc Gia de ghi file
int So_Luong_Doc_Gia(TreeDocGia p)
{
	TreeDocGia root = p;
	int n = 0;
	const int STACKSIZE = 100;
	TreeDocGia Stack[STACKSIZE];
	int sp = -1;
	do
	{
		while (root != NULL)
		{
			Stack[++sp] = root;
			root = root->left;
		}
		if (sp != -1)
		{
			root = Stack[sp--];
			n++;
			root = root->right;
		}
		else break;
	} while (1);
	return n;
}
//=== Them Sach ma Doc Gia Muon
void Them_Muon_TRa(PTRMuonTra& p, MuonTra s)
{
	PTRMuonTra q = new NodeMuonTra;
	q->muonTra = s;
	q->next = p;
	p = q;
}
void Them_Doc_Gia(TreeDocGia& p, DocGia them)
{
	if (p == NULL)
	{
		p = new NodeDG;
		p->docGia = them;
		p->left = NULL;
		p->right = NULL;
	}
	else if (them.maDG < p->docGia.maDG)
		Them_Doc_Gia(p->left, them);
	else if (them.maDG > p->docGia.maDG)
		Them_Doc_Gia(p->right, them);
	else
		return;
}
//=== Ghi File Doc Gia===
void Ghi_File_Doc_Gia(TreeDocGia p)
{
	TreeDocGia root = p;
	ofstream f("DocGia.txt");
	int n;
	int i = 0;
	n = So_Luong_Doc_Gia(root);
	f << n << endl;
	const int STACKSIZE = 100;
	TreeDocGia Stack[STACKSIZE];
	int sp = -1;
	do
	{
		while (root != NULL)
		{
			Stack[++sp] = root;
			root = root->left;
		}
		if (sp != -1)
		{
			root = Stack[sp--];
			f << root->docGia.maDG << endl;
			f << root->docGia.ho << endl;
			f << root->docGia.ten << endl;
			f << root->docGia.phai << endl;
			f << root->docGia.trangThaiThe << endl;
			f << root->docGia.soSachMuon << endl;
			if (root->docGia.soSachMuon > 0)
			{
				for (PTRMuonTra p = root->docGia.FirstMuonTra; p != NULL; p = p->next)
				{
					f << p->muonTra.maSach << endl;
					f << p->muonTra.trangThaiMuonTraSach << endl;
					f << p->muonTra.ngayMuon.day << endl;
					f << p->muonTra.ngayMuon.month << endl;
					f << p->muonTra.ngayMuon.year << endl;
					f << p->muonTra.ngayTra.day << endl;
					f << p->muonTra.ngayTra.month << endl;
					f << p->muonTra.ngayTra.year << endl;
				}
			}
			root = root->right;
		}
		else break;
	} while (1);
}
//=== Doc File Doc Gia====
void Doc_File_Doc_Gia(TreeDocGia& root)
{
	ifstream fi("DocGia.txt");
	MuonTra t;
	DocGia s;
	int n = 0;
	fi >> n;
	for (int j = 0; j < n; j++)
	{
		fi >> s.maDG;
		fi >> s.ho;
		fi >> s.ten;
		fi >> s.phai;
		fi >> s.trangThaiThe;
		fi >> s.soSachMuon;
		Them_Doc_Gia(root, s);
		TreeDocGia dg = Tim_Doc_Gia_Theo_Ma(root, s.maDG);
		dg->docGia.FirstMuonTra = NULL;
		for (int i = 0; i < s.soSachMuon; i++)
		{
			fi >> t.maSach;
			fi >> t.trangThaiMuonTraSach;
			fi >> t.ngayMuon.day;
			fi >> t.ngayMuon.month;
			fi >> t.ngayMuon.year;
			fi >> t.ngayTra.day;
			fi >> t.ngayTra.month;
			fi >> t.ngayTra.year;
			Them_Muon_TRa(dg->docGia.FirstMuonTra, t);
		}
	}
	fi.close();
}
// kiem tra loi phat sinh khi nhap doc gia
int Kiem_Tra_Loi_Doc_Gia(string& s, int k, TreeDocGia root)   // K: fill nhap tuong ung trong table nhap doc gia
{
	if (k == 2 || k == 3)
	{
		if (Check_Chu(s) != 1)
			return kiTuDocGia;
	}
	string Nam = "NAM";
	string Nu = "NU";
	char temp[31];
	strcpy(temp, s.c_str());  // chuyen string thanh char
	switch (k)
	{
	case 1:		//Nhap Ma Doc Gia
	{
		if (s == "")
			return maDGBB;
		if (Check_So(s) != 1)
			return maDGSo;
		if (Tim_Doc_Gia_Theo_Ma(root, atoi(temp)) != NULL)
			return maDGBiTrung;
		if (s.length() > 5)
			return maQDai;
		break;
	}
	case 2:		//Nhap Ho Doc Gia
	{
		if (s == "")
			return hoBB;
		else if (s.length() > 10)
			return hoQDai;
		break;
	}
	case 3:			// Nhap Ten Doc Gia
	{
		if (s == "")
			return tenBB;
		else if (s.length() > 10)
			return tenQDai;
		break;
	}
	case 4:			// Nhap Phai
	{
		if (s == "")
			return phaiBB;
		else if (strupr(temp) != Nam && strupr(temp) != Nu)
			return phaiKhopLe;
		break;
	}
	case 5:			// Nhap Trang thai the	
	{
		if (s == "")
			return ttTheBB;
		if (Check_So(s) != 1 || s.length() > 2)
			return ttTheDGSo;
	}
	}
	return 0;
}
//nhap ma doc gia frame tra ve doc gia co ma do
TreeDocGia Nhap_Kiem_Tra_Ma_Doc_Gia(TreeDocGia root)
{
DocGia:
	Button_ESC();
	Frame_Doc_Gia(37, 15);
	int x = 40, y = 15;
	int keybhit, dem;
	string text, field;
	field = "";
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 5, y + 1);
		if (dem < 9)       // chieu dai chuoi <9 xuat het ra
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else			// >9 xuuat tu 9 cho den het
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);  // xoa bo khoang trang thua vua nhap
			}
		}
		else if (keybhit == ENTER)
		{
			if (text == "")   // chuoi rong
			{
				textcolor(15);
				Del_Error();
				keybhit = 0;
				gotoxy(boxx + 25, 29);
				textcolor(15);
				cout << "VUI LONG NHAP MA DOC GIA";
				goto DocGia;
			}
			else
			{
				textcolor(15);
				Del_Error();
				TreeDocGia dg = Tim_Doc_Gia_Theo_Ma(root, atoi((char*)text.c_str()));
				if (dg == NULL)
				{
					gotoxy(boxx + 25, 29);
					textcolor(15);
					cout << "MA DOC GIA KHONG TON TAI";
					goto DocGia;
				}
				else
					return dg;
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			Menu(root, listDauSach);
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}
//======Sua Doc Gia
void Sua_Doc_Gia(TreeDocGia& root)
{
	TreeDocGia dg = Nhap_Kiem_Tra_Ma_Doc_Gia(root);  // nhap ma doc gia can sua
	// thao tac sua
	while (1)
	{
		system("cls");
		Box_Nhap_Doc_Gia();
		Button_OK();
		Button_ESC();
		textcolor(15);
		HighLight();
		gotoxy(35, 2);	cout << "                     ";
		gotoxy(35, 3);	cout << "    NHAP DOC GIA     ";
		gotoxy(35, 4);	cout << "                     ";
		Normal();
		int keybhit, x = 22;
		int demkitu;
		string text, field[5];
		field[0] = "";
		field[1] = "";
		field[2] = "";
		field[3] = "";
		field[4] = "";
		for (int n = 4, k = 2; k < 5; n += 2, k++)
		{
			keybhit = 0;
			demkitu = field[k - 1].length();
			text = field[k - 1];
			Xuat_Chuoi(Chuyen_So_Thanh_Chuoi(dg->docGia.maDG), 2, x);   // ma dg va tt the duoc giu nguyen
			Xuat_Chuoi(Chuyen_So_Thanh_Chuoi(dg->docGia.trangThaiThe), 10, x);
			while (keybhit != ENTER)
			{
				gotoxy(boxx + x, boxy + n);
				if (demkitu < boxs - x)
				{
					cout << text;
					for (int i = 1; i < boxs - x + 1 - demkitu; i++)
						cout << " ";
				}
				if (demkitu < boxs - x)
					gotoxy(boxx + x + demkitu, boxy + n);
				keybhit = getch();
				if (keybhit == 224) // 4phim right left 
				{
					keybhit = getch();
					if (keybhit == UP)
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
						Xuat_Chuoi(text, n, x);
						field[k - 1] = text;
						Del_Error();
						if (k > 2)
						{
							n -= 2;
							k--;
						}
						demkitu = field[k - 1].length();
						text = field[k - 1];
					}
					else if (keybhit == DOWN)
					{
						if (Kiem_Tra_Loi_Doc_Gia(text, k, root) != 0)
						{
							keybhit = 0;
							Loi_Nhap_Doc_Gia(Kiem_Tra_Loi_Doc_Gia(text, k, root));
							Xuat_Chuoi(text, n, x);
						}
						else
						{
							if (k == 2 || k == 3 || k == 4)
								text = Sua_Ten_Chuoi(text);
							Xuat_Chuoi(text, n, x);
							field[k - 1] = text;
							Del_Error();
							if (k < 5)
							{
								n += 2;
								k++;
							}
							demkitu = field[k - 1].length();
							text = field[k - 1];

							if (keybhit == DOWN)
							{
								Xuat_Chuoi(text, n, x);
							}
						}
					}
				}
				else if (keybhit == BACKSPACE)
				{
					if (demkitu > 0)
					{
						demkitu--;
						text = text.substr(0, text.size() - 1);
						Del_Error();
					}
				}
				else if (keybhit == ESC)
				{
					break;
				}
				else if (keybhit == ENTER)
				{
					if (Kiem_Tra_Loi_Doc_Gia(text, k, root) != 0)
					{
						keybhit = 0;
						Loi_Nhap_Doc_Gia(Kiem_Tra_Loi_Doc_Gia(text, k, root));
						Xuat_Chuoi(text, n, x);
						Sleep(500);
					}
					else
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
					}
				}
				else
				{
					demkitu++;
					text += char(keybhit);
					Del_Error();
				}
			}
			if (keybhit == ESC)
			{
				Button_ESC();
				Sleep(500);
				system("cls");
				return;
			}
			Xuat_Chuoi(text, n, x);
			field[k - 1] = text;
			Del_Error();
		}
		if (keybhit == ENTER)
		{
			dg->docGia.maDG = dg->docGia.maDG;
			dg->docGia.ho = field[1];
			dg->docGia.ten = field[2];
			dg->docGia.phai = field[3];
			dg->docGia.trangThaiThe = dg->docGia.trangThaiThe;
			dg->docGia.soSachMuon = dg->docGia.soSachMuon;
			textcolor(15);
			gotoxy(boxx + 20, 29);
			cout << "SUA THANH CONG";
			Button_OK();
			textcolor(15);
			Sleep(500);
			return;
		}
	}
}
//====Xoa Doc Gia
void Remove_case3_DGia(TreeDocGia& r)
{
	TreeDocGia rp;
	if (r->left != NULL)
		Remove_case3_DGia(r->left);   // di chuyen r nut cuc trai cua nhanh phai voi nut goc la rp;
	else
	{
		rp->docGia = r->docGia;
		rp = r;
		r = rp->right;        // chep noi dunng cua r cho rp; de delete rp
	}
}
int Xoa_Node_Doc_Gia(TreeDocGia& root, int maDG)
{
	TreeDocGia rp;
	if (root == NULL) return 0;
	else
	{
		if (maDG < root->docGia.maDG)
			Xoa_Node_Doc_Gia(root->left, maDG);
		else if (maDG > root->docGia.maDG)
			Xoa_Node_Doc_Gia(root->right, maDG);
		else
		{
			rp = root;
			if (rp->right == NULL)  // 1 node con ben trai, hoac nut la
				root = rp->left;
			else if (rp->left == NULL)   // 1 node con ben phai
				root = rp->right;
			else						// 2 node
				Remove_case3_DGia(rp->right);
			delete rp;
		}
	}
	return 1;
}
void Xoa_Doc_Gia(TreeDocGia& root)
{
	while (1)
	{
		TreeDocGia dg = Nhap_Kiem_Tra_Ma_Doc_Gia(root);
		if (dg->docGia.soSachMuon > 0)
		{
			gotoxy(boxx + 25, 29);
			cout << "DOC GIA CHUA TRA SACH";
			Sleep(500);
			return;
		}
		else
		{
			int qq = Xac_Nhan_Xoa();   // 0 k xoa, 1 la xoa, hien cai box
			if (qq == 1)
			{
				if (Xoa_Node_Doc_Gia(root, dg->docGia.maDG) == 1)
				{
					gotoxy(boxx + 28, 29);
					cout << "XOA THANH CONG";
					Sleep(500);
					return;
				}
			}
			else
				return;
		}
	}
}
//=====Tim Doc Gia  
void Giao_Dien_Tim_Doc_Gia(TreeDocGia dg)  // xuat doc gia cân tim ra man hinh
{
	system("cls");
	system("color 0A");
	textcolor(15);
	Table_Doc_Gia();
	int dem = 0;
	Button_ESC();
	textcolor(15);
	gotoxy(13, 7 + dem);	cout << dg->docGia.maDG;
	gotoxy(27, 7 + dem);	cout << dg->docGia.ho;
	gotoxy(45, 7 + dem);	cout << dg->docGia.ten;
	gotoxy(57, 7 + dem);	cout << dg->docGia.phai;
	gotoxy(70, 7 + dem);
	if (dg->docGia.trangThaiThe == binhThuong)
		cout << "BinhThuong";
	else
		cout << "ViPham";
	while (1)
	{
		int c = getch();
		if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
	}
}
void Nhap_Tim_Doc_Gia(TreeDocGia root)
{
	Button_ESC();
	int x = 40, y = 15;  // vi tri xuat frame
	Frame_Doc_Gia(x, y);
	int keybhit, dem;
	string text, field;
	field = "";
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 8, y + 1);
		if (dem < 9)
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		if (dem < 9)
			gotoxy(x + 8 + dem, y + 1);
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);
			}
		}
		else if (keybhit == ENTER)
		{
			if (text == "")
			{
				textcolor(15);
				Del_Error();
				keybhit = 0;
				gotoxy(boxx + 27, 29);
				cout << "VUI LONG NHAP MA DOC GIA";
			}
			else
			{
				textcolor(15);
				Del_Error();
				if (Tim_Doc_Gia_Theo_Ma(root, atoi((char*)text.c_str())) == NULL)
				{
					gotoxy(boxx + 20, 29);
					cout << "MA DOC GIA KHONG TON TAI";
				}
				else
				{
					TreeDocGia dg = Tim_Doc_Gia_Theo_Ma(root, atoi((char*)text.c_str()));
					system("cls");
					Giao_Dien_Tim_Doc_Gia(dg);
					return;
				}
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			return;
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}
//===Nhap Doc Gia====
void Nhap_Doc_Gia(TreeDocGia& root)
{
	DocGia data;
	while (1)
	{
		system("cls");
		HighLight();
		gotoxy(35, 2);	cout << "                     ";
		gotoxy(35, 3);	cout << "    NHAP DOC GIA     ";
		gotoxy(35, 4);	cout << "                     ";
		Normal();
		Box_Nhap_Doc_Gia();
		Button_OK();
		Button_ESC();
		textcolor(15);
		int keybhit, x = 22;
		int demkitu;
		string text, field[5];
		field[0] = "";
		field[1] = "";
		field[2] = "";
		field[3] = "";
		field[4] = "";

		for (int n = 2, k = 1; k < 5; n += 2, k++)
		{
			keybhit = 0;
			demkitu = field[k - 1].length();
			text = field[k - 1];
			string s = "0";
			Xuat_Chuoi(s, 10, x);  // gan tt the cua doc gia moi tao là binh thuong
			while (keybhit != ENTER)
			{
				gotoxy(boxx + x, boxy + n);
				if (demkitu < boxs - x)
				{
					cout << text;
					for (int i = 1; i < boxs - x + 1 - demkitu; i++)
						cout << " ";
				}
				if (demkitu < boxs - x)
					gotoxy(boxx + x + demkitu, boxy + n);
				keybhit = getch();
				if (keybhit == 224)
				{
					keybhit = getch();
					if (keybhit == UP)
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
						Xuat_Chuoi(text, n, x);
						field[k - 1] = text;
						Del_Error();
						if (k > 1)
						{
							n -= 2;
							k--;
						}
						demkitu = field[k - 1].length();
						text = field[k - 1];
					}
					else if (keybhit == DOWN)
					{
						if (Kiem_Tra_Loi_Doc_Gia(text, k, root) != 0)
						{
							keybhit = 0;
							Loi_Nhap_Doc_Gia(Kiem_Tra_Loi_Doc_Gia(text, k, root));
							Xuat_Chuoi(text, n, x);
						}
						else
						{
							if (k == 2 || k == 3 || k == 4)
								text = Sua_Ten_Chuoi(text);
							Xuat_Chuoi(text, n, x);
							field[k - 1] = text;
							Del_Error();
							if (k < 5)
							{
								n += 2;
								k++;
							}
							demkitu = field[k - 1].length();
							text = field[k - 1];

							if (keybhit == DOWN)
							{
								Xuat_Chuoi(text, n, x);
							}
						}
					}
				}
				else if (keybhit == BACKSPACE)
				{
					if (demkitu > 0)
					{
						demkitu--;
						text = text.substr(0, text.size() - 1);
						Del_Error();
					}
				}
				else if (keybhit == ESC)    // thoat khoi vong while nhap ki tu
				{
					break;
				}
				else if (keybhit == ENTER)
				{
					if (Kiem_Tra_Loi_Doc_Gia(text, k, root) != 0)
					{
						keybhit = 0;
						Loi_Nhap_Doc_Gia(Kiem_Tra_Loi_Doc_Gia(text, k, root));
						Xuat_Chuoi(text, n, x);
						Sleep(500);
					}
					else
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
					}
				}
				else
				{
					demkitu++;
					text += char(keybhit);
					Del_Error();
				}
			}
			if (keybhit == ESC) // thoat khoi chuong trinh nhap
			{
				Button_ESC();
				textcolor(15);
				Sleep(500);
				return;
			}
			Xuat_Chuoi(text, n, x);
			field[k - 1] = text;
			Del_Error();
		}
		if (keybhit == ENTER)
		{
			data.maDG = atoi((char*)field[0].c_str());
			data.ho = field[1];
			data.ten = field[2];
			data.phai = field[3];
			data.trangThaiThe = 0;
			data.soSachMuon = 0;
			Them_Doc_Gia(root, data);
			Button_OK();
			textcolor(15);
			Sleep(500);
		}
	}
}

void Chuyen_Cay(TreeDocGia root, DocGia dG[], int sl)
{
	TreeDocGia p = root;
	sl = So_Luong_Doc_Gia(p);
	int i = 0;
	const int STACKSIZE = 100;
	TreeDocGia Stack[STACKSIZE];
	int sp = -1;
	do
	{
		while (p != NULL)
		{
			Stack[++sp] = p;
			p = p->left;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			dG[i++] = p->docGia;
			p = p->right;
		}
		else
			break;
	} while (1);
}
void Xuat_1_Trang_Doc_Gia(int trang, int sl, DocGia dG[])
{
	int j = 7; 	// tab y + 2 hang ve 1 hang muc luc
	for (int i = (trang - 1) * 10; i < sl && i < trang * 10; i++)
	{
		gotoxy(10, j);	cout << dG[i].maDG;
		gotoxy(25, j);	cout << dG[i].ho;
		gotoxy(42, j);	cout << dG[i].ten;
		gotoxy(57, j);	cout << dG[i].phai;
		Date d1;
		Lay_Ngay_He_Thong(d1);
		if (dG[i].soSachMuon == 3)
			dG[i].trangThaiThe = viPham;
		else if (dG[i].soSachMuon > 0)
			for (PTRMuonTra p = dG[i].FirstMuonTra; p != NULL; p = p->next)
			{
				if (Tinh_Ngay(p->muonTra.ngayMuon, d1) >= 15)
				{
					dG[i].trangThaiThe = viPham;
					break;
				}
			}
		if (dG[i].trangThaiThe == binhThuong)
		{
			gotoxy(69, j);	cout << "BinhThuong";
		}
		else if (dG[i].trangThaiThe == viPham)
		{
			gotoxy(69, j);	cout << "ViPham";
		}
		j = j + 2;
	}
}
void Xoa_Du_Lieu_Table_DG()
{
	int j = 7;
	for (int i = 0; i < 10; i++)
	{
		gotoxy(10, j);	cout << "      ";
		gotoxy(25, j);	cout << "         ";
		gotoxy(42, j);	cout << "         ";
		gotoxy(57, j);	cout << "      ";
		gotoxy(69, j);	cout << "            ";
		j += 2;
	}
}
//==Xuat Danh Sach Doc Gia
void Xuat_Danh_Sach_Doc_Gia(TreeDocGia root)
{
Xuat:				// nhan cap nhat lai ds moi khi thuc hien them xoa sua
	TreeDocGia p = root;
	int sl = So_Luong_Doc_Gia(p);
	DocGia dG[sl];
	Chuyen_Cay(p, dG, sl);
	system("cls");
	system("color 0A");
	int trang = 1;
	int tongTrang = 0;
	if (sl % 10 != 0)
		tongTrang = sl / 10 + 1;
	else
		tongTrang = sl / 10;
	Table_Doc_Gia();
	Button_Sreach();
	Button_ESC();
	Button_Them();
	Button_Xoa();
	Button_Sua();
	textcolor(15);
	Xoa_Du_Lieu_Table_DG();
	Xuat_1_Trang_Doc_Gia(trang, sl, dG);
	int c = 0;
	while (c != ESC)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DG();
			Xuat_1_Trang_Doc_Gia(trang, sl, dG);
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
		else if (c == F1)
		{
			Button_Them();
			Sleep(500);
			Nhap_Doc_Gia(root);
			goto Xuat;
		}
		else if (c == F2)
		{
			Button_Xoa();
			Sleep(500);
			Xoa_Doc_Gia(root);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
		else if (c == F3)
		{
			Button_Sua();
			Sleep(500);
			Sua_Doc_Gia(root);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
		else if (c == F4)
		{
			Button_Sreach();
			Sleep(500);
			Nhap_Tim_Doc_Gia(root);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
	}
}
//===DAU SACH=== 					
//tim ra vi tri cua dau sach, them xoa sua nhap
int Tim_Kiem_Dau_Sach(ListDauSach list, string isbn)
{
	for (int i = 0; i < list.soDauSach; i++)
		if (So_Sanh_Chuoi(list.sach[i].ISBN, isbn) == 1)
			return i;
	return -1;
}
// tra ve muc sach cua dau sach
PTRDanhMucSach Tim_Kiem_Sach(ListDauSach& list, int maSach)
{
	for (int i = 0; i < list.soDauSach; i++)
		for (PTRDanhMucSach p = list.sach[i].FirstDanhMucSach; p != NULL; p = p->next)
			if (p->mucSach.maSach == maSach)
				return p;
	return NULL;
}

void Them_Dau_Sach(ListDauSach& list, DauSach s)
{
	if (list.soDauSach > MaxDauSach)
		return;
	list.sach[list.soDauSach] = s; // them cuoi danh sach
}
//===Them Danh Muc Sach
void Them_Danh_Muc_Sach(PTRDanhMucSach& p, MucSach s)
{
	PTRDanhMucSach q = new NodeDanhMucSach;
	q->mucSach = s;
	q->next = NULL;

	if (p == NULL) p = q;
	else {
		q->next = p;
		p = q;
	}
}
// === Ghi File Dau Sach ===
void Ghi_File_Dau_Sach(ListDauSach& list)
{
	ofstream f("DauSach.txt");
	f << list.soDauSach << endl;
	for (int i = 0; i < list.soDauSach; i++)
	{
		f << list.sach[i].ISBN << endl;
		f << list.sach[i].tenSach << endl;
		f << list.sach[i].tacGia << endl;
		f << list.sach[i].theLoai << endl;
		f << list.sach[i].soTrang << endl;
		f << list.sach[i].namXuatBan << endl;
		f << list.sach[i].soLanMuon << endl;
		f << list.sach[i].soSach << endl;
		for (PTRDanhMucSach p = list.sach[i].FirstDanhMucSach; p != NULL; p = p->next)
		{
			f << p->mucSach.maSach << endl;
			f << p->mucSach.trangThaiSach << endl;
			f << p->mucSach.viTri << endl;
		}
	}
	f.close();
}
//=== Doc File Dau Sach ===
void Doc_File_Dau_Sach(ListDauSach& list)
{
	ifstream fi("DauSach.txt");
	int soLuongDauSach = 0;
	fi >> soLuongDauSach;
	fi.ignore();
	MucSach s;
	DauSach d;
	for (int i = 0; i < soLuongDauSach; i++)
	{
		getline(fi, d.ISBN);
		getline(fi, d.tenSach);
		getline(fi, d.tacGia);
		getline(fi, d.theLoai);
		fi >> d.soTrang;
		fi >> d.namXuatBan;
		fi >> d.soLanMuon;
		fi >> d.soSach;
		d.FirstDanhMucSach = NULL;
		fi.ignore();
		Them_Dau_Sach(list, d);
		for (int j = 0; j < d.soSach; j++)
		{

			fi >> s.maSach;
			fi.ignore();
			fi >> s.trangThaiSach;
			fi.ignore();
			getline(fi, s.viTri);
			Them_Danh_Muc_Sach(list.sach[list.soDauSach].FirstDanhMucSach, s);
		}
		list.soDauSach++;
	}
	fi.close();
}

int Kiem_Tra_Loi_Dau_Sach(string& s, int k, ListDauSach list)
{
	switch (k)
	{
	case 1: 			// nhap ISBN
	{
		if (s == "")
			return maISBN;
		if (Check_So(s) != 1)
			return maISBNSo;
		if (Tim_Kiem_Dau_Sach(list, s) != -1)
			return maDSTrung;
		break;
	}
	case 2: 			// Nhap Ten Sach
	{
		if (s == "")
			return tenSach;
		if (Check_Chu_So(s) != 1)
			return kiTuKhongHopLe;
		if (s.length() > 10)
			return QuaDai;
		break;
	}
	case 3:				// Nhap Tac Gia
	{
		if (s == "")
			return tenTacGia;
		if (Check_Chu(s) != 1)
			return kiTuKhongHopLe;
		if (s.length() > 10)
			return QuaDai;
		break;
	}
	case 4:				// Nhap The Loai
	{
		if (s == "")
			return theLoaiBB;
		if (Check_Chu(s) != 1)
			return kiTuKhongHopLe;
		if (s.length() > 10)
			return QuaDai;
		break;
	}
	case 5:			//Nhap So Trang
	{
		if (s == "")
			return soTrangBB;
		if (Check_So(s) != 1)
			return soTrangSo;
		break;
	}
	case 6:				// Nhap Nam Xuat Ban
	{
		if (s == "")
			return namXBanBB;
		if (Check_So(s) != 1)
			return namXBanSo;
		if (atoi((char*)s.c_str()) > 2017 || atoi((char*)s.c_str()) < 1800)
			return namXBanSai;
	}
	}
	return 0;
}
// tim sach qua ten
int Tim_Kiem_Ten_Sach(ListDauSach& list, string tenSach)
{
	for (int i = 0; i < list.soDauSach; i++)
	{
		if (list.sach[i].tenSach.find(tenSach) != -1) // find ==-1 k tim thay
			return i;
	}
	return -1;
}
//=== check dau sach dung de sua dau sach===
int Kiem_Tra_Dau_Sach(ListDauSach list)  // nhap vao ma tim ra vi tri dau sach
{
	Button_ESC();
	int x = 40, y = 15;
	Frame_Dau_Sach(x, y);
	int keybhit, dem;
	string text, field;
	field = "";
	char temp[10];
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 8, y + 1);
		if (dem < 9)
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		if (dem < 9)
			gotoxy(x + 8 + dem, y + 1);
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);
			}
		}
		else if (keybhit == ENTER)
		{
			if (text == "")
			{
				textcolor(15);
				Del_Error();
				keybhit = 0;
				gotoxy(boxx + 20, 29);
				cout << "VUI LONG NHAP MA ISBN";
			}
			else
			{
				textcolor(15);
				Del_Error();
				strcpy(temp, text.c_str());
				if (Tim_Kiem_Dau_Sach(list, temp) == -1)
				{
					gotoxy(boxx + 20, 29);
					cout << "MA ISBN KHONG TON TAI";
				}
				else
				{
					Button_OK();
					Sleep(500);
					return Tim_Kiem_Dau_Sach(list, temp);  // tra ve vi tri dau sach
				}
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			return -1;
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}
//===Sua Dau Sach
void Sua_Dau_Sach(ListDauSach& list)
{
	int vitri = Kiem_Tra_Dau_Sach(list);
	DauSach data;
	while (1)
	{
		system("color 0A");
		system("cls");
		Box_Nhap_Dau_Sach();
		Button_OK();
		Button_ESC();
		textcolor(15);
		gotoxy(10, 5); cout << " NHAP DAU SACH ";
		int keybhit, x = 22;
		int demkitu;
		string text, field[6];
		field[0] = "";
		field[1] = "";
		field[2] = "";
		field[3] = "";
		field[4] = "";
		field[5] = "";

		for (int y = 4, k = 2; k < 7; y += 2, k++)
		{
			keybhit = 0;
			demkitu = field[k - 1].length();
			text = field[k - 1];
			Xuat_Chuoi(list.sach[vitri].ISBN, 2, x);
			while (keybhit != ENTER)
			{
				gotoxy(boxx + x, boxy + y);
				if (demkitu < boxs - x)
				{
					cout << text;
					for (int i = 1; i < boxs - x + 1 - demkitu; i++)
						cout << " ";
				}
				if (demkitu < boxs - x)
					gotoxy(boxx + x + demkitu, boxy + y);
				keybhit = getch();
				if (keybhit == 224)
				{
					keybhit = getch();
					if (keybhit == UP)
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
						Xuat_Chuoi(text, y, x);
						field[k - 1] = text;
						Del_Error();
						if (k > 2)
						{
							y -= 2;
							k--;
						}
						demkitu = field[k - 1].length();
						text = field[k - 1];
					}
					else if (keybhit == DOWN)
					{
						keybhit = 0;
						int loi = Kiem_Tra_Loi_Dau_Sach(text, k, list);
						if (loi != 0)
						{
							keybhit = 0;
							Loi_Nhap_Doc_Gia(loi);
							Xuat_Chuoi(text, y, x);
						}
						else
						{
							if (k == 2 || k == 3 || k == 4)
								text = Sua_Ten_Chuoi(text);
							Xuat_Chuoi(text, y, x);
							field[k - 1] = text;
							Del_Error();
							if (k < 6)
							{
								y += 2;
								k++;
							}
							demkitu = field[k - 1].length();
							text = field[k - 1];
							if (keybhit == DOWN)
							{
								Xuat_Chuoi(text, y, x);
							}
						}
					}
				}
				else if (keybhit == BACKSPACE)
				{
					if (demkitu > 0)
					{
						demkitu--;
						text = text.substr(0, text.size() - 1);
						Del_Error();
					}
				}
				else if (keybhit == ESC)
				{
					break;
				}
				else if (keybhit == ENTER)
				{
					int loi = Kiem_Tra_Loi_Dau_Sach(text, k, list);
					if (loi != 0)
					{
						keybhit = 0;
						Loi_Nhap_Doc_Gia(loi);
						Xuat_Chuoi(text, y, x);
					}
					else
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
					}
				}
				else
				{
					demkitu++;
					text += char(keybhit);
					Del_Error();
				}
			}
			if (keybhit == ESC)
			{
				Button_ESC();
				textcolor(15);
				Sleep(500);
				return;
			}
			Xuat_Chuoi(text, y, x);
			field[k - 1] = text;
			Del_Error();
		}
		if (keybhit == ENTER)
		{
			Button_OK();
			textcolor(15);
			list.sach[vitri].ISBN = list.sach[vitri].ISBN;
			list.sach[vitri].tenSach = field[1];
			list.sach[vitri].tacGia = field[2];
			list.sach[vitri].theLoai = field[3];
			list.sach[vitri].soTrang = atoi((char*)field[4].c_str());
			list.sach[vitri].namXuatBan = atoi((char*)field[5].c_str());
			list.sach[vitri].soSach = list.sach[vitri].soSach;
			gotoxy(boxx + 25, 29); cout << "SUA THANH CONG";
			Sleep(500);
			system("cls");
			return;
		}
	}
}
//=====Xoa Sach
// nhap ma can xoa kiem tra tinh hop le cua ma, tra ve ma sach can
int Kiem_Tra_Sach(ListDauSach list)
{
	Button_ESC();
	int x = 40, y = 15;
	Frame_Muc_Sach(x, y);
	int keybhit, dem;
	string text, field;
	field = "";
	char temp[10];
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 8, y + 1);
		if (dem < 9)
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		if (dem < 9)
			gotoxy(x + 8 + dem, y + 1);
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);
			}
		}
		else if (keybhit == ENTER)
		{
			if (text == "")
			{
				textcolor(15);
				Del_Error();
				keybhit = 0;
				gotoxy(boxx + 20, 29);
				cout << "VUI LONG NHAP MA SACH";
			}
			else
			{
				textcolor(15);
				Del_Error();
				PTRDanhMucSach p = Tim_Kiem_Sach(list, atoi((char*)text.c_str()));
				if (p == NULL)
				{
					gotoxy(boxx + 20, 29);
					cout << "MA SACH KHONG TON TAI";
					return -1;
				}
				else
					return p->mucSach.maSach;
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			return -1;
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}
// Xoa muc sach theo ma sach
int Xoa_Sach_Trong_DMS(PTRDanhMucSach& mSach, int ma)
{
	if (mSach == NULL)
		return 0;
	PTRDanhMucSach p = Tim_Kiem_Sach(listDauSach, ma);
	if (p == NULL)
		return 0;
	if (p == mSach)
	{
		p = mSach;
		mSach = p->next;
		delete p;
		return 1;
	}
	else
	{
		PTRDanhMucSach q = mSach;
		while (q->next != p)
			q = q->next;
		p = q->next;
		q->next = p->next;
		delete p;
		return 1;
	}
	return 0;
}
void Xoa_Sach(ListDauSach& list)   // xóa sach trong dau sach
{
	int ma = Kiem_Tra_Sach(list);   // nhap ma can xoa kiem tra tinh hop le cua ma
	if (ma == -1)   // truong hop nay chi xra khi nhan esc trong qua trinh nhap tim ma
		return;
	for (int i = 0; i < list.soDauSach; i++)
	{
		for (PTRDanhMucSach p = list.sach[i].FirstDanhMucSach; p != NULL; p = p->next)
		{
			if (p->mucSach.maSach == ma)
			{
				if (p->mucSach.trangThaiSach == daMuon)
				{
					gotoxy(boxx + 25, 29);
					cout << "SACH DANG DUOC MUON";
					Sleep(500);
				}
				else
				{
					int qq = Xac_Nhan_Xoa();
					if (qq == 1)
					{
						if (Xoa_Sach_Trong_DMS(list.sach[i].FirstDanhMucSach, ma) == 1)
						{
							list.sach[i].soSach--;
							gotoxy(boxx + 32, 29);
							cout << "XOA THANH CONG";
							Sleep(500);
						}
					}
				}
			}
		}
	}
}
//===Tim Max cua ma sach de sinh so ngau nhien
int Max_Muc_Sach(ListDauSach list)
{
	int max = 0;
	PTRDanhMucSach p;
	for (int i = 0; i < list.soDauSach; i++)
	{
		p = list.sach[i].FirstDanhMucSach;
		while (p != NULL)
		{
			if (p->mucSach.maSach > max)
				max = p->mucSach.maSach;
			p = p->next;
		}
	}
	return max;
}
//==== Nhap Danh Muc Sach cua tung dau sach
void Nhap_Danh_Muc_Sach(PTRDanhMucSach& mSach, int a)
{
	MucSach data;
	while (1)
	{
		system("cls");
		system("color 0A");
		HighLight();
		gotoxy(35, 2);	cout << "                     ";
		gotoxy(35, 3);	cout << "    DANH MUC SACH    ";
		gotoxy(35, 4);	cout << "                     ";
		Normal();
		Box_Nhap_Danh_Muc_Sach();
		Button_OK();
		Button_ESC();
		textcolor(15);
		int keybhit, x = 22;
		int demkitu;
		string text, field[4];
		field[0] = "";
		field[1] = "";
		field[2] = "";
		for (int y = 6, k = 3; k < 4; y += 2, k++)
		{
			string s = Chuyen_So_Thanh_Chuoi(a);
			Xuat_Chuoi(s, 2, x);
			string s1 = "0";  // cai dat trang thai mac dinh cua sach la 0, cho muon duoc
			Xuat_Chuoi(s1, 4, x);
			keybhit = 0;
			demkitu = field[k - 1].length();
			text = field[k - 1];
			while (keybhit != ENTER)
			{
				gotoxy(boxx + x, boxy + y);
				if (demkitu < boxs - x)
				{
					cout << text;
					for (int i = 1; i < boxs - x + 1 - demkitu; i++)
						cout << " ";
				}
				keybhit = getch();
				if (keybhit == BACKSPACE)
				{
					if (demkitu > 0)
					{
						demkitu--;
						text = text.substr(0, text.size() - 1);
						Del_Error();
					}
				}
				else if (keybhit == ESC)
				{
					break;
				}
				else
				{
					demkitu++;
					text += char(keybhit);
					Del_Error();
				}
			}
			if (keybhit == ESC)
			{
				Button_ESC();
				textcolor(15);
				Sleep(500);
				system("cls");
				return;
			}
			Xuat_Chuoi(text, y, x);
			field[k - 1] = text;
			Del_Error();
		}
		if (keybhit == ENTER)
		{
			Button_OK();
			textcolor(15);
			data.maSach = a;
			data.trangThaiSach = 0;
			data.viTri = field[2];
			Them_Danh_Muc_Sach(mSach, data);
			gotoxy(boxx + 22, 29);
			cout << "THEM SACH THANH CONG";
			Sleep(500);
			break;
		}
	}
}
//===Nhap Dau Sach ====
void Nhap_Dau_Sach(ListDauSach& list)
{
	DauSach data;
	int masach = 0;
	while (1)
	{
		system("cls");
		HighLight();
		gotoxy(35, 2);	cout << "                     ";
		gotoxy(35, 3);	cout << "    NHAP DAU SACH    ";
		gotoxy(35, 4);	cout << "                     ";
		Normal();
		Box_Nhap_Dau_Sach();
		Button_OK();
		Button_ESC();
		textcolor(15);
		int keybhit, x = 22;
		int demkitu;
		string text, field[6];
		field[0] = "";
		field[1] = "";
		field[2] = "";
		field[3] = "";
		field[4] = "";
		field[5] = "";
		for (int y = 2, k = 1; k < 7; y += 2, k++)
		{
			keybhit = 0;
			demkitu = field[k - 1].length();
			text = field[k - 1];
			while (keybhit != ENTER)
			{
				gotoxy(boxx + x, boxy + y);
				if (demkitu < boxs - x)
				{
					cout << text;
					for (int i = 1; i < boxs - x + 1 - demkitu; i++)
						cout << " ";
				}
				if (demkitu < boxs - x)
					gotoxy(boxx + x + demkitu, boxy + y);
				keybhit = getch();
				if (keybhit == 224)
				{
					keybhit = getch();
					if (keybhit == UP)
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
						Xuat_Chuoi(text, y, x);
						field[k - 1] = text;
						Del_Error();
						if (k > 1)
						{
							y -= 2;
							k--;
						}
						demkitu = field[k - 1].length();
						text = field[k - 1];
					}
					else if (keybhit == DOWN)
					{
						keybhit = 0;
						int loi = Kiem_Tra_Loi_Dau_Sach(text, k, list);
						if (loi != 0)
						{
							keybhit = 0;
							Loi_Nhap_Dau_Sach(loi);
							Xuat_Chuoi(text, y, x);
						}
						else
						{
							if (k == 2 || k == 3 || k == 4)
								text = Sua_Ten_Chuoi(text);
							Xuat_Chuoi(text, y, x);
							field[k - 1] = text;
							Del_Error();
							if (k < 6)
							{
								y += 2;
								k++;
							}
							demkitu = field[k - 1].length();
							text = field[k - 1];

							if (keybhit == DOWN)
							{
								Xuat_Chuoi(text, y, x);
							}
						}
					}
				}
				else if (keybhit == BACKSPACE)
				{
					if (demkitu > 0)
					{
						demkitu--;
						text = text.substr(0, text.size() - 1);
						Del_Error();
					}
				}
				else if (keybhit == ESC)
				{
					system("cls");
					break;
				}
				else if (keybhit == ENTER)
				{
					int loi = Kiem_Tra_Loi_Dau_Sach(text, k, list);
					if (loi != 0)
					{
						keybhit = 0;
						Loi_Nhap_Dau_Sach(loi);
						Xuat_Chuoi(text, y, x);
					}
					else
					{
						if (k == 2 || k == 3 || k == 4)
							text = Sua_Ten_Chuoi(text);
					}
				}
				else
				{
					demkitu++;
					text += char(keybhit);
					Del_Error();
				}
			}
			if (keybhit == ESC)
			{
				system("cls");
				return;
			}
			Xuat_Chuoi(text, y, x);
			field[k - 1] = text;
			Del_Error();
		}
		if (keybhit == ENTER)
		{
			Button_OK();
			textcolor(15);
			data.ISBN = field[0];
			data.tenSach = field[1];
			data.tacGia = field[2];
			data.theLoai = field[3];
			data.soTrang = atoi((char*)field[4].c_str());
			data.namXuatBan = atoi((char*)field[5].c_str());
			data.soSach = 0;
			data.soLanMuon = 0;
			Them_Dau_Sach(list, data);     // so dau sach da tang
			masach = Max_Muc_Sach(list) + 1; // sinh ma cho sach trong muc sach moi tao	
			Nhap_Danh_Muc_Sach(list.sach[list.soDauSach].FirstDanhMucSach, masach);
			list.sach[list.soDauSach].soSach++;
			list.soDauSach++;
		}
	}
}
int Xoa_Dau_Sach(ListDauSach& list, string ma)
{
	if (list.soDauSach == 0)
		return -1;
	int xoa = 0;
	for (int i = 0; i < list.soDauSach; i++)
	{
		if (So_Sanh_Chuoi(list.sach[i].ISBN, ma) == 1)
			xoa = i;
	}
	for (int i = xoa; i < list.soDauSach - 1; i++)
		list.sach[i] = list.sach[i + 1];
	list.soDauSach--;
	return 1;
}
void Giao_Dien_Xoa_Dau_Sach(ListDauSach& list)
{
	int a = Kiem_Tra_Dau_Sach(list);  //nhap roi tra ve vi tri dau sach
	if (a == -1)
		return;
	PTRDanhMucSach p = list.sach[a].FirstDanhMucSach;
	while (p != NULL)  // dau sach co sach dang muon khong duoc xoa
	{
		if (p->mucSach.trangThaiSach == daMuon)
		{
			gotoxy(boxx + 25, 29);
			cout << "DAU SACH CO SACH DANG DUOC MUON. XOA KHONG THANH CONG";
			sleep(1);
			return;
		}
		p = p->next;
	}
	int qq = Xac_Nhan_Xoa();
	if (qq == 1)
	{
		Xoa_Dau_Sach(list, list.sach[a].ISBN);
	}
}
//==== Xuat Dau Sach
void Xuat_1_Trang_Dau_Sach(ListDauSach list, int trang)
{
	int i = 7;
	for (int j = (trang - 1) * 10; j < list.soDauSach && j < trang * 10; j++) // 10 : so luong sach xuat tren 1 trang
	{
		gotoxy(3 + tabx, i); 	  cout << list.sach[j].ISBN;
		gotoxy(15 + tabx, i); 	cout << list.sach[j].tenSach;
		gotoxy(34 + tabx, i); 	cout << list.sach[j].tacGia;
		gotoxy(48 + tabx, i); 	cout << list.sach[j].theLoai;
		gotoxy(60 + tabx, i); 	cout << list.sach[j].soTrang;
		gotoxy(72 + tabx, i); 	cout << list.sach[j].namXuatBan;
		gotoxy(85 + tabx, i);	cout << list.sach[j].soLanMuon;
		i = i + 2;
	}
}
void Xoa_Du_Lieu_Table_DS()
{
	int j = 7;
	for (int i = 0; i < 10; i++)
	{
		gotoxy(3 + tabx, j); 	cout << "       ";
		gotoxy(15 + tabx, j);	cout << "          ";
		gotoxy(34 + tabx, j);	cout << "          ";
		gotoxy(48 + tabx, j);	cout << "          ";
		gotoxy(60 + tabx, j);	cout << "       ";
		gotoxy(72 + tabx, j);	cout << "         ";
		gotoxy(85 + tabx, j);	cout << "      ";
		j = j + 2;
	}
}
void Xuat_Dau_Sach(ListDauSach& list)
{
Xuat:
	system("cls");
	textcolor(15);
	int trang = 1;
	int tongTrang = 0;
	if (list.soDauSach % 10 != 0)
		tongTrang = list.soDauSach / 10 + 1;
	else
		tongTrang = list.soDauSach / 10;
	Table_Dau_Sach();
	Button_ESC();
	Button_Them();
	Button_Xoa();
	Button_Sua();
	textcolor(15);
	Xoa_Du_Lieu_Table_DS();
	Xuat_1_Trang_Dau_Sach(list, trang);
	int c = 0;
	while (c != ESC)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DS();
			Xuat_1_Trang_Dau_Sach(list, trang);
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}

		else if (c == F1)
		{
			Button_Them();
			Sleep(500);
			Nhap_Dau_Sach(list);
			goto Xuat;
		}
		else if (c == F2)
		{
			Button_Xoa();
			Sleep(500);
			Giao_Dien_Xoa_Dau_Sach(list);
			goto Xuat;
		}
		else if (c == F3)
		{
			Button_Sua();
			Sleep(500);
			Sua_Dau_Sach(list);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
	}
}
void Sap_Xep_DS_ISBN(ListDauSach& list)
{
	for (int i = 0; i < list.soDauSach - 1; i++)
	{
		for (int j = i + 1; j < list.soDauSach; j++)
		{
			if (list.sach[j].ISBN.length() == list.sach[i].ISBN.length())
			{
				if (strcmp(list.sach[j].ISBN.c_str(), list.sach[i].ISBN.c_str()) < 0)
				{
					DauSach temp;
					temp = list.sach[j];
					list.sach[j] = list.sach[i];
					list.sach[i] = temp;
				}
			}
			if (list.sach[j].ISBN.length() < list.sach[i].ISBN.length())
			{
				DauSach temp;
				temp = list.sach[j];
				list.sach[j] = list.sach[i];
				list.sach[i] = temp;
			}
		}
	}
}
void Sap_Xep_DS_Ten(ListDauSach& list)
{
	for (int i = 0; i < list.soDauSach - 1; i++)
	{
		for (int j = i + 1; j < list.soDauSach; j++)
		{
			if (strcmp(list.sach[j].tenSach.c_str(), list.sach[i].tenSach.c_str()) < 0)
			{
				DauSach temp;
				temp = list.sach[j];
				list.sach[j] = list.sach[i];
				list.sach[i] = temp;
			}
		}
	}
}
//==== Tim Sach
// xuat so muc sach cua dau sach
void Giao_Dien_Tim_Sach(int vitri, ListDauSach list)
{

Xuat:
	system("cls");
	textcolor(15);
	Table_Danh_Sach_Sach();
	int dem = 0;
	Button_ESC();
	for (int i = 0; i < list.soDauSach; i++)
	{
		if (list.sach[i].tenSach == list.sach[vitri].tenSach)
		{
			for (PTRDanhMucSach p = list.sach[i].FirstDanhMucSach; p != NULL; p = p->next)
			{
				gotoxy(3 + tabx, 7 + dem); cout << list.sach[i].ISBN;
				gotoxy(15 + tabx, 7 + dem);	cout << p->mucSach.maSach;
				gotoxy(30 + tabx, 7 + dem);	cout << list.sach[i].tenSach;
				gotoxy(55 + tabx, 7 + dem);	cout << p->mucSach.trangThaiSach;
				gotoxy(67 + tabx, 7 + dem);	cout << p->mucSach.viTri;
				dem++;
			}
		}
	}
	while (1)
	{
		int c = getch();
		if (c == 27)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
	}
}
void Tim_Sach(ListDauSach list)
{
	Button_ESC();
	int x = 40, y = 15;
	Frame_Ten_Sach(x, y);
	int keybhit, dem;
	string text, field;
	field = "";
	char temp[10];
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 8, y + 1);
		if (dem < 9)
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);
			}
		}
		else if (keybhit == ENTER)
		{
			if (text == "")
			{
				textcolor(15);
				Del_Error();
				keybhit = 0;
				gotoxy(boxx + 27, 29);
				cout << "VUI LONG NHAP TEN SACH";
			}
			else
			{
				textcolor(15);
				Del_Error();
				text = Sua_Ten_Chuoi(text);
				if (Tim_Kiem_Ten_Sach(list, text) == -1)
				{
					gotoxy(boxx + 20, 29);
					cout << "TEN SACH KHONG TON TAI";
				}
				else
				{
					int vitri = Tim_Kiem_Ten_Sach(list, text);
					system("cls");
					Giao_Dien_Tim_Sach(vitri, list);
					return;
				}
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			return;
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}
//=== Xuat Danh Sach Sach
void Xuat_1_Trang_DSS(ListDauSach list, int trang)
{
	int dem = 0;
	for (int i = (trang - 1) * 10; i < list.soDauSach; i++)
	{
		if (dem < 20)
		{
			PTRDanhMucSach p = list.sach[i].FirstDanhMucSach;
			while (p != NULL)
			{
				gotoxy(3 + tabx, 7 + dem); cout << list.sach[i].ISBN;
				gotoxy(15 + tabx, 7 + dem);	cout << p->mucSach.maSach;
				gotoxy(30 + tabx, 7 + dem);	cout << list.sach[i].tenSach;
				gotoxy(55 + tabx, 7 + dem);	cout << p->mucSach.trangThaiSach;
				gotoxy(67 + tabx, 7 + dem);	cout << p->mucSach.viTri;
				dem++;
				p = p->next;
			}
		}
		if (dem == 20)
			return;
	}
}
void Xoa_Du_Lieu_Table_DSS()
{
	int j = 7;
	for (int i = 0; i < 20; i++)
	{
		gotoxy(3 + tabx, j);	cout << "       ";
		gotoxy(15 + tabx, j);	cout << "       ";
		gotoxy(30 + tabx, j);	cout << "        ";
		gotoxy(55 + tabx, j);	cout << "      ";
		gotoxy(67 + tabx, j);	cout << "    ";
		j++;
	}
}
void Xuat_Danh_Sach_Sach(ListDauSach& list)
{
	//sap xep dau sach theo ten
	int soSach = 0;
	for (int i = 0; i < list.soDauSach; i++)
	{
		PTRDanhMucSach p = list.sach[i].FirstDanhMucSach;
		while (p != NULL)
		{
			soSach++;
			p = p->next;
		}
	}
Xuat:

	system("cls");
	textcolor(15);
	int trang = 1;
	int tongTrang = 0;
	if (soSach % 20 != 0)
		tongTrang = soSach / 20 + 1;
	else
		tongTrang = soSach / 20;
	Table_Danh_Sach_Sach();
	Button_Sreach();
	Button_ESC();
	Button_Them();
	Button_Xoa();
	Xoa_Du_Lieu_Table_DSS();
	Xuat_1_Trang_DSS(list, trang);
	textcolor(15);
	int c = 0;
	while (1)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DSS();
			Xuat_1_Trang_DSS(list, trang);
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
		else if (c == F1)
		{
			Button_Them();
			Sleep(500);
			int a = Kiem_Tra_Dau_Sach(list);
			if (a == -1)
				return;
			int maSach = Max_Muc_Sach(list) + 1;
			Sleep(500);
			Nhap_Danh_Muc_Sach(list.sach[a].FirstDanhMucSach, maSach);
			list.sach[a].soSach++;
			goto Xuat;
		}
		else if (c == F2)
		{
			Button_Xoa();
			Sleep(500);
			Xoa_Sach(list);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
		else if (c == F4)
		{
			Button_Sreach();
			Sleep(500);
			Tim_Sach(list);
			textcolor(15);
			system("cls");
			goto Xuat;
		}
	}
}
//===== Muon Sach ====
TreeDocGia Nhap_Doc_Gia_Muon(TreeDocGia& r)
{
	TreeDocGia root = r;
CheckMaDG:
	Button_ESC();
	Frame_Doc_Gia(37, 15);
	int x = 40, y = 15;
	int keybhit, dem;
	Date d1;
	string text, field;
	field = "";
	keybhit = 0;
	dem = field.length();
	text = field;
	while (1)
	{
		gotoxy(x + 5, y + 1);
		if (dem < 9)
		{
			cout << text;
			for (int i = 1; i < 11 - dem; i++)
				cout << " ";
		}
		else
		{
			for (int i = dem - 9; i < dem; i++)
				cout << text[i];
		}
		if (dem < 9)
			gotoxy(x + 5 + dem, y + 1);
		keybhit = getch();
		if (keybhit == BACKSPACE)
		{
			if (dem > 0)
			{
				dem--;
				text = text.substr(0, text.size() - 1);
			}
		}
		else if (keybhit == ENTER)
		{
			textcolor(15);
			Del_Error();
			TreeDocGia dg = Tim_Doc_Gia_Theo_Ma(root, atoi((char*)text.c_str()));
			if (dg == NULL)
			{
				gotoxy(boxx + 25, 29);
				cout << "MA DOC GIA KHONG TON TAI";
			}
			else
			{
				Lay_Ngay_He_Thong(d1);
				if (dg->docGia.soSachMuon >= 3)
				{
					gotoxy(boxx + 20, 29);
					dg->docGia.trangThaiThe = viPham;
					cout << "DOC GIA DA MUON SACH QUA 3 CUON !!";
					Sleep(500);
					goto CheckMaDG;
				}
				else if (dg->docGia.trangThaiThe == viPham)
				{
					gotoxy(boxx + 23, 29);
					cout << "THE DOC GIA DA VI PHAM !!";
					Sleep(500);
				}
				for (PTRMuonTra p = dg->docGia.FirstMuonTra; p != NULL; p = p->next)
				{
					if (Tinh_Ngay(p->muonTra.ngayMuon, d1) > 15)
					{
						gotoxy(boxx + 21, 29);
						cout << "DOC GIA MUON SACH QUA 15 NGAY !!";
						Sleep(500);
						goto CheckMaDG;
					}
					if (p->muonTra.trangThaiMuonTraSach == lamMatSach)
						dg->docGia.trangThaiThe = viPham;
				}
				return 	dg;
			}
		}
		else if (keybhit == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			Menu(root, listDauSach);
		}
		else
		{
			dem++;
			text += (char)keybhit;
			Del_Error();
		}
	}
}

void Muon_Sach(TreeDocGia& r, ListDauSach& list)
{
	TreeDocGia root = r;
	TreeDocGia dg = Nhap_Doc_Gia_Muon(root);// kiem tra doc gia co vi pham k truoc khi cho nhap ma sach muon
	MuonTra mt;
MuonSach:
	system("color 0A");
	system("cls");
	textcolor(15);
	Table_Danh_Sach_Sach();
	int hang = 7;
	Button_ESC();
	Button_Muon();
	textcolor(15);
	// xuat ra nhung cuon sach ma doc gia da muon
	PTRMuonTra h = dg->docGia.FirstMuonTra;
	for (PTRMuonTra p = h; p != NULL; p = p->next)
	{
		for (int i = 0; i < list.soDauSach; i++)
		{
			PTRDanhMucSach k = list.sach[i].FirstDanhMucSach;
			for (PTRDanhMucSach q = k; q != NULL; q = q->next)
			{

				if (p->muonTra.maSach == q->mucSach.maSach)
				{

					gotoxy(3 + tabx, hang); cout << list.sach[i].ISBN;
					gotoxy(15 + tabx, hang); cout << p->muonTra.maSach;
					gotoxy(30 + tabx, hang); cout << list.sach[i].tenSach;
					gotoxy(55 + tabx, hang); cout << q->mucSach.trangThaiSach;
					gotoxy(67 + tabx, hang); cout << q->mucSach.viTri;
					hang++;
				}
			}
		}
	}
	while (1)
	{
		int c = getch();
		if (c == F5)   // muon sach
		{
			system("cls");
			system("color 0A");
			Button_ESC();
			Button_OK();
			int x = 40, y = 15;
			Frame_Muc_Sach(40, 15);
			int keybhit, dem;
			string text, field;
			field = "";
			char temp[10];
			keybhit = 0;
			dem = field.length();
			text = field;
			// nhap ma sach muon
			while (1)
			{
				gotoxy(x + 8, y + 1);
				if (dem < 9)
				{
					cout << text;
					for (int i = 1; i < 11 - dem; i++)
						cout << " ";
				}
				else
				{
					for (int i = dem - 9; i < dem; i++)
						cout << text[i];
				}
				if (dem < 9)
					gotoxy(x + 8 + dem, y + 1);
				keybhit = getch();
				if (keybhit == BACKSPACE)
				{
					if (dem > 0)
					{
						dem--;
						text = text.substr(0, text.size() - 1);
					}
				}
				else if (keybhit == ENTER)
				{
					if (text == "")
					{
						textcolor(15);
						Del_Error();
						keybhit = 0;
						gotoxy(boxx + 27, 29);
						textcolor(15);
						cout << "VUI LONG NHAP MA SACH";
						Sleep(500);
						goto MuonSach;
					}
					else
					{
						textcolor(15);
						Del_Error();
						Button_OK();
						Sleep(500);
						PTRDanhMucSach sach = Tim_Kiem_Sach(list, atoi((char*)text.c_str()));
						if (sach == NULL)
						{
							gotoxy(boxx + 25, 29);
							textcolor(15);
							cout << "MA SACH KHONG TON TAI";
							Sleep(800);
							goto MuonSach;
						}
						if (sach->mucSach.trangThaiSach == daMuon)
						{
							gotoxy(boxx + 25, 29);
							textcolor(15);
							cout << "SACH DA CO NGUOI MUON";
							Sleep(800);
							goto MuonSach;
						}
						if (sach->mucSach.trangThaiSach == thanhLy)
						{
							gotoxy(boxx + 25, 29);
							textcolor(15);
							cout << "SACH DA THANH LY";
							Sleep(800);
							goto MuonSach;
						}
						else			// sach cho muon duoc
						{
							if (dg->docGia.soSachMuon == 3)
							{
								cout << "DOC GIA DA MUON 3 CUON";
								Sleep(800);
								goto MuonSach;
							}

							mt.maSach = atoi((char*)text.c_str());
							mt.trangThaiMuonTraSach = chuaTra;
							// gang ngay muon va ngay tra cho ngay hien tai
							Lay_Ngay_He_Thong(mt.ngayMuon);
							Lay_Ngay_He_Thong(mt.ngayTra);
							sach->mucSach.trangThaiSach = daMuon;
							// cap nhat so lan duoc muon cua dau sach // XXXXX
							for (int i = 0; i < list.soDauSach; i++)
							{
								PTRDanhMucSach p = list.sach[i].FirstDanhMucSach;
								while (p != NULL)
								{
									if (p->mucSach.maSach == sach->mucSach.maSach)
										list.sach[i].soLanMuon++;
									p = p->next;
								}
							}
							dg->docGia.soSachMuon++;   // de kiem tra so luong sach doc gia muon
							Them_Muon_TRa(dg->docGia.FirstMuonTra, mt);
							textcolor(15);
							gotoxy(boxx + 32, 29);
							cout << "MUON THANH CONG";
							Sleep(500);
							goto MuonSach;
						}
					}
				}
				else if (keybhit == ESC)
				{
					Button_ESC();
					Sleep(500);
					system("cls");
					return;
				}
				else
				{
					dem++;
					text += (char)keybhit;
					Del_Error();
				}
			}
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
	}
}

void Giao_Dien_Muon_Sach(TreeDocGia& root, ListDauSach& list)
{
	TreeDocGia p = root;
	int sl = So_Luong_Doc_Gia(p);
	DocGia dG[sl];
	Chuyen_Cay(p, dG, sl);
	int trang = 1;
	int tongTrang = 0;
	if (sl % 10 != 0)
		tongTrang = sl / 10 + 1;
	else
		tongTrang = sl / 10;
Xuat:
	system("cls");
	textcolor(15);

	Table_Doc_Gia();
	int dem = 0;
	Button_Sreach();
	Button_ESC();
	textcolor(15);
	Xuat_1_Trang_Doc_Gia(trang, sl, dG);
	const int STACKSIZE = 100;
	TreeDocGia Stack[STACKSIZE];
	int c = 0;
	while (c != ESC)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DG();
			Xuat_1_Trang_Doc_Gia(trang, sl, dG);
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
		else if (c == F4)
		{
			Button_Sreach();
			Sleep(500);
			Muon_Sach(root, list);
			goto Xuat;
		}
	}
}
//=== Tra Sach ===
PTRMuonTra Tim_Kiem_Muon_Tra(PTRMuonTra mt, int maSach)
{
	for (PTRMuonTra p = mt; p != NULL; p = p->next)
	{
		if (p->muonTra.maSach == maSach)
			return p;
	}
	return NULL;
}

int Xoa_Muon_Tra(PTRMuonTra& mt, int maSach)
{
	if (mt == NULL)
		return 0;
	PTRMuonTra p = Tim_Kiem_Muon_Tra(mt, maSach);
	if (p == NULL)
		return 0;
	if (p == mt)
	{
		p = mt;
		mt = p->next;
		delete p;
		return 1;
	}
	else
	{
		PTRMuonTra q = mt;
		while (q->next != p)
			q = q->next;
		p = q->next;
		q->next = p->next;
		delete p;
		return 1;
	}
	return 0;
}

void Tra_Sach(TreeDocGia& r, ListDauSach& list)
{
	TreeDocGia root = r;
X:
	TreeDocGia dg = Nhap_Kiem_Tra_Ma_Doc_Gia(root);
	if (dg->docGia.soSachMuon == 0)
	{
		textcolor(15);
		gotoxy(boxx + 20, 30);
		cout << "DOC GIA CHUA MUON SACH !!";
		Sleep(1000);
		goto X;
	}
	Date d1;
	MuonTra mt;
TraSach:
	system("color 0A");
	system("cls");
	while (1)
	{
		system("cls");
		textcolor(15);
		Table_Danh_Sach_Sach();
		int hang = 7;
		Button_ESC();
		Button_Tra();
		textcolor(15);
		// xuat sach doc gia muon
		for (PTRMuonTra p = dg->docGia.FirstMuonTra; p != NULL; p = p->next)
		{
			for (int i = 0; i < list.soDauSach; i++)
			{
				PTRDanhMucSach h = list.sach[i].FirstDanhMucSach;
				for (PTRDanhMucSach q = h; q != NULL; q = q->next)
				{
					if (p->muonTra.maSach == q->mucSach.maSach)
					{

						gotoxy(3 + tabx, hang); cout << list.sach[i].ISBN;
						gotoxy(15 + tabx, hang); cout << p->muonTra.maSach;
						gotoxy(30 + tabx, hang); cout << list.sach[i].tenSach;
						gotoxy(55 + tabx, hang); cout << q->mucSach.trangThaiSach;
						gotoxy(67 + tabx, hang); cout << q->mucSach.viTri;
						hang++;
					}
				}
			}
		}
		int c = getch();
		if (c == F6)   // Tra Sach
		{
			system("cls");
			Button_ESC();
			Button_OK();
			int x = 40, y = 15;
			Frame_Muc_Sach(x, y);
			int keybhit, dem;
			string text, field;
			field = "";
			char temp[10];
			keybhit = 0;
			dem = field.length();
			text = field;
			while (1)
			{
				gotoxy(x + 8, y + 1);
				if (dem < 9)
				{
					cout << text;
					for (int i = 1; i < 11 - dem; i++)
						cout << " ";
				}
				else
				{
					for (int i = dem - 9; i < dem; i++)
						cout << text[i];
				}
				if (dem < 9) gotoxy(x + 8 + dem, y + 1);
				keybhit = getch();
				if (keybhit == BACKSPACE)
				{
					if (dem > 0)
					{
						dem--;
						text = text.substr(0, text.size() - 1);
					}
				}
				else if (keybhit == ENTER)
				{
					if (text == "")
					{
						textcolor(15);
						Del_Error();
						keybhit = 0;
						gotoxy(boxx + 28, 29);
						cout << "VUI LONG NHAP MA SACH";
					}
					else
					{
						textcolor(15);
						Del_Error();
						if (Tim_Kiem_Muon_Tra(dg->docGia.FirstMuonTra, atoi((char*)text.c_str())) == 0)
						{
							gotoxy(boxx + 28, 29);
							cout << "MA SACH KHONG TON TAI";
						}
						else
						{
							Button_OK();
							Sleep(500);
							PTRMuonTra mt = Tim_Kiem_Muon_Tra(dg->docGia.FirstMuonTra, atoi((char*)text.c_str())); // tim ra sach muon tra 
							if (mt->muonTra.trangThaiMuonTraSach == lamMatSach)
							{
								gotoxy(boxx + 28, 29);
								cout << "DOC GIA LAM MAT SACH. TRA KHONG THANH CONG";
								sleep(10);
								goto TraSach;
							}
							PTRDanhMucSach sach = Tim_Kiem_Sach(list, atoi((char*)text.c_str()));
							if (Xoa_Muon_Tra(dg->docGia.FirstMuonTra, mt->muonTra.maSach) == 1)  // xoa thanh cong
							{
								textcolor(15);
								gotoxy(boxx + 28, 29);
								cout << "TRA THANH CONG";
							}
							sach->mucSach.trangThaiSach = choMuonDuoc;
							Lay_Ngay_He_Thong(mt->muonTra.ngayTra);
							if (Tinh_Ngay(mt->muonTra.ngayMuon, mt->muonTra.ngayTra) >= 15 || dg->docGia.soSachMuon == 3 && dg->docGia.trangThaiThe == viPham)
								dg->docGia.trangThaiThe = binhThuong;
							dg->docGia.soSachMuon--;
							Sleep(500);
							goto TraSach;
						}
					}
				}
				else if (keybhit == ESC)
				{
					Button_ESC();
					system("cls");
					goto TraSach;
				}
				else
				{
					dem++;
					text += (char)keybhit;
					Del_Error();
				}
			}
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;
		}
	}
}

void Giao_Dien_Tra_Sach(TreeDocGia root, ListDauSach& list)
{
Xuat:
	TreeDocGia p = root;
	int sl = So_Luong_Doc_Gia(p);
	DocGia dG[sl];
	Chuyen_Cay(p, dG, sl);
	system("cls");
	int trang = 1;
	int tongTrang = 0;
	if (sl % 10 != 0)
		tongTrang = sl / 10 + 1;
	else
		tongTrang = sl / 10;
	textcolor(15);
	Table_Doc_Gia();
	int dem = 0;
	Button_Sreach();
	Button_ESC();
	textcolor(15);
	Xuat_1_Trang_Doc_Gia(trang, sl, dG);
	int c = 0;
	while (c != ESC)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DG();
			Xuat_1_Trang_Doc_Gia(trang, sl, dG);
		}
		else if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			Menu(root, list);
		}

		else if (c == F4)
		{
			Button_Sreach();
			Sleep(500);
			Tra_Sach(root, list);
			goto Xuat;
		}
	}
}

//====Liet Ke Sach Muon Cua 1 Doc Gia====
void Liet_Ke_Sach_Doc_Gia_Muon(TreeDocGia root, ListDauSach list)
{
	TreeDocGia p = root;
	int sl = So_Luong_Doc_Gia(p);
	DocGia dG[sl];
	Chuyen_Cay(p, dG, sl);
	int trang = 1;
	int tongTrang = 0;
	if (sl % 10 != 0)
		tongTrang = sl / 10 + 1;
	else
		tongTrang = sl / 10;
Y:	Table_Doc_Gia();
	Button_ESC();
	Button_OK();
	Xuat_1_Trang_Doc_Gia(trang, sl, dG);
	int c = 0;
	// xuat tat ca doc gia
	while (c != ESC)
	{
		c = getch();
		if (c == LEFT || c == RIGHT)
		{
			if (c == LEFT)
			{
				if (trang > 1)
					trang--;
				else
					trang = tongTrang;
			}
			else if (c == RIGHT)
			{
				if (trang == tongTrang)
					trang = 1;
				else
					trang++;
			}
			Xoa_Du_Lieu_Table_DG();
			Xuat_1_Trang_Doc_Gia(trang, sl, dG);
		}
		else if (c == ENTER)
			break;
		else if (c == ESC)
		{
			system("cls");
			return;
		}
	}
	TreeDocGia dg = Nhap_Kiem_Tra_Ma_Doc_Gia(root);  // nhap doc gia can liet ke
	if (dg->docGia.soSachMuon == 0)
	{
		Sleep(500);
		gotoxy(boxx + 20, 30);
		cout << "DOC GIA CHUA MUON SACH !!";
		Sleep(500);
		system("cls");
		goto Y;
	}
	system("cls");
	textcolor(15);
	Table_Danh_Sach_Sach();
	int dem = 7;
	Button_ESC();
	for (PTRMuonTra p = dg->docGia.FirstMuonTra; p != NULL; p = p->next)
	{
		for (int i = 0; i < list.soDauSach; i++)
		{
			PTRDanhMucSach h = list.sach[i].FirstDanhMucSach;
			for (PTRDanhMucSach q = list.sach[i].FirstDanhMucSach; q != NULL; q = q->next)
			{

				if (p->muonTra.maSach == q->mucSach.maSach)
				{
					gotoxy(3 + tabx, dem); cout << list.sach[i].ISBN;
					gotoxy(15 + tabx, dem);	cout << q->mucSach.maSach;
					gotoxy(30 + tabx, dem);	cout << list.sach[i].tenSach;
					gotoxy(55 + tabx, dem);	cout << q->mucSach.trangThaiSach;
					gotoxy(67 + tabx, dem);	cout << q->mucSach.viTri;
					dem++;
				}
			}
		}
	}
	while (1)
	{
		int c1 = getch();
		if (c1 == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			goto Y;

		}
	}
}
//==== Doc Gia Muon Qua Han===
TreeDocGia DS_Qua_Han(TreeDocGia root)  // lay ra nhung doc gia qua han
{
	TreeDocGia qh = NULL;
	TreeDocGia p = root;
	int dem = 0;
	Date d1;
	Lay_Ngay_He_Thong(d1);
	const int STACKSIZE = 100;
	TreeDocGia Stack[STACKSIZE];
	int sp = -1;
	do
	{
		while (p != NULL)
		{
			Stack[++sp] = p;
			p = p->left;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			if (p->docGia.FirstMuonTra != NULL)
			{
				PTRMuonTra q = p->docGia.FirstMuonTra;
				while (q != NULL)
				{
					if (Tinh_Ngay(q->muonTra.ngayMuon, d1) >= 15)
					{
						DocGia s;
						s = p->docGia;
						Them_Doc_Gia(qh, s);
					}
					q = q->next;
				}
			}
			p = p->right;
		}
		else break;
	} while (1);
	return qh;
}

void Qua_Han(TreeDocGia root)
{
	TreeDocGia p = DS_Qua_Han(root);  // p chua nhung doc gia qua han
	if (p == NULL)
	{
		gotoxy(20, 20);
		cout << "KHONG CO DOC GIA QUA HAN";
		Sleep(500);
		system("cls");
		return;
	}
	const int STACKSIZE = 100;
	Date d1;
	Lay_Ngay_He_Thong(d1);
	TreeDocGia Stack[STACKSIZE];
	DocGia dGQuaHan[STACKSIZE];   // mang chua doc gia qua han
	int ngayQuaHan[STACKSIZE]; // mang chua ngay qua han
	int sl = 0;
	int sp = -1;
	do
	{
		while (p != NULL)
		{
			Stack[++sp] = p;
			p = p->left;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			dGQuaHan[sl] = p->docGia;
			int max = 0;
			for (PTRMuonTra q = p->docGia.FirstMuonTra; q != NULL; q = q->next)
			{
				if (Tinh_Ngay(q->muonTra.ngayMuon, d1) > max)     // tinh ngay qua han lon nhat trong so nhung quyen sach doc gia muon
					max = Tinh_Ngay(q->muonTra.ngayMuon, d1);
			}
			ngayQuaHan[sl] = max;
			sl++;
			p = p->right;
		}
		else break;
	} while (1);

	Table_Qua_Han();
	Button_ESC();
	// sap xep lai doc gia qua han
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if (ngayQuaHan[j] < ngayQuaHan[i])
			{
				int ngay;
				ngay = ngayQuaHan[j];
				ngayQuaHan[j] = ngayQuaHan[i];
				ngayQuaHan[i] = ngay;
				DocGia d;
				d = dGQuaHan[j];
				dGQuaHan[j] = dGQuaHan[i];
				dGQuaHan[i] = d;

			}
		}
	}
	int dem = 7;
	for (int i = 0; i < sl; i++)
	{
		gotoxy(13, dem);	cout << dGQuaHan[i].maDG;
		gotoxy(25, dem);	cout << dGQuaHan[i].ho;
		gotoxy(42, dem);	cout << dGQuaHan[i].ten;
		gotoxy(57, dem);	cout << dGQuaHan[i].phai;
		gotoxy(69, dem);	cout << ngayQuaHan[i];
		dem += 2;
	}
	while (1)
	{
		int c = getch();
		if (c == ESC || c == ENTER)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;

		}
	}
}

//==== 10 sach muon nhieu nhat=====
void Top_10_Sach_Muon_Nhieu_Nhat(ListDauSach list)
{
	system("cls");
	textcolor(15);
	Table_Dau_Sach();
	Button_ESC();
	textcolor(15);
	// sap xep lai theo so lan muon
	for (int i = 0; i < list.soDauSach - 1; i++)
	{
		for (int j = i + 1; j < list.soDauSach; j++)
		{
			if (list.sach[j].soLanMuon > list.sach[i].soLanMuon)
			{
				DauSach temp;
				temp = list.sach[i];
				list.sach[i] = list.sach[j];
				list.sach[j] = temp;
			}
		}
	}
	int n;
	int dem = 0;
	if (list.soDauSach < 10)
		n = list.soDauSach;
	else
	{
		n = 10;
		for (int i = 10; i < list.soDauSach; i++)
		{
			if (list.sach[9].soLanMuon == list.sach[i].soLanMuon && list.sach[9].soLanMuon != 0)
				dem++;
		}
	}
	int i = 7;
	for (int j = 0; j < n + dem; j++)
	{
		gotoxy(3 + tabx, i); 	cout << list.sach[j].ISBN;
		gotoxy(15 + tabx, i); 	cout << list.sach[j].tenSach;
		gotoxy(34 + tabx, i); 	cout << list.sach[j].tacGia;
		gotoxy(48 + tabx, i); 	cout << list.sach[j].theLoai;
		gotoxy(60 + tabx, i); 	cout << list.sach[j].soTrang;
		gotoxy(72 + tabx, i); 	cout << list.sach[j].namXuatBan;
		gotoxy(87 + tabx, i);	cout << list.sach[j].soLanMuon;
		i++;
	}
	while (1)
	{
		int c = getch();
		if (c == ESC)
		{
			Button_ESC();
			Sleep(500);
			system("cls");
			return;

		}
	}
}


void Menu(TreeDocGia& root, ListDauSach& list)
{
	const int so_item = 11;
	char thucDon[so_item][100] = { " 1.  NHAP DOC GIA                        ",
									" 2.  DANH SACH DOC GIA                   ",
									" 3.  NHAP DAU SACH                       ",
									" 4.  DANH SACH DAU SACH                  ",
									" 5.  DANH SACH SACH                      ",
									" 6.  MUON SACH                           ",
									" 7.  TRA SACH                            ",
									" 8.  LIET KE SACH DOC GIA DANG MUON      " ,
									" 9.  DANH SACH DOC GIA MUON SACH QUA HAN ",
									" 10. IN 10 DAU SACH MUON NHIEU NHAT     ",
									" 11. KET THUC CHUONG TRINH              " };

	int chon = 0;
	int keybhit;
	const int cot = 15;
	const int dong = 16;

	do
	{
		HighLight();
		gotoxy(30, 4); cout << "                              ";
		gotoxy(30, 5); cout << "        QUAN LY THU VIEN      ";
		gotoxy(30, 6); cout << "                              ";
		gotoxy(30, 7); cout << "Ten: Nguyen Thi Phuong        ";
		gotoxy(30, 8); cout << "MSV: N14DCCN268               ";
		gotoxy(30, 9); cout << "                              ";
		Normal();
		for (int i = 0; i < so_item; i++)
		{
			gotoxy(cot, dong + i);
			cout << thucDon[i];
		}
		HighLight();
		gotoxy(cot, dong + chon);
		cout << thucDon[chon];
		keybhit = getch();
		if (keybhit == UP)
		{
			Normal();
			gotoxy(cot, dong + chon);
			cout << thucDon[chon];
			if (chon >= 1)
				chon--;
			else
				chon = 10;
			HighLight();
			gotoxy(cot, dong + chon);
			cout << thucDon[chon];
		}
		if (keybhit == DOWN)
		{
			Normal();
			gotoxy(cot, dong + chon);
			cout << thucDon[chon];
			if (chon < 10)
				chon++;
			else
				chon = 0;
			HighLight();
			gotoxy(cot, dong + chon);
			cout << thucDon[chon];
		}
		if (keybhit == ENTER)
		{
			switch (chon)
			{
			case 0:
				textcolor(15);
				system("cls");
				Nhap_Doc_Gia(root);
				system("cls");
				break;
			case 1:
				textcolor(15);
				system("cls");
				Xuat_Danh_Sach_Doc_Gia(root);
				break;
			case 2:
				textcolor(15);
				system("cls");
				Nhap_Dau_Sach(list);
				break;
			case 3:
				textcolor(15);
				system("cls");
				int h;
				cout << "1. Sap Xep Theo Ten" << endl;
				cout << "2. Sap Xep Theo ISBN" << endl;
				cout << "Nhap Lua Chon:(1/2) ";
				do
				{
					cin >> h;
				} while (h != 1 && h != 2);
				if (h == 1)
					Sap_Xep_DS_Ten(list);
				else
					Sap_Xep_DS_ISBN(list);
				Xuat_Dau_Sach(list);
				break;
			case 4:
				textcolor(15);
				system("cls");
				Xuat_Danh_Sach_Sach(list);
				break;
			case 5:
				textcolor(15);
				system("cls");
				Giao_Dien_Muon_Sach(root, list);
				break;
			case 6:
				textcolor(15);
				system("cls");
				Giao_Dien_Tra_Sach(root, list);
				break;
			case 7:
				textcolor(15);
				system("cls");
				Liet_Ke_Sach_Doc_Gia_Muon(root, list);
				break;
			case 8:
				textcolor(15);
				system("cls");
				Qua_Han(root);
				break;
			case 9:
				textcolor(15);
				system("cls");
				Top_10_Sach_Muon_Nhieu_Nhat(list);
				break;
			case 10:
				// luu file
				if (Xac_Nhan_Luu_File())
				{
					Ghi_File_Doc_Gia(root);
					Ghi_File_Dau_Sach(list);
				}
				exit(0);
				textcolor(15);
			}
		}
	} while (true);
}
int main(int argc, char** argv)
{
	rootDocGia = NULL;
	listDauSach.soDauSach = 0;
	Doc_File_Doc_Gia(rootDocGia);
	Doc_File_Dau_Sach(listDauSach);
	SetWindow(100, 40);
	//Xuat_1_Trang_DSS(listDauSach,1);
	Menu(rootDocGia, listDauSach);
	return 0;
}

