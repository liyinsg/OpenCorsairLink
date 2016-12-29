#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel/asetek4.h"
#include "lowlevel/hid.h"
#include "device.h"

extern struct corsair_device_info corsairlink_devices[2];

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
		return -1;
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
	int r; // result from libusb functions
	int i; // for loops
	
	for (i=0; i<2; i++) {
		dev = &corsairlink_devices[i];
		r = corsairlink_find_device(dev);
		if (r >= 0) {
			fprintf(stdout, "CorsairLink Device Found: %s!\n", dev->name);
			break;
		}
	}

	r = dev->init(dev->handle, dev->write_endpoint);
	// r = corsairlink_asetek_fan_curve(dev, 20, 25, 29, 33, 37, 40, 30, 40, 50, 60, 70, 80);
	r = corsairlink_led_change_led(dev, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 60, 1);
	r = dev->deinit(dev->handle, dev->write_endpoint);

exit:
	corsairlink_close(dev);
	return 0;
}
