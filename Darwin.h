#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>


using namespace std;

class World {
private:
	int cols;
	int rows;
	vector< vector< char > > grid;

public:
	World(int c, int r);
	void printWorld();
};

#endif