#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel/asetek4.h"
#include "device.h"

int corsairlink_asetek_fan_curve(struct corsair_device_info *dev,
			unsigned char temp1, unsigned char temp2, unsigned char temp3,
			unsigned char temp4, unsigned char temp5, unsigned char temp6,
			unsigned char speed1, unsigned char speed2, unsigned char speed3,
			unsigned char speed4, unsigned char speed5, unsigned char speed6)
{
	int r;
	unsigned char response[32];
	unsigned char commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x11;
	commands[1] = 0x00;
	
	commands[2] = temp1;
	commands[3] = temp2;
	commands[4] = temp3;
	commands[5] = temp4;
	commands[6] = temp5;
	commands[7] = temp6;

	commands[8] = speed1;
	commands[9] = speed2;
	commands[10] = speed3;
	commands[11] = speed4;
	commands[12] = speed5;
	commands[13] = speed6;
	
	r = dev->write(dev->handle, dev->write_endpoint, commands, 14);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}
