#include<iostream>
using namespace std;

struct CONTACT {
	SDT ds_SDT[10];
	string ten;
	NHOM nhom;
	bool gioiTinh;
	DIACHI diachi;
	DATE ngaysinh;
	string email;
	string ghiChu;
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
	SDT* next;
	CONTACT conTact;
};

struct DIACHI {
	string huyen;
	string tinh;
	string nuoc;
	DIACHI* next;
	CONTACT* ds_contact;
};

struct NHOM {
	string ten;
	CONTACT* ds_contact;
	NHOM* next;
};