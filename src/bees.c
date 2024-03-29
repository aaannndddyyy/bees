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


http://www.dave-cushman.net/bee/behaviour.html
*/

#include "bees.h"

void bee_init(unsigned int ID, agent_bee * bee, agent_hive * hive)
{
    unsigned int i;

    bee->ID = ID;
    bee->queen_ID = 0;
    bee->caste = CASTE_WORKER;
    brain_init(&bee->brain);
    memset((void*)bee->vision,'\0',BRAIN_DIMENSION_VISION*sizeof(double));
    for (i = 0; i < DIMENSION_PHYSICS; i++) bee->physics[i]=0;
    bee->physics[PHYSICS_TEMPERATURE] = 15;
    bee->physics[PHYSICS_ENERGY]=1000;
    bee->frame=0;
    bee->frame_target=0;
    bee->cell[POSITION_X]=0;
    bee->cell[POSITION_Y]=0;
    bee->cell_target[POSITION_X]=0;
    bee->cell_target[POSITION_Y]=0;
    bee->location = LOCATION_FRAME;
    bee->state=BEE_STATE_CLEANING;
	bee->pose.environment.posn[POSITION_X]=0;
	bee->pose.environment.posn[POSITION_Y]=0;
	bee->pose.environment.heading=0;
	bee->pose.environment.vel=0;
	bee->pose.hive.posn[POSITION_X]=0;
	bee->pose.hive.posn[POSITION_Y]=0;
	bee->pose.hive.heading=0;
	bee->pose.hive.vel=0;

    for (i = 0; i < PAYLOADS; i++) bee->payload[i]=0;
    for (i = 0; i < PHEROMONES; i++) {
        bee->smell[i]=0;
        bee->pheremone[i]=0;
    }
}

void bee_behavior_building(agent_bee * bee)
{
}

void bee_behavior_forage(agent_bee * bee)
{
}

void bee_behavior_grow(agent_bee * bee)
{
}

void bee_behavior_guard(agent_bee * bee)
{
}

void bee_behavior_robber(agent_bee * bee)
{
}

void bee_behavior_fanning(agent_bee * bee)
{
}

void bee_behavior_heating(agent_bee * bee)
{
}

void bee_behavior_laying(agent_bee * bee)
{
}

void bee_behavior_capping(agent_bee * bee)
{
}

void bee_behavior_mating(agent_bee * bee)
{
}

void bee_behavior_cleaning(agent_bee * bee)
{
}

void bee_behavior_polishing(agent_bee * bee)
{
}

void bee_behavior_undertaking(agent_bee * bee)
{
}

void bee_behavior_grooming(agent_bee * bee)
{
}

void bee_behavior_retinue(agent_bee * bee)
{
}

void bee_behavior_balling(agent_bee * bee)
{
}

void bee_behavior_resting(agent_bee * bee)
{
}

void bee_behavior_dancing(agent_bee * bee)
{
}

void bee_behavior_nursing(agent_bee * bee)
{
}

void bee_cycle(agent_bee * bee)
{
    brain_cycle(bee);

    switch (bee->state)
    {
    case BEE_STATE_BUILDING: {
        bee_behavior_building(bee);
        break;
    }
    case BEE_STATE_LAVA: {
        bee_behavior_grow(bee);
        break;
    }
    case BEE_STATE_FORAGE: {
        bee_behavior_forage(bee);
        break;
    }
    case BEE_STATE_FANNING: {
        bee_behavior_fanning(bee);
        break;
    }
    case BEE_STATE_HEATING: {
        bee_behavior_heating(bee);
        break;
    }
    case BEE_STATE_GUARD: {
        bee_behavior_guard(bee);
        break;
    }
    case BEE_STATE_ROBBER: {
        bee_behavior_robber(bee);
        break;
    }
    case BEE_STATE_LAYING: {
        bee_behavior_laying(bee);
        break;
    }
    case BEE_STATE_CAPPING: {
        bee_behavior_capping(bee);
        break;
    }
    case BEE_STATE_MATING: {
        bee_behavior_mating(bee);
        break;
    }
    case BEE_STATE_CLEANING: {
        bee_behavior_cleaning(bee);
        break;
    }
    case BEE_STATE_POLISHING: {
        bee_behavior_polishing(bee);
        break;
    }
    case BEE_STATE_UNDERTAKING: {
        bee_behavior_undertaking(bee);
        break;
    }
    case BEE_STATE_GROOMING: {
        bee_behavior_grooming(bee);
        break;
    }
    case BEE_STATE_BALLING: {
        bee_behavior_balling(bee);
        break;
    }
    case BEE_STATE_RESTING: {
        bee_behavior_resting(bee);
        break;
    }
    case BEE_STATE_DANCING: {
        bee_behavior_dancing(bee);
        break;
    }
    case BEE_STATE_RETINUE: {
        bee_behavior_retinue(bee);
        break;
    }
    case BEE_STATE_NURSING: {
        bee_behavior_nursing(bee);
        break;
    }
    }
}
