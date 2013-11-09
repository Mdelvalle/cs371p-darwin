#include "Darwin.h"
#include <iterator>
#include <string>
#include "string.h"
#include <cstdlib>
#include <cassert>

Species::Species() {
	species_name = '.';
}

Species::Species(char s) {
	species_name = s;
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
    assert(r > 0);
    assert(c > 0);
	rows = r;
	cols = c;
	grid.resize(r, vector<Creature*>(c, NULL));
    c_vec.resize(r, vector<bool>(c));
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            c_vec[i][j] = false;
        }
    }
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
         c_vec[r][c - 1] = 1;
         c_vec[r][c] = 0;
         grid[r][c] = nullptr;
         return;
       }
       else if((dir == 1) && (r > 0) && (grid[r - 1][c] == NULL)) {
         place_at(creature, r - 1, c);
         ++(creature.pc);
         c_vec[r - 1][c] = 1;
         c_vec[r][c] = 0;
         grid[r][c] = nullptr;
         return;
       }
       else if((dir == 2) && (c < (cols-1)) && (grid[r][c + 1] == NULL)) {
         place_at(creature, r, c + 1);
         ++(creature.pc);
         c_vec[r][c + 1] = 1;
         c_vec[r][c] = 0;
         grid[r][c] = nullptr;
         return;
       }
       else if((dir == 3) && (r < (rows-1)) && (grid[r + 1][c] == NULL)) {
         place_at(creature, r + 1, c);
         ++(creature.pc);
         c_vec[r + 1][c] = 1;
         c_vec[r][c] = 0;
         grid[r][c] = nullptr;
         return;
       }
    }
    else if(strcmp(ins.c_str(), "left") == 0) {
       if(dir == 0) {
        creature.direction = 3;
         ++(creature.pc);
        return;
      }
      else if(dir == 1) {
        creature.direction = 0;
         ++(creature.pc);
        return;
      }
      else if(dir == 2) {
        creature.direction = 1;
         ++(creature.pc);
        return;
      }
      else if(dir == 3) {
         creature.direction = 2;
         ++(creature.pc);
        return;
      }
   }
 
   else if(strcmp(ins.c_str(), "right") == 0) {
      if(dir == 0) {
        creature.direction = 1;
         ++(creature.pc);
        return;
      }
      else if(dir == 1) {
        creature.direction = 2;
         ++(creature.pc);
        return;
      }
      else if(dir == 2) {
        creature.direction = 3;
         ++(creature.pc);
        return;
      }
      else if(dir == 3) {
         creature.direction = 0;
         ++(creature.pc);
        return;
      }
   }
   else if(strcmp(ins.c_str(), "infect") == 0) {
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
	if(strcmp((ins.substr(0, 8)).c_str(), "if_empty") == 0) {
    if((dir == 0) && (c > 0) && (grid[r][c - 1] == NULL)) {
        // change 9 to a string.length() - 1
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    else if((dir == 1) && (r > 0) && (grid[r - 1][c] == NULL)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    else if((dir == 2) && (c < (cols-1)) && (grid[r][c + 1] == NULL)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    else if((dir == 3) && (r < (rows-1)) && (grid[r + 1][c] == NULL)) {
         creature.pc = stoi(ins.substr(9, 1));
         simulate(creature, r, c);
    }
    else {
      ++(creature.pc);
      simulate(creature, r, c);
    }
  }
	else if(strcmp((ins.substr(0, 7)).c_str(), "if_wall") == 0) {
    if((dir == 0) && (c == 0)) {
         creature.pc = stoi(ins.substr(8, 1));
         simulate(creature, r, c);
    }
    else if((dir == 1) && (r == 0)) {
         creature.pc = stoi(ins.substr(8, 1));
         simulate(creature, r, c);
    }
    else if((dir == 2) && (c == (cols-1))) {
         creature.pc = stoi(ins.substr(8, 1));
         simulate(creature, r, c);
    }
    else if((dir == 3) && (r == (rows-1))) {
         creature.pc = stoi(ins.substr(8, 1));
         simulate(creature, r, c);
    }
    else {
        ++(creature.pc);
        simulate(creature, r, c);
    }
  }
	else if(strcmp((ins.substr(0, 9)).c_str(), "if_random") == 0) {
    int r = rand();
    if((r % 2) == 1) {
         creature.pc = stoi(ins.substr(10, 1));
         simulate(creature, r, c);
       }
    else {
         ++(creature.pc);
         simulate(creature, r, c);
    }
  }
	else if(strcmp((ins.substr(0, 8)).c_str(), "if_enemy") == 0) {
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
    else {
      ++(creature.pc);
      simulate(creature, r, c);
    }
  }

	else if(strcmp((ins.substr(0, 2)).c_str(), "go") == 0) {
     creature.pc = stoi((ins.substr(3, 1)));
     simulate(creature, r, c);
  }
}

void World::print_world() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(j == 0) {
                cout << i % 10 << " ";
            }
            if(grid[i][j] == NULL)
                cout << ". ";
            else
                cout << grid[i][j]->species.species_name << " ";
        }
        cout << endl;
    }
}

void World::darwin(int num_turns) {
	turn = 0;
    assert(turn == 0);
	while(turn <= num_turns) {
        for(int x = 0; x < rows; ++x) {
            for(int z = 0; z < cols; ++z) {
                if(grid[x][z] != 0)
                c_vec[x][z] = 0;
            }
        }
        cout << "Turn: " << turn << endl;
        cout << "  ";
        for(int m = 0; m < cols; ++m) {
            cout << m % 10<< " ";
        }
        cout << endl;
		print_world();
        cout << endl;
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if((grid[i][j] != 0) && (c_vec[i][j] == 0)) {
                    simulate(*grid[i][j], i, j);
                }
			}
		}
		++turn;
	}
}

void World::darwin(int num_turns, int first = 0, int every = 0) {
    turn = 0;
    while(turn < first) {
        for(int x = 0; x < rows; ++x) {
            for(int z = 0; z < cols; ++z) {
                if(grid[x][z] != 0)
                c_vec[x][z] = 0;
            }
        }
        cout << "Turn: " << turn << endl;
        cout << "  ";
        for(int m = 0; m < cols; ++m) {
            cout << m % 10 << " ";
        }
        cout << endl;
        print_world();
        cout << endl;
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                if((grid[i][j] != 0) && (c_vec[i][j] == 0)) {
                    simulate(*grid[i][j], i, j);
                }
            }
        }
        ++turn;
    }
    while(turn <= num_turns) {
        if((turn % every) == 0) {
        for(int x = 0; x < rows; ++x) {
            for(int z = 0; z < cols; ++z) {
                if(grid[x][z] != 0)
                c_vec[x][z] = 0;
            }
        }
            cout << "Turn: " << turn << endl;
            cout << "  ";
            for(int m = 0; m < cols; ++m) {
                cout << m % 10 << " ";
            }
            cout << endl;
            print_world();
            cout << endl;
            for(int i = first; i < rows; ++i) {
                for(int j = 0; j < cols; ++j) {
                    if((grid[i][j] != 0) && (c_vec[i][j] == 0)) {
                        simulate(*grid[i][j], i, j);
                    }
                }
            }
        }
        ++turn;
    }
}

