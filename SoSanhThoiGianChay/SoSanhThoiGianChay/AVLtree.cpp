#include<iostream>
#include<cmath>
#include<time.h>
#include <iomanip>
using namespace std;
#include<fstream>
const int MAX = 50000;

struct NODE {
	int data;
	NODE* right;
	NODE* left;
	int height; //Chiều cao của node
};

NODE* newNode(int x)
{
	NODE* node = new NODE();
	node->data = x;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

//Hàm tìm chiều cao của node
int height(NODE* t) {
	return t == NULL ? 0 : t->height;
}


//Xoay phải
NODE* rightRotate(NODE* y)
{
	NODE* x = y->left;
	NODE* T2 = x->right;

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
NODE* leftRotate(NODE* x)
{
	NODE* y = x->right;
	NODE* T2 = y->left;

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
int balanceFactor(NODE* t) {
	return t == NULL ? 0 : (height(t->left) - height(t->right));
}

//Hàm thêm data
NODE* insertData(NODE*& contact, int data) {
	if (contact == NULL) { //Nếu cây rỗng
		return newNode(data);
	}
	if (contact->data < data) {
		contact->right = insertData(contact->right, data);
	}
	else if (contact->data > data) {
		contact->left = insertData(contact->left, data);
	}

	//Cập nhật lại hệ số cân bằng và cây cân bằng
	contact->height = 1 + max(height(contact->left), height(contact->right));
	int balance = balanceFactor(contact);
	// Left Left Case
	if (balance > 1 && data < contact->left->data)
		return rightRotate(contact);

	// Right Right Case
	if (balance < -1 && data> contact->right->data)
		return leftRotate(contact);

	// Left Right Case
	if (balance > 1 && data > contact->left->data)
	{
		contact->left = leftRotate(contact->left);
		return rightRotate(contact);
	}

	// Right Left Case
	if (balance < -1 && data < contact->right->data)
	{
		contact->right = rightRotate(contact->right);
		return leftRotate(contact);
	}
	return contact;
}

//Xóa
NODE* find_minValue(NODE* node) {
	NODE* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

NODE* deleteContact(NODE*& contact, int sdtData) {
	if (sdtData < contact->data)
		contact->left = deleteContact(contact->left, sdtData);
	else if (sdtData > contact->data)
		contact->right = deleteContact(contact->right, sdtData);
	else {
		if ((contact->left == NULL) || (contact->right == NULL)) {
			NODE* temp = contact->left ? contact->left : contact->right;
			if (temp == NULL) {
				temp = contact;
				contact = NULL;
			}
			else
				*contact = *temp;
			free(temp);
		}
		else {
			NODE* temp = find_minValue(contact->right);
			contact->data = temp->data;
			contact->right = deleteContact(contact->right, temp->data);
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

//Hàm duyệt data
void duyetContact(NODE* contact) {
	if (contact != NULL) {
		cout << contact->data << "\n";
		duyetContact(contact->left);
		duyetContact(contact->right);
	}
}


void timKiem(NODE* t, int x)
{
	if (t == NULL)
	{
		return;
	}
	else
	{
		if (x > t->data)
		{
			timKiem(t->right, x);
		}
		else if (x < t->data)
		{
			timKiem(t->left, x);
		}
		else
		{
			cout << "\n\t\t" << t->data << " ";
			return;
		}
	}
}

void nhapDanhSachSDT(int arr[], int& n, int sdt) {
	cout << "\n\tNhap so luong dien thoai: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		arr[i] = sdt;
		sdt--;
	}
	cout << "\n\tDanh sach so dien thoai da nhap\n";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << "\n";
	}
}

void timMaxAverage(double arr[], int n) {
	double max = arr[0];
	double average = 0;
	double sum = 0;

	for (int i = 1; i < n; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}

	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	average = sum / n;

	cout << "\n\t\tMax time: " << fixed << setprecision(20) << max;
	cout << "\n\t\tAverage time: " << fixed << setprecision(20) << average;
}

void ghiDataBinary(ofstream& fileout, int sdt) {
	clock_t start, end;
	double cputime;
	start = clock();
	fileout.write(reinterpret_cast<char*>(&sdt), sizeof(int));
	end = clock();
	cputime = double(end - start) / CLOCKS_PER_SEC;
}

void ghiDanhSachBinary(ofstream& fileout, NODE*& contact) {
	if (contact != NULL) {
		ghiDataBinary(fileout, contact->data);
		ghiDanhSachBinary(fileout, contact->left);
		ghiDanhSachBinary(fileout, contact->right);
	}

}

void docFileBinary(ifstream& filein, NODE*& contact) {
	while (filein.eof() == false) {
		int  data;
		filein.read(reinterpret_cast<char*>(&data), sizeof(int));
		contact = insertData(contact, data);
	}
}

//Các bước tiến hành test
//B1: Chọn chức năng số 5 để tạo danh sách số điện thoại
//B2: Chọn chức năng số 1 để thêm danh sách vào cây
//B3: Có thể test chức năng tìm kiếm, chức năng đọc, ghi file

void Menu(NODE*& tree, int ds[], int& n, int sdt, ifstream& filein, ofstream& fileout) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t===========================BEGIN==============================";
		cout << "\n\n\t\t1. Them";
		cout << "\n\n\t\t2. Xoa";
		cout << "\n\n\t\t3. Tim kiem";
		cout << "\n\n\t\t4. Xuat";
		cout << "\n\n\t\t5. Nhap danh sach so dien thoai";
		cout << "\n\n\t\t6 Ghi file nhi phan";
		cout << "\n\n\t\t7 Doc file nhi phan";
		cout << "\n\n\t\t===========================END==============================";

		cout << "\n\tNhap lua chon: ";
		cin >> luachon;
		if (luachon == 1) {
			double a[MAX];
			for (int i = 0; i < n; i++) {
				clock_t start, end;
				double cputime;
				start = clock();
				tree = insertData(tree, ds[i]);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				a[i] = cputime;
			}
			timMaxAverage(a, n);
			system("pause");
		}
		else if (luachon == 2) {
			int sdt;
			cout << "\n\tNhap xoa dien thoai can xoa: ";
			cin >> sdt;
			clock_t start, end;
			double cputime;
			start = clock();
			tree = deleteContact(tree, sdt);
			end = clock();
			cputime = double(end - start) / CLOCKS_PER_SEC;
			system("pause");

		}
		else if (luachon == 3) {
			double a[MAX];
			for (int i = 0; i < n; i++) {
				clock_t start, end;
				double cputime;
				start = clock();
				timKiem(tree, ds[i]);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				a[i] = cputime;
			}
			timMaxAverage(a, n);
			system("pause");
		}
		else if (luachon == 4) {
			cout << "\n\n";
			duyetContact(tree);
			system("pause");
		}
		else if (luachon == 5) {
			nhapDanhSachSDT(ds, n, sdt);
			system("pause");
		}
		else if (luachon == 6) { //ghi file
			fileout.open("data.dat", ios::out | ios::binary);
			if (!fileout) {
				cout << "Khong the ghi file. Vui long kiem tra lai!" << endl;
			}
			else {
				clock_t start, end;
				double cputime;
				start = clock();
				ghiDanhSachBinary(fileout, tree);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				cout << "\n\t\tCPU write file time: " << fixed << setprecision(20) << cputime;
				fileout.close();
				cout << "\n\t\t\tDanh sach da duoc ghi vao file....\n";
			}
			system("pause");
		}
		else if (luachon == 7) {
			filein.open("data.dat", ios::in | ios::binary);
			if (!filein) {
				cout << "Khong the doc file. Vui long kiem tra lai!" << endl;
			}
			else {
				clock_t start, end;
				double cputime;
				start = clock();
				docFileBinary(filein, tree);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				cout << "\n\t\tCPU total read time: " << fixed << setprecision(20) << cputime;
				filein.close();
				cout << "\n\t\t\tDanh sach da duoc doc....\n";
				system("pause");
			}
		}
	}
}

int main() {
	int ds[MAX];
	int n;
	int sdt = 999999999;
	NODE* tree = NULL;
	ifstream filein;
	ofstream fileout;
	Menu(tree, ds, n, sdt, filein, fileout);
}

