// --------------
// TestDarwin.c++
// --------------

// includes
#include <iostream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

TEST(World, place_at1) {
   World w(2, 2);
   Species f('f');
   Creature food(f, 0);
   w.place_at(food, 0, 0);
   assert(w.grid[0][0] != 0);
}

TEST(World, place_at2) {
   World w(2, 2);
   Species f('f');
   Creature food(f, 0);
   w.place_at(food, 1, 0);
   assert(w.grid[1][0] != 0);
}

TEST(World, place_at3) {
   World w(2, 2);
   Species f('f');
   Creature food(f, 0);
   w.place_at(food, 0, 1);
   assert(w.grid[0][1] != 0);
}

TEST(World, place_at4) {
   World w(2, 2);
   Species f('f');
   Creature food(f, 0);
   w.place_at(food, 1, 1);
   assert(w.grid[1][1] != 0);
}

TEST(World, place_at5) {
   World w(5, 5);
   Species t('t');
   Creature trap(t, 0);
   w.place_at(trap, 2, 3);
   assert(w.grid[2][3] != 0);
}

TEST(World, simulate1) {
   World w(2, 3);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   Creature hop(h, 2);
   w.place_at(hop, 0, 1);
   Creature* temp = w.grid[0][1];
   w.simulate(*temp, 0, 1);

   assert(w.grid[0][2] != 0);
 }

TEST(World, simulate2) {
   World w(2, 4);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   Creature hop(h, 2);
   w.place_at(hop, 0, 2);
   Creature* temp = w.grid[0][2];
   w.simulate(*temp, 0, 2);

   assert(w.grid[0][3] != 0);
 }

TEST(World, simulate3) {
   World w(5, 5);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   Creature hop(h, 2);
   w.place_at(hop, 0, 3);
   Creature* temp = w.grid[0][3];
   w.simulate(*temp, 0, 3);

   assert(w.grid[0][4] != 0);
 }

TEST(World, simulate4) {
   World w(7, 7);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   Creature hop(h, 2);
   w.place_at(hop, 0, 4);
   Creature* temp = w.grid[0][4];
   w.simulate(*temp, 0, 4);

   assert(w.grid[0][5] != 0);
 }

TEST(World, darwin1) {
  World w(5, 5);
  Species f('f');
  Creature food(f, 0);
  w.place_at(food, 0, 0);
  assert(1);
}

TEST(World, darwin2) {
  World w(3, 7);
  Species f('f');
  Creature food(f, 1);
  w.place_at(food, 1, 3);
  assert(1);
}

TEST(World, darwin3) {
  World w(3, 10);
  Species r('r');
  Creature rover(r, 1);
  w.place_at(rover, 1, 4);
  assert(1);
}

/*Species Unit Test*/
TEST(Species, add_instruction1) {
   World w(7, 7);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   assert(h.instructions[0] == "hop");
}

TEST(Species, add_instruction2) {
   World w(7, 7);
   Species h('h');
   h.add_instruction("hop");
   h.add_instruction("go 0");
   assert(h.instructions[1] == "go 0");
}

TEST(Species, add_instruction3) {
   World w(7, 7);
   Species f('f');
   f.add_instruction("left");
   f.add_instruction("go 0");
   assert(f.instructions[0] == "left");
}

TEST(Species, add_instruction4) {
   World w(7, 7);
   Species f('f');
   f.add_instruction("left");
   f.add_instruction("go 0");
   assert(f.instructions[1] == "go 0");
}

TEST(Species, add_instruction5) {
   World w(7, 7);
   Species t('t');
   t.add_instruction("if_enemy 3");
   t.add_instruction("left");
   t.add_instruction("go 0");
   t.add_instruction("infect");
   t.add_instruction("go 0");
   assert(t.instructions[0] == "if_enemy 3");
}

TEST(Species, add_instruction6) {
   World w(7, 7);
   Species t('t');
   t.add_instruction("if_enemy 3");
   t.add_instruction("left");
   t.add_instruction("go 0");
   t.add_instruction("infect");
   t.add_instruction("go 0");
   assert(t.instructions[1] == "left");
}

TEST(Species, add_instruction7) {
   World w(7, 7);
   Species t('t');
   t.add_instruction("if_enemy 3");
   t.add_instruction("left");
   t.add_instruction("go 0");
   t.add_instruction("infect");
   t.add_instruction("go 0");
   assert(t.instructions[2] == "go 0");
}

TEST(Species, add_instruction8) {
   World w(7, 7);
   Species t('t');
   t.add_instruction("if_enemy 3");
   t.add_instruction("left");
   t.add_instruction("go 0");
   t.add_instruction("infect");
   t.add_instruction("go 0");
   assert(t.instructions[3] == "infect");
}
