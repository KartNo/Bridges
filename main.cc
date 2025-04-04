#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "/public/colors.h"

using namespace std;

const int SIZE = 34;
const int DEAD = 0;
const int TREE = 1;
const int FIRE = 2;
int difficulty = 0;

void die() {
	cout << "BAD INPUT" << endl;
	exit(EXIT_FAILURE);
}

bool survive() {
	int prob = 0;

	if (difficulty == 1) prob = 10;
	else if (difficulty == 2) prob = 30;
	else if (difficulty == 3) prob = 65;
	else die();

	if ((rand() % 100) < prob) return false;
	else return true;
}

void spread(int arr[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j] == FIRE) {
				bool north = survive();
				bool south = survive();
				bool east = survive();
				bool west = survive();

				if (!north) {
					if (i == 0) {}
					else {
						if (arr[i - 1][j] != TREE) {}
						else arr[i - 1][j] = FIRE;
					}
				}

				if (!south) {
					if (i == SIZE - 1) {}
					else {
						if (arr[i + 1][j] != TREE) {}
						else arr[i + 1][j] = FIRE;
					}
				}

				if (!east) {
					if (j == SIZE - 1) {}
					else {
						if (arr[i][j + 1] != TREE) {}
						else arr[i][j + 1] = FIRE;
					}
				}

				if (!west) {
					if (j == 0) {}
					else {
						if (arr[i][j - 1] != TREE) {}
						else arr[i][j - 1] = FIRE;
					}
				}
			}
		}
	}
}

void oof(int arr[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j] == FIRE) {
				arr[i][j] = DEAD;
			}
		}
	}
}

void copy(int copy[SIZE][SIZE], int tree[SIZE][SIZE]) {
	for (int a = 0; a < SIZE; a++) {
		for (int b = 0; b < SIZE; b++) {
			copy[a][b] = tree[a][b];
		}
	}
}

bool same(int arr[SIZE][SIZE], int tree[SIZE][SIZE]) {
	for (int a = 0; a < SIZE; a++) {
		for (int b = 0; b < SIZE; b++) {
			if (arr[a][b] != tree[a][b]) return false;
		}
	}
	return true;
}

void print(int arr[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j] == DEAD) setbgcolor(72, 74, 32);
			else if (arr[i][j] == TREE) setbgcolor(34, 139, 34);
			else setbgcolor(159, 35, 5);
			cout << "  ";
			resetcolor();
		}
		cout << endl;
	}
}

int main() {
	srand(time(0));

	cout << "What level would you like?" << endl;
	cout << "\tEasy: (1)" << endl << "\tMedium: (2)" << endl << "\tHard: (3)" << endl;

	int choice = 0;
	cin >> choice;

	if (!choice) die();

	if (choice < 1 || choice > 3) die();
	else if (choice == 1) difficulty = choice;
	else if (choice == 2) difficulty = choice;
	else difficulty = choice;

	int tree_map[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			tree_map[i][j] = TREE;
		}
	}

	tree_map[SIZE / 2][SIZE / 2] = FIRE;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == 0 || j == 0 || i > SIZE - 2 || j > SIZE - 2) tree_map[i][j] = DEAD;
		}
	}

	print(tree_map);

	int copy_map[SIZE][SIZE];
	copy(copy_map, tree_map);

	spread(tree_map);

	while (!same(copy_map, tree_map)) {
//		clearscreen();
		copy(copy_map, tree_map);
		oof(tree_map);
		spread(tree_map);
		print(tree_map);
		usleep(500000);
	}
}
