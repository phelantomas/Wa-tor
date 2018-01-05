// wa-tor.cpp --- 
// 
// Filename: wa-tor.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Thu Nov 30 11:07:19 2017 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Fri Jan  5 15:20:26 2018 (+0000)
//           By: Tomas Phelan
//     Update #: 104
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

#include <omp.h>
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
int fishLife = 20;
int sharkLife = 25;
int moves = 0;
int sharkBreed = 6;
int sharkStarve = 25;
int fishBreed = 2;

int numOfSharks = 500;
int numOfFish = 1000;

double finishTime = 0;

void writeToFile(double finishTime){
  ofstream myfile;
  myfile.open("runtime.txt", ios::app);
  myfile << fixed << setprecision(17) << finishTime << "\n";
  myfile.close();
  
}

int findPartner(int x, int y, int type, Animal temp[8]) {
	int found = 0;
	int newLoc = rand() % 8;

	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[y][x].type == type) {
			found = 1;
			break;
		}
	}
	if (found == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == type) {
				found = 1;
				break;
			}
		}
	}
	return found;
}

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

	for (int pos = newLoc; pos < 7; pos++) {
		x = temp[pos].x;
		y = temp[pos].y;
		if (ocean[y][x].type == 1) {
			foundFish = 1;
			ocean[y][x].makeAnimal(0, y, x);
			ate = 1;
			break;
		}
	}

	if (foundFish == 0) {
		for (int pos = newLoc; pos > 0; pos--) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 1) {
				foundFish = 1;
				ocean[y][x].makeAnimal(0, y, x);
				ate = 1;
				break;
			}
		}
	}


	if (foundFish == 0) {
		for (int pos = newLoc; pos < 7; pos++) {
			x = temp[pos].x;
			y = temp[pos].y;
			if (ocean[y][x].type == 0) {
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
	}

	if (found == 0) {
		y = i;
		x = j;
	}

	if (ocean[i][j].turn > 0 && ocean[i][j].turn % 4 == 0)
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
		ocean[y][x] = ocean[i][j];
		if (y != i || j != x)
			ocean[i][j].makeAnimal(0, i, j);
	}
	else {
		dead = 1;
	}
	//breeds new shark
	ocean[y][x].foundPartner = findPartner(x, y, 2, temp);
	if (ocean[y][x].turn > sharkBreed && ocean[y][x].spawned == 0 && ocean[y][x].foundPartner == 1) {
		ocean[y][x].foundPartner = 0;
		ocean[y][x].spawned = 1;
		ocean[i][j].makeAnimal(2, i, j);
	}
	if (dead == 1) {
		ocean[i][j].makeAnimal(0, i, j);
	}
}

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
	//------------------------------------------------------------------------------------------


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

	//breeds fish
	ocean[y][x].foundPartner = findPartner(x, y, 1, temp);
	if (ocean[y][x].turn > fishBreed && ocean[y][x].spawned == 0 && ocean[y][x].foundPartner == 1) {
		ocean[y][x].foundPartner = 0;
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

	cout << "Fish(#): " << fishCount << "        Sharks(&): " << sharkCount << "      Turns: " << moves << std::endl;
	if (fishCount == 0 || sharkCount == 0) {
		return false;
	}
	return true;
}

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
	system("CLS");

	bool allAlive = true;
	while (moves < 800)/*! execute while there are shark, fish, or a year hasn't elasped*/
	{
		checkOcean();
		allAlive = displayMap();
		//	usleep(500000);
		system("CLS");	
	}

	displayMap();
	finishTime = (clock() - tStart) / (double) CLOCKS_PER_SEC;
	writeToFile(finishTime);
	cout << "Fish life(#): " << fishLife << "    Shark life(m): " << sharkLife << "    Grid size: " << rows << 'x' << columns << std::endl;
	printf("Time taken to execute: \n");

	cout.precision(17);
	cout <<  finishTime << endl;
	return 0;
}



