#include<iostream>
using namespace std;

struct CONTACT { //Cây nhị phân tìm kiếm
	SDT* ds_SDT; //Lưu theo mảng động
	int soLuong; //Số số điện thoại mà một người sở hữu
	string ten;
	NHOM nhom;
	bool gioiTinh;
	DIACHI diachi;
	DATE ngaysinh;
	string email;
	string ghiChu;
	CONTACT* right;
	CONTACT* left;
};

struct DATE {
	int day;
	int month;
	int year;
};

struct SDT { 
	int sdt;
	string tenVung;
	string Loai;
};

struct DIACHI { //Danh sách liên kết đơn
	string huyen;
	string tinh;
	string nuoc;
	DIACHI* next;
	CONTACT* ds_conTact;
};

struct NHOM { //Lưu theo danh sách liên kết đơn
	string ten;
	CONTACT* ds_contact;
	NHOM* next;
};
void TimNodeThayThe(CONTACT*& X, CONTACT*& Y) {
	if (Y->right != NULL) {
		TimNodeThayThe(X, Y->right);//Tìm Node phải nhất của cây con trái
	}
	else
	{
		X = Y;
		Y = Y->left;
	}
}
void XoaThongTin(CONTACT*& danhba)
{
	int sdtxoa;
	cout << "\n\n\t\t Nhap so dien thoai can xoa: ";
	cin >> sdtxoa;
	if (danhba == NULL)
	{
		return;
	}
	else
	{
		if (danhba->ds_SDT->sdt != sdtxoa)
		{
			if (danhba->left != NULL)
			{
				XoaThongTin(danhba->left);
			}
			if (danhba->right != NULL)
			{
				XoaThongTin(danhba->right);
			}
		}
		else
		{
			CONTACT* X = danhba;
			if (danhba->left == NULL)//duyệt cập nhật mối liên kết của node cha của node cần xóa với node con của node cần xóa
			{
				danhba = danhba->right;
			}
			else if (danhba->right == NULL)
			{
				danhba = danhba->left;
			}
			else //node cần xóa có 2 con
			{
				TimNodeThayThe(X, danhba->left);
			}
			delete X;
		}
	}
}
void Menu(CONTACT*& danhba, DIACHI*& ds_DiaChi, NHOM*& ds_nhom) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t::::::::::::::::::::::::::::QUAN LY DANH BA DIEN THOAI::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t1. Them thong tin so dien thoai";
		cout << "\n\n\t\t2. Xoa thong tin so dien thoai";
		cout << "\n\n\t\t3. Xuat danh sach so dien thoai theo ten";
		cout << "\n\n\t\t:::::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::::::::::";

		cout << "\n\n\t\t Nhap luachon: ";
		cin >> luachon;

		if(luachon == 1){
		
		}
		else if (luachon == 2) {
			XoaThongTin(danhba);
		}
		else {
			break;
		}

	}


}


int main() {
	CONTACT* danhBa = NULL;
	DIACHI* ds_diaChi = NULL;
	NHOM* ds_nhom = NULL;
}
