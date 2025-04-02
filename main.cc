#include <iostream>
#include <ctime>
#include <cstdlib>
#include "/public/colors.h"

using namespace std;

const int DEAD = 0;
const int TREE = 1;
const int BURN = 2;
int difficulty = 0;

void die() {
	cout << "BAD INPUT" << endl;
	exit(EXIT_FAILURE);
}

class Status {
  private:
	int row = 0;
	int col = 0;
	int cur_stat = 0;
  public:
	Status(int r, int c, int status) {
		row = r;
		col = c;
		cur_stat = status;
	}

	int get_status() const {
		return cur_stat;
	}

	void set_status(int status) {
		cur_stat = status;
	}

	int get_row() const {
		return row;
	}

	int get_col() const {
		return col;
	}

	void print_status() const {
		if (cur_stat == 0) setbgcolor(235, 212, 162);
		else if (cur_stat == 1) setbgcolor(34, 139, 34);
		else setbgcolor(255, 0, 0);

		cout << " ";
		cout.flush();
		resetcolor();
	}
};

bool survive() {
	int prob = 0;

	if (difficulty == 1) prob = 5;
	else if (difficulty == 2) prob = 15;
	else if (difficulty == 3) prob = 45;
	else die();

	if (((rand() % 100) + 1) < prob) return false;
	else return true;
}

void print(Status &s, int arr[25][25], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (survive) continue;
			else {
				if (s.get_status() == DEAD) continue;
				else if (s.get_status() == TREE) {
					s.set_status(2);
				}
			}
			if (s.get_status() == BURN) s.set_status(3);
			cout << s.print_status() << " ";
		}
		cout << endl;
	}
}

int main() {
	srand(time(0));

	int row = 0;
	int col = 0;

	cout << "How big do you want the map to be? (Max: 25)" << endl;
	cout << "Rows: ";
	cin >> row;

	if (!row) die();
	if (row < 0 || row > 25) die();

	cout << "Columns: ";
	cin >> col;

	if (!col) die();
	if (col < 0 || col > 25) die();

	cout << "What level would you like?" << endl;
	cout << "\tEasy: (1)" << endl << "\tMedium: (2)" << endl << "\tHard: (3)" << endl;

	int choice = 0;
	cin >> choice;

	if (!choice) die();

	if (choice < 1 || choice > 3) die();
	else if (choice == 1) difficulty = choice;
	else if (choice == 2) difficulty = choice;
	else difficulty = choice;

	int map[row][col] = {0};

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Status s(i, j, 0);
		}
	}
}
