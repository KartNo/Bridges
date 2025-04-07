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

	int gridCols = 30;
	int gridRows = 30;

	// Map of cells containing either fire, a tree, or nothing
	int treeMap[30][30];
	int newTreeMap[30][30];

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

	bool burn() {	//Chance of tree catching fire
		int luck = rand() % 100;
		if (luck < 15) return true;
		else return false;
	}
	void spread(int arr[gridRows][gridCols], int i, int j) {
			// Checks if the trees surrounding FIRE catch on fire
			bool above = burn();
			bool below = burn();
			bool left = burn();
			bool right = burn();

			if (above) {
				if (i != 0 && treeMap[i - 1][j] == TREE) {
					treeMap[i - 1][j] = FIRE;
				}
			}

			if (below) {
				if  (i != gridRows - 1 && treeMap[i + 1][j] == TREE) {
					treeMap[i + 1][j] = FIRE;
				}
			}

			if (left) {
				if  (j != 0 && treeMap[i][j - 1]) {
					treeMap[i][j - 1] = FIRE;
				}
			}

			if (right) {
				if  (j != gridCols - 1 && treeMap[i][j + 1]) {
					treeMap[i][j + 1] = FIRE;
				}
			}
		}
	}

	void dead(int arr[gridRows][gridCols], int i, int j) {
		// Turns the original FIRE to EMPTY
		arr[i][j] = EMPTY;
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
		srand(time(0));
		for (int r = 0; r < gridRows; r++){
			for (int s = 0; s < gridcols; s++){
				if (rand() % 100 < 95){
					treeMap[i][j] = TREE; // 95% chance of tree
				} else {
					treeMap[i][j] = EMPTY; //5% empty space
				}
			}
		}
		treeMap[gridRows / 2][gridCols / 2] = FIRE; // fire in center
	}

	virtual void gameLoop() override {
		// TODO:
		// Each frame run the logic of each cell based on what object
		// the cell currently is.
		// Fire should have a random chance to burn out and turn into an empty cell
		// Trees should turn into fire if they are adjacent to a fire cell
		copy(newTreeMap, treeMap);
		spread(treeMap, gridRows / 2, gridCols / 2);

		while(!same(newTreeMap, treeMap)) {
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
	}
};

int main(int argc, char** argv) {
	SpreadingFire bridges_g (114, "BRIDGES_USER_ID", "BRIDGES_API_KEY");

	bridges_g.start();
}
