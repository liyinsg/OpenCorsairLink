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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "../../lowlevel/asetek4.h"
#include "../../device.h"

int corsairlink_asetek_device_id(struct corsair_device_info *dev)
{
	return 0x00;
}

int corsairlink_asetek_22000000(struct corsair_device_info *dev)
{
	int r;
	uint8_t response[32];
	uint8_t commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x22;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_14000000(struct corsair_device_info *dev)
{
	int r;
	uint8_t response[32];
	uint8_t commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x14;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_20(struct corsair_device_info *dev)
{
	int r;
	uint8_t response[32];
	uint8_t commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x20;

	r = dev->driver->write(dev->handle, dev->write_endpoint, commands, 1);
	r = dev->driver->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_continue_transaction(struct corsair_device_info *dev)
{
	int r;
	int bytes_transferred;

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_OUT,
				0x02, 0x0001, 0x0000, NULL, 0, 0);

	return r;
}

int corsairlink_asetek_start_transaction(struct corsair_device_info *dev)
{
	int r;
	int bytes_transferred;

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_IN,
				255, 0x370B, 0x0000, NULL, 1, 0);

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_OUT,
				0x00, 0x0000, 0x0000, NULL, 0, 0);

	return r;
}
