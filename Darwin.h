#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;

class Species {
  //make vars private
	public:
		vector<string> instructions;		// instruction list
		char species_name;
		Species();							// No default species; put '.' instead
		Species(char s);					// Initialize species char
		void add_instruction(string inst);	// push_back instruction to instruction vector
		string operator [] (int i);
    //void got_infected();
    //probably need operator = and !=
    //void print_name();
};

class Creature {
  //make vars private
	public:
		Species species;
		int pc;								// program counter
		int direction;						// W: 0, N: 1, E: 2, S: 3
    	bool action;              // true if action completes(will prob rem)
		Creature();							// No default species; put '.' instead
		Creature(Species s, int d);			// give creature a species and a direction
		void left();
		void right();
    //void left()
    //void right()
    //void print_creature();    //calls print_name()
};

class World {
private:
	int rows;
	int cols;
	int turn;								// # of times darwin(the game) will run

public:
  // maybe make it Creature* const?
	vector<vector<Creature*> > grid;		// world grid vector of creature pointers
	World(int r, int c);
    /*bool hop();
    //void infect();
    bool empty();
    bool wall();*/
    //bool random();
    bool enemy();
	void print_world();
	void place_at(Creature& creature, int r, int c);
	void simulate(/*vector<string> inst*/Creature& creature, int r, int c);
	void darwin(int num_turns);
};


#endif
