#include<iostream>
using namespace std;

struct CONTACT { //Cây nhị phân tìm kiếm
	SDT* ds_SDT[10]; //Lưu theo mảng động
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
