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
            bee->pose.hive.heading =
                (rand()%10000/10000.0)*PI*2;
            bee->pose.hive.vel = 0;
			bee->state=BEE_STATE_BUILDING;
            bee->frame = i;
            bee->frame_target = i;
            bee->location = LOCATION_FRAME;
            frame_add(bee, hive, i);
        }
    }

    hive->population = ctr;
}

void hive_cycle(agent_hive * hive)
{
    unsigned int i, j, index;
    agent_hive_frame * f;

    for (i = 0; i < hive->population; i++) {
        bee_cycle(&hive->bee[i]);
    }

    for (i = 0; i < HIVE_FRAMES; i++) {
        f = &hive->frame[i];
        for (j = 0; j < f->bees; j++) {
            index = f->bee_ID[j];
            frame_navigate(&hive->bee[index], hive);
        }
    }
}
