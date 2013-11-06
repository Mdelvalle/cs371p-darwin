#include "Darwin.h"
#include <iterator>

Species::Species() {
	species_name = '.';
	instructions.resize(0);
}

Species::Species(char s) {
	species_name = s;
	instructions.resize(0);
}

void Species::add_instruction(string inst) {
	instructions.push_back(inst);
}

Creature::Creature() {
	pc = 0;
	direction = 0;
}

Creature::Creature(Species s, int d) {
	species = s;
	direction = d;
	pc = 0;
}

/*Creature& Creature::operator=(const Creature &lhs, const Creature &rhs) {
	lhs = rhs;
}*/

World::World(int r, int c) {
	rows = r;
	cols = c;
	grid.resize(cols, vector<Creature*>(rows, NULL));
}

void World::print_world() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(grid[i][j] == NULL)
				cout << ". ";
			else
				cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void World::place_at(Creature creature, int r, int c) {
	grid[r][c]->species = creature.species;
}

void World::simulate(int num_turns) {
	turn = 0;
	while(turn < num_turns) {
		print_world();
		// TODO: actual darwin logic


		++turn;
	}
}

int main() {
	World grid(10, 10);
	grid.print_world();

	Species f('f');
    f.add_instruction("left");
    f.add_instruction("go 0");
    Creature food1(f, 2);
    cout << food1.species.species << endl;
    grid.place_at(food1, 0, 0);
    grid.print_world();

	return 0;
}
