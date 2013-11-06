#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;

class Species {
	private:
		vector<string> instructions;		// instruction list

	public:
		char species_name;
		Species();							// No default species; put '.' instead
		Species(char s);					// Initialize species char
		void add_instruction(string inst);	// push_back instruction to instruction vector
};

class Creature {
	private:
		int pc;								// program counter
		int direction;						// W: 0, N: 1, E: 2, S: 3

	public:
		Species species;
		Creature();							// No default species; put '.' instead
		Creature(Species s, int d);			// give creature a species and a direction
/*		Creature& operator=(const Creature &lhs, const Creature &rhs);*/
};

class World {
private:
	vector<vector<Creature*> > grid;		// world grid vector of creature pointers
	int rows;
	int cols;
	int turn;								// # of times darwin(the game) will run

public:
	World(int r, int c);
	void print_world();
	void place_at(Creature creature, int r, int c);
	void simulate(int num_turns);
};


#endif
