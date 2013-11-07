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
  action = false;
}

Creature::Creature(Species s, int d) {
	species = s;
	direction = d;
	pc = 0;
  action = false;
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

static void World::place_at(Creature creature, int r, int c) {
	grid[r][c] = &creature;
}

void World::simulate(Creature creature, int r, int c) {
  // Actions
  if(!creature->action) {
	  if(strcmp(creature->species.instructions[creature->pc], "hop") == 0) {
      int d = creature->direction;
       if(d == 0 && c > 0 && grid[r][c - 1] == NULL) {
         place_at(creature, r, c - 1);
         creature->pc += 1;
         //creature->action = true;
         return;
       }
       else if(d == 1 && r > 0 && grid[r - 1][c] == NULL) {
         place_at(creature, r - 1, c);
         creature->pc += 1;
         //creature->action = true;
         return;
       }
       else if(d == 2 && c < (cols-1) && grid[r][c + 1] == NULL) {
         place_at(creature, r, c + 1);
         creature->pc += 1;
         //creature->action = true;
         return;
       }
       else if(d == 3 && r < (rows-1) && grid[r + 1][c] == NULL) {
         place_at(creature, r + 1, c);
         creature->pc += 1;
         //creature->action = true;
         return;
       }
    }
    else if(strcmp(creature->species.instructions[creature->pc], "left") == 0) {
       if(creature->direction == 0) {
        creature->direction = 3;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 1) {
        creature->direction = 0;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 2) {
        creature->direction = 1;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 3) {
        creature->direction = 2;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
   }
   else if(strcmp(creature->species.instructions[creature->pc], "right") == 0) {
      if(creature->direction == 0) {
        creature->direction = 1;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 1) {
        creature->direction = 2;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 2) {
        creature->direction = 3;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
      else if(creature->direction == 3) {
        creature->direction = 0;
        creature->pc += 1;
        //creature->action = true;
        return;
      }
   }
   else if(strcmp(creature->species.instructions[creature->pc], "infect") == 0) {
        if((creature->direction == 0) && (c > 0) &&
                                     (grid[r][c - 1]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r][c - 1]->species = creature->species
        grid[r][c - 1]->pc = 0;
        return;
       }
       else if((creature->direction == 1) && (r > 0) &&
                                     (grid[r][c - 1]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r - 1][c]->species = creature->species
        grid[r - 1][c]->pc = 0;
        return;
       }
       else if((creature->direction == 2) && (c < (cols - 1)) &&
                                     (grid[r][c - 1]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r][c + 1]->species = creature->species
        grid[r][c + 1]->pc = 0;
        return;
       }
       else if((creature->direction == 3) && (r < (rows - 1)) &&
                                     (grid[r][c - 1]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r + 1][c]->species = creature->species
        grid[r + 1][c]->pc = 0;
        return;
       }
   }
 }
  // Control Flow
	if(creature->species.instructions[creature->pc].compare("if_empty")) {

  }
	else if(creature->species.instructions[creature->pc].compare("if_wall")) {

  }
	else if(creature->species.instructions[creature->pc].compare("if_random")) {

  }
	else if(creature->species.instructions[creature->pc].compare("if_enemy")) {

  }
	else if(creature->species.instructions[creature->pc].compare("go")) {

  }
}

void World::darwin(int num_turns) {
	turn = 0;
	while(turn < num_turns) {
		print_world();
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(grid[i][j] == NULL)
					continue;
				else
					simulate(grid[i][j], i, j);
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
