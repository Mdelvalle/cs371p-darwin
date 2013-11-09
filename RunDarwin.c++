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
#include "Darwin.h"

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

    // ----
    // best
    // ----
        Species b('b');
    /*
         0: if_enemy 6
         1: if_empty 4
         2: left
         3: go 0
         4: hop
         5: go 0
         6: infect
         7: go 0
*/
        b.add_instruction("if_enemy 6");
        b.add_instruction("if_empty 4");
        b.add_instruction("left");
        b.add_instruction("go 0");
        b.add_instruction("hop");
        b.add_instruction("go 0");
        b.add_instruction("infect");
        b.add_instruction("go 0");

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
        world.darwin(5);
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
        Creature trap1(t, 3);
        world.place_at(trap1, 0, 0);
        Creature hopper1(h, 2);
        world.place_at(hopper1, 3, 2);
        Creature rover1(r, 1);
        world.place_at(rover1, 5, 4);
        Creature trap2(t, 0);
        world.place_at(trap2, 6, 8);
        world.darwin(5);
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
        World world(72, 72);

        int pos = rand() % 5184;
        int dir = rand() % 4;
        Creature food1(f, dir);
        world.place_at(food1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food2(f, dir);
        world.place_at(food2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food3(f, dir);
        world.place_at(food3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food4(f, dir);
        world.place_at(food4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food5(f, dir);
        world.place_at(food5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food6(f, dir);
        world.place_at(food6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food7(f, dir);
        world.place_at(food7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food8(f, dir);
        world.place_at(food8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food9(f, dir);
        world.place_at(food9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food10(f, dir);
        world.place_at(food10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper1(h, dir);
        world.place_at(hopper1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper2(h, dir);
        world.place_at(hopper2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper3(h, dir);
        world.place_at(hopper3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper4(h, dir);
        world.place_at(hopper4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper5(h, dir);
        world.place_at(hopper5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper6(h, dir);
        world.place_at(hopper6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper7(h, dir);
        world.place_at(hopper7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper8(h, dir);
        world.place_at(hopper8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper9(h, dir);
        world.place_at(hopper9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper10(h, dir);
        world.place_at(hopper10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover1(r, dir);
        world.place_at(rover1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover2(r, dir);
        world.place_at(rover2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover3(r, dir);
        world.place_at(rover3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover4(r, dir);
        world.place_at(rover4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover5(r, dir);
        world.place_at(rover5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover6(r, dir);
        world.place_at(rover6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover7(r, dir);
        world.place_at(rover7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover8(r, dir);
        world.place_at(rover8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover9(r, dir);
        world.place_at(rover9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover10(r, dir);
        world.place_at(rover10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap1(t, dir);
        world.place_at(trap1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap2(t, dir);
        world.place_at(trap2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap3(t, dir);
        world.place_at(trap3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap4(t, dir);
        world.place_at(trap4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap5(t, dir);
        world.place_at(trap5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap6(t, dir);
        world.place_at(trap6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap7(t, dir);
        world.place_at(trap7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap8(t, dir);
        world.place_at(trap8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap9(t, dir);
        world.place_at(trap9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap10(t, dir);
        world.place_at(trap10, pos / 72, pos % 72);

        world.darwin(1000, 10, 100);
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
        World world(72, 72);

        int pos = rand() % 5184;
        int dir = rand() % 4;
        Creature food1(f, dir);
        world.place_at(food1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food2(f, dir);
        world.place_at(food2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food3(f, dir);
        world.place_at(food3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food4(f, dir);
        world.place_at(food4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food5(f, dir);
        world.place_at(food5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food6(f, dir);
        world.place_at(food6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food7(f, dir);
        world.place_at(food7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food8(f, dir);
        world.place_at(food8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food9(f, dir);
        world.place_at(food9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature food10(f, dir);
        world.place_at(food10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper1(h, dir);
        world.place_at(hopper1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper2(h, dir);
        world.place_at(hopper2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper3(h, dir);
        world.place_at(hopper3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper4(h, dir);
        world.place_at(hopper4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper5(h, dir);
        world.place_at(hopper5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper6(h, dir);
        world.place_at(hopper6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper7(h, dir);
        world.place_at(hopper7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper8(h, dir);
        world.place_at(hopper8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper9(h, dir);
        world.place_at(hopper9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature hopper10(h, dir);
        world.place_at(hopper10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover1(r, dir);
        world.place_at(rover1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover2(r, dir);
        world.place_at(rover2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover3(r, dir);
        world.place_at(rover3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover4(r, dir);
        world.place_at(rover4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover5(r, dir);
        world.place_at(rover5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover6(r, dir);
        world.place_at(rover6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover7(r, dir);
        world.place_at(rover7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover8(r, dir);
        world.place_at(rover8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover9(r, dir);
        world.place_at(rover9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature rover10(r, dir);
        world.place_at(rover10, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap1(t, dir);
        world.place_at(trap1, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap2(t, dir);
        world.place_at(trap2, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap3(t, dir);
        world.place_at(trap3, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap4(t, dir);
        world.place_at(trap4, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap5(t, dir);
        world.place_at(trap5, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap6(t, dir);
        world.place_at(trap6, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap7(t, dir);
        world.place_at(trap7, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap8(t, dir);
        world.place_at(trap8, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap9(t, dir);
        world.place_at(trap9, pos / 72, pos % 72);

        pos = rand() % 5184;
        dir = rand() % 4;
        Creature trap10(t, dir);
        world.place_at(trap10, pos / 72, pos % 72);

        world.darwin(1000, 10, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// START MY TESTS
    try {
        cout << "*** 5x5 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(5, 5);
                                Creature c1(h, 2);
                                Creature c2(h, 3);
                                Creature c3(h, 0);
                                Creature c4(h, 1);
                                d.place_at(c1, 0, 0);
                                d.place_at(c2, 0, 1);
                                d.place_at(c3, 1, 1);
                                d.place_at(c4, 1, 0);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** 6x9 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(6, 9);
                                Creature c1(h, 1);
                                Creature c2(h, 2);
                                Creature c3(h, 3);
                                Creature c4(h, 1);
                                d.place_at(c1, 0, 3);
                                d.place_at(c2, 3, 1);
                                d.place_at(c3, 1, 5);
                                d.place_at(c4, 1, 2);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** 7x20 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(7, 20);
                                Creature c1(h, 2);
                                Creature c2(h, 1);
                                Creature c3(h, 0);
                                Creature c4(h, 0);
                                d.place_at(c1, 4, 17);
                                d.place_at(c2, 0, 11);
                                d.place_at(c3, 1, 1);
                                d.place_at(c4, 1, 13);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** 6x6 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(6, 6);
                                Creature c1(h, 0);
                                Creature c2(h, 0);
                                Creature c3(h, 0);
                                Creature c4(h, 0);
                                d.place_at(c1, 4, 0);
                                d.place_at(c2, 0, 1);
                                d.place_at(c3, 4, 3);
                                d.place_at(c4, 1, 8);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** 10x10 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(10, 10);
                                Creature c1(h, 1);
                                Creature c2(h, 3);
                                Creature c3(h, 1);
                                Creature c4(h, 0);
                                d.place_at(c1, 0, 7);
                                d.place_at(c2, 0, 1);
                                d.place_at(c3, 7, 7);
                                d.place_at(c4, 1, 8);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
//_______________________________________________________________________
// START 'ENSIGN' TESTS

    // ------------------
    // Hoppers Trapped 4x4
    // ------------------

    try {
        cout << "*** Hoppers Trapped 4x4 ***" << endl;
        srand(0);
                                /*        
                                4x4 Darwin
                                Hopper, facing east at (0, 0)
                                Hopper, facing south at (0, 1)
                                Hopper, facing west at (1, 1)
                                Hopper, facing north at (1, 0)
                                Simulate 10
                                Print every move
                                */
                                World d(4, 4);
                                Creature c1(h, 2);
                                Creature c2(h, 3);
                                Creature c3(h, 0);
                                Creature c4(h, 1);
                                d.place_at(c1, 0, 0);
                                d.place_at(c2, 0, 1);
                                d.place_at(c3, 1, 1);
                                d.place_at(c4, 1, 0);
                                d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Hop Down 10x1
    // ------------------

    try {
        cout << "*** Hop Down 10x1 ***" << endl;
        srand(0);
                                /*        
                                10x1 Darwin
                                Hopper, facing south at (0, 0)
                                Simulate 9 moves
                                Print every move
                                */
                                World d(10, 1);
                                Creature c1(h, 3);
                                d.place_at(c1, 0, 0);
                                d.darwin(9);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
// END 'ENSIGN' TESTS

// START 'KBIXBY' TESTS

    try {
        cout << "*** Darwin 2x2 Two Rovers ***" << endl;
        srand(0);
            /*
            2x2 Grid
            North Rover @ (0, 0)
            East Rover @ (1, 0)
            */
        World d(2, 2);
        Creature rn(r, 1);
        Creature re(r, 2);
        d.place_at(rn, 0, 0);
        d.place_at(re, 1, 0);
        d.darwin(10);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// END 'KBIXBY' TESTS



     try {
        cout << "*** Darwin 3x8 Guantlet***" << endl;
        /*
3x8 Darwin
Trap, facing south, at (0, 3)
Trap, facing east, at (0, 4)
Trap, facing north, at (2, 3)
Trap, facing east, at (2, 4)
Hopper, facing east, at (1, 0)
Simulate 10 moves.
Print every grid.
*/
        World a(3, 8);

        Creature c1(t, 3);
        Creature c2(t, 2);
        Creature c3(t, 1);
        Creature c4(t, 2);
        Creature c5(h, 2);

        a.place_at(c1, 0, 3);
        a.place_at(c2, 0, 4);
        a.place_at(c3, 2, 3);
        a.place_at(c4, 2, 4);
        a.place_at(c5, 1, 0);
        a.darwin(10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// END 'KBIXBY' TESTS

// START 'RYAN76' TESTS
    try {
        cout << "*** Darwin 6x6 ***" << endl;
        srand(0);
        
        /*
7x9 Darwin
Trap, facing south, at (0, 0)
Hopper, facing east, at (3, 2)
Rover, facing north, at (5, 4)
Trap, facing west, at (6, 6)
Simulate 5 moves.
Print every grid.
*/
        
        World x(7, 9);
        Creature trap1(t, 3);
        x.place_at(trap1, 0, 0);
        Creature hopper1(h, 2);
        x.place_at(hopper1, 3, 2);
        Creature rover1(r, 1);
        x.place_at(rover1, 5, 4);
        Creature trap2(t, 0);
        x.place_at(trap2, 6, 6);
        
        x.darwin(5);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// END 'RYAN76' TESTS

// START 'RBROOKS' TESTS
    try
    {
        /*
make a 2x20 world
1 hopper on top row 0,0 facing east
1 rovers on second row 1,0 facing east
4 foods on tird row col 16-19 facing WEst
4 foods on bottom row col 16-19 facing west
20 years
print every
the rover and hopper race to food.
rover plays dirty
*/
        cout << "*** Darwin 2x20 Drag Race ***" << endl;
        srand(0);
        World test(2,20);
        
        Creature crit_hopper1(h, 2);
        test.place_at(crit_hopper1, 0, 0);
        Creature crit_rover1(r, 2);
        test.place_at(crit_rover1, 1, 0);

        Creature crit_food1(f, 0);
        test.place_at(crit_food1, 1, 19);

        Creature crit_food2(f, 0);
        test.place_at(crit_food2, 1, 18);

        Creature crit_food3(f, 0);
        test.place_at(crit_food3, 1, 17);

        Creature crit_food4(f, 0);
        test.place_at(crit_food4, 1, 16);
        
        Creature crit_food5(f, 0);
        test.place_at(crit_food5, 1, 19);
        
        Creature crit_food6(f, 0);
        test.place_at(crit_food6, 1, 18);
        
        Creature crit_food7(f, 0);
        test.place_at(crit_food7, 1, 17);
        
        Creature crit_food8(f, 0);
        test.place_at(crit_food8, 1, 16);
        
        test.darwin(20);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
// END 'RBROOKS' TESTS
// START 'mjs4373' TESTS
/*    try
    {
        srand(0);
        cout << "*** Darwin 3x3 trap vs rover ***" << endl;
        World world(3, 3);

        Creature b1(, SOUTH);
        Creature b2('b', SOUTH);
        Creature b3('b', SOUTH);
        Creature r1('r', NORTH);
        Creature r2('r', NORTH);
        Creature r3('r', NORTH);

        world.add_creature(b1, 0, 0);
        world.add_creature(b2, 1, 0);
        world.add_creature(b3, 0, 1);
        world.add_creature(r1, 2, 2);
        world.add_creature(r2, 2, 1);
        world.add_creature(r3, 1, 2);

        cout << world << endl;
        for (size_t i = 1; i <= 15; ++i)
        {
            world.next_turn();
            if (i < 3)
            {
                cout << world << endl;
            }
            if (i % 5 == 0)
            {
                cout << world << endl;
            }
        }
    }
    catch (const invalid_argument&)
    {
        assert(false);
    }
    catch (const out_of_range&)
    {
        assert(false);
    }*/
// END 'MJS4373' TESTS
    return 0;}
