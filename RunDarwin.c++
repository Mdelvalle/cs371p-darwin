// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----
    Species f('f');

    /*
     0: left
     1: go 0
    */
     f.add_instruction("left");
     f.add_instruction("go 0");

    // ------
    // hopper
    // ------
     Species h('h');

    /*
     0: hop
     1: go 0
    */
     h.add_instruction("hop");
     h.add_instruction("go 0");

    // -----
    // rover
    // -----
     Species r('r');

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
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

    // ----
    // trap
    // ----
     Species t('t');

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
     t.add_instruction("if_enemy 3");
     t.add_instruction("left");
     t.add_instruction("go 0");
     t.add_instruction("infect");
     t.add_instruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        World world(8, 8);
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
        world.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        World world(7, 9);
        Creature trap1()
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print the first 10 grids          (i.e. 0, 1, 2...9).
        Print every 100th grid after that (i.e. 100, 200, 300...1000).
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
