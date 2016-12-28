#include <stdio.h>
#include <libusb.h>
#include "../lowlevel/hid.h"

#define HID_SET_REPORT 0x09
#define HID_GET_REPORT 0x01
#define HID_REPORT_TYPE_INPUT 0x01
#define HID_REPORT_TYPE_OUTPUT 0x02
#define HID_REPORT_TYPE_FEATURE 0x03
#define TIMEOUT_DEFAULT 1000
#define INTERFACE_NUMBER 0
#define INTERRUPT_IN_ENDPOINT 0x81

// Values for bmRequestType in the Setup transaction's Data packet.

static const int CONTROL_REQUEST_TYPE_IN = LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE;
static const int CONTROL_REQUEST_TYPE_OUT = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE;

int corsairlink_hid_init(struct libusb_device_handle *dev_handle,
			unsigned char endpoint)
{
	return 0;
}

int corsairlink_hid_deinit(struct libusb_device_handle *dev_handle,
			unsigned char endpoint)
{
	return 0;
}

int corsairlink_hid_write(struct libusb_device_handle *dev_handle,
 			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_control_transfer(dev_handle,
 				CONTROL_REQUEST_TYPE_OUT,
				HID_SET_REPORT, /** HID Set_Report */
				(HID_REPORT_TYPE_OUTPUT<<8)|0x00,
				INTERFACE_NUMBER,
				data, length, TIMEOUT_DEFAULT);
	return r;
}

int corsairlink_hid_read(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_interrupt_transfer(dev_handle,
				INTERRUPT_IN_ENDPOINT,
				data, length,
				&bytes_transferred, TIMEOUT_DEFAULT);
	return r;
}
