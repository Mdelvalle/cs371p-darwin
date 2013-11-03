#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;

/************
****World****
*************/
class World {
private:
	vector< vector< Creature* > > grid;
	int cols;
	int rows;

public:
	World(int c, int r);
	void printWorld();
};

/***********
**Creature**
************/
template<typename T>
class Creature {
private:
	T species;
	int row;
	int col;
	int prog_counter;
	char direction;
public:
	Creature(T sp, char dir, int r, int c);
	void initSpecies();
};

/**************
**Instruction**
**************/
template<typename T>
class Instruction {
private:
	T sp;
	vector<String> instructions;

public:
	Instruction(T species);
};

/*********
***Food***
*********/
class Food {
private:
	String name;
	Instruction inst;

public:
	Food();
};

/***********
***Hopper***
***********/
class Hopper {
private:
	String name;
	Instruction inst;

public:
	Hopper();
};

/**********
***Rover***
**********/
class Rover {
private:
	String name;
	Instruction inst;

public:
	Rover();
};

/*********
***Trap***
*********/
class Trap {
private:
	String name;
	Instruction inst;

public:
	Trap();
};

#endif