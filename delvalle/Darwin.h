#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;


// -------------
// Species Class
// -------------

/**
  * Species class holds the instruction set
  */
class Species {
	public:
		vector<string> instructions;		 /*instruction list*/
		char species_name;					 /*Name*/
		

		// -------------
		// Species
		// -------------

		/**
		 *
		 *  No default species; put '.' instead
		 */
		Species();						
		
		// -------------
		// Species
		// -------------

		/**
		 * @param s species type name
		 *  Initialize species char
		 */
		Species(char s);					 
		
		// -------------
		// add_instruction
		// -------------

		/**
		 * @param inst is the instruction that needs to be executed
		 *  push_back instruction to instruction vector
		 */
		void add_instruction(string inst);};


		

// -------------
// Creature Class
// -------------

/**
  * Creature class holds they species type and keep of the creatures' properties
  */
class Creature {
	public:
		Species species;                     /*< type of species*/
		int pc;								 /*< program counter*/
		int direction;						 /*< W: 0, N: 1, E: 2, S: 3*/
		
		// -------------
		// Creature
		// -------------

	   /**
		 * No default species; put '.' instead
		 */
		Creature();				
		
		// -------------
		// Creature
		// -------------

		/**
		 * @param s type of species
		 * @param d direction
		 *  give creature a species and a direction
		 */
		Creature(Species s, int d);};



////////////
/// World Class
///////////

/**
  *World Class Holds the board
  *
  */
class World {
	private:
		int rows;								 /*# of Rows in this board*/
		int cols;								 /*# of Rows in this board*/
		int turn;								 /*# of times darwin(the game) will run*/

	public:
		vector<vector<Creature*> > grid;		 /*world grid vector of creature pointers*/
		vector<vector<bool> > c_vec;			 /*Dirty Fix to give everyone one turn only*/
		// -------------
		// World
		// -------------
		/**
		  * World class
		  * @param r is the # of rows in the grid
		  * @param c is the # of columns in the grid
		  */
		World(int r, int c);

		// -------------
		// print_world
		// -------------
		/**
		 * print out the current state of the board
		 */
		void print_world();

		// -------------
		// place_at
		// -------------

		/**
		 * @param creature 
		 * @param r row index 
		 * @param c col index
		 * @return places the creature in appropiate location in the grid
		 */
		void place_at(Creature& creature, int r, int c);

		// -------------
		// simulate
		// -------------

		/**
		 * @param creature 
		 * @param r row index 
		 * @param c col index
		 * @return executes the next instruction of the creature untl it finds an action move
		 */
		void simulate(Creature& creature, int r, int c);
		
		// -------------
		// darwin
		// -------------

		/**
		 * @param num_turns executes that many turns 
		 *  Calls simulate the make moves
		 */
		void darwin(int num_turns);

		// -------------
		// darwin
		// -------------
		/**
		 * @param number of turns to execute 
		 * @param first iteration of printed boards
		 * @param every after printed boards
		 */
		void darwin(int num_turns, int first, int every);};


#endif
