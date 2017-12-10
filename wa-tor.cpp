// wa-tor.cpp --- 
// 
// Filename: wa-tor.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Thu Nov 30 11:07:19 2017 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Sun Dec 10 17:57:57 2017 (+0000)
//           By: Tomas Phelan
//     Update #: 24
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary:
//
//
// Todo:
// 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:

#include <omp.h>
#include <iostream>
#include "Animal.h"
#include <stdio.h>
#include <stdlib.h>    
#include <time.h> 
#include <chrono>
#include <limits>
#include <unistd.h>
using namespace std;

//change these in order to affect the size of the world
int const rows = 25;
int const columns = 40;

char map[rows][columns];
Animal ocean[rows][columns];
int fishLife = 20;
int sharkLife = 25;
int moves = 0;
int sharkBreed = 0;
int sharkStarve = 0;
int fishBreed = 0;

/*!
Brief: Wraps around the map
 */
void wrap(int *a, int *b, int *c, int *d, int i, int j){
        *a = i - 1;
        *b = j - 1;
        *c = i + 1;
	*d = j + 1;

	//wraps
	if (*a < 0) {
		*a = rows - 1;
	}
	if (*b < 0) {
		*b = columns - 1;
	}
	if (*a > rows - 1) {
		*a = 0;
	}
	if (*b > columns - 1) {
		*b = 0;
	}
}


/*! 
Brief: Checks if a shark has eaten, if not, the shark will be removed
*/
void checkStarve(int i, int j, int x, int y, int ate, int foundShark) {
	int dead = 0;
	//if shark has reached its starve limit, check if it has eaten
	if (ocean[i][j].turn > 0 && ocean[i][j].turn % sharkStarve == 0)
	{
		if (ate == 0) {
			dead = 1;
		}
		else {
			ate = 0;
		}
	}						//sharkLife
	if (ocean[i][j].turn < sharkStarve) { //changed sharkLife to sharkStarve? Based on whether shark has reached turn limit?
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;
		ocean[y][x] = ocean[i][j];
		if (y != i || j != x) {
			dead = 1;
			ocean[i][j].makeAnimal(0, i, j);
		}
	}
	else {
		dead = 1;
	}
	//if value for turn greater than value for breed, create new shark // doesn't check if any are beside it
	if (ocean[y][x].turn > sharkBreed && ocean[y][x].spawned == 0 && foundShark == 1 && dead == 0) {
		ocean[y][x].spawned = 1;
		ocean[i][j].makeAnimal(2, i, j);
	}
	if (dead == 1) {
		ocean[i][j].makeAnimal(0, i, j);
	}	
}

/*! 
Brief: Shark checks whether anything is in it's adjecent fields
*/
int findAnimals(int newLoc, int i, int j, int *x, int *y, Animal temp[8]) {
	int foundFish = 0;
	int ate = 0;
	int foundFreeSpace = 0;
	int foundShark = 0;

	//this finds shark to breed
	if (foundShark == 0) {
		for (int pos = newLoc; pos < 7; pos++) {
			*x = temp[pos].x;
			*y = temp[pos].y;
			if (ocean[*y][*x].type == 2) {
				foundShark = 1;
				break;
			}
		}

		if (foundShark == 0) {
			for (int pos = newLoc; pos > 0; pos--) {
				*x = temp[pos].x;
				*y = temp[pos].y;
				if (ocean[*y][*x].type == 2) {// was 0
					foundShark = 1;
					break;
				}
			}
		}
	}
	
	//checks for fish
	for (int pos = newLoc; pos < 7; pos++) {
		*x = temp[pos].x;
		*y = temp[pos].y;
		if (ocean[*y][*x].type == 1) {//if fish
			foundFish = 1;
			ocean[*y][*x].makeAnimal(0, *y, *x);//removes fish
			ate = 1;
			break;
		}
	}

	if (foundFish == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			*x = temp[pos].x;
			*y = temp[pos].y;
			if (ocean[*y][*x].type == 1) {
				foundFish = 1;
				ocean[*y][*x].makeAnimal(0, *y, *x);
				ate = 1;
				break;
			}
		}
	}

	//this moves shark
	if (foundFish == 0) {
		for (int pos = newLoc; pos < 7; pos++) {
			*x = temp[pos].x;
			*y = temp[pos].y;
			if (ocean[*y][*x].type == 0) {
				break;
			}
		}

		if (foundFreeSpace == 0) {
			for (int pos = newLoc; pos > 0; pos--) {
				*x = temp[pos].x;
				*y = temp[pos].y;
				if (ocean[*y][*x].type == 0) {// was 0
					foundFreeSpace = 1;
					break;
				}
			}
		}
	}

	
	if (foundFreeSpace == 0) {
		*y = i;
		*x = j;
	}
	return foundShark;
}

/*!
Brief: Calls all functions for a shark
 */
void sharkTurn(int i, int j) {

	//pick a random adjacent square to move into-------------------------------
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	wrap(&a, &b, &c, &d, i, j);

	Animal temp[8] = { ocean[i][d], ocean[c][d], ocean[c][j], ocean[c][b],
		ocean[i][b], ocean[a][b], ocean[a][j], ocean[a][d] };
	
	srand(time(NULL));
	int y;
	int x;
	int foundShark = 0;
	int newLoc = rand() % 8; // random 
	int foundFish = 0;
	int noFish = 0;
	int ate = 0;
	int dead = 0;

	foundShark = findAnimals(newLoc, i, j, &x, &y, temp);
	//starves to death
	checkStarve(i, j, x, y, ate, foundShark);
}

void fishTurn(int i, int j) {
	//pick a random adjacent square to move into-------------------------------
        int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	wrap(&a, &b, &c, &d, i, j);

	Animal temp[8] = { ocean[i][d], ocean[c][d], ocean[c][j], ocean[c][b],
		ocean[i][b], ocean[a][b], ocean[a][j], ocean[a][d] };

	srand(time(NULL));
	int y;
	int x;
	int found = 0;
	int newLoc = rand() % 8;
	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[y][x].type == 0) {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 0) {
				found = 1;
				break;
			}
		}
	}

	if (found == 0) {
		y = i;
		x = j;
	}
      

	//kill fish
	if (ocean[i][j].turn < fishLife) {
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;
		ocean[y][x] = ocean[i][j];
		if (y != i || j != x)
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {
		ocean[i][j].makeAnimal(0, i, j);
	}

	//generate new fish
	if (ocean[y][x].turn > fishBreed && ocean[y][x].spawned == 0) {
		ocean[y][x].spawned = 1;
		ocean[i][j].makeAnimal(1, i, j);
	}
}

void populateMap() {
#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = 0;
			ocean[i][j].makeAnimal(0, i, j);
		}
	}
}

using namespace std;
bool displayMap() {
	int fishCount = 0;
	int sharkCount = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << ocean[i][j].showAnimal() << " ";
			if (ocean[i][j].type == 1) {
				fishCount++;
			}
			if (ocean[i][j].type == 2) {
				sharkCount++;
			}
		}
		cout << std::endl;
	}
	cout << "Fish(-): " << fishCount << "        Sharks(&): " << sharkCount << "      Turns: " << moves << std::endl;

	/*if (fishCount == 0 || sharkCount == 0) {
		return false;
	}*/
	return true;
}

void checkOcean() {
#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ocean[i][j].type == 2 && ocean[i][j].moved == 0) {
				sharkTurn(i, j);
			}
			if (ocean[i][j].type == 1 && ocean[i][j].moved == 0) {
				fishTurn(i, j);
			}
		}
	}
	moves++;
#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ocean[i][j].type == 2) {
				ocean[i][j].moved = 0;
			}
			if (ocean[i][j].type == 1) {
				ocean[i][j].moved = 0;
			}

		}
	}
}

/*! 
Brief: Return the number input by the user
*/
int returnNumber() {
	int number = 0;
	
	while (!(std::cin >> number)) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Invalid input.  Try again: ";
	}
	std::cout << "You entered: " << number << std::endl;

	return number;
}

int main()
{
	//Creating a map already populated with some sharks and fish
	populateMap();

	//cout enter in number of sharks 
	//replace with random
	int numOfSharks = 0;
	int numOfFish = 0;

	int numOfSharksCreated = 0;
	int numOfFishCreated = 0;

	int maxAnimalsAllowed = 0;
	int numOfAnimalsEntered = 0;

	maxAnimalsAllowed = rows * columns;

	std::cout << "Enter in number of sharks wanted: ";
	numOfSharks = returnNumber();

	std::cout << "Enter in breed time of sharks wanted: ";
	sharkBreed = returnNumber();

	std::cout << "Enter in starve time of sharks wanted: ";
	sharkStarve = returnNumber();

	std::cout << "Enter in number of fishies wanted: ";
	numOfFish = returnNumber();

	std::cout << "Enter in breed time of fish wanted: ";
	fishBreed = returnNumber();

	numOfAnimalsEntered = numOfSharks + numOfFish;

	if (numOfAnimalsEntered > maxAnimalsAllowed) {
		std::cout << "Too many animals entered ";
		system("pause");
		return 0;
	}
	else {
		while (numOfSharksCreated != numOfSharks && numOfFishCreated != numOfFish) {
		  #pragma omp parallel for
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++) {
					int newAnimal = rand() % 3;

					if (ocean[i][j].type == 0) {
						if (newAnimal == 1) {
							if (numOfFishCreated < numOfFish) {
								numOfFishCreated++;
								ocean[i][j].makeAnimal(newAnimal, i, j);
							}
						}
						else if (newAnimal == 2) {
							if (numOfSharksCreated < numOfSharks) {
								numOfSharksCreated++;
								ocean[i][j].makeAnimal(newAnimal, i, j);
							}
						}
					}

				}
		}
	}

	clock_t tStart = clock();
	displayMap();
	system("clear");

	bool allAlive = true;

	while (allAlive)
	{
		checkOcean();
		allAlive = displayMap();
		usleep(500000); 
		system("clear");
	}

	displayMap();
	cout << "Fish life(n): " << fishLife << "    Shark life(m): " << sharkLife << "    Grid size: " << rows << 'x' << columns << std::endl;
	printf("Time taken to ecxecute: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}///need to associate the turns with the individual sharks instead of the blocks

// 
// wa-tor.cpp ends here
