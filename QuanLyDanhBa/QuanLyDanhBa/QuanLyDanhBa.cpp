#include<iostream>
#include <stdio.h>
#include <string>
#include<fstream>
#include<string.h>
#include<algorithm>
using namespace std;

struct DATE {
	int day = 1;
	int month = 1;
	int year = 1;
};

struct SDT {
	int sdt;
	string loai;
};

struct DATA {
	SDT  SDT;
	string ten;
	int nhom; //1: Gia dinh, 2: Ban be, 3: Cong viec
	string gioiTinh;
	string diachi;
	DATE ngaysinh;
	string email;
	string ghiChu;
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

//Hàm nhập thông tin DATA
void inputDATA(DATA& x) {
	while (getchar() != '\n');
	cout << "\t\tNhap ten: ";
	getline(cin, x.ten);
	cout << "\t\tGioi tinh: ";
	getline(cin, x.gioiTinh);
	inputPhoneNumber(x.SDT);
	while (getchar() != '\n');
	cout << "\t\tDia chi: ";
	getline(cin, x.diachi);
	inputDateBirth(x.ngaysinh);
	cout << "\t\tChon nhom";
	cout << "\n\t\t\tNhap '1' chon Gia dinh";
	cout << "\n\t\t\tNhap '2' chon Ban be";
	cout << "\n\t\t\tNhap '3' chon Cong viec";
	cout << "\n\t\tLua chon: ";
	cin >> x.nhom;
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
		else if (ktMail == "n") {
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
		else if (ktNote == "n") {
			x.ghiChu = "";
			break;
		}
	} while (ktNote != "y" && ktNote != "n");
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
	node->height = 1; // new node is initially
					  // added at leaf
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
	if (contact->data.SDT.sdt < data.SDT.sdt) {
		contact->right = insertData(contact->right, data);
	}
	else if (contact->data.SDT.sdt > data.SDT.sdt) {
		contact->left = insertData(contact->left, data);
	}
	
	//Cập nhật lại hệ số cân bằng và cây cân bằng
	contact->height = 1 + max(height(contact->left), height(contact->right));
	int balance = balanceFactor(contact);
	// Left Left Case
	if (balance > 1 && data.SDT.sdt < contact->left->data.SDT.sdt)
		return rightRotate(contact);

	// Right Right Case
	if (balance < -1 && data.SDT.sdt > contact->right->data.SDT.sdt)
		return leftRotate(contact);

	// Left Right Case
	if (balance > 1 && data.SDT.sdt > contact->left->data.SDT.sdt)
	{
		contact->left = leftRotate(contact->left);
		return rightRotate(contact);
	}

	// Right Left Case
	if (balance < -1 && data.SDT.sdt < contact->right->data.SDT.sdt)
	{
		contact->right = rightRotate(contact->right);
		return leftRotate(contact);
	}
	/* return the (unchanged) node pointer */
	return contact;
}

//Hàm xuất thông tin
void printDATA(DATA data) {
	cout << "\n\t\tTen: " << data.ten;
	cout << "\n\t\tSo dien thoai: 0" << data.SDT.sdt;
	cout << "\n\t\tNha mang: " << data.SDT.loai;
	cout << "\n\t\tGioi tinh: " << data.gioiTinh;
	cout << "\n\t\tDia chi: " << data.diachi;
	cout << "\n\t\tNgay sinh: " << data.ngaysinh.day << "/" << data.ngaysinh.month << "/" << data.ngaysinh.year;
	if (data.nhom == 1) {
		cout << "\n\t\tNhom: Gia dinh";
	}
	else if (data.nhom == 2) {
		cout << "\n\t\tNhom: Ban be";
	}
	else if (data.nhom == 3) {
		cout << "\n\t\tNhom: Cong viec";
	}
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
CONTACT* find_minValue(CONTACT* node) {
	CONTACT* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

CONTACT* deleteContact(TREE& contact, int sdtData) {
	if (contact == NULL)
		return contact;
	if (sdtData < contact->data.SDT.sdt)
		contact->left = deleteContact(contact->left, sdtData);
	else if (sdtData > contact->data.SDT.sdt)
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
			contact->right = deleteContact(contact->right, temp->data.SDT.sdt);
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
		string Contact = to_string(contact->data.SDT.sdt); //Convert số trong cây nhị phân sang kiểu string

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
void SearchName(NODE*& data, string name, int x, int& sl)
{
	if (data == NULL)
		return;
	NODE* p = data;

	for (int i = 0; i <= p->data.ten.length()-x ; i++)
	{
		string name2 = p->data.ten.substr(i, x);//  coppy n phan tu dau cua choi
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
//Hàm chỉnh sưa thông tin
void Chinhsua(NODE*& data, string name)
{
	if (data == NULL)
		return;
	string name2 = data->data.ten;
	Chuyenkytu(name2);
	if (name2.compare(name) == 0)
	{
		int yeucau;
		while (true) {
			system("cls");
			printDATA(data->data);
			cout << "\n\n\t\t:::::::::::::::::CHON THONG TIN CAN CHINH SUA:::::::::::::::::::::";
			cout << "\n\n\t\t1. Ten";
			cout << "\n\n\t\t2. So dien thoai";
			cout << "\n\n\t\t3. Ghi chu";
			cout << "\n\n\t\t4. Nhom";
			cout << "\n\n\t\t5. Gioi tinh";
			cout << "\n\n\t\t6. Dia Chi";
			cout << "\n\n\t\t7. Ngay sinh";
			cout << "\n\n\t\t8. email";
			cout << "\n\n\t\t0. Ket thuc";
			cout << "\n\n\t\t\t Chon chuc nang: ";
			cin >> yeucau;
			if (yeucau == 1)
			{
				string name3;
				cout << "\n\n\t\tNhap Ten Moi:  ";
				fflush(stdin);
				while (getchar() != '\n');
				getline(cin, name3);
				data->data.ten = name3;
				//printDATA(data->data);
				//system("pause");
			}
			else if (yeucau == 2)
			{
				int newsdt;
				cout << "\n\n\t\tNhap so dien thoai moi:  ";
				cin >> newsdt;
				data->data.SDT.sdt = newsdt;
				//printDATA(data->data);
			//	system("pause");
			}
			else if (yeucau == 3)
			{
				string newkeep;
				cout << "\n\n\t\tNhap ghi chu:  ";
				fflush(stdin);
				while (getchar() != '\n');
				getline(cin, newkeep);
				data->data.ghiChu = newkeep;
			//	printDATA(data->data);
			//	system("pause");
			}
			else if (yeucau == 4)
			{
				int suanhom;
				cout << "\t\tChon nhom: ";
				cout << "\n\t\t\tNhap '1' chon Gia dinh";
				cout << "\n\t\t\tNhap '2' chon Ban be";
				cout << "\n\t\t\tNhap '3' chon Cong viec";
				cout << "\n\t\tLua chon: ";
				cin >> suanhom;
				data->data.nhom = suanhom;
			//	printDATA(data->data);
				//system("pause");
			}
			else if (yeucau == 5)
			{
				string gioitinh;
				cout << "\n\n\t\tNhap gioi tinh:  ";
				fflush(stdin);
				while (getchar() != '\n');
				getline(cin, gioitinh);
				data->data.gioiTinh = gioitinh;
			//	printDATA(data->data);
				//system("pause");
			}
			else if (yeucau == 6)
			{
				string newdiachi;
				cout << "\n\n\t\tNhap dia chi:  ";
				fflush(stdin);
				while (getchar() != '\n');
				getline(cin, newdiachi);
				data->data.diachi = newdiachi;
			//	printDATA(data->data);
			//	system("pause");
			}
			else if (yeucau == 7)
			{
				inputDateBirth(data->data.ngaysinh);
			//	printDATA(data->data);
			//	system("pause");
			}
			else if (yeucau == 8) {
				string newmail;
				cout << "\n\n\t\tNhap email:  ";
				fflush(stdin);
				while (getchar() != '\n');
				getline(cin, newmail);
				data->data.email = newmail;
				//printDATA(data->data);
			//	system("pause");
			}
			else if (yeucau == 0)
			{
				break;
			}
		}

	}
	else
	{
		Chinhsua(data->pNext, name);
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

void Menu(TREE& contact, NODE*& pHead) {
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
		cout << "\n\n\t\t0. Ket thuc";
		cout << "\n\n\t\t:::::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::::::::::";
		cout << "\n\n\t\t\t Chon chuc nang: ";
		cin >> luachon;

		if (luachon == 1) {
			cout << "\n\t\t\tTHEM THONG TIN SO DIEN THOAI\n";
			DATA data;
			inputDATA(data);
			contact = insertData(contact, data);
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
			string name;
			fflush(stdin);
			while (getchar() != '\n');
			getline(cin, name);
			Chuyenkytu(name);
			int leng = name.length();
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
			BTStoLinkedList(contact, pHead);
			cout << "\n\t\t\tNhap ten nguoi can chinh sua : ";
			string name;
			fflush(stdin);
			while (getchar() != '\n');
			getline(cin, name);
			Chuyenkytu(name);
			Chinhsua(pHead,name);
			NODE* tam = NULL;
			while (pHead != NULL) {
				tam = pHead;
				pHead = pHead->pNext;
				delete tam;
			}
			system("pause");
			
		}
		else if (luachon == 0) {
			break;
		}
	}
}

//Doc mot thong tin
void docData(ifstream& filein, DATA& data) {
	getline(filein, data.ten, ',');
	getline(filein, data.gioiTinh, ',');
	getline(filein, data.diachi);
	filein >> data.SDT.sdt >> data.nhom >> data.ngaysinh.day >> data.ngaysinh.month >> data.ngaysinh.year;
}


//Doc danh sach thong tin
void docDanhSachData(ifstream& filein, TREE& contact) {
	while (filein.eof() == false) {
		DATA data;
		docData(filein, data);
		insertData(contact, data);
	}
}

int main() {
	TREE contact = NULL;
	NODE* pHead = NULL;
	/*ifstream filein;
	filein.open("input.txt", ios_base::in);
	if (filein.fail()) {
		cout << "\n\t\t\tDuong dan khong hop le";
		return 0;
	}
	docDanhSachData(filein, contact);
	filein.close();*/
	Menu(contact, pHead);
}
