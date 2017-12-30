// Animal.cpp --- 
// 
// Filename: Animal.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Thu Nov 30 11:10:28 2017 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Dec 30 16:17:58 2017 (+0000)
//           By: Tomas Phelan
//     Update #: 6
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
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
#include "Animal.h"



Animal::Animal()
{

}

Animal::~Animal()
{

}

void Animal::makeAnimal(int t, int i, int j) {
	type = t;
	x = j;
	y = i;
	turn = 0;
	moved = 0;
	spawned = 0;
	foundPartner = 0;

}

char Animal::showAnimal()
{
	if (type == 0)
		return '~';
	if (type == 1)
		return '3';
	if (type == 2)
		return '&';
}

void Animal::wrap(int *a, int *b, int *c, int *d, int i, int j, int rows, int columns){
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
// 
// Animal.cpp ends here
