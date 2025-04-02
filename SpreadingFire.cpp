//
//  main.cpp
//  Bridges_Student_Project_Example
//
//  Created by Allie Beckman on 9/12/19.
//  Copyright © 2019 Allie Beckman. All rights reserved.
//

#include <NonBlockingGame.h>
#include <iostream>
#include <time.h>
#include <vector>

using namespace bridges::game;
using namespace std;

struct SpreadingFire : public NonBlockingGame {

  int gridCols = 30;
  int gridRows = 30;

  // Map of cells containing either fire, a tree, or nothing
  int treeMap[30][30];

  int FIRE = 2;
  int TREE = 1;
  int EMPTY = 0;

  NamedColor fireColor = NamedColor::red;
  NamedColor treeColor = NamedColor::green;
  NamedColor emptyColor = NamedColor::yellow;

  NamedSymbol fireSymbol = NamedSymbol::campfire;
  NamedSymbol treeSymbol = NamedSymbol::triangle_up;
  NamedSymbol emptySymbol = NamedSymbol::none;

  SpreadingFire(int assID, std::string username, std::string apikey)
    : NonBlockingGame (0, username, apikey, 30, 30) {
      setTitle("Spreading Fire");
      setDescription("Simulate the spread of fire. Probability of fire spreading 15%. Forest Density 95. Press the arrow keys to try different types of forests");

  }

  virtual void initialize() override {
    // TODO:
    // Set up the initial board by adding fire or trees to the map
    // in a pattern on the map
  }

  virtual void gameLoop() override {
    // TODO:
    // Each frame run the logic of each cell based on what object
    // the cell currently is.
    // Fire should have a random chance to burn out and turn into an empty cell
    // Trees should turn into fire if they are adjacent to a fire cell
  }
};

int main(int argc, char** argv) {
  SpreadingFire bridges_g (114, "BRIDGES_USER_ID", "BRIDGES_API_KEY");

  
  bridges_g.start();
}
