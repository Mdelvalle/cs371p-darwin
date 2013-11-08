#include "Darwin.h"
#include <iterator>
#include <string>
#include "string.h"

Species::Species() {
	species_name = '.';
	//instructions.resize(0);
  //instructions = vector<string>(0);
}

Species::Species(char s) {
	species_name = s;
  //instructions = vector<string>(0);
	//instructions.resize(0);
  //instructions = vector<string>(0);
}

void Species::add_instruction(string inst) {
	instructions.push_back(inst);
}

string Species::operator [] (int i) {
    return instructions [i];
}

/*void Species::got_infected() {

}

void Species::print_name() {

}*/

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

void Creature::left() {
    if(direction == 0) {
        direction = 3;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 1) {
        direction = 0;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 2) {
        direction = 1;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 3) {
        direction = 2;
        pc += 1;
        action = true;
        return;
    }
}

void Creature::right() {
    if(direction == 0) {
        direction = 1;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 1) {
        direction = 2;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 2) {
        direction = 3;
        pc += 1;
        action = true;
        return;
    }
    else if(direction == 3) {
        direction = 0;
        pc += 1;
        action = true;
        return;
    }
}

/*
void Creature::infect() {
        if((direction == 0) && (c > 0) &&
                                     (grid[r][c - 1].species.species_name !=
                                      species.species_name)) {
        grid[r][c - 1].species = species
        grid[r][c - 1].pc = 0;
        action = true;
        return;
       }
       else if((direction == 1) && (r > 0) &&
                                     (grid[r][c - 1].species.species_name !=
                                     species.species_name)) {
        grid[r - 1][c].species = species
        grid[r - 1][c].pc = 0;
        action = true;
        return;
       }
       else if((creature.direction == 2) && (c < (cols - 1)) &&
                                     (grid[r][c - 1].species.species_name !=
                                     species.species_name)) {
        grid[r][c + 1].species = species
        grid[r][c + 1].pc = 0;
        action = true;
        return;
       }
       else if((direction == 3) && (r < (rows - 1)) &&
                                     (grid[r][c - 1].species.species_name !=
                                     species.species_name)) {
        grid[r + 1][c].species = species;
        grid[r + 1][c].pc = 0;
        action = true;
        return;
       }
}


bool Creature::enemy() {
  
}

bool Creature::random() {
  
}

void Creature::print_creature() {
  
}*/

World::World(int r, int c) {
	rows = r;
	cols = c;
	grid.resize(c, vector<Creature*>(r, NULL));
}

/*bool World::hop(Creature& creature) {
       if(!wall(creature) && empty())
         return true;
       else
         return false;
}

bool World::wall(Creature& creature, int r, int c) {
    if((*creature->direction == 0) && (c == 0)) {
      return true;
    }
    else if((*creature->direction == 1) && (r == 0)) {
      return true;
    }
    else if((*creature->direction == 2) && (c == (cols-1))) {
      return true;
    }
    else if((*creature->direction == 3) && (r == (rows-1))) {
      return true;
    }
    else
        return false;
}

bool Creature::empty(Creature& creature, int r, int c) {
    if((*creature->direction == 0) && !wall(creature, r, c) && (grid[r][c - 1] == NULL)) {
        // change 9 to a string.length() - 1
        pc = stoi(species.instructions[pc].substr(9, 1));
        simulate(species.instructions, r, c);
    }
    else if((*creature->direction == 1) && !wall(creature, r, c) && (grid[r - 1][c] == NULL)) {
        pc = stoi(species.instructions[pc].substr(9, 1));
        simulate(species.instructions, r, c);
    }
    else if(*creature->direction == 2 && !wall(creature, r, c) && (grid[r][c + 1] == NULL)) {
        pc = stoi(species.instructions[pc].substr(9, 1));
        simulate(species.instructions, r, c);
    }
    else if(*creature->direction == 3 && !wall(creature, r, c) && (grid[r + 1][c] == NULL)) {
        pc = stoi(species.instructions[pc].substr(9, 1));
        simulate(species.instructions, r, c);
    }
    else
        pc += 1;
}*/

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

void World::place_at(Creature& cr, int r, int c) {
  Creature* temp = &cr;
	grid[r][c] = temp;
}

void World::simulate(Creature& creature, int r, int c) {
  int dir = creature.direction;
  int prog_c = creature.pc;
  string ins = creature.species.instructions.at(prog_c);
	  if(strcmp(ins.c_str(), "hop") == 0) {
       if((dir == 0) && (c > 0) && (grid[r][c - 1] == NULL)) {
         place_at(creature, r, c - 1);
         ++(creature.pc);
         grid[r][c] = NULL;
         return;
       }
       else if((dir == 1) && (r > 0) && (grid[r - 1][c] == NULL)) {
         place_at(creature, r - 1, c);
         ++(creature.pc);
         grid[r][c] = NULL;
         creature.action = true;
         return;
       }
       else if((dir == 2) && (c < (cols-1)) && (grid[r][c + 1] == NULL)) {
         place_at(creature, r, c + 1);
         ++(creature.pc);
         grid[r][c] = NULL;
         return;
       }
       else if((dir == 3) && (r < (rows-1)) && (grid[r + 1][c] == NULL)) {
         place_at(creature, r + 1, c);
         ++(creature.pc);
         grid[r][c] = NULL;
         return;
       }
    }
    else if(strcmp(ins.c_str(), "left") == 0) {
       if(dir == 0) {
        dir = 3;
         ++(creature.pc);
        return;
      }
      else if(dir == 1) {
        dir = 0;
         ++(creature.pc);
        return;
      }
      else if(dir == 2) {
        dir = 1;
         ++(creature.pc);
        return;
      }
      else if(dir == 3) {
         dir = 2;
         ++(creature.pc);
        return;
      }
   }
 
   else if(strcmp(ins.c_str(), "right") == 0) {
      if(dir == 0) {
        dir = 1;
         ++(creature.pc);
        return;
      }
      else if(dir == 1) {
        dir = 2;
         ++(creature.pc);
        return;
      }
      else if(dir == 2) {
        dir = 3;
         ++(creature.pc);
        return;
      }
      else if(dir == 3) {
         dir = 0;
         ++(creature.pc);
        return;
      }
   }
   else if(strcmp(ins.c_str(), "infect") == 0) {
    cout << "in infect " << endl;
        if((dir == 0) && (c > 0) &&
                                     (grid[r][c - 1]->species.species_name !=
                                      creature.species.species_name)) {
        grid[r][c - 1]->species = creature.species;
        grid[r][c - 1]->pc = 0;
        return;
       }
       else if((dir == 1) && (r > 0) &&
                                     (grid[r - 1][c]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r - 1][c]->species = creature.species;
        grid[r - 1][c]->pc = 0;
        return;
       }
       else if((dir == 2) && (c < (cols - 1)) &&
                                     (grid[r][c + 1]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r][c + 1]->species = creature.species;
        grid[r][c + 1]->pc = 0;
        return;
       }
       else if((dir == 3) && (r < (rows - 1)) &&
                                     (grid[r + 1][c]->species.species_name !=
                                     creature.species.species_name)) {
        grid[r + 1][c]->species = creature.species;
        grid[r + 1][c]->pc = 0;
        return;
       }
   }
  // Control Flow
	/*if(strcmp((ins.c_str().substr(0, 8)).c_str(), "if_empty")) {
    // if(!wall() && !enemy())
    int d = dir;
    if(d == 0 && c > 0 && (grid[r][c - 1] == NULL)) {
        // change 9 to a string.length() - 1
        prog_c = stoi(creature.species.instructions[prog_c].substr(9, 1));
        simulate(creature, r, c);
    }
    else if(d == 1 && r > 0 && (grid[r - 1][c] == NULL)) {
        prog_c = stoi(creature.species.instructions[prog_c].substr(9, 1));
        simulate(creature, r, c);
    }
    else if(d == 2 && c < (cols-1) && (grid[r][c + 1] == NULL)) {
        prog_c = stoi(creature.species.instructions[prog_c].substr(9, 1));
        simulate(creature, r, c);
    }
    else if(d == 3 && r < (rows-1) && (grid[r + 1][c] == NULL)) {
        prog_c = stoi(creature.species.instructions[prog_c].substr(9, 1));
        simulate(creature, r, c);
    }
    else
        prog_c += 1;
  }
	else if(strcmp((creature.species.instructions[prog_c].substr(0, 7)).c_str(), "if_wall")) {
    // if(wall())
    int d = dir;
    if((d == 0) && (c == 0)) {
         prog_c = stoi(creature.species.instructions[prog_c].substr(8, 1));
         simulate(creature, r, c);
    }
    else if((d == 1) && (r == 0)) {
         prog_c = stoi(creature.species.instructions[prog_c].substr(8, 1));
         simulate(creature, r, c);
    }
    else if((d == 2) && (c == (cols-1))) {
         prog_c = stoi(creature.species.instructions[prog_c].substr(8, 1));
         simulate(creature, r, c);
    }
    else if((d == 3) && (r == (rows-1))) {
         prog_c = stoi(creature.species.instructions[prog_c].substr(8, 1));
         simulate(creature, r, c);
    }
    else
        prog_c += 1;
  }
	else if(strcmp((creature.species.instructions[prog_c].substr(0, 9)).c_str(), "if_random")) {
    int d = dir;
    if(d == 0 && c > 0 && (grid[r][c - 1] == NULL)) {
         place_at(creature, r, c - 1);
         prog_c += 1;
         simulate(creature, r, c);
       }
       else if(d == 1 && r > 0 && (grid[r - 1][c] == NULL)) {
         place_at(creature, r - 1, c);
         prog_c += 1;
         simulate(creature, r, c);
       }
       else if(d == 2 && c < (cols-1) && (grid[r][c + 1] == NULL)) {
         place_at(creature, r, c + 1);
         prog_c += 1;
         simulate(creature, r, c);
       }
       else if(d == 3 && r < (rows-1) && (grid[r + 1][c] == NULL)) {
         place_at(creature, r + 1, c);
         prog_c += 1;
         simulate(creature, r, c);
       }
  }*/
	else if(strcmp(ins.c_str(), "if_enemy")) {
    if((dir == 0) && (c > 0) && (grid[r][c - 1] != NULL)&&(grid[r][c - 1]->species.species_name != creature.species.species_name)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
     if((dir == 1) && (r > 0) && (grid[r - 1][c] != NULL)&&(grid[r - 1][c]->species.species_name != creature.species.species_name)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
     if((dir == 2) && (c < (cols - 1)) && (grid[r][c + 1] != NULL)&&(grid[r][c + 1]->species.species_name != creature.species.species_name)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    if((dir == 3) && (r < (rows - 1)) && (grid[r + 1][c] != NULL)&&(grid[r + 1][c]->species.species_name != creature.species.species_name)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    else
      ++(creature.pc);
  }


	if(strcmp((ins.substr(0, 2)).c_str(), "go") == 0) {
     creature.pc = stoi((ins.substr(3, 1)));
     simulate(creature, r, c);
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
				else {
					simulate(*grid[i][j], i, j);
        }
        cout << endl;
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
    t.add_instruction("if_enemy 2");
    //t.add_instruction("left");
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

        Creature trap1(t, 2);
        world.place_at(trap1, 0, 2);

        world.darwin(5);

	return 0;
}
