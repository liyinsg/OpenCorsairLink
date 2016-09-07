#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>

int main(int argc, char *argv[])
{
	libusb_device_handle *dev_handle;
	libusb_context *ctx = NULL;
	ssize_t cnt;
	unsigned char data[64];
	int i; // looping
	int r; // result from libusb functions
	int actual; //used to find out how many bytes were written
	unsigned int timeout = 5000;

	r = libusb_init(&ctx);
	if (r < 0) {
		fprintf(stdout, "Init Error %d\n", r);
		return 1;
	}
	libusb_set_debug(ctx, 3);

	dev_handle = libusb_open_device_with_vid_pid(ctx, 0x1b1c, 0x0c04);
	//dev_handle = libusb_open_device_with_vid_pid(ctx, 0x1b1c, 0x0c09);
	if(dev_handle == NULL) {
		fprintf(stdout, "Cannot open device\n");
		goto exit;
	} else {
		fprintf(stdout, "Device Opened\n");
	}

	//r = libusb_detach_kernel_driver(dev_handle, 0);
	r = libusb_claim_interface(dev_handle, 0);
	memset(data, 0, sizeof(data));
	data[0] = 0x03;
	data[1] = 0x81; // CommandID
	data[2] = 0x07; // ReadOneByte
	data[3] = 0x00; // DeviceID
	data[4] = 0x00;

	r = libusb_control_transfer(dev_handle, REQUEST_TYPE, REQUEST, VALUE, INDEX, data, 5000);
	//r = libusb_interrupt_transfer(dev_handle, (0x01 | LIBUSB_ENDPOINT_OUT), data, 4, &actual, 5000);
	//r = libusb_bulk_transfer(dev_handle, (0x02 | LIBUSB_ENDPOINT_OUT), data, 4, &actual, 5000);
	if (r == 0 && actual == 4) {
		fprintf(stdout, "Writing Successful!\n");
	} else {
		fprintf(stdout, "Write Error\n");
		goto exit;
	}

	//r = libusb_interrupt_transfer(dev_handle, (0x01 | LIBUSB_ENDPOINT_IN), data, 4, &actual, 5000);
	r = libusb_bulk_transfer(dev_handle, (0x02 | LIBUSB_ENDPOINT_IN), data, 64, &actual, 5000);
	if (r == 0 && actual > 1) {
		fprintf(stdout, "Reading Successful!\n");
		for (i=0;i<actual;i++) {
			fprintf(stdout, "%02X ", data[i]);
		}
		fprintf(stdout, "\n");
	} else {
		fprintf(stdout, "Read Error\n");
		goto exit;
	}

exit:
	r = libusb_release_interface(dev_handle, 0);
	libusb_close(dev_handle);
	libusb_exit(ctx);

	return 0;
}
