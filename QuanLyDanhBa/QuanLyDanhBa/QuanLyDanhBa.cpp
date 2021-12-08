#include<iostream>
#include <stdio.h>
#include <string>
#include<string.h>
#include<fstream>
#include<string.h>
#include<algorithm>
#pragma warning(disable : 4996)
using namespace std;

struct DATA {
	int SDT;
	char ten[50];
	int nhom; //1: Gia dinh, 2: Ban be, 3: Cong viec
	char gioiTinh[50];
	char diachi[50];
};

struct NODE {
	DATA data;
	NODE* pNext;
};

struct CONTACT { //Cây nhị phân tìm kiếm
	DATA data;
	CONTACT* right;
	CONTACT* left;
	int height; //Chiều cao của node
};
typedef CONTACT* TREE;

//Hàm kiểm tra số điện thoại hợp lệ
bool ktraSoDienThoai(string sdt) {
	if (sdt.length() != 10) {
		return false;
	}
	for (int i = 0; i < sdt.length(); i++) {
		if (sdt[i] <= '9' && sdt[i] >= '0')
			continue;
		else
			return false;
	}
}

//Hàm nhập thông tin DATA
void inputDATA(DATA& x) {
	cout << "\t\tNhap so dien thoai: ";
	cin >> x.SDT;
	
	while (getchar() != '\n');
	cout << "\t\tNhap ten: ";
	cin.getline(x.ten, 50);
	cout << "\t\tGioi tinh: ";
	cin.getline(x.gioiTinh, 50);
	cout << "\t\tDia chi: ";
	cin.getline(x.diachi, 50);
	//inputDateBirth(x.ngaysinh);
	cout << "\t\tChon nhom";
	cout << "\n\t\t\tNhap '1' chon Gia dinh";
	cout << "\n\t\t\tNhap '2' chon Ban be";
	cout << "\n\t\t\tNhap '3' chon Cong viec";
	cout << "\n\t\tLua chon: ";
	cin >> x.nhom;
}

//Khỏi tạo Node
NODE* khoiTaoNODE_nv(DATA x) {
	NODE* p = new NODE;
	p->data = x;
	p->pNext = NULL;
	return p;
}

//Thêm NODE vào cuối danh sách
void themNODE(NODE*& pHead, NODE* p) {
	if (pHead == NULL) {
		pHead = p;
	}
	else {
		for (NODE* k = pHead; k != NULL; k = k->pNext) {
			if (k->pNext == NULL) {
				k->pNext = p;
				return;
			}
		}
	}
}


//Xử lí chuyển dữ liệu từ BFS sang DSLKD
void BTStoLinkedList(TREE t, NODE*& pHead) {
	if (t != NULL) {
		NODE* p = khoiTaoNODE_nv(t->data);
		themNODE(pHead, p);
		BTStoLinkedList(t->right, pHead);
		BTStoLinkedList(t->left, pHead);
	}
}

CONTACT* newNode(DATA key)
{
	CONTACT* node = new CONTACT();
	node->data = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

//Tìm giá trị lớn nhất của 2 NODE
int max(int a, int b) {
	return (a > b) ? a : b;
}

//Hàm tìm chiều cao của node
int height(CONTACT* t) {
	return t == NULL ? 0 : t->height;
}


//Xoay phải
CONTACT* rightRotate(CONTACT* y)
{
	CONTACT* x = y->left;
	CONTACT* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),
		height(y->right)) + 1;
	x->height = max(height(x->left),
		height(x->right)) + 1;

	// Return new root
	return x;
}
//Xoay trái
CONTACT* leftRotate(CONTACT* x)
{
	CONTACT* y = x->right;
	CONTACT* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;

	// Return new root
	return y;
}


//Tìm hệ số cân bằng của NODE = chiều cao cây con trái trừ chiều cao cây con phải
int balanceFactor(CONTACT* t) {
	return t == NULL ? 0 : (height(t->left) - height(t->right));
}

//Hàm thêm data
CONTACT* insertData(TREE& contact, DATA data) {
	if (contact == NULL) { //Nếu cây rỗng
		return newNode(data);
	}
	if (contact->data.SDT < data.SDT) {
		contact->right = insertData(contact->right, data);
	}
	else if (contact->data.SDT > data.SDT) {
		contact->left = insertData(contact->left, data);
	}
	
	//Cập nhật lại hệ số cân bằng và cây cân bằng
	contact->height = 1 + max(height(contact->left), height(contact->right));
	int balance = balanceFactor(contact);
	// Left Left Case
	if (balance > 1 && data.SDT < contact->left->data.SDT)
		return rightRotate(contact);

	// Right Right Case
	if (balance < -1 && data.SDT > contact->right->data.SDT)
		return leftRotate(contact);

	// Left Right Case
	if (balance > 1 && data.SDT > contact->left->data.SDT)
	{
		contact->left = leftRotate(contact->left);
		return rightRotate(contact);
	}

	// Right Left Case
	if (balance < -1 && data.SDT < contact->right->data.SDT)
	{
		contact->right = rightRotate(contact->right);
		return leftRotate(contact);
	}
	return contact;
}

//Hàm xuất thông tin
void printDATA(DATA data) {
	cout << "\n\t\tTen: " << data.ten;
	cout << "\n\t\tSo dien thoai: 0" << data.SDT;
	cout << "\n\t\tGioi tinh: " << data.gioiTinh;
	cout << "\n\t\tDia chi: " << data.diachi;
	if (data.nhom == 1) {
		cout << "\n\t\tNhom: Gia dinh";
	}
	else if (data.nhom == 2) {
		cout << "\n\t\tNhom: Ban be";
	}
	else if (data.nhom == 3) {
		cout << "\n\t\tNhom: Cong viec";
	}
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
		if (sdtData == contact->data.SDT)
		{
			return true;
		}
		else if (sdtData > contact->data.SDT)
		{
			return	kiemTraTonTai(contact->right, sdtData);
		}
		else if (sdtData < contact->data.SDT)
		{
			return kiemTraTonTai(contact->left, sdtData);
		}
	}
	return false;
}

//Xóa
CONTACT* find_minValue(CONTACT* node) {
	CONTACT* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

CONTACT* deleteContact(TREE& contact, int sdtData) {
	if (contact == NULL)
		return contact;
	if (sdtData < contact->data.SDT)
		contact->left = deleteContact(contact->left, sdtData);
	else if (sdtData > contact->data.SDT)
		contact->right = deleteContact(contact->right, sdtData);
	else {
		if ((contact->left == NULL) || (contact->right == NULL)) {
			CONTACT* temp = contact->left ? contact->left : contact->right;
			if (temp == NULL) {
				temp = contact;
				contact = NULL;
			}
			else
				*contact = *temp;
			free(temp);
		}
		else {
			CONTACT* temp = find_minValue(contact->right);
			contact->data = temp->data;
			contact->right = deleteContact(contact->right, temp->data.SDT);
		}
	}

	if (contact == NULL)
		return contact;
	// Cập nhật hệ số cân bằng
	contact->height = 1 + max(height(contact->left),
		height(contact->right));
	int balance = balanceFactor(contact);
	if (balance > 1 && balanceFactor(contact->left) >= 0)
		return rightRotate(contact);

	if (balance > 1 && balanceFactor(contact->left) < 0) {
		contact->left = leftRotate(contact->left);
		return rightRotate(contact);
	}

	if (balance < -1 && balanceFactor(contact->right) <= 0)
		return leftRotate(contact);

	if (balance < -1 && balanceFactor(contact->right) > 0) {
		contact->right = rightRotate(contact->right);
		return leftRotate(contact);
	}
	return contact;

		
}

void XuatDanhBaTheoTen(NODE* pHead) {
	for (NODE* k = pHead; k != NULL; k = k->pNext) {
		for (NODE* h = k->pNext; h != NULL; h = h->pNext) {
			string str1 = k->data.ten;
			string str2 = h->data.ten;
			transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
			transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
			if (str1.compare(str2) > 0) {
				swap(k->data, h->data);
			}
		}
	}

	//Xuất họ tên nhân viên
	for (NODE* k = pHead; k != NULL; k = k->pNext) {
		printDATA(k->data);
	}
}


void searchPhoneNumber(TREE& contact, int sdtData, bool& flat)
{
	if (contact != NULL) {
		string data = to_string(sdtData); // Convert số nhập vào sang kiểu string
		string Contact = to_string(contact->data.SDT); //Convert số trong cây nhị phân sang kiểu string

		if (data == Contact)
		{
			printDATA(contact->data); // Nếu số nhập vào trùng thì in thông tin danh bạ
			flat = 1;
		}
		else {
			int m = data.size();
			int n = Contact.size();
			int count = 0;

			for (int i = 0; i < m; i++) {
				if (data[i] == Contact[i]) //Nếu từng chữ số nhập vào trùng với các chữ số trong cây nhị phân
					count++; //  thì ta tăng biến đếm

				if (count == data.size()) // Nếu biến đếm trùng với kích thước của số nhập vào
				{
					printDATA(contact->data); // thì ta in thông tin danh bạ
					flat = 1;
				}

			}
		}
		searchPhoneNumber(contact->left, sdtData, flat); // Tiếp tục tìm kiếm các số trùng với số nhập vào ở bên trái
		searchPhoneNumber(contact->right, sdtData, flat); // và ở bên phải	
	}

}
//Tim thong tin theo ten
void Chuyenkytu(string& s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 65 && s[i] <= 90)
			s[i] = s[i] + 32;
	}
}
void SearchName(NODE*& data, char name[], int x, int& sl)
{
	if (data == NULL)
		return;
	NODE* p = data;
	string s = p->data.ten;
	for (int i = 0; i <= s.length()-x ; i++)
	{
		string name2 = s.substr(i, x);//  coppy n phan tu dau cua choi
		Chuyenkytu(name2);
		if (name2.compare(name) == 0)// so sanh 2 chuoi
		{
			printDATA(p->data);
			sl++;
			break;
		}
		fflush(stdin);
	}
	fflush(stdin);
	SearchName(p->pNext, name, x, sl);
}
void Chinhsua(char name[], TREE& contact)
{

	if (contact == NULL)
		return;
	string name2 = contact->data.ten;
	Chuyenkytu(name2);
	if (name2.compare(name) == 0)
	{
		int yeucau;
		while (true) {
			system("cls");
			printDATA(contact->data);
			cout << "\n\n\t\t:::::::::::::::::CHON THONG TIN CAN CHINH SUA:::::::::::::::::::::";
			cout << "\n\n\t\t1. Ten";
			cout << "\n\n\t\t2. So dien thoai";
			cout << "\n\n\t\t3. Nhom";
			cout << "\n\n\t\t4. Gioi tinh";
			cout << "\n\n\t\t5. Dia Chi";
			cout << "\n\n\t\t0. Ket thuc";
			cout << "\n\n\t\t\t Chon chuc nang: ";
			cin >> yeucau;
			if (yeucau == 1)
			{
				char name3[50];
				cout << "\n\n\t\tNhap Ten Moi:  ";
				fflush(stdin);
				while (getchar() != '\n');
				cin.getline(name3, 50);
				int len = strlen(name3);
				contact->data.ten[len] = name3[len];

			}
			else if (yeucau == 2)
			{
				int newsdt;
				cout << "\n\n\t\tNhap so dien thoai moi:  ";
				cin >> newsdt;

				contact->data.SDT = newsdt;
			}
			else if (yeucau == 3)
			{
				int suanhom;
				cout << "\t\tChon nhom: ";
				cout << "\n\t\t\tNhap '1' chon Gia dinh";
				cout << "\n\t\t\tNhap '2' chon Ban be";
				cout << "\n\t\t\tNhap '3' chon Cong viec";
				cout << "\n\t\tLua chon: ";
				cin >> suanhom;

				contact->data.nhom = suanhom;
			}
			else if (yeucau == 4)
			{
				char gioitinh[50];
				cout << "\n\n\t\tNhap gioi tinh:  ";
				fflush(stdin);
				while (getchar() != '\n');
				cin.getline(gioitinh, 50);
				int len = strlen(gioitinh);
				contact->data.gioiTinh[len] = gioitinh[len];
			}
			else if (yeucau == 5)
			{
				char newdiachi[50];
				cout << "\n\n\t\tNhap dia chi:  ";
				fflush(stdin);
				while (getchar() != '\n');
				cin.getline(newdiachi, 50);
				int len = strlen(newdiachi);
				contact->data.diachi[len] = newdiachi[len];
			}
			else if (yeucau == 0)
			{
				break;
			}
		}
	}
	else
	{
		if (contact->left != NULL)
		{
			Chinhsua(name, contact->left);
		}
		if (contact->right != NULL)
		{
			Chinhsua(name, contact->right);
		}
	}
}
//Hàm xuất danh sách theo nhóm
void printGroup(TREE contact, int maNhom) {
	if (contact != NULL) {
		if (contact->data.nhom == maNhom)
			printDATA(contact->data);
		printGroup(contact->left, maNhom);
		printGroup(contact->right, maNhom);
	}
}

void ghiDataBinary(ofstream& fileout, DATA& data) {
	fileout.write(reinterpret_cast<char*>(&data), sizeof(DATA));
}

void ghiDanhSachBinary(ofstream& fileout, TREE& contact) {
	int i = 0;
	if (contact != NULL) {
		ghiDataBinary(fileout, contact->data);
		ghiDanhSachBinary(fileout, contact->left);
		ghiDanhSachBinary(fileout, contact->right);
	}
}

void docFileBinary(ifstream& filein, TREE& contact) {
	if (!filein) {
		cout << "\n\t\t\tDuong dan khong hop le";
	}
	while (filein.eof() == false) {
		DATA  data;
		filein.read(reinterpret_cast<char*>(&data), sizeof(DATA));
		contact = insertData(contact, data);
	}
}

void Menu(TREE& contact, NODE*& pHead, ofstream& fileout, ifstream& filein) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t::::::::::::::::::::::::::::QUAN LY DANH BA DIEN THOAI::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t1. Them thong tin so dien thoai";
		cout << "\n\n\t\t2. Xoa thong tin so dien thoai";
		cout << "\n\n\t\t3. Xuat danh sach so dien thoai";
		cout << "\n\n\t\t4. Tim thong tin danh ba theo so dien thoai";
		cout << "\n\n\t\t5. Xuat danh sach so dien thoai theo ten";
		cout << "\n\n\t\t6. Xuat danh sach theo nhom";
		cout << "\n\n\t\t7. Tim thong tin theo ten";
		cout << "\n\n\t\t8. Chinh sua thong tin danh ba";
		cout << "\n\n\t\t9. Ghi file";
		cout << "\n\n\t\t10. Doc file";
		cout << "\n\n\t\t0. Ket thuc";
		cout << "\n\n\t\t:::::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t\t Chon chuc nang: ";
		cin >> luachon;

		if (luachon == 1) {
			cout << "\n\t\t\tTHEM THONG TIN SO DIEN THOAI\n";
			DATA data;
			inputDATA(data);
			if (kiemTraTonTai(contact, data.SDT)) {
				cout << "\n\t\tSo dien thoai da ton tai. Vui long kiem tra lai!\n";
			}
			else { 
				contact = insertData(contact, data); 
				cout << "\n\t\tThong tin da duoc them....\n";
			}
			system("pause");
		}
		else if (luachon == 2) {
			cout << "\n\t\t\tXOA THONG TIN SO DIEN THOAI\n\n";
			int sdtData;
			cout << "\n\t\tNhap so dien thoai can xoa: ";
			cin >> sdtData;
			if (kiemTraTonTai(contact, sdtData)) { //Kiểm tra số điện thoại cần xóa có tồn tại hay không
				contact = deleteContact(contact, sdtData);
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
			cout << "\n\t\t\tTIM KIEM SO DIEN THOAI";
			int sdtData;
			bool flat = 0;
			cout << "\n\t\tNhap so dien thoai ban can tim: ";
			cin >> sdtData;
			searchPhoneNumber(contact, sdtData, flat);
			if (flat == 0)
				cout << "\n\t\tSo dien thoai khong ton tai\n\n";
			system("pause");
		}
		else if (luachon == 5) {
			cout << "\n\t\t\tXUAT DANH SACH THEO TEN";
			BTStoLinkedList(contact, pHead);
			XuatDanhBaTheoTen(pHead);
			NODE* tam = NULL;
			while (pHead != NULL) {
				tam = pHead;
				pHead = pHead->pNext;
				delete tam;
			}
			system("pause");
		}
		else if (luachon == 6) {
			cout << "\n\t\t\tXUAT DANH SACH THEO NHOM";
			cout << "\n\t\tBan muon xuat danh sach nhom?";
			cout << "\n\t\t\tNhap '1' chon Gia dinh";
			cout << "\n\t\t\tNhap '2' chon Ban be";
			cout << "\n\t\t\tNhap '3' chon Cong viec";
			cout << "\n\t\tLua chon: ";
			int maNhom;
			cin >> maNhom;
			printGroup(contact, maNhom);
			system("pause");
		}
		else if (luachon == 7) {
			cout << "\n\t\t\tTIM KIEM THEO TEN";
			BTStoLinkedList(contact, pHead);
			cout << "\n\t\t\tNhap ten can tim : ";
			char name[50];
			fflush(stdin);
			while (getchar() != '\n');
			cin.getline(name, 50);
			strlwr(name);
			int leng = strlen(name);
			int sl = 0;
			SearchName(pHead, name, leng, sl);
			if (sl != 0)
			{
				NODE* tam = NULL;
				while (pHead != NULL) {
					tam = pHead;
					pHead = pHead->pNext;
					delete tam;
				}
			}
			else
			{
				cout << "\n\t\tKhong tim thay ten\n\n";
			}
			system("pause");
		}
		else if (luachon == 8) {
			cout << "\n\t\t\tCHINH SUA THONG TIN DANH BA";
			cout << "\n\t\t\tNhap ten nguoi can chinh sua : ";
			char name[50];
			fflush(stdin);
			while (getchar() != '\n');
			cin.getline(name, 50);
			strlwr(name);
			Chinhsua(name, contact);
			system("pause");
			
		}
		else if (luachon == 9) {
		fileout.open("data.dat", ios::out | ios::binary);
		
		if (!fileout) {
			cout << "Khong the ghi file. Vui long kiem tra lai!" << endl;
		}
		ghiDanhSachBinary(fileout, contact);
		fileout.close();
		cout << "\n\t\t\tDanh sach da duoc ghi vao file....\n";
		system("pause");
		}
		else if (luachon == 10) {
		if (!filein) {
			cout << "Khong the doc file. Vui long kiem tra lai!" << endl;
		}
		docFileBinary(filein, contact);
		fileout.close();
		cout << "\n\t\t\tDanh sach da duoc doc....\n";
		system("pause");
		}
		else if (luachon == 0) {
			break;
		}
	}
}


int main() {
	TREE contact = NULL;
	NODE* pHead = NULL;
	ifstream filein;
	ofstream fileout;
	filein.open("data.dat", ios::in | ios::binary);

	Menu(contact, pHead, fileout, filein);
}
