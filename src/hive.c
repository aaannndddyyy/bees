/*
    bees - A bee simulation
    Copyright (C) 2015 Bob Mottram
    bob@robotics.uk.to

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "bees.h"

void hive_init(agent_hive * hive, unsigned int population,
			   double frame_width_mm, double frame_height_mm)
{
	unsigned int i, j, ctr=0;
	agent_bee * bee;

	hive->frame_size[POSITION_X] = frame_width_mm;
	hive->frame_size[POSITION_Y] = frame_height_mm;

	for (i = 0; i < HIVE_FRAMES; i++) {
		for (j = 0; j < population/HIVE_FRAMES; j++, ctr++) {
			bee = &hive->bee[ctr];
			bee_init(ctr, bee, hive);
			bee->pose.hive.posn[POSITION_X] =
				(rand()%10000/10000.0)*hive->frame_size[POSITION_X];
			bee->pose.hive.posn[POSITION_Y] =
				(rand()%10000/10000.0)*hive->frame_size[POSITION_Y];
			frame_add(bee, hive, i);
		}
	}

	population = ctr;
}
