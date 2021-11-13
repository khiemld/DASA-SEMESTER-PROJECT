#include<iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct DATE {
	int day;
	int month;
	int year;
};

struct SDT {
	int sdt;
	//int maQuocGia;
	string loai;
};

struct DIACHI { //Danh sách liên kết đơn
	string tinh;
	string nuoc;
	DIACHI* next;
};

struct NHOM { //Lưu theo danh sách liên kết đơn
	string ten;
	NHOM* next;
};

struct DATA {
	SDT  SDT;
	string ten;
	NHOM nhom;
	string gioiTinh;
	DIACHI diachi;
	DATE ngaysinh;
	string email;
	string ghiChu;
};

struct CONTACT { //Cây nhị phân tìm kiếm
	DATA data;
	CONTACT* right;
	CONTACT* left;
};
typedef CONTACT* TREE;

//Hàm tách 3 số đầu của số điện thoại
int tachSoDau(int sdt) {
	int dem = 1;
	while (dem <= 7) {
		sdt /= 10;
		dem++;
	}
	return sdt;
}

//Hàm nhập thông điện thoại
void inputPhoneNumber(SDT& dt) {
	/*cout << "\tNhập mã nước: ";
	cin >> dt.maQuocGia;*/
	cout << "\t\tNhap so dien thoai: ";
	cin >> dt.sdt;
	int soDau = tachSoDau(dt.sdt);
	if (soDau == 86 || soDau == 96 || soDau == 97 || soDau == 98 || soDau == 32 || soDau == 33 || soDau == 34 || soDau == 35
		|| soDau == 36 || soDau == 37 || soDau == 38 || soDau == 39)
		dt.loai = "Viettel";
	else if (soDau == 88 || soDau == 91 || soDau == 94 || soDau == 83 || soDau == 84 || soDau == 85 || soDau == 81 || soDau == 82)
		dt.loai = "Vinaphone";
	else if (soDau == 89 || soDau == 90 || soDau == 93 || soDau == 70 || soDau == 79 || soDau == 77 || soDau == 76 || soDau == 78)
		dt.loai = "Mobiphone";
	else if (soDau == 92 || soDau == 56 || soDau == 58)
		dt.loai = "Vietnammobile";
}

//Hàm nhập ngày sinh
void inputDateBirth(DATE& date) {
	cout << "\t\tNhap ngay sinh: ";
	cin >> date.day;
	cout << "\t\tNhap thang sinh: ";
	cin >> date.month;
	cout << "\t\tNhap nam sinh: ";
	cin >> date.year;
}
 
//Hàm nhập địa chỉ
void inputAddress(DIACHI& diaChi) {
	while (getchar() != '\n');
	cout << "\t\tTinh: ";
	getline(cin, diaChi.tinh);
}

//Hàm nhập thông tin DATA
void inputDATA(DATA& x) {
	while (getchar() != '\n');
	cout << "\t\tNhap ten: ";
	getline(cin, x.ten);
	cout << "\t\tGioi tinh: ";
	getline(cin, x.gioiTinh);
	inputPhoneNumber(x.SDT);
	inputAddress(x.diachi);
	inputDateBirth(x.ngaysinh);
	while (getchar() != '\n');
	string ktMail;
	do {
		cout << "\t\tBan co muon nhap email <y/n>?";
		getline(cin, ktMail);
		if (ktMail == "y") {
			cout << "\t\tEmail: ";
			getline(cin, x.email);
			break;
		}
		else if(ktMail == "n") {
			x.email = "";
			break;
		}
	} while (ktMail != "y" && ktMail != "n");
	string ktNote;
	do {
		cout << "\t\tBan co them ghi chu <y/n>?";
		getline(cin, ktNote);
		if (ktNote == "y") {
			cout << "\t\tGhi chu: ";
			getline(cin, x.ghiChu);
			break;
		}
		else if(ktNote == "n") {
			x.ghiChu = "";
			break;
		}
	} while (ktNote != "y" && ktNote != "n");
}

//Hàm thêm data
void insertData(TREE &contact, DATA data) {
	if (contact == NULL) { //Nếu cây rỗng
		CONTACT* p = new CONTACT;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		contact = p; //Thêm node p vào cây
	}
	else {
		if (contact->data.SDT.sdt < data.SDT.sdt) {
			insertData(contact->right, data);
		}
		else if(contact->data.SDT.sdt > data.SDT.sdt){
			insertData(contact->left, data);
		}
	}
}

//Hàm xuất thông tin
void printDATA(DATA data) {
	cout << "\n\t\tTen: " << data.ten;
	cout << "\n\t\tSo dien thoai: 0" << data.SDT.sdt;
	cout << "\n\t\tNha mang: " << data.SDT.loai;
	cout << "\n\t\tGioi tinh: " << data.gioiTinh;
	cout << "\n\t\tDia chi: tinh " << data.diachi.tinh;
	cout << "\n\t\tNgay sinh: " << data.ngaysinh.day << "/" << data.ngaysinh.month << "/" << data.ngaysinh.year;
	if (data.email != "")
		cout << "\n\t\tEmail: " << data.email;
	if (data.ghiChu != "")
		cout << "\n\t\tGhi chu: " << data.ghiChu;
	cout << "\n";
}

//Hàm duyệt data
void duyetContact(TREE contact) {
	if (contact != NULL) {
		printDATA(contact->data);
		duyetContact(contact->left);
		duyetContact(contact->right);
	}
}

//Hàm kiểm tra phần tử có tồn tại
bool kiemTraTonTai(TREE contact, int sdtData)
{
	if (contact == NULL)
	{
		return false;
	}
	else
	{
		if (sdtData == contact->data.SDT.sdt)
		{
			return true;
		}
		else if (sdtData > contact->data.SDT.sdt)
		{
			return	kiemTraTonTai(contact->right, sdtData);
		}
		else if (sdtData < contact->data.SDT.sdt)
		{
			return kiemTraTonTai(contact->left, sdtData);
		}
	}
	return false;
}

//Xóa
void timNODEThayThe(CONTACT*& X, CONTACT*& Y) { //Tìm NODE trái nhất của cây con phải
	if (Y->left != NULL) {
		timNODEThayThe(X, Y->left);
	}
	else {
		X->data = Y->data;
		X = Y; // X giữ địa chỉ NODE cần xóa
		Y = Y->right;
	}
}

void deleteContact(TREE& contact, int sdtData) {
	if (contact == NULL) {
		return;
	}
	else {
		if (contact->data.SDT.sdt < sdtData) {
			deleteContact(contact->right, sdtData);
		}
		else if (contact->data.SDT.sdt > sdtData) {
			deleteContact(contact->right, sdtData);
		}
		else { 
			CONTACT* temp = contact; // temp tạm giữ NODE contact cần xóa
			if (contact->left == NULL) {
				contact = contact->right;
			}
			else if (contact->right == NULL) {
				contact = contact->left;
			}
			else {
				//Tìm NODE trái nhất của của cây con phải
				timNODEThayThe(temp, contact->right);
			}
			delete temp;
		}
	}
}

void searchPhoneNumber(TREE& contact, int sdtData) 
{
	if (contact != NULL) {
		string data = to_string(sdtData); // Convert số nhập vào sang kiểu string
		string Contact = to_string(contact->data.SDT.sdt); //Convert số trong cây nhị phân sang kiểu string
		
		if (data == Contact) 
			printDATA(contact->data); // Nếu số nhập vào trùng thì in thông tin danh bạ
		int m = data.size();
		int n = Contact.size();
		int count = 0;
		
		for (int i = 0; i < m; i++) {
			if (data[i] == Contact[i]) //Nếu từng chữ số nhập vào trùng với các chữ số trong cây nhị phân
				count++; //  thì ta tăng biến đếm
			
			if (count == data.size()) // Nếu biến đếm trùng với kích thước của số nhập vào
				printDATA(contact->data); // thì ta in thông tin danh bạ
		}
		searchPhoneNumber(contact->left, sdtData); // Tiếp tục tìm kiếm các số trùng với số nhập vào ở bên trái
		searchPhoneNumber(contact->right,sdtData); // và ở bên phải		
	}
}


void Menu(TREE& contact) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t::::::::::::::::::::::::::::QUAN LY DANH BA DIEN THOAI::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t1. Them thong tin so dien thoai";
		cout << "\n\n\t\t2. Xoa thong tin so dien thoai";
		cout << "\n\n\t\t3. Xuat danh sach so dien thoai";
		cout << "\n\n\t\t4. Tim thong tin danh ba theo so dien thoai";
		cout << "\n\n\t\t0. Ket thuc";
		cout << "\n\n\t\t:::::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::::::::::";

		cout << "\n\n\t\t\t Lua chon: ";
		cin >> luachon;

		if (luachon == 1) {
			cout << "\n\t\t\tTHEM THONG TIN SO DIEN THOAI\n";
			DATA data;
			inputDATA(data);
			insertData(contact, data);
		}
		else if (luachon == 2) {
			cout << "\n\t\t\tXOA THONG TIN SO DIEN THOAI\n\n";
			int sdtData;
			cout << "\n\t\tNhap so dien thoai can xoa: ";
			cin >> sdtData;
			if (kiemTraTonTai(contact, sdtData)) { //Kiểm tra số điện thoại cần xóa có tồn tại hay không
				deleteContact(contact, sdtData);
				cout << "\n\t\tDeleted................\n";
				system("pause");
			}
			else {
				cout << "\n\t\tSo dien thoai khong ton tai\n\n";
				system("pause");
			}
		}
		else if (luachon == 3) {
			cout << "\n\t\t\tDANH SACH SO DIEN THOAI\n";
			duyetContact(contact);
			system("pause");
		}
		else if (luachon == 4) {
			int sdtData;
			cout << "\n\t\tNhap so dien thoai ban can tim: ";
			cin >> sdtData;
			searchPhoneNumber(contact, sdtData);
			system("pause");
		}
		else if(luachon == 0){
			break;
		}
	}
}


int main() {
	TREE contact = NULL;
	Menu(contact);
}
