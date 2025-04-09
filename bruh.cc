#include <iostream>

using namespace std;

const int SIZE = 30;

bool same(int left[SIZE][SIZE], int right[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (left[i][j] != right[i][j]) return false;
		}
	}
	return true;
}

int main() {
	int arr1[SIZE][SIZE];
	int arr2[SIZE][SIZE];
	int arr3[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			arr1[i][j] = 1;
			arr2[i][j] = 0;
			arr3[i][j] = 1;
		}
	}

	bool bad = same(arr1, arr2);
	bool good = same(arr1, arr3);

	if (!bad) cout << "bad is false" << endl;
	else cout << "bad is true" << endl;

	cout << endl;

	if (good) cout << "good is true" << endl;
	else cout << "good is false" << endl;

	return 0;
}
