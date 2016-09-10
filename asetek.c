#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel.h"
#include "device.h"

int corsairlink_asetek_test(struct corsair_device_info *dev)
{
	int r;
	int i;

	unsigned char response[64];
	unsigned char commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x20;
	commands[1] = 0x00; // CommandID
	commands[2] = 0x00; // ReadOneByte
	commands[3] = 0x00; // DeviceID

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 1);
	if (r >= 0) {
		fprintf(stdout, "Writing Successful!\n");
		for (i=0;i<20;i++) {
			fprintf(stdout, "%02X ", commands[i]);
		}
		fprintf(stdout, "\n");
	} else {
		fprintf(stdout, "Writing Error\n");
	}

	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	if (r == 0) {
		fprintf(stdout, "Reading Successful!\n");
		for (i=0;i<32;i++) {
			fprintf(stdout, "%02X ", response[i]);
		}
		fprintf(stdout, "\n");
		fprintf(stdout, "fan rpm = %ld\n", (long int)response[0]*16*16 + response[1]);
		fprintf(stdout, "pump rpm = %ld\n", (long int)response[8]*16*16 + response[9]);
		fprintf(stdout, "liquid temp = %f\n", (double)response[10] + (double) response[14]/10);
	} else {
		fprintf(stdout, "Read Error\n");

	}
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_change_led(struct corsair_device_info *dev, uint8_t RR, uint8_t GG, uint8_t BB)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x10;
	commands[1] = RR;
	commands[2] = GG;
	commands[3] = BB;
	commands[4] = 0x00;
	commands[5] = 0xff;
	commands[6] = 0xff;
	commands[7] = 0xff;
	commands[8] = 0x00;
	commands[9] = 0x00;
	commands[10] = 0x37; // 0x37 = ??, 0x2d = ??
	commands[11] = 0x0a;
	commands[12] = 0x05;
	commands[13] = 0x01;
	commands[14] = 0x00;
	commands[15] = 0x00;
	commands[16] = 0x01;
	commands[17] = 0x00;
	commands[19] = 0x01;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 19);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_22000000(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x22;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_14000000(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x14;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_20(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x20;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 1);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_1342(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x42;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}

int corsairlink_asetek_1328(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x28;

	r = dev->init(dev->handle, dev->write_endpoint);
	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);
	r = dev->deinit(dev->handle, dev->write_endpoint);

	return r;
}
