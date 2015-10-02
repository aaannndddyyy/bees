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

/* removes a bee from a frame */
void frame_remove(agent_bee * bee, agent_hive * hive, unsigned int frame)
{
    agent_hive_frame * f = &hive->frame[frame];
    unsigned int min=0, curr=0, i;
    unsigned int max=f->bees;

    if (bee->frame != frame) return;

    while (max > min) {
        curr = min + ((max-min)/2);
        if (f->bee_ID[curr] > bee->ID) {
            max = curr;
        }
        else {
            min = curr;
        }
    }
    for (i = curr; i < f->bees; i--) {
        f->bee_ID[i] = f->bee_ID[i+1];
    }
    f->bees--;
}

/* adds a bee to a frame */
void frame_add(agent_bee * bee, agent_hive * hive, unsigned int frame)
{
    agent_hive_frame * f = &hive->frame[frame];
    unsigned int min=0, curr=0, i;
    unsigned int max=f->bees;

    if (bee->frame == frame) return;

    while (max > min) {
        curr = min + ((max-min)/2);
        if (f->bee_ID[curr] > bee->ID) {
            max = curr;
        }
        else {
            min = curr;
        }
    }
    frame_remove(bee, hive, bee->frame);
    bee->frame = frame;
    if (f->bee_ID[curr] == bee->ID) return;
    for (i = f->bees; i > curr; i--) {
        f->bee_ID[i+1] = f->bee_ID[i];
    }
    f->bee_ID[curr] = bee->ID;
    f->bees++;
    bee->pose.hive.heading=fmod(bee->pose.hive.heading+PI,PI);
}

/* distance between a bee and its target on a frame */
double frame_dist_to_target(agent_bee * bee)
{
    double dx = bee->target.hive.posn[POSITION_X] - bee->pose.hive.posn[POSITION_X];
    double dy = bee->target.hive.posn[POSITION_Y] - bee->pose.hive.posn[POSITION_Y];
    return sqrt(dx*dx + dy*dy);
}

/* is the given point inside a bee? */
unsigned int frame_point_inside_bee(double x, double y, agent_bee * bee)
{
    double cosa=cos(bee->pose.hive.heading);
    double sina=sin(bee->pose.hive.heading);
    double dd=bee->minor_axis/2*bee->minor_axis/2;
    double DD=bee->major_axis/2*bee->major_axis/2;

    double a = pow(cosa*(x - bee->pose.hive.posn[POSITION_X]) +
                   sina*(y - bee->pose.hive.posn[POSITION_Y]),2);
    double b = pow(sina*(x - bee->pose.hive.posn[POSITION_X]) -
                   cosa*(y - bee->pose.hive.posn[POSITION_Y]),2);
    double ellipse = (a/dd)+(b/DD);

    if (ellipse <= 1) return 1;
    return 0;
}

/* detect a collision with a given angular offset */
unsigned int frame_detect_collision(agent_bee * bee, agent_hive * hive, double heading_offset)
{
    double cx = bee->pose.hive.posn[POSITION_X];
    double cy = bee->pose.hive.posn[POSITION_Y];
    double radius = bee->major_axis * 0.5;
    double x = cx + (radius*sin(bee->pose.hive.heading + heading_offset));
    double y = cy + (radius*cos(bee->pose.hive.heading + heading_offset));
    unsigned int i;
    agent_hive_frame * f = &hive->frame[bee->frame];
    agent_bee * other_bee;

    if ((x < 0) || (y < 0) ||
        (x > hive->frame_size[POSITION_X]) ||
        (y > hive->frame_size[POSITION_Y])) return 1;

    for (i = 0; i < f->bees; i++) {
        if (f->bee_ID[i] == bee->ID) continue;
        other_bee = &hive->bee[f->bee_ID[i]];
        if (frame_point_inside_bee(x,y,other_bee) != 0) return 1;
    }
    return 0;
}

/* update the movement of a bee */
unsigned int frame_move(agent_bee * bee, agent_hive * hive)
{
    double dist = frame_dist_to_target(bee);
    if (dist < CELL_DIAMETER_MM*0.25) return 0;
    bee->pose.hive.vel = VEL_WALK_MM;
    if (frame_detect_collision(bee, hive, 0) != 0) {
        if (frame_detect_collision(bee, hive, -PI*0.2) != 0) {
            if (frame_detect_collision(bee, hive, PI*0.2) != 0) {
                bee->pose.hive.vel = -VEL_WALK_MM*0.2;
            }
            else {
                bee->pose.hive.vel = 0;
                bee->pose.hive.heading =
                    fmod(bee->pose.hive.heading + HEADING_CHANGE_PER_STEP, 2*PI);
            }
        }
        else {
            bee->pose.hive.vel = 0;
            bee->pose.hive.heading =
                fmod(bee->pose.hive.heading - HEADING_CHANGE_PER_STEP, 2*PI);
        }
    }
    bee->pose.hive.posn[POSITION_X] +=
        bee->pose.hive.vel*sin(bee->pose.hive.heading);
    bee->pose.hive.posn[POSITION_Y] +=
        bee->pose.hive.vel*cos(bee->pose.hive.heading);
    return 1;
}

/* navigate within the frames of a hive */
void frame_navigate(agent_bee * bee, agent_hive * hive)
{
    if (bee->frame_target != bee->frame) {
        /* move to the top of the frame */
        bee->target.hive.posn[POSITION_X] =
            bee->pose.hive.posn[POSITION_X];
        bee->target.hive.posn[POSITION_Y] = 0;
        if (frame_move(bee, hive) == 0) {
            frame_add(bee, hive, bee->frame_target);
        }
        return;
    }

    frame_move(bee, hive);
}
