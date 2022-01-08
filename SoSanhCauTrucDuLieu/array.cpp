#include<iostream>
using namespace std;
#include<time.h>
#include <iomanip>

const int MAX = 10000;

void xoa(int arr[], int& n, int sdt) {
	int vt = -1;
	for (int i = 0; i < n; i++) {
		if (arr[i] == sdt) {
			vt = i;
			break;
		}
	}
	if (vt == -1) {
		cout << "\n\tKhong co phan tu can xoa";
	}
	else {
		for (int i = vt; i < n; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
	}
}

void xuat(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << "\n";
	}
}

void timKiem(int arr[], int n, int sdt) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == sdt) {
			cout << arr[i] << "\n";
			break;
		}
	}
}

void nhapDanhSachSDT(int arr[], int& n, int sdt, double a[]) {
	cout << "\n\tNhap so luong dien thoai: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		clock_t start, end;
		double cputime;
		start = clock();
		arr[i] = sdt;
		sdt--;
		end = clock();
		cputime = double(end - start) / CLOCKS_PER_SEC;
		a[i] = cputime;
		cout << "\n\t\tInsert time: " << fixed << setprecision(20) << cputime;
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


void menu(int &n, int ds[], int sdt) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t===========================BEGIN==============================";
		cout << "\n\n\t\t1. Them";
		cout << "\n\n\t\t2. Xoa";
		cout << "\n\n\t\t3. Tim kiem";
		cout << "\n\n\t\t4. Xuat";
		cout << "\n\n\t\t===========================END==============================";

		cout << "\n\tNhap lua chon: ";
		cin >> luachon;
		if (luachon == 1) {
			double a[MAX];
			nhapDanhSachSDT(ds, n, sdt, a);
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
			xoa(ds, n, sdt);
			end = clock();
			cputime = double(end - start) / CLOCKS_PER_SEC;
			cout << "\n\t\tCPU delete time: " << fixed << setprecision(20) << cputime;
			system("pause");

		}
		else if (luachon == 3) {
			double a[MAX];
			for (int i = 0; i < n; i++) {
				clock_t start, end;
				double cputime;
				start = clock();
				timKiem(ds, n, ds[i]);
				end = clock();
				cputime = double(end - start) / CLOCKS_PER_SEC;
				a[i] = cputime;
				cout << "\n\t\tCPU find time: " << fixed << setprecision(20) << cputime;
			}
			timMaxAverage(a, n);
			system("pause");
		}
		else if (luachon == 4) {
			cout << "\n\n\t\t";
			xuat(ds, n);
			system("pause");
		}
	}
}


int main() {
	int ds[MAX];
	int n;
	int sdt = 999999999;
	menu(n, ds, sdt);
}