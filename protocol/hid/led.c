/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2014  Sean Nelson <audiohacked@gmail.com>

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lowlevel/hid.h"
#include "../../device.h"
#include "core.h"

int corsairlink_hid_change_led(struct corsair_device_info *dev,
			unsigned char Led_Red, unsigned char Led_Green, unsigned char Led_Blue,
			unsigned char Warning_Red, unsigned char Warning_Green, unsigned char Warning_Blue,
			unsigned char Warning_Temp, unsigned char Warning_Enable)
{
	int r;
	unsigned char response[32];
	unsigned char commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	unsigned int CommandId = 0x81;
	unsigned char i = 1;

	commands[i++] = CommandId++; // Command ID
	commands[i++] = WriteOneByte; // Command Opcode
	commands[i++] = LED_SelectCurrent; // Command data...
	commands[i++] = 1;

	commands[i++] = CommandId++; // Command ID
	commands[i++] = WriteOneByte; // Command Opcode
	commands[i++] = LED_Mode; // Command data...
	commands[i++] = 0x00;

	commands[i++] = CommandId++; // Command ID
	commands[i++] = WriteThreeBytes; // Command Opcode
	commands[i++] = LED_CycleColors; // Command data...
	commands[i++] = 0x0C;

	commands[i++] = Led_Red;
	commands[i++] = Led_Green;
	commands[i++] = Led_Blue;

	commands[i++] = Led_Red;
	commands[i++] = Led_Green;
	commands[i++] = Led_Blue;

	commands[i++] = Led_Red;
	commands[i++] = Led_Green;
	commands[i++] = Led_Blue;

	commands[i++] = Led_Red;
	commands[i++] = Led_Green;
	commands[i++] = Led_Blue;

	commands[0] = i; // Length

	r = dev->write(dev->handle, dev->write_endpoint, commands, 64);
	r = dev->read(dev->handle, dev->read_endpoint, response, 64);

	// fan_rpm = (long int) response[0]*16*16 + response[1];
	// pump_rpm = (response[8]*16*16)+response[9];
	// liquid_temp = (double) response[10] + (double) response[14]/10;

	return r;
}
