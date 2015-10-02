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
	bee->ID = ID;
	bee->queen_ID = 0;
	bee->caste = CASTE_WORKER;
	brain_init(&bee->brain);
	memset((void*)bee->vision,'\0',BRAIN_DIMENSION_VISION*sizeof(double));
    bee->physics[PHYSICS_TEMPERATURE] = 15;
    bee->physics[PHYSICS_HUMIDITY]=0;
    bee->physics[PHYSICS_PRESSURE]=0;
	bee->physics[PHYSICS_VIBRATION]=0;
	bee->physics[PHYSICS_TIME_OF_DAY]=0;
	bee->physics[PHYSICS_TIME_OF_YEAR]=0;
    bee->physics[PHYSICS_AGE_DAYS]=0;
    bee->physics[PHYSICS_ENERGY]=1000;
}

void bee_forage(agent_bee * bee)
{
}

void bee_grow(agent_bee * bee)
{
}

void bee_guard(agent_bee * bee)
{
}

void bee_robber(agent_bee * bee)
{
}

void bee_fanning(agent_bee * bee)
{
}

void bee_heating(agent_bee * bee)
{
}

void bee_laying(agent_bee * bee)
{
}

void bee_capping(agent_bee * bee)
{
}

void bee_mating(agent_bee * bee)
{
}

void bee_cleaning(agent_bee * bee)
{
}

void bee_polishing(agent_bee * bee)
{
}

void bee_undertaking(agent_bee * bee)
{
}

void bee_grooming(agent_bee * bee)
{
}

void bee_retinue(agent_bee * bee)
{
}

void bee_balling(agent_bee * bee)
{
}

void bee_resting(agent_bee * bee)
{
}

void bee_dancing(agent_bee * bee)
{
}

void bee_nursing(agent_bee * bee)
{
}

void bee_update(agent_bee * bee)
{
    switch (bee->state)
    {
    case BEE_STATE_LAVA: {
        bee_grow(bee);
        break;
    }
    case BEE_STATE_FORAGE: {
        bee_forage(bee);
        break;
    }
    case BEE_STATE_FANNING: {
        bee_fanning(bee);
        break;
    }
    case BEE_STATE_HEATING: {
        bee_heating(bee);
        break;
    }
    case BEE_STATE_GUARD: {
        bee_guard(bee);
        break;
    }
    case BEE_STATE_ROBBER: {
        bee_robber(bee);
        break;
    }
    case BEE_STATE_LAYING: {
        bee_laying(bee);
        break;
    }
    case BEE_STATE_CAPPING: {
        bee_capping(bee);
        break;
    }
    case BEE_STATE_MATING: {
        bee_mating(bee);
        break;
    }
    case BEE_STATE_CLEANING: {
        bee_cleaning(bee);
        break;
    }
    case BEE_STATE_POLISHING: {
        bee_polishing(bee);
        break;
    }
    case BEE_STATE_UNDERTAKING: {
        bee_undertaking(bee);
        break;
    }
    case BEE_STATE_GROOMING: {
        bee_grooming(bee);
        break;
    }
    case BEE_STATE_BALLING: {
        bee_balling(bee);
        break;
    }
    case BEE_STATE_RESTING: {
        bee_resting(bee);
        break;
    }
    case BEE_STATE_DANCING: {
        bee_dancing(bee);
        break;
    }
    case BEE_STATE_RETINUE: {
        bee_retinue(bee);
        break;
    }
    case BEE_STATE_NURSING: {
        bee_nursing(bee);
        break;
    }
    }
}
