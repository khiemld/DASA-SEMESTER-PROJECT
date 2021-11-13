
#include<iostream>
using namespace std;
#include<string>
#include<conio.h>

struct FLIGHT {
	string code;
	string day;
	string name;
	string time;
	string start;
	string desti;
};

struct LIST {
	FLIGHT* ds[100];
	int soluong;
};

void nhap(FLIGHT& x);
void xuat(FLIGHT x);
void inListFlight(LIST& dsbay);
void outListFlight(LIST dsbay);
void erase(LIST& dsbay, int vt);
void eraseCode(LIST& dsbay);
void insertFlight(LIST& dsbay);
int yearFlight(string x);
void hoanVi(FLIGHT* x, FLIGHT* y);
void sapXepTangDanTheoNam(LIST& dsbay);
void timChuyenBayTheoNgay(LIST dsbay);
void timChuyenBayTheoMaSo(LIST dsbay);
int monthFlight(string x);
int dayFlight(string x);
bool ktNamNhuan(int y);
int countDay(int d, int m, int y);
int ngayTrongThang(int m, int y);
void timChuyenBayTheoKhoangThoiGian(LIST dsbay);
void timChuyenBayTheoTenHanhKhach(LIST dsbay);
void Menu(LIST dsbay);

int main() {
	LIST dsbay;
	dsbay.soluong = 0;
	Menu(dsbay);
	return 0;
}

void Menu(LIST dsbay) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t========== QUAN LI CHUYEN BAY ==========";
		cout << "\n\t\t1. NHAP DANH SACH THONG TIN CHUYEN BAY";
		cout << "\n\t\t2. XUAT THONG TIN CAC CHUYEN BAY";
		cout << "\n\t\t3. XOA CHUYEN BAY CO MA SO BAT KY";
		cout << "\n\t\t4. THEM CHUYEN BAY MOI VAO DANH SACH";
		cout << "\n\t\t5. SAP XEP CHUYEN BAY TANG DAN THEO NAM";
		cout << "\n\t\t6. TIM KIEM CHUYEN BAY CO NGAY BAT KY";
		cout << "\n\t\t7. TIM KIEM CHUYEN BAY CO MA SO BAT KY";
		cout << "\n\t\t8. TIM KIEM CAC CHUYEN BAY TRONG KHOANG THOI GIAN (X, Y) CHO TRUOC";
		cout << "\n\t\t9. TIM KIEM CHUYEN BAY THEO HO TEN HANH KHACH";
		cout << "\n\t\t0. KET THUC";
		cout << "\n\n\t\t============= THANK YOU! ===============";

		cout << "\nNhap lua chon: ";
		cin >> luachon;

		if (luachon == 1) {
			cout << "\n\t\tNHAP THONG TIN CHUYEN BAY";
			inListFlight(dsbay);
		}
		else if (luachon == 2) {
			cout << "\n\t\tXUAT THONG TIN CHUYEN BAY";
			outListFlight(dsbay);
			system("pause");
		}
		else if (luachon == 3) {
			cout << "\n\t\tXOA CHUYEN BAY CO MA SO BAT KY";
			eraseCode(dsbay);
		}
		else if (luachon == 4) {
			cout << "\n\t\tTHEM CHUYEN BAY MOI VAO DANH SACH";
			insertFlight(dsbay);
		}
		else if (luachon == 5) {
			cout << "\n\t\tSAP XEP CHUYEN BAY TANG DAN THEO NAM";
			sapXepTangDanTheoNam(dsbay);
			system("pause");
		}
		else if (luachon == 6) {
			cout << "\n\t\tTIM KIEM CHUYEN BAY CO NGAY BAT KY";
			timChuyenBayTheoNgay(dsbay);
			system("pause");
		}
		else if (luachon == 7) {
			cout << "\n\t\tTIM KIEM CHUYEN BAY CO MA SO BAT KY";
			timChuyenBayTheoMaSo(dsbay);
			system("pause");
		}
		else if (luachon == 8) {
			cout << "\n\t\tTIM KIEM CAC CHUYEN BAY TRONG KHOANG THOI GIAN (X, Y) CHO TRUOC";
			timChuyenBayTheoKhoangThoiGian(dsbay);
			system("pause");
		}
		else if (luachon == 9) {
			cout << "\n\t\tTIM KIEM CHUYEN BAY THEO HO TEN HANH KHACH";
			timChuyenBayTheoTenHanhKhach(dsbay);
			system("pause");
		}
		else {
			break;
		}
	}
}


//Nhập thông tin một chuyến bay
void nhap(FLIGHT& x) {

	do {
		cout << "\nNhap ma bay: ";
		getline(cin, x.code);
		if (x.code.length() > 5) {
			cout << "Nhap lai ma chuyen bay: (Tối đa 5 kí tự)";
		}
	} while (x.code.length() > 5);

	do {
		cout << "Nhap ho ten hanh khach: ";
		getline(cin, x.name);
		if (x.name.length() > 30) {
			cout << "Nhap lai ho ten: (Tối đa 30 kí tự)";
		}
	} while (x.name.length() > 30);

	cout << "Nhap ngay bay: ";
	getline(cin, x.day);

	cout << "Nhap gio bay: ";
	getline(cin, x.time);

	do {
		cout << "Nhap noi di: ";
		getline(cin, x.start);
		if (x.start.length() > 20) {
			cout << "Nhap lai noi di: (Tối đa 20 kí tự)";
		}
	} while (x.start.length() > 20);

	do {
		cout << "Nhap noi den: ";
		getline(cin, x.desti);
		if (x.desti.length() > 20) {
			cout << "Nhap lai noi den: (Tối đa 20 kí tự)";
		}
	} while (x.desti.length() > 20);
}

//Xuất thông tin một chuyến bay
void xuat(FLIGHT x) {
	cout << "\nMa chuyen bay: " << x.code;
	cout << "\nTen hanh khach: " << x.name;
	cout << "\nNgay bay: " << x.day;
	cout << "\nGio bay: " << x.time;
	cout << "\nNoi di: " << x.start;
	cout << "\nNoi den: " << x.desti;
}


//Nhập thông tin danh sách chuyến bay
void inListFlight(LIST& dsbay) {
	cout << "\n\tNhap so luong chuyen bay: ";
	cin >> dsbay.soluong;
	while (getchar() != '\n');
	for (int i = 0; i < dsbay.soluong; i++) {
		cout << "\nNhap thong tin chuyen bay thu " << i + 1;
		dsbay.ds[i] = new FLIGHT;
		nhap(*dsbay.ds[i]);
	}
}

//Xuất thông tin danh sách chuyến bay
void outListFlight(LIST dsbay) {
	for (int i = 0; i < dsbay.soluong; i++) {
		cout << "\n\tThong tin chuyen bay thu " << i + 1;
		xuat(*dsbay.ds[i]);
	}
}

//Xóa chuyến bay có mã chuyến bay bất kì
void erase(LIST& dsbay, int vt) {
	for (int i = vt + 1; i < dsbay.soluong; i++) {
		dsbay.ds[i - 1] = dsbay.ds[i];
	}
	dsbay.soluong--;
}

void eraseCode(LIST& dsbay) {
	string codeF;
	do {
		cout << "\nNhap ma bay can xoa: ";
		while (getchar() != '\n');
		getline(cin, codeF);
		if (codeF.length() > 5) {
			cout << "Nhap lai ma chuyen bay can xoa: (Tối đa 5 kí tự)";
		}
	} while (codeF.length() > 5);

	for (int i = 0; i < dsbay.soluong; i++) {
		if (dsbay.ds[i]->code == codeF) {
			erase(dsbay, i);
		}
	}
}

//Thêm chuyến bay
void insertFlight(LIST& dsbay) {
	FLIGHT x;
	while (getchar() != '\n');
	cout << "\nNhap chuyen bay can them";
	nhap(x);
	dsbay.ds[dsbay.soluong] = new FLIGHT;
	*dsbay.ds[dsbay.soluong] = x;
	dsbay.soluong++;
}


//Lấy năm bay
int yearFlight(string x) {
	string year;
	for (int i = x.length() - 1; i >= 0; i--) {
		if (x[i] != '/') {
			year.insert(year.begin() + 0, x[i]);
		}
		else {
			break;
		}
	}

	int nam = atoi((char*)year.c_str()); //Hàm chuyển chuỗi số thành số nguyên
	return nam;
}

void hoanVi(FLIGHT* x, FLIGHT* y) {
	FLIGHT* tam;
	tam = new FLIGHT;
	*tam = *x;
	*x = *y;
	*y = *tam;
}

//Sắp xếp danh sách chuyến bay tăng dần theo năm bay
void sapXepTangDanTheoNam(LIST& dsbay) {
	for (int i = 0; i < dsbay.soluong; i++) {
		int x = yearFlight(dsbay.ds[i]->day);
		for (int j = i + 1; j < dsbay.soluong; j++) {
			int y = yearFlight(dsbay.ds[j]->day);
			if (x > y) {
				hoanVi(dsbay.ds[i], dsbay.ds[j]);
			}
		}
	}

	outListFlight(dsbay);
}


//Tìm kiếm chuyến bay có ngày bay bất kì
void timChuyenBayTheoNgay(LIST dsbay) {
	string ngay;
	cout << "\nNhap ngay can tim: ";
	while (getchar() != '\n');
	getline(cin, ngay);

	for (int i = 0; i < dsbay.soluong; i++) {
		if (ngay == dsbay.ds[i]->day) {
			xuat(*dsbay.ds[i]);
			cout << endl;
		}
	}
}


//Tìm chuyến bay theo mã
void timChuyenBayTheoMaSo(LIST dsbay) {
	string maso;
	do {
		cout << "\nNhap ma bay can tim ";
		while (getchar() != '\n');
		getline(cin, maso);
		if (maso.length() > 5) {
			cout << "Nhap lai ma chuyen bay can tim: (Tối đa 5 kí tự)";
		}
	} while (maso.length() > 5);

	for (int i = 0; i < dsbay.soluong; i++) {
		if (maso == dsbay.ds[i]->code) {
			xuat(*dsbay.ds[i]);
			cout << endl;
		}
	}
}

//Tách tháng
int monthFlight(string x) {
	string month;
	int i;
	for (i = x.length() - 1; i >= 0; i--) {
		if (x[i] == '/') {
			break;
		}
	}
	for (i--; i >= 0; i--) {
		if (x[i] != '/') {
			month.insert(month.begin() + 0, x[i]);
		}
		else {
			break;
		}
	}

	int thang = atoi((char*)month.c_str()); //Hàm chuyển chuỗi số thành số nguyên
	return thang;
}

//Tách ngày
int dayFlight(string x) {
	string day;
	for (int i = 0; i <= x.length(); i++) {
		if (x[i] != '/') {
			day.push_back(x[i]);
		}
		else
			break;
	}

	int ngay = atoi((char*)day.c_str()); //Hàm chuyển chuỗi số thành số nguyên
	return ngay;
}

/*Tìm kiếm các chuyến bay trong khoảng thời gian (X, Y) cho trước
Ý tưởng: Tính số ngày từ ngày 1/1/1 đến khoảng thời gian X (x)
		 Tính số ngày từ ngày 1/1/1 đến khoảng thời gian Y (y)
		 Tính số ngày ngày 1/1/1 đến ngày của chuyến bay a (d)
		 Nếu   x < d < y thì chuyến bay a có ngày bay trong khoảng thời gian (X, Y)*/

		 //Kiểm tra năm nhuận
bool ktNamNhuan(int y) {
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
		return true;
	}
	return false;
}

//Tính số ngày trong một tháng
int ngayTrongThang(int m, int y) {
	if (m == 4 || m == 6 || m == 9 || m == 11) {
		return 30;
	}
	else if (m == 2) {
		if (ktNamNhuan(y) == true) {
			return 29;
		}
		return 28;
	}
	else {
		return 31;
	}
}

//Tính số ngày từ ngày 1/1/1 đến ngày dd/mm/yy
int countDay(int d, int m, int y) {
	int day = 0;
	for (int i = 1; i < y; i++) { //Tính số ngày từ năm 1 đến năm y - 1
		if (ktNamNhuan(y) == true) {
			day += 366;
		}
		else {
			day += 365;
		}
	}

	for (int i = 1; i < m; i++) { //Cộng thêm số ngày từ tháng 1 năm y đến tháng m -1 năm y
		day += ngayTrongThang(i, y);
	}

	day += d; //Cộng thêm số ngày của tháng m

	return day;
}

//Xử lí tìm chuyến bay có ngày trong khoảng thời gian (X, Y) cho trước
void timChuyenBayTheoKhoangThoiGian(LIST dsbay) {
	string X;
	cout << "\nNhap thoi gian X: ";
	while (getchar() != '\n');
	getline(cin, X);

	string Y;
	cout << "\nNhap thoi gian Y: ";
	getline(cin, Y);

	int dX = dayFlight(X); //Ngày của X
	int mX = monthFlight(X); //Tháng của X
	int yX = yearFlight(X); //Năm của X

	int dY = dayFlight(Y); //Ngày của Y
	int mY = monthFlight(Y); //Tháng của Y
	int yY = yearFlight(Y); //Năm của Y

	int dayX = countDay(dX, mX, yX); //Số ngày tính từ ngày 1/1/1 đến ngày dX/mX/yX
	int dayY = countDay(dY, mY, yY); //Số ngày tính từ ngày 1/1/1 đến ngày dY/mY/yY

	bool kt = false; //Giả sử không có chuyến bay nào thỏa

	for (int i = 0; i < dsbay.soluong; i++) { //Vòng lặp xuất các chuyến bay thuộc khoảng thời gian (X, Y)
		int d = dayFlight(dsbay.ds[i]->day); //Ngày của chuyến bay i
		int m = monthFlight(dsbay.ds[i]->day); //Tháng của chuyến bay i
		int y = yearFlight(dsbay.ds[i]->day); //Năm của chuyến bay i
		int day = countDay(d, m, y); //Số ngày tính từ ngày 1/1/1 đến ngày d/m/y
		if (day > dayX && day < dayY) {
			kt = true;
			xuat(*dsbay.ds[i]);
		}
	}

	if (kt == false) {
		cout << "\n\t\tKhong co chuyen bay nao trong khoang thoi gian tren";
	}

}

//Tìm kiếm thông tin chuyến bay có họ tên hành khách có chữ cái trong họ tên trùng với sâu x cần tìm kiếm
void timChuyenBayTheoTenHanhKhach(LIST dsbay) {
	string x;
	cout << "\nNhap ho ten khach hang can tim: ";
	char c;
	cout << "Nhap c = ";
	bool flag = true;
	while (flag) {
		cin >> c;
		if (c == 13) {
			break;
		}
		else if (c == 8) {
			if (x.length() != 0) {
				x.erase(x.begin() + x.length() - 1);
				cout << "\b \b";
			}
		}
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			x.push_back(c);
			for (int i = 0; i < x.length(); i++) {
				for (int j = 0; j < dsbay.soluong; j++) {
					for (int k = 0; k < dsbay.ds[j]->name.length(); k++) {
						if (x[i] == dsbay.ds[j]->name[k]) {
							cout << dsbay.ds[j]->name;
							flag = false;
						}
					}
				}
			}
		}
	}
}
