#include "Darwin.h"

Species::Species() {
	species = '.';
	instructions(0);
}

Species::Species(char s) {
	species = s;
	instructions(0);
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

World::World(int r, int c) {
	rows = r;
	cols = c;
	grid.resize(cols, vector<Creature*>(rows, NULL));
}

void World::print_world() {
	vector< vector<Creature*> >::iterator it=grid.begin(), end=grid.end();
	while(it != end) {
		vector<Creature*>::iterator it1=it->begin(), end1=it->end();
		copy(it1, end1, ostream_iterator<Creature*>(cout, " "));
		cout << endl;
		++it;
	}
}

void World::simulate(int num_turns) {
	turn = 0;
	while(turn < num_turns) {
		print_world();
		// TODO: actual darwin logic

		++turn;
	}
}