#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;

class Species {
	public:
		vector<string> instructions;		// instruction list
		char species_name;
		Species();							// No default species; put '.' instead
		Species(char s);					// Initialize species char
		void add_instruction(string inst);	// push_back instruction to instruction vector
};

class Creature {
	public:
		Species species;
		int pc;								// program counter
		int direction;						// W: 0, N: 1, E: 2, S: 3
		Creature();							// No default species; put '.' instead
		Creature(Species s, int d);			// give creature a species and a direction
};

class World {
private:
	int rows;
	int cols;
	int turn;								// # of times darwin(the game) will run

public:
	vector<vector<Creature*> > grid;		// world grid vector of creature pointers
	World(int r, int c);
	void print_world();
	void place_at(Creature creature, int r, int c);
	void simulate(vector<string> inst);
	void darwin(int num_turns);
};


#endif
