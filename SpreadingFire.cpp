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
#include <cstdlib>
#include <ctime>

using namespace bridges::game;
using namespace std;

struct SpreadingFire : public NonBlockingGame {

	static const int gridCols = 30;
	static const int gridRows = 30;

	// Map of cells containing either fire, a tree, or nothing
	int treeMap[gridRows][gridCols];
	int newTreeMap[gridRows][gridCols];

	const int FIRE = 2;
	const int TREE = 1;
	const int EMPTY = 0;

	const NamedColor fireColor = NamedColor::red;
	const NamedColor treeColor = NamedColor::green;
	const NamedColor emptyColor = NamedColor::yellow;

	const NamedSymbol fireSymbol = NamedSymbol::campfire;
	const NamedSymbol treeSymbol = NamedSymbol::triangle_up;
	const NamedSymbol emptySymbol = NamedSymbol::none;

	SpreadingFire(int assID, std::string username, std::string apikey)
		: NonBlockingGame (0, username, apikey, 30, 30) {
			setTitle("Spreading Fire");
			setDescription("Simulate the spread of fire. Probability of fire spreading 65%. Forest Density 95.");
		}

	bool burn() {	//Chance of tree catching fire
		int luck = rand() % 100;
		if (luck < 65) return true;
		else return false;
	}

	void spread(int i, int j) {
		if (newTreeMap[i][j] != FIRE) return; 
		else {
			// Checks if the trees surrounding FIRE catch on fire
			bool above = burn();
			bool below = burn();
			bool left = burn();
			bool right = burn();

			if (above) {
				if (i != 0 && treeMap[i - 1][j] == TREE) {
					newTreeMap[i - 1][j] = FIRE;
				}
			}

			if (below) {
				if  (i != gridRows - 1 && treeMap[i + 1][j] == TREE) {
					newTreeMap[i + 1][j] = FIRE;
				}
			}

			if (left) {
				if  (j != 0 && treeMap[i][j - 1] == TREE) {
					newTreeMap[i][j - 1] = FIRE;
				}
			}

			if (right) {
				if  (j != gridCols - 1 && treeMap[i][j + 1] == TREE) {
					newTreeMap[i][j + 1] = FIRE;
				}
			}
			newTreeMap[i][j] = EMPTY;
		}
	}

	void copy(int copy[gridRows][gridCols], int tree[gridRows][gridCols]) {
		for (int a = 0; a < gridRows; a++) {
			for (int b = 0; b < gridCols; b++) {
				copy[a][b] = tree[a][b];
			}
		}
	}

	bool same(int arr[gridRows][gridCols], int tree[gridRows][gridCols]) {
		for (int f = 0; f < gridRows; f++) {
			for (int g = 0; g < gridCols; g++) {
				if (arr[f][g] != tree[f][g]) return false;
			}
		}
		return true;
	}

	virtual void initialize() override {
		// TODO:
		// Set up the initial board by adding fire or trees to the map
		// in a pattern on the map
		for (int i = 0;i < gridRows; i++){
			for (int j = 0; j < gridCols; j++){
				if (i < 1 || j < 1 || i > gridRows - 2 || j > gridCols - 2) {
					treeMap[i][j] = EMPTY;
				}
				else if (i == gridRows / 2 && j == gridCols / 2) {
					treeMap[gridRows / 2][gridCols / 2] = FIRE; // fire in center
				}
				else {
					if (rand() % 100 < 95){
						treeMap[i][j] = TREE; // 95% chance of tree
					} else {
						treeMap[i][j] = EMPTY; //5% empty space
					}
				}
			}
		}
		copy(newTreeMap, treeMap);
	}

	virtual void gameLoop() override {
		// TODO:
		// Each frame run the logic of each cell based on what object
		// the cell currently is.
		// Fire should have a random chance to burn out and turn into an empty cell
		// Trees should turn into fire if they are adjacent to a fire cell

		//Add a for loop
		for (int i = 0; i < gridRows; i++){
			for (int j = 0; j < gridCols; j++){
				if (newTreeMap[i][j] == TREE) {
					setBGColor(i,j,treeColor);// sets bg to green
					drawSymbol(i,j, treeSymbol, NamedColor::black);
				}
				else if (newTreeMap[i][j] == FIRE) {
					setBGColor(i,j, fireColor);// bg to red
					drawSymbol(i,j, fireSymbol, NamedColor::black);
				}
				else {
					setBGColor(i,j, emptyColor);// bg to yellow
					drawSymbol(i,j, emptySymbol, NamedColor::black);
				}
			}
		}
		for (int a = 0; a < gridRows; a++){
			for (int b = 0; b < gridCols; b++){
				spread(a, b);
			}
		}
		if (!same(treeMap,newTreeMap)) copy(treeMap,newTreeMap);
//		else exit(0);

		/*
		   while(!same(newTreeMap, treeMap)) {
		   copy(newTreeMap, treeMap);
		   for (int i = 0; i < gridRows; i++){
		   for (int j = 0; j < gridCols; j++){
		   if(treeMap[i][j] == FIRE){
		   dead(treeMap, i, j);
		   spread(treeMap, i, j);
		   }

		   if (treeMap[i][j] == TREE) {
		   setBGColor(i,j,treeColor);// sets bg to green
		   drawSymbol(i,j, treeSymbol, NamedColor::black);
		   }
		   else if (treeMap[i][j] == FIRE) {
		   setBGColor(i,j, fireColor);// bg to red
		   drawSymbol(i,j, fireSymbol, NamedColor::black);
		   }
		   else {
		   setBGColor(i,j, emptyColor);// bg to yellow
		   drawSymbol(i,j, emptySymbol, NamedColor::black);
		   }
		   }
		   }
		   }
		   */
	}
};

int main(int argc, char** argv) {
	srand(time(0));
	SpreadingFire bridges_g (114, "KartNo", "1724369027536");

	bridges_g.start();
}
