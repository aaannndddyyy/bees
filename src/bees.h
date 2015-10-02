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

#ifndef BEES_H
#define BEES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define VERSION             1.00

#define MAX_BEES            32000
#define HIVE_FRAMES         10
#define FRAME_CELLS         1000
#define CELL_DIAMETER_MM    10
#define PI                  3.1415927

#define HEADING_CHANGE_PER_STEP (20.0*PI/180.0)
#define VEL_WALK_MM             5

#define MIN_TEMPERATURE    -10
#define MAX_TEMPERATURE     40

#define MIN_HUMIDITY         0
#define MAX_HUMIDITY       100

#define MIN_PRESSURE         0
#define MAX_PRESSURE       100

#define MIN_VIBRATION        0
#define MAX_VIBRATION      100

enum {
    PHYSICS_TEMPERATURE,
    PHYSICS_HUMIDITY,
    PHYSICS_PRESSURE,
    PHYSICS_VIBRATION,
    PHYSICS_TIME_OF_DAY,
    PHYSICS_TIME_OF_YEAR,
    PHYSICS_AGE_DAYS,
    PHYSICS_ENERGY,
    DIMENSION_PHYSICS
};

enum {
    PAYLOAD_POLLEN,
    PAYLOAD_NECTAR,
    PAYLOAD_WATER,
    PAYLOAD_RESIN,
    PAYLOADS
};

enum {
    CASTE_QUEEN,
    CASTE_DRONE,
    CASTE_WORKER,
    CASTES
};

enum {
    BEE_STATE_LAVA,
    BEE_STATE_LAYING,
    BEE_STATE_CAPPING,
    BEE_STATE_CLEANING,
    BEE_STATE_BUILDING,
    BEE_STATE_POLISHING,
    BEE_STATE_UNDERTAKING,
    BEE_STATE_GROOMING,
    BEE_STATE_RETINUE,
    BEE_STATE_NURSING,
    BEE_STATE_MATING,
    BEE_STATE_BALLING,
    BEE_STATE_RESTING,
    BEE_STATE_DANCING,
    BEE_STATE_FANNING,
    BEE_STATE_HEATING,
    BEE_STATE_FORAGE,
    BEE_STATE_GUARD,
    BEE_STATE_ROBBER,
    BEE_STATE_DEAD,
    BEE_STATES
};

enum {
    LOCATION_CELL,
    LOCATION_FRAME,
    LOCATION_HIVE_EXTERIOR,
    LOCATION_ENVIRONMENT,
    LOCATIONS
};

enum {
    PHEROMONE_ALARM,
    PHERONOME_BROOD,
    PHEROMONE_DRONE,
    PHEROMONE_DUFOURS,
    PHEROMONE_EGG_MARKING,
    PHEROMONE_FOOTPRINT,
    PHEROMONE_NASONOV,
    PHEROMONE_QUEEN_MANDIBULAR,
    PHEROMONE_QUEEN_RETINUE,
    PHEROMONES
};

#define BRAIN_DIMENSION_VISION  2
#define BRAIN_DIMENSION4 ((PHEROMONES + BRAIN_DIMENSION_VISION + \
                           DIMENSION_PHYSICS + PAYLOADS)*2)
#define BRAIN_DIMENSION3 (LOCATIONS*(BRAIN_DIMENSION4))
#define BRAIN_DIMENSION2 (BEE_STATES*(BRAIN_DIMENSION3))
#define BRAIN_DIMENSION1 (BEE_STATES*(BRAIN_DIMENSION2))
#define BRAIN_DIMENSION  (CASTES*(BRAIN_DIMENSION1))

enum {
    BODY_ABDOMEN,
    BODY_ANTENNA,
    BODY_EYE,
    BODY_HEAD,
    BODY_LEG,
    BODY_MANDIBLE,
    BODY_PROBOSCIS,
    BODY_POLLEN_BASKET,
    BODY_POLLEN_PRESS,
    BODY_COMBS,
    BODY_STINGER,
    BODY_THORAX,
    BODY_WAX_GLAND,
    BODY_WING,
    BODY_PARTS
};

enum {
    POSITION_X,
    POSITION_Y,
    POSITION_Z
};

typedef struct
{
    double heading;
    double posn[2];
    double vel;
    double accn;
    double alt;
} agent_environment_pose;

typedef struct
{
    int frame;
    double heading;
    double posn[2];
    double vel;
    double accn;
} agent_hive_pose;

typedef struct
{
    agent_environment_pose environment;
    agent_hive_pose hive;
} agent_pose;

enum {
    CONDITION_NONE,
    CONDITION_GREATER,
    CONDITION_LESS,
    CONDITION_EQUAL
};

#define LAND_DIMENSION 1000

typedef struct
{
    unsigned char elevation[LAND_DIMENSION];
    unsigned char flora[LAND_DIMENSION];
    double nectar[LAND_DIMENSION];
    double pollen[LAND_DIMENSION];
    double water[LAND_DIMENSION];
} land;

typedef struct
{
    unsigned char matrix[BRAIN_DIMENSION];
} agent_bee_brain;

typedef struct
{
    /* identity */
    unsigned int ID;
    unsigned int queen_ID;

    /* visual inputs in the range 0.0-1.0 */
    double vision[BRAIN_DIMENSION_VISION];

    /* sensed temperature, humidity, pressure,
       vibration, time days, age, energy */
    double physics[DIMENSION_PHYSICS];

    /* body */
    double length[BODY_PARTS];
    unsigned char color[BODY_PARTS*3];
    double major_axis, minor_axis;

    /* location within a hive */
    unsigned int frame, frame_target;
    unsigned int cell[2], cell_target[2];

    /* environment location */
    agent_pose pose, target;
    /* type of location */
    unsigned char location;

    /* pollen, nectar, water, resin */
    double payload[PAYLOADS];

    /* queen, drone or worker */
    int caste;

    /* current behavior */
    int state;

    /* pheromones smelt and emitted, in the range 0.0-1.0 */
    double smell[PHEROMONES];
    double pheremone[PHEROMONES];

    agent_bee_brain brain;
} agent_bee;

typedef struct
{
    unsigned int bees;
    unsigned int bee_ID[MAX_BEES];
    unsigned char occupancy[FRAME_CELLS];
    int total[3];
} agent_hive_frame;

typedef struct
{
    /* identity */
    unsigned int ID;
    unsigned int queen_ID;

    /* frames within the hive */
    double frame_size[2];
    agent_hive_frame frame[HIVE_FRAMES];

    /* location */
    agent_environment_pose location;

    /* total population */
    int population;

    /* hive physics */
    double physics[DIMENSION_PHYSICS];
    double mass;

    /* individuals */
    agent_bee bee[MAX_BEES];
} agent_hive;

void run_tests();
void frame_navigate(agent_bee * bee, agent_hive * hive);
void brain_init(agent_bee_brain * brain);
void bee_init(unsigned int ID, agent_bee * bee, agent_hive * hive);
void hive_init(agent_hive * hive, unsigned int population,
               double frame_width_mm, double frame_height_mm);
void frame_add(agent_bee * bee, agent_hive * hive, unsigned int frame);
unsigned int brain_cycle(agent_bee * bee);
void hive_cycle(agent_hive * hive);
void bee_cycle(agent_bee * bee);

#endif
