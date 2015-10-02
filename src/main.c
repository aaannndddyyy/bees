/*
    bees - a bee simulation
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

void show_help()
{
    printf("bees: A bee simulation\n\n");
    printf(" -t  --tests                 Run unit tests\n");
    printf(" -h  --help                  Show help\n");
    printf(" -v  --version               Show version number\n");
}

int main(int argc, char* argv[])
{
	int i;

    /* if no options given then show help */
    if (argc <= 1) {
        show_help();
        return 1;
    }

    /* parse the options */
    for (i = 1; i < argc; i++) {
        /* unit tests */
        if ((strcmp(argv[i],"-t")==0) ||
                (strcmp(argv[i],"--tests")==0)) {
            run_tests();
            return 0;
        }
        /* show help */
        if ((strcmp(argv[i],"-h")==0) ||
                (strcmp(argv[i],"--help")==0)) {
            show_help();
            return 0;
        }
        /* show version number */
        if ((strcmp(argv[i],"-v")==0) ||
            (strcmp(argv[i],"--version")==0)) {
            printf("Version %.2f\n",VERSION);
            return 0;
        }
    }

    return 0;
}
