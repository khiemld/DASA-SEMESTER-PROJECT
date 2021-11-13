#include<iostream>
#include<string>
using namespace std;

string hamTachTen(string s) {
	string ten = "";
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == ' ' || i==0) {
			if (i == 0) {
				for (int j = i; j < s.length(); j++) {
					ten.push_back(s[j]);
				}
				break;
			}
			for (int j = i + 1; j < s.length(); j++) {
				ten.push_back(s[j]);
			}
			break;
		}
	}
	return ten;
}

int main() {
	cout << hamTachTen("Duy Khiem");
}