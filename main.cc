#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

srand(time(0));

class Status() {
	private:
		int cur_stat = 0;
		const int DEAD = 0;
		const int TREE = 1;
		const int BURN = 2;
	public:
		Status(int status) {
			status = cur_stat;
		}
		int get_status() const {
			return cur_status;
		}
		void set_status(int status) {
			cur_status = status;
		}
};

void chance(Status &s) {
}

int main() {
}
