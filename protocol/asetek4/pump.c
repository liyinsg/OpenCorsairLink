#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "../../lowlevel/asetek4.h"
#include "../../device.h"

int corsairlink_asetek_pump_mode_performance(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[32];
	unsigned char commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x42;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_pump_mode_quiet(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[32];
	unsigned char commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x28;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}
