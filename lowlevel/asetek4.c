#include <stdio.h>
#include <libusb.h>
#include "lowlevel/asetek4.h"

#define HID_SET_REPORT 0x09
#define HID_GET_REPORT 0x01
#define HID_REPORT_TYPE_INPUT 0x01
#define HID_REPORT_TYPE_OUTPUT 0x02
#define HID_REPORT_TYPE_FEATURE 0x03
#define TIMEOUT_DEFAULT 1000
#define INTERFACE_NUMBER 0

int corsairlink_asetek_init(struct libusb_device_handle *dev_handle,
			unsigned char endpoint)
{
	int r;
	r = libusb_control_transfer(dev_handle, 0x40, 0x00, 0xffff, 0x0000, "", 0, 0);
	r = libusb_control_transfer(dev_handle, 0x40, 0x02, 0x0002, 0x0000, "", 0, 0);
	return r;
}

int corsairlink_asetek_deinit(struct libusb_device_handle *dev_handle,
			unsigned char endpoint)
{
	int r;
	r = libusb_control_transfer(dev_handle, 0x40, 0x02, 0x0004, 0x0000, "", 0, 200);
	return r;
}

int corsairlink_asetek_write(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_bulk_transfer(dev_handle, 0x02, data, length, &bytes_transferred, TIMEOUT_DEFAULT);
	//if (r == 0 && bytes_transferred == length) {
	//	fprintf(stdout, "Writing Successful!\n");
	//} else {
	//	fprintf(stdout, "Write Error\n");
	//}
	return r;
}

int corsairlink_asetek_read(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_bulk_transfer(dev_handle, 0x82, data, length, &bytes_transferred, TIMEOUT_DEFAULT);
	//if (r == 0 && bytes_transferred > 1) {
	//	fprintf(stdout, "Reading Successful!\n");
	//} else {
	//	fprintf(stdout, "Read Error\n");
	//}
	return r;
}
