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
	// dev_handle = libusb_open_device_with_vid_pid(ctx, 0x1b1c, 0x0c09);
	if(dev->handle == NULL) {
		fprintf(stdout, "Cannot open device\n");
	} else {
		fprintf(stdout, "Device Opened\n");
	}

	//r = libusb_detach_kernel_driver(dev_handle, 0);
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
	unsigned char data[64];
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
	
	memset(data, 0, sizeof(data));
	data[0] = 0x03;
	data[1] = 0x81; // CommandID
	data[2] = 0x07; // ReadOneByte
	data[3] = 0x00; // DeviceID
	data[4] = 0x00;

	r = dev->write(dev->handle, dev->write_endpoint, data, 5);
	r = dev->read(dev->handle, dev->read_endpoint, data, 5);
	if (r == 0) {
		fprintf(stdout, "Reading Successful!\n");
		for (i=0;i<8;i++) {
			fprintf(stdout, "%02X ", data[i]);
		}
		fprintf(stdout, "\n");
	} else {
		fprintf(stdout, "Read Error\n");

	}

exit:
	corsairlink_close(dev);
	return 0;
}
