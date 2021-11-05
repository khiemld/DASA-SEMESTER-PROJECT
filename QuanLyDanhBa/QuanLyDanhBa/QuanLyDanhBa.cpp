#include<iostream>
#include<queue>
#include <stdio.h>
#include <string>
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
CONTACT* CreateContact(SDT* data) {
	CONTACT* newContact = new CONTACT();
	if (!newContact) {
		cout << "Memory error\n";
		return NULL;
	}
	newContact->ds_SDT[0] = data;
	newContact->left = newContact->right = NULL;
	return newContact;
}

CONTACT* InsertPhoneNumber(CONTACT* root, SDT* data) {
	if (root == NULL) {
		root = CreateContact(data);
		return root;
	}
	queue<CONTACT*>q;
	q.push(root);
	while (!q.empty()) {
		CONTACT* temp = q.front();
		q.pop();
		if (temp->left != NULL) q.push(temp->left);
		else {
			temp->left = CreateContact(data);
			return root;
		}
		if (temp->right != NULL) q.push(temp->right);
		else {
			temp->right = CreateContact(data);
			return root;
		}
	}
}
void printPhoneNumber(CONTACT* temp) {
	if (temp == NULL)return;

	printPhoneNumber(temp->left);
	cout << temp << ' ';
	printPhoneNumber(temp->right);
}
void InputPhoneNumber(CONTACT* danhba) {
	cout << "Moi nhap so dien thoai ban muon them vao danh ba: ";
	for (int i = 0; i < 10; i++) {
		if (danhba->ds_SDT[i] != NULL)break; //Neu vi tri hien tai da co so thi den vi tri ke
		cin >> danhba->ds_SDT[i]->sdt;
		cout << "Moi nhap ten cua ban o day: ";
		cin >> danhba->ten; break;
	}
	danhba = InsertPhoneNumber(danhba, danhba->ds_SDT);
	printPhoneNumber(danhba);



	//int extra = 0;
	//do {
	//	cout << "Ban co muon them thong tin cu the cho so dien thoai nay khong?\n/*Nhan 1 neu muon\nNhan 0 neu ban khong can*/";
	//	cin >> extra;
	//	if (extra == 1) {
	//		bool test;
	//		cout << "Nhan 1 neu ban la nam/ Nhan 0 neu ban la nu";
	//		cin >> test;
	//		if (test) {
	//			danhba->gioiTinh = "Gioi tinh: Nam";
	//		}
	//		else {
	//			danhba->gioiTinh = "Gioi tinh: Nu";
	//		}

	//		cout << "Hay nhap vao ngay sinh cua ban theo thu tu: ngay, thang, nam:";
	//		//cin >> danhba->ngaysinh;

	//		cout << "Hay nhap vao dia chi cua ban:";
	//		//getline(cin, danhba->diachi);

	//		cout << "Hay nhap vao dia chi email cua ban:";
	//		getline(cin, danhba->email);

	//		cout << "Ban co muon ghi chu gi cho so dien thoai nay khong?";
	//		getline(cin, danhba->ghiChu);
	//		
	//		danhba = InsertPhoneNumber(danhba, danhba->ds_SDT);
	//		printPhoneNumber(danhba);
	//	}
	//	else {
	//		cout << "Chuc mung ban vua nhap vao so dien thoai voi noi dung nhu sau:";
	//		danhba = InsertPhoneNumber(danhba, danhba->ds_SDT);
	//		printPhoneNumber(danhba);
	//	}
	//} while (extra != 0 || extra != 1);

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

		if (luachon == 1) {
			InputPhoneNumber(danhba);
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
	Menu(danhBa, ds_diaChi, ds_nhom);
}
