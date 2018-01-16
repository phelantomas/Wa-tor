// wa-tor.cpp --- 
// 
// Filename: wa-tor.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Thu Nov 30 11:07:19 2017 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Sun Jan 14 21:34:19 2018 (+0000)
//           By: Tomas Phelan
//     Update #: 137
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
// Add in check for other fish to decide to breed
// Allow sharks to breed without eating
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

//#include <omp.h>
#include <iostream>
#include <fstream>
#include "Animal.h"
#include <stdio.h>
#include <stdlib.h>    
#include <time.h> 
#include <chrono>
#include <limits>
#include <unistd.h>
#include <iomanip>
using namespace std;

//default values
int const rows = 35;
int const columns = 60;
char map[rows][columns];
Animal ocean[rows][columns];
int fishLife = 25;
int sharkLife = 25;
int moves = 0;
int sharkBreed = 15;
int sharkStarve = 25;
int fishBreed = 13;

int numOfSharks = 40;
int numOfFish = 150;

double finishTime = 0;

/*!
Brief : Writes the finish time to a file
 */
void writeToFile(double finishTime){
  ofstream myfile;
  myfile.open("runtime.txt", ios::app);
  myfile << fixed << setprecision(17) << finishTime << "\n";
  myfile.close();
  
}

/*!
Brief: Searches for an animal type that is the same as itself
*/
int findPartner(int x, int y, int type, Animal temp[8]) {
	int found = 0;
	int newLoc = rand() % 8;
	//going to eventually change the y x to see if it works still
	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[x][y].type == type) {
			found = 1;
			break;
		}
	}
	if (found == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[x][y].type == type) {
				found = 1;
				break;
			}
		}
	}
	return found;
}

/*!
Brief: Does the sharks turn 
 */
void moveShark(int i, int j) {
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	ocean[i][j].wrap(&a, &b, &c, &d, i, j, rows, columns);

	Animal temp[8] = { ocean[i][d], ocean[c][d], ocean[c][j], ocean[c][b],
		ocean[i][b], ocean[a][b], ocean[a][j], ocean[a][d] };

	srand(time(NULL));
	int y;
	int x;
	int found = 0;
	int newLoc = rand() % 8;
	int foundFish = 0;
	int noFish = 0;
	int ate = 0;
	int dead = 0;
	/*!check surrounding spaces clockwise*/
	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[x][y].type == 1) {
			foundFish = 1;
			ocean[x][y].makeAnimal(0, x, y);
			ate = 1;
			break;
		}
	}
	/*!check surrounding squares counter-clockwise if fish not found*/
	if (foundFish == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[x][y].type == 1) {
				foundFish = 1;
				ocean[x][y].makeAnimal(0, x, y);
				ate = 1;
				break;
			}
		}
	}
	/*!this is where the shark moves, changed foundFish to found(ie found space to move to)*/
	if (found == 0) {//changed because this if controls access to next 2 blocks of code, if eaten, can't move?
		for (int pos = newLoc; pos < 7; pos++) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[x][y].type == 0) {
			        found = 1;
				break;
			}
		}
		if (found == 0) {
			for (int pos = newLoc; pos > 0; pos--) {
				x = temp[pos].x;
				y = temp[pos].y;
				if (ocean[x][y].type == 0) {
					found = 1;
					break;
				}
			}
		}
	}
	
	if (found == 0) {
		y = i;
		x = j;
	}
	/*!was turn % 4 for seemingly no reason, now based on sharkStarve to determine if it starves*/
	if (ocean[i][j].turn > 0 && ocean[i][j].turn % sharkStarve == 0)
	{
		if (ate == 0) {
			dead = 1;
		}
		else {
			ate = 0;
		}
	}
	if (ocean[i][j].turn < sharkLife) {
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;
		ocean[x][y] = ocean[i][j];
		if (x != i || j != y)//if the shark moved, remove object from previous position, otherwise do nothing
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {//if sharkLife exceeded, die of old age, in bed, surrounded by family, RIP Jaws
		dead = 1;
	}
	//breeds new shark
	ocean[x][y].foundPartner = findPartner(x, y, 2, temp);
	//changing to modulo sharkBreed to allow multiple breeds
	if (ocean[x][y].turn % sharkBreed == 0  && ocean[x][y].foundPartner == 1) {
		ocean[x][y].foundPartner = 0;
		ocean[x][y].spawned = 1;//if moved spawns on previous position? Also spawned not used for anything?
		ocean[i][j].makeAnimal(2, i, j);//if hasn't moved, breeds on own position? Overwrites self
	}
	if (dead == 1) {//murder
		ocean[i][j].makeAnimal(0, i, j);
	}
}

/*!
Brief: Does the fish turn
 */
void moveFish(int i, int j) {

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	ocean[i][j].wrap(&a, &b, &c, &d, i, j, rows, columns);

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
		if (ocean[x][y].type == 0) {
			found = 1;
			break;
		}
	}
	if (found == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[x][y].type == 0) {
				found = 1;
				break;
			}
		}
	}
	//is actually needed to fix values of x and y to original position
	if (found == 0) {
	        x = i;
		y = j;
	}
	//------------------------------------------------------------------------------------------


	if (ocean[i][j].turn < fishLife) {
		ocean[i][j].turn++;
		ocean[i][j].moved = 1;//even if technically didn't move, had turn
		ocean[x][y] = ocean[i][j];
		if (y != i || j != x)//if fish has moved, void previous location
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {//murder fish in cold blood, and water
		ocean[i][j].makeAnimal(0, i, j);
	}

	//breeds fish
       	ocean[x][y].foundPartner = findPartner(x, y, 1, temp);
	//changing to modulo, same as shark above
	if (ocean[x][y].turn % fishBreed == 0 && ocean[x][y].foundPartner == 1) { // && ocean[x][y].foundPartner == 1
		ocean[x][y].foundPartner = 0;
		ocean[x][y].spawned = 1;//only allow to spawn once?
		ocean[i][j].makeAnimal(1, i, j);
	}
}

/*!
Brief: Creates map as empty
 */
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
/*!
Brief:  Displays the current location of animals, and their count
 */
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

	cout << "Fish(#): " << fishCount << "        Sharks(&): " << sharkCount << "      Turns: " << moves << std::endl;
	if (fishCount == 0 || sharkCount == 0) {
		return false;
	}
	return true;
}

/*!
Brief: Calls the turns for the animals
 */
void checkOcean() {
#pragma omp parallel for
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ocean[i][j].type == 2 && ocean[i][j].moved == 0) {
				moveShark(i, j);
			}
			if (ocean[i][j].type == 1 && ocean[i][j].moved == 0) {
				moveFish(i, j);
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

	int numOfSharksCreated = 0;
	int numOfFishCreated = 0;

	int maxAnimalsAllowed = 0;
	int numOfAnimalsEntered = 0;

	maxAnimalsAllowed = rows * columns;

	//commented out to run python script a 1000 times

	/*!	std::cout << "Enter in number of sharks wanted: ";
	numOfSharks = returnNumber();

	std::cout << "Enter in breed time of sharks wanted: ";
	sharkBreed = returnNumber();

	std::cout << "Enter in starve time of sharks wanted: ";
	sharkStarve = returnNumber();

	std::cout << "Enter in number of fishies wanted: ";
	numOfFish = returnNumber();

	std::cout << "Enter in breed time of fish wanted: ";
	fishBreed = returnNumber();

	*/
	// not needed when input commented out
	//numOfAnimalsEntered = numOfSharks + numOfFish;

	/*!
	  Puts animals into the map
	  if will never pass without user input
	 */
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
	while (moves < 800)/*! execute while under 800 turns*/
	{
		checkOcean();
		allAlive = displayMap();
		usleep(50000);
		system("clear");	
	}
	system("clear");

	displayMap();
	//finishTime = (clock() - tStart) / (double) CLOCKS_PER_SEC;
	//writeToFile(finishTime);
	cout << "Fish life(#): " << fishLife << "    Shark life(m): " << sharkLife << "    Grid size: " << rows << 'x' << columns << std::endl;
	printf("Time taken to execute: \n");

	cout.precision(17);
	cout <<  finishTime << endl;
	return 0;
}




