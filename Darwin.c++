#include "Darwin.h"
#include <iterator>

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

Creature::Creature(T sp, char dir, int r, int c) {
	row = r;
	col = c;
	direction = dir;
	species = sp;
}

void Creature::initSpecies() {
	species();
}

Instruction::Instruction(T species) {
	switch(species) {
		case (species.name.compare("Food") == 0):
			instructions.push_back("left");
			instructions.push_back("go 0");
			break;

		case (species.name.compare("Hopper") == 0):
			instructions.push_back("hop");
			instructions.push_back("go 0");
			break;

		case (species.name.compare("Rover") == 0):
			instructions.push_back("if_enemy 9");
			instructions.push_back("if_empty 7");
			instructions.push_back("if_random 5");
			instructions.push_back("left");
			instructions.push_back("go 0");
			instructions.push_back("right");
			instructions.push_back("go 0");
			instructions.push_back("hop");
			instructions.push_back("go 0");
			instructions.push_back("infect");
			instructions.push_back("go 0");
			break;

		case (species.name.compare("Trap") == 0):
			instructions.push_back("if_enemy 3");
			instructions.push_back("left");
			instructions.push_back("go 0");
			instructions.push_back("infect");
			instructions.push_back("go 0");
			break;
		default:
			break;
	}
}

Food::Food() {
	name = "Food";
	inst(Food f);
}

Rover::Rover() {
	name = "Rover";
	inst(Rover r);
}

Hopper::Hopper() {
	name = "Hopper";
	inst(Hopper h);
}

Trap::Trap() {
	name = "Trap";
	inst(Trap t);
}

int main() {
	World world(10, 10);
	world.printWorld();

	Creature Food(Food f, 'E', 0, 0);

	return 0;
}