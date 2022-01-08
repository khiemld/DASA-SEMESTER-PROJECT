#include<iostream>
using namespace std;
#include<cmath>
#include<time.h>
#include <iomanip>
const int MAX = 10000;

struct NODE {
	int data;
	NODE* pNext;
};

NODE* khoiTaoNode(int x) {
	NODE* p = new NODE;
	p->data = x;
	p->pNext = NULL;
	return p;
}

void themDau(NODE*& pHead, NODE* p) {
	if (pHead == NULL) {
		pHead = p;
	}
	else {
		p->pNext = pHead; //Lấy con trỏ của NODE p trỏ đến NODE đầu danh sách
		pHead = p; //Cập nhật lại NODE đầu
	}
}


bool ktNguyenTo(int x) {
	if (x < 2) {
		return false;
	}
	else {
		for (int i = 2; i <= sqrt(x); i++) {
			if (x % i == 0) {
				return false;
			}
		}
	}
	return true;
}

void xuatDanhSach(NODE* pHead) {
	int dem = 1;
	for (NODE* k = pHead; k != NULL; k = k->pNext) {
		cout << dem << ": " << k->data << "\n";
		dem++;
	}
}

void themCuoi(NODE*& pHead, NODE* p) {
	if (pHead == NULL) {
		pHead = p;
	}
	else {
		for (NODE* k = pHead; k != NULL; k = k->pNext) {
			//Kiểm tra nếu pNext hiện tại là NULL thì NODE đang duyệt là cuối danh sách
			if (k->pNext == NULL) {
				k->pNext = p; //thêm p vào cuối danh sách
				return; //Không cần duyệt nữa
			}
		}
	}
}




void xoaPhanTuDauDanhSach(NODE*& pHead) {
	if (pHead == NULL) {
		return;
	}
	else {
		NODE* k = pHead; //Node k tạm giữ NODE đầu danh sách
		pHead = pHead->pNext; //NODE pHead liên kết với NODE sau NODE k
		delete k;
	}
}

void xoaPhanTuCuoiDanhSach(NODE*& pHead) {
	if (pHead == NULL) {
		return;
	}
	else {
		NODE* q = NULL; //NODE q liên kết với NODE trước NODE k
		for (NODE* k = pHead; k != NULL; k = k->pNext) {
			if (k->pNext == NULL) {
				q->pNext = NULL; //Ngắt mỗi liên kết giữa NODE trước NODE k và NODE k
				delete k; //Xóa NODE k
				return; //Sau khi xóa NODE thì kết thúc công việc
			}
			q = k;

		}
	}
}

void xoa_NODE_Bat_Ky(NODE*& pHead, NODE* p) {
	if (pHead->data == p->data) {
		xoaPhanTuDauDanhSach(pHead);
	}
	else {
		NODE* q = NULL; //NODE q liên kết với NODE trước NODE k
		for (NODE* k = pHead; k != NULL; k = k->pNext) {
			if (k->data == p->data) {
				q->pNext = k->pNext; //NODE q liên kết kết với NODE sau NODE k
				delete k; //Xóa NODE k
				return;
			}
			q = k;
		}
	}
}

void timKiem(NODE* pHead, int sdt) {
	bool kt = false;
	for (NODE* k = pHead; k != NULL; k = k->pNext) {
		if (k->data == sdt) {
			cout << "\n\n\t\t" << k->data;
			kt = true;
			break;
		}
	}
	if (kt == false) {
		cout << "\n\tKhong co so dien thoai can tim";
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

//Các bước tiến hành test
//B1: Chọn chức năng số 1 để tạo danh sách số điện thoại
//B2: Chọn chức năng số 2 để thêm danh sách vào list
//B3: Có thể test chức năng tìm kiếm

void Menu(NODE*& pHead, int arr[], int& n, int sdt) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t======================DANH SACH LIEN KET DON SO NGUYEN====================== ";
		cout << "\n\t1. Nhap danh sach so dien thoai"; //Bước luôn được chọn đầu tiên để tạo ra danh sách số điện thoại để test
		cout << "\n\t2. Them NODE vao cuoi danh sach"; //Bước luôn được chọn thứ 2 để thêm danh sach vào linked list
		cout << "\n\t3. Xoa NODE bat ky";
		cout << "\n\t4. Xuat danh sach lien ket don";
		cout << "\n\t5. Tim kiem";
		cout << "\n\t0. Ket thuc";
		cout << "\n\n\t\t===================================END===================================";

		cout << "\nNhap lua chon: ";
		cin >> luachon;

		if (luachon == 1) {
		nhapDanhSachSDT(arr, n, sdt);
		system("pause");
		}
		else if (luachon == 4) {
			xuatDanhSach(pHead);
			system("pause");
		}
		else if (luachon == 2) {
			double a[MAX];
			for (int i = 0; i < n; i++) {
				NODE* p = khoiTaoNode(arr[i]);
				clock_t start, end;
				double cputime;
				start = clock();
				themCuoi(pHead, p);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				a[i] = cputime;
				cout << "\n\t\tCPU insert time: " << fixed << setprecision(20) << cputime;
			}
			timMaxAverage(a, n);
			system("pause");
		}
		else if (luachon == 3) {
			int x;
			cout << "Nhap gia tri can xoa: ";
			cin >> x;
			NODE* p = khoiTaoNode(x);
			p->data = x;
			p->pNext = NULL;
			xoa_NODE_Bat_Ky(pHead, p);
			system("pause");
		}
		else if (luachon == 5) {
			double a[MAX];
			for (int i = 0; i < n; i++) {
				clock_t start, end;
				double cputime;
				start = clock();
				timKiem(pHead, arr[i]);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				a[i] = cputime;
				cout << "\n\t\tCPU search time: " << fixed << setprecision(20) << cputime;
			}
			timMaxAverage(a, n);
			system("pause");
		}
		

	}
}

int main() {
	int arr[MAX];
	int n;
	int sdt = 999999999;
	NODE* pHead = NULL;
	Menu(pHead, arr, n, sdt);

	//Giải phóng vùng nhớ cho danh sách liên kết đơn
	for (NODE* k = pHead; k != NULL; k = k->pNext) {
		NODE* tam = pHead;// NODE tạm giữ con trỏ đầu danh sách
		pHead = pHead->pNext; //Cập nhật lại con trỏ đầu danh sách tiếp theo
		delete tam; //Giải phóng NODE đầu danh sách
	}
	return 0;

}