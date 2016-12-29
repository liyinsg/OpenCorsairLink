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

#include "Proto.h"
#include "Link.h"
#include "Temperature.h"

extern CorsairLink *cl;

int CorsairTemp::SelectSensor(int index)
{
	memset(commands,0x00,sizeof(commands));

	commands[0] = 0x04; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = WriteOneByte; // Command Opcode
	commands[3] = TEMP_SelectActiveSensor; // Command data...
	commands[4] = index;

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return commands[2];
}

int CorsairTemp::CurrentSensor()
{
	memset(commands,0x00,sizeof(commands));

	commands[0] = 0x03; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = ReadOneByte; // Command Opcode
	commands[3] = TEMP_SelectActiveSensor; // Command data...

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return commands[2];
}

int CorsairTemp::GetTempSensors()
{//1
	memset(commands,0x00,sizeof(commands));
	// Read fan Mode
	commands[0] = 0x03; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = ReadOneByte; // Command Opcode
	commands[3] = TEMP_CountSensors; // Command data...

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	return commands[2];
}

int CorsairTemp::GetTemp()
{//2
	memset(commands,0x00,sizeof(commands));
	// Read fan Mode
	commands[0] = 0x03; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = ReadTwoBytes; // Command Opcode
	commands[3] = TEMP_Read; // Command data...

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}
	int temp = commands[3]<<8;
	temp += commands[2];
	return temp;
}

int CorsairTemp::GetTempLimit()
{//2
	memset(commands,0x00,sizeof(commands));
	// Read fan Mode
	commands[0] = 0x03; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = ReadTwoBytes; // Command Opcode
	commands[3] = TEMP_Limit; // Command data...

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		//return -1;
	}

	int limit = commands[5]<<8;
	limit += commands[4];

	return limit;
}

int CorsairTemp::SetTempLimit(int limit)
{//2
	memset(commands,0x00,sizeof(commands));
	// Read fan Mode
	commands[0] = 0x05; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = WriteTwoBytes; // Command Opcode
	commands[3] = TEMP_Limit; // Command data...
	commands[4] = limit & 0x00FF;
	commands[5] = limit >> 8;

	int res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		return -1;
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		return -1;
	}

	return 0;
}
