#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel/asetek4.h"
#include "device.h"

int corsairlink_asetek_change_led(struct corsair_device_info *dev,
			unsigned char Led_Red, unsigned char Led_Green, unsigned char Led_Blue,
			unsigned char Warning_Red, unsigned char Warning_Green, unsigned char Warning_Blue,
			unsigned char Warning_Temp, unsigned char Warning_Enable)
{
	int r;
	unsigned char response[32];
	unsigned char commands[32] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x10;
	commands[1] = Led_Red;
	commands[2] = Led_Green;
	commands[3] = Led_Blue;
	commands[4] = 0x00;
	commands[5] = 0xff;
	commands[6] = 0xff;
	commands[7] = Warning_Red;
	commands[8] = Warning_Green;
	commands[9] = Warning_Blue;
	commands[10] = Warning_Temp; // 0x37 = ??, 0x2d = ??
	commands[11] = 0x0a;
	commands[12] = 0x05;
	commands[13] = 0x01;
	commands[14] = 0x00;
	commands[15] = 0x00;
	commands[16] = Warning_Enable;
	commands[17] = 0x00;
	commands[19] = 0x01;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 19);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}
