#include "Darwin.h"
#include <iterator>

// using namespace std;

// World constructor
World::World(int c, int r) {
	cols = c;
	rows = r;

	grid.resize(cols, vector<char>(rows, '.'));
}

// Print world
void World::printWorld() {
	vector< vector<char> >::iterator it=grid.begin(), end=grid.end();
	while(it != end) {
		vector<char>::iterator it1=it->begin(), end1=it->end();
		copy(it1, end1, ostream_iterator<char>(cout, " "));
		cout << endl;
		++it;
	}
}

int main() {
	World world(10, 10);
	world.printWorld();

	return 0;
}