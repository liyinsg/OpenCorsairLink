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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>

#include "../../lowlevel/hid.h"
#include "../../device.h"

unsigned char CommandId = 0x81;

// int GetDeviceId(void)
// {
// 	memset(buf,0,sizeof(buf));
//
// 	// Read Device ID: 0x3b = H80i. 0x3c = H100i. 0x41 = H110i
// 	buf[0] = 0x03; // Length
// 	buf[1] = this->CommandId++; // Command ID
// 	buf[2] = ReadOneByte; // Command Opcode
// 	buf[3] = DeviceID; // Command data...
// 	buf[4] = 0x00;
//
// 	int res = hid_write(handle, buf, 17);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	hid_read_wrapper(handle, buf);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	return buf[2];
// }
//
// int GetFirmwareVersion()
// {
// 	memset(buf,0,sizeof(buf));
//
// 	// Read Device ID: 0x3b = H80i. 0x3c = H100i. 0x41 = H110i
// 	buf[0] = 0x03; // Length
// 	buf[1] = this->CommandId++; // Command ID
// 	buf[2] = ReadTwoBytes; // Command Opcode
// 	buf[3] = FirmwareID; // Command data...
// 	buf[4] = 0x00;
//
// 	int res = hid_write(handle, buf, 17);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	hid_read_wrapper(handle, buf);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(handle) );
// 	}
// 	int firmware = buf[3]<<8;
// 	firmware += buf[2];
// 	return firmware;
// }
//
// int GetProductName(char *ostring)
// {
// 	memset(buf,0,sizeof(buf));
//
// 	// Read Device ID: 0x3b = H80i. 0x3c = H100i. 0x41 = H110i
// 	buf[0] = 0x04; // Length
// 	buf[1] = this->CommandId++; // Command ID
// 	buf[2] = ReadThreeBytes; // Command Opcode
// 	buf[3] = ProductName; // Command data...
// 	buf[4] = 0x08;
//
// 	int res = hid_write(handle, buf, 8);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	hid_read_wrapper(handle, buf);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(handle) );
// 	}
// 	memcpy(ostring, buf + 3, 8);
// 	return 0;
// }
//
// int GetDeviceStatus()
// {
// 	memset(buf,0,sizeof(buf));
//
// 	buf[0] = 0x03; // Length
// 	buf[1] = this->CommandId++; // Command ID
// 	buf[2] = ReadOneByte; // Command Opcode
// 	buf[3] = Status; // Command data...
// 	buf[4] = 0x00;
//
// 	int res = hid_write(handle, buf, 17);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	hid_read_wrapper(handle, buf);
// 	if (res < 0) {
// 		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(handle) );
// 	}
//
// 	return buf[2];
// }
