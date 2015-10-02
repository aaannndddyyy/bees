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

/* given an existing behavior state and a situation
   move to a new behavior state */
void brain_rule(unsigned int caste,
                unsigned int current_state,
                unsigned int current_location,
                double smell_pheromone[],
                double vision[],
                double physics[],
                double payload[],
                unsigned char condition,
                unsigned int new_state,
                agent_bee_brain * brain)
{
    unsigned int i, index =
        (caste*BRAIN_DIMENSION1) +
        (current_state*BRAIN_DIMENSION2) +
        (new_state*BRAIN_DIMENSION3) +
        (current_location*BRAIN_DIMENSION4);

    for (i = 0; i < PHEROMONES; i++) {
        brain->matrix[index++] = (unsigned char)(smell_pheromone[i]*255);
        brain->matrix[index++] = condition;
    }
    for (i = 0; i < BRAIN_DIMENSION_VISION; i++) {
        brain->matrix[index++] = (unsigned char)(vision[i]*255);
        brain->matrix[index++] = condition;
    }
    brain->matrix[index++] =
        (unsigned char)((physics[PHYSICS_TEMPERATURE] - MIN_TEMPERATURE)/
                        (MAX_TEMPERATURE-MIN_TEMPERATURE));
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)((physics[PHYSICS_HUMIDITY] - MIN_HUMIDITY)/
                        (MAX_HUMIDITY-MIN_HUMIDITY));
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)((physics[PHYSICS_PRESSURE] - MIN_PRESSURE)/
                        (MAX_PRESSURE-MIN_PRESSURE));
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)((physics[PHYSICS_VIBRATION] - MIN_VIBRATION)/
                        (MAX_VIBRATION-MIN_VIBRATION));
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)(physics[PHYSICS_TIME_OF_DAY]/24.0);
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)(physics[PHYSICS_TIME_OF_YEAR]/365.0);
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)(physics[PHYSICS_AGE_DAYS]/365.0);
    brain->matrix[index++] = condition;

    brain->matrix[index++] =
        (unsigned char)(physics[PHYSICS_ENERGY]*255.0);
    brain->matrix[index++] = condition;

    for (i = 0; i < PAYLOADS; i++) {
        brain->matrix[index++] = (unsigned char)(payload[i]*255.0);
        brain->matrix[index++] = condition;
    }
}

/* apply a condition to a pair of values */
unsigned int brain_condition(unsigned char value,
                             unsigned char value_compare,
                             unsigned char condition)
{
    switch(condition)
    {
    case CONDITION_GREATER: {
        if (value > value_compare) return value - value_compare;
        break;
    }
    case CONDITION_LESS: {
        if (value < value_compare) return value_compare - value;
        break;
    }
    case CONDITION_EQUAL: {
        if (value == value_compare) return (unsigned int)1;
        break;
    }
    }

    return (unsigned int)0;
}

unsigned int brain_cycle(agent_bee * bee)
{
    unsigned int new_state, index, i, score, max_score=0;
    unsigned int next_state = bee->state;

    for (new_state = 0; new_state < BEE_STATES; new_state++) {
        index =
            (bee->caste*BRAIN_DIMENSION1) +
            (bee->state*BRAIN_DIMENSION2) +
            (new_state*BRAIN_DIMENSION3) +
            (bee->location*BRAIN_DIMENSION4);

        score = 0;
        for (i = 0; i < PHEROMONES; i++, index += 2) {
            score += brain_condition((unsigned char)(bee->smell[i]*255),
                                     bee->brain.matrix[index],
                                     bee->brain.matrix[index+1]);
        }
        for (i = 0; i < BRAIN_DIMENSION_VISION; i++, index += 2) {
            score += brain_condition((unsigned char)(bee->vision[i]*255),
                                     bee->brain.matrix[index],
                                     bee->brain.matrix[index+1]);
        }

        score += brain_condition((unsigned char)((bee->physics[PHYSICS_TEMPERATURE] -
                                                  MIN_TEMPERATURE)/
                                                 (MAX_TEMPERATURE-MIN_TEMPERATURE)),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)((bee->physics[PHYSICS_HUMIDITY] -
                                                  MIN_HUMIDITY)/
                                                 (MAX_HUMIDITY-MIN_HUMIDITY)),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)((bee->physics[PHYSICS_PRESSURE] -
                                                  MIN_PRESSURE)/
                                                 (MAX_PRESSURE-MIN_PRESSURE)),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)((bee->physics[PHYSICS_VIBRATION] -
                                                  MIN_VIBRATION)/
                                                 (MAX_VIBRATION-MIN_VIBRATION)),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)(bee->physics[PHYSICS_TIME_OF_DAY]/24.0),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)(bee->physics[PHYSICS_TIME_OF_YEAR]/365.0),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)(bee->physics[PHYSICS_AGE_DAYS]/365.0),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        score += brain_condition((unsigned char)(bee->physics[PHYSICS_ENERGY]*255.0),
                                 bee->brain.matrix[index],
                                 bee->brain.matrix[index+1]);
        index += 2;

        for (i = 0; i < PAYLOADS; i++) {
            score += brain_condition((unsigned char)(bee->payload[i]*255),
                                     bee->brain.matrix[index],
                                     bee->brain.matrix[index+1]);
        }

        if (score > max_score) {
            next_state = new_state;
            max_score = score;
        }
    }
    if (bee->state != next_state) {
        bee->state = next_state;
        return 1;
    }
    return 0;
}

void brain_init(agent_bee_brain * brain)
{
	memset((void*)brain->matrix,'\0',BRAIN_DIMENSION*sizeof(unsigned char));
}
