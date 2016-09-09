#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel.h"
#include "device.h"

int corsairlink_find_device(struct corsair_device_info *dev)
{
	int r;
	r = libusb_init(&dev->context);
	if (r < 0) {
		fprintf(stdout, "Init Error %d\n", r);
		return 1;
	}
	libusb_set_debug(dev->context, 3);

	dev->handle = libusb_open_device_with_vid_pid(dev->context, dev->vendor_id, dev->product_id);
	if(dev->handle == NULL) {
		fprintf(stdout, "Cannot open device\n");
	} else {
		fprintf(stdout, "Device Opened\n");
	}

	r = libusb_detach_kernel_driver(dev->handle, 0);
	r = libusb_claim_interface(dev->handle, 0);

	return 0;
}

void corsairlink_close(struct corsair_device_info *dev)
{
	int r;
	r = libusb_release_interface(dev->handle, 0);
	libusb_close(dev->handle);
	libusb_exit(dev->context);
}

int main(int argc, char *argv[])
{
	struct corsair_device_info *dev;
	unsigned char response[64];
	unsigned char commands[64];
	int i; // looping
	int r; // result from libusb functions
	
	for (i=0; i<2; i++) {
		dev = &corsairlink_devices[i];
		r = corsairlink_find_device(dev);
		if (r >= 0) {
			fprintf(stdout, "CorsairLink Device Found: !\n");
			break;
		}
	}
	
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = 0x81; // CommandID
	commands[2] = 0x07; // ReadOneByte
	commands[3] = 0x00; // DeviceID
	commands[4] = 0x00;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 5);
	if (r >= 0) {
		fprintf(stdout, "Writing Successful!\n");
		for (i=0;i<64;i++) {
			fprintf(stdout, "%02X ", commands[i]);
		}
		fprintf(stdout, "\n");
	} else {
		fprintf(stdout, "Writing Error\n");
	}

	r = dev->read(dev->handle, dev->read_endpoint, response, 64);
	if (r == 0) {
		fprintf(stdout, "Reading Successful!\n");
		for (i=0;i<64;i++) {
			fprintf(stdout, "%02X ", response[i]);
		}
		fprintf(stdout, "\n");
	} else {
		fprintf(stdout, "Read Error\n");

	}

exit:
	corsairlink_close(dev);
	return 0;
}
