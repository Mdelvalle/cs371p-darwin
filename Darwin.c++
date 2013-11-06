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

World::World(int r, int c) {
	rows = r;
	cols = c;
	grid.resize(c, vector<Creature*>(r, NULL));
}

void World::print_world() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(grid[i][j] == NULL)
				cout << ". ";
			else
				cout << grid[i][j]->species.species_name << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void World::place_at(Creature creature, int r, int c) {
	grid[r][c] = &creature;
}

void World::simulate(vector<string> inst) {
	int i = 0;
	if(strcmp(inst[i], "left"))
}

void World::darwin(int num_turns) {
	turn = 0;
	while(turn < num_turns) {
		print_world();
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(grid[i][j] == NULL)
					continue;
				else {
					simulate(grid[i][j]->species.instructions);
				}
			}
		}

		++turn;
	}
}

int main() {
    World world(8, 8);

    Species f('f');
    f.add_instruction("left");
    f.add_instruction("go 0");

    Species h('h');
    h.add_instruction("hop");
    h.add_instruction("go 0");

    Species r('r');
    r.add_instruction("if_enemy 9");
    r.add_instruction("if_empty 7");
    r.add_instruction("if_random 5");
    r.add_instruction("left");
    r.add_instruction("go 0");
    r.add_instruction("right");
    r.add_instruction("go 0");
    r.add_instruction("hop");
    r.add_instruction("go 0");
    r.add_instruction("infect");
    r.add_instruction("go 0");

    Species t('t');
    t.add_instruction("if_enemy 3");
    t.add_instruction("left");
    t.add_instruction("go 0");
    t.add_instruction("infect");
    t.add_instruction("go 0");

        Creature food1(f, 2);
        world.place_at(food1, 0, 0);

        Creature hopper1(h, 1);
        world.place_at(hopper1, 3, 3);

        Creature hopper2(h, 2);
        world.place_at(hopper2, 3, 4);

        Creature hopper3(h, 3);
        world.place_at(hopper3, 4, 4);

        Creature hopper4(h, 0);
        world.place_at(hopper4, 4, 3);

        Creature food2(f, 1);
        world.place_at(food2, 7, 7);

        world.print_world();
        //world.darwin(5);

	return 0;
}