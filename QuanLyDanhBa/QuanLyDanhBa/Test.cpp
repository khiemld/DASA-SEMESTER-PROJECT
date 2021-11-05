#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* pLeft;
	Node* pRight;
};
typedef Node* TREE;

//Hàm thêm node vào cây nhị phân tìm kiếm
void insert(TREE& t, int x) {
	if (t == NULL) { //Nếu cây rỗng
		Node* p = new Node;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p; //Thêm node p vào cây
	}
	else {
		if (t->data < x) {
			insert(t->pRight, x);
		}
		else {
			insert(t->pLeft, x);
		}
	}
}

//Duyệt cây
//Cách 1: Node - Left - Right
void NLR(TREE t) {
	if (t != NULL) {
		cout << t->data << " ";
		NLR(t->pLeft);
		NLR(t->pRight);
	}
}

//Cách 2: Node - Right - Left
void NRL(TREE t) {
	if (t != NULL) {
		cout << t->data << " ";
		NLR(t->pRight);
		NLR(t->pLeft);
	}
}

//Cách 3: Left - Node - Right
void LNR(TREE t) {
	if (t != NULL) {
		NLR(t->pLeft);
		cout << t->data << " ";
		NLR(t->pRight);
	}
}

//Cách 4: Right - Node - Left
void RNL(TREE t) {
	if (t != NULL) {
		NLR(t->pRight);
		cout << t->data << " ";
		NLR(t->pLeft);
	}
}

//Cách 5: Left - Right - Node
void LRN(TREE t) {
	if (t != NULL) {
		NLR(t->pLeft);
		NLR(t->pRight);
		cout << t->data << " ";
	}
}

//Cách 6: Right - Left - Node
void RLN(TREE t) {
	if (t != NULL) {
		NLR(t->pRight);
		NLR(t->pLeft);
		cout << t->data << " ";
	}
}

void Menu(TREE& t) {
	int luachon;
	while (true) {
		system("cls");
		cout << "\n\n\t\t=======================CAY NHI PHAN TIM KIEM=======================";
		cout << "\n\n\t\t1. Them node";
		cout << "\n\n\t\t2. Duyet cay";
		cout << "\n\n\t\t0. Ket thuc";
		cout << "\n\n\t\t=============================END====================================";

		cout << "\n\n\t\tNhap lua chon: ";
		cin >> luachon;

		if (luachon == 1) {
			cout << "\n\tTHEM NODE";
			int x;
			cout << "\n\tNhap gia tri can them";
			cin >> x;
			insert(t, x);
		}
		else if (luachon == 2) {
			cout << "\n\tDUYET CAY";
			cout << "\nNLR: "; NLR(t);
			cout << "\nNRL: "; NRL(t);
			cout << "\nLNR: "; LNR(t);
			cout << "\nRNL: "; RNL(t);
			cout << "\nLRN: "; LRN(t);
			cout << "\nRLN: "; RLN(t);
			system("pause");
		}
		else if (luachon == 0) {
			break;
		}
		else {
			break;
		}
	}
}

int main() {
	TREE t = NULL;
	cout << "alo";
	Menu(t);
}