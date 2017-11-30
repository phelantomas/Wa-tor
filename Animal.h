/* Animal.h --- 
 * 
 * Filename: Animal.h
 * Description: 
 * Author: Tomas Phelan
 * Maintainer: 
 * Created: Thu Nov 30 11:09:30 2017 (+0000)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Thu Nov 30 11:09:48 2017 (+0000)
 *           By: Tomas Phelan
 *     Update #: 1
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */


class Animal
{

public:
	int type;
	int turn;
	int moved;
	int x;
	int y;
	int spawned;
	Animal();
	~Animal();
	char showAnimal();
	bool checkAlive();
	void makeAnimal(int t, int i, int j);

};

/* Animal.h ends here */
