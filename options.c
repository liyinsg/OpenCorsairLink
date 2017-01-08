/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2017  Sean Nelson <audiohacked@gmail.com>

 * OpenCorsairLink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.

 * OpenCorsairLink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OpenCorsairLink.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "options.h"

static struct option long_options[] = {
	{"help",       no_argument,          0,  0},
	{"version",    no_argument,          0,  1},

	{"device",     optional_argument,    0,  2},
	{"firmware",   no_argument,          0,  3},

	{"print",      no_argument,          0,  4},

	{"led",        required_argument,    0,  5},
	{"led-warn",   required_argument, NULL,  6},
	{"led-temp",   required_argument, NULL,  7},

	{"fan-speeds", required_argument, NULL,  8},
	{"fan-temps",  required_argument, NULL,  9},

	{"pump",       required_argument, NULL,  10},

	{0, 0, 0, 0}
};

void options_print(void);

int options_parse(int argc, char **argv, struct option_flags *flags, 
	struct color *led, struct color *warning, int8_t *warning_temp,
	struct fan_table *fan, struct fan_table *pump, uint8_t *pump_mode)
{
	int c, returnCode = 0;

	// INIT_OPTIONS(&ropt);
	// INIT_FAN_TABLE(ropt.fan);
	// INIT_FAN_TABLE(ropt.pump);

	while (1) {
		int option_index = 0;

		c = getopt_long (argc, argv, "", long_options, &option_index);

		if (c == -1 || returnCode != 0)
			break;

		switch (c) {
		case 0:
			options_print();
			break;
		case 1: /* program version */
			fprintf(stdout, "OpenCorsairLink Version: %s", VERSION);
			break;

		case 2:
			// sscanf(optarg, "%u", device_number);
			break;
		
		case 3:
			flags->device_firmware = 1;
			break;

		case 4:
			flags->read_temperature = 1;
			break;

		case 5: /* led color */
			sscanf(optarg, "%02hhX%02hhX%02hhX", &led->red, &led->green, &led->blue);
			break;
		case 6: /* led warning color */
			sscanf(optarg, "%02hhX%02hhX%02hhX", &warning->red, &warning->green, &warning->blue);
			break;
		case 7: /* led warning temperature */
			sscanf(optarg, "%hhd", warning_temp);
			break;

		case 8:
			sscanf(optarg, "%hhd,%hhd,%hhd,%hhd,%hhd",
				&fan->s1,
				&fan->s2,
				&fan->s3,
				&fan->s4,
				&fan->s5);
			break;
		case 9:
			sscanf(optarg, "%hhd,%hhd,%hhd,%hhd,%hhd",
				&fan->t1,
				&fan->t2,
				&fan->t3,
				&fan->t4,
				&fan->t5);
			break;
		case 10:
			sscanf(optarg, "%hhd", pump_mode);
			break;

		default:
			exit(1);
			returnCode = 0;
		}
	}
	return returnCode;
}

void options_print() {
	fprintf(stdout, "OpenCorsairLink [options]\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "\t-h, --help :Prints this Message\n");
	fprintf(stdout, "\t-i, --info :Displays information about the Fans, Pumps, or LEDs.\n");
	fprintf(stdout, "\t-p, --print :Displays all information about the Fans, Pumps, and LEDs.\n");

	fprintf(stdout, "\t-l, --led <led number> :Selects a LED to setup. LEDs are numbered 1 & up.\n");
	fprintf(stdout, "\t\t--led-mode <led mode> :Sets LED Mode (in HH format).\n");
	fprintf(stdout, "\t\t\tModes:\n");
	fprintf(stdout, "\t\t\t\t 0x00 - Static Color\n");
	fprintf(stdout, "\t\t\t\t 0x40 - 2-Color Cycle (requries to specify RGB1 & RGB2)\n");
	fprintf(stdout, "\t\t\t\t 0x80 - 4-Color Cycle (requires to specify RGB1, RGB2, RGB3, & RGB4)\n");
	fprintf(stdout, "\t\t\t\t 0xC0 - Temperature Mode (requires to specify RGB1, RGB2, & RGB3)\n");
	fprintf(stdout, "\t\t\t\t\tLow Nibble controls Cycle Speed or Temperature Channel\n");
	fprintf(stdout, "\t\t\t\t\t(0 = internal sensor; 7 = manual)\n");
	fprintf(stdout, "\t\t--rgb1 <HTML Color Code> :Define Color for LEDs\n");
	fprintf(stdout, "\t\t--rgb2 <HTML Color Code> :Define Color for LEDs\n");
	fprintf(stdout, "\t\t--rgb3 <HTML Color Code> :Define Color for LEDs\n");
	fprintf(stdout, "\t\t--rgb4 <HTML Color Code> :Define Color for LEDs\n");

	fprintf(stdout, "\t-t, --temperature <sensor number> :Selects a Temperature Sensor.\n");
	fprintf(stdout, "\t\t--temperature-limit <temp limit> :Sets Max Temperature (high temp warning).\n");

	fprintf(stdout, "\t-f, --fan <fan number>{:<fan number>} :Selects a fan to setup. Accepted values are 1, 2, 3 or 4.\n");
	fprintf(stdout, "\t\t--fan-mode <fan mode> :Sets the mode for the selected fan\n");
	fprintf(stdout, "\t\t\tModes:\n");
	fprintf(stdout, "\t\t\t\t 2 - Fixed PWM (requires to sepcify the PWM)\n");
	fprintf(stdout, "\t\t\t\t 4 - Fixed RPM (requires to specify the RPM)\n");
	fprintf(stdout, "\t\t\t\t 6 - Default\n");
	fprintf(stdout, "\t\t\t\t 8 - Quiet\n");
	fprintf(stdout, "\t\t\t\t10 - Balanced\n");
	fprintf(stdout, "\t\t\t\t12 - Performance\n");
	fprintf(stdout, "\t\t--fan-pwm <fan PWM> :The desired PWM speed for the selected fan. NOTE: it only works when fan mode is set to Fixed PWM\n");
	fprintf(stdout, "\t\t--fan-rpm <fan RPM> :The desired RPM for the selected fan. NOTE: it works only when fan mode is set to Fixed RPM\n");
	fprintf(stdout, "\t\t--fan-warning <fan threshold> :Sets the Fan Warning Limit (Sets Underspeed Threshold).\n");
}
