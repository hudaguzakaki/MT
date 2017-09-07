//Гоголев Михаил Александрович
#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;
const int arraySize = 4;

void PrintArray(int* array, int arrayarraySize, char arrayName) {
	cout << "array " << arrayName << ":" << endl;
	for (int i = 0; i < arrayarraySize; i++) {
		cout << array[i] << endl;
	}
}

void main() {
	int a[arraySize], b[arraySize], c[arraySize * 2];
	srand(time(0));

	for (int i = 0; i < arraySize; i++) {
		a[i] = rand();
		b[i] = rand();
	}

	PrintArray(a, arraySize, 'a');
	PrintArray(b, arraySize, 'b');

	for (int i = 0; i < arraySize; i++) {
		c[i] = a[i];
		c[i + 4] = b[i];
	}

	PrintArray(c, arraySize * 2, 'c');

	int max = 0;
	for (int i = 0; i < arraySize * 2; i++) {
		if (max < c[i])
			max = c[i];
	}

	cout << "max value of array c: " << max << endl;
	cin.get();
}
