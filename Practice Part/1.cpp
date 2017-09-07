//Гоголев Михаил Александрович
#include <iostream>
#include <string>

using namespace std;

string FirstMethod(string str) {
	reverse(str.begin(), str.end());
	return str;
}

string SecondMethod(string str) {
	for (int i = 0; i<str.length() / 2; i++)
		swap(str[i], str[str.length() - i - 1]);
	return str;
}

void main() {
	string str = "abcdefghijklmnop";
	cout << str << endl;
	cout << FirstMethod(str) << endl;
	cout << SecondMethod(str) << endl;
	cin.get();
}
