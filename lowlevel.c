#include <stdio.h>
#include <libusb.h>
#include "lowlevel.h"

#define HID_SET_REPORT 0x09
#define HID_GET_REPORT 0x01
#define HID_REPORT_TYPE_INPUT 0x01
#define HID_REPORT_TYPE_OUTPUT 0x02
#define TIMEOUT_DEFAULT 1000
#define INTERFACE_NUMBER 0

int corsairlink_hid_write(struct libusb_device_handle *dev_handle,
 			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_control_transfer(dev_handle, 				LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
				HID_SET_REPORT, /** HID Set_Report */
				(HID_REPORT_TYPE_OUTPUT<<8)|data[0],
				INTERFACE_NUMBER,
				data, length, TIMEOUT_DEFAULT);
	// r = libusb_interrupt_transfer(dev->device_handle,
	// 		INTERRUPT_OUT_ENDPOINT,
	// 		data, length,
	// 		&bytes_transferred, TIMEOUT_DEFAULT);
	return r;
}

int corsairlink_hid_read(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_control_transfer(dev_handle, 				LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_IN,
				HID_GET_REPORT, /** HID Set_Report */
				(HID_REPORT_TYPE_INPUT<<8)|data[0],
				INTERFACE_NUMBER,
				data, length, TIMEOUT_DEFAULT);
	// r = libusb_interrupt_transfer(dev_handle,
	// 			INTERRUPT_IN_ENDPOINT,
	// 			data, length,
	// 			&bytes_transferred, TIMEOUT_DEFAULT);
	return r;
}

int corsairlink_bulk_write(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_bulk_transfer(dev_handle, endpoint, data, length, &bytes_transferred, 5000);
	if (r == 0 && bytes_transferred == length) {
		fprintf(stdout, "Writing Successful!\n");
	} else {
		fprintf(stdout, "Write Error\n");
	}
	return r;
}

int corsairlink_bulk_read(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length)
{
	int bytes_transferred;
	int r;
	
	r = libusb_bulk_transfer(dev_handle, endpoint, data, length, &bytes_transferred, 5000);
	if (r == 0 && bytes_transferred > 1) {
		fprintf(stdout, "Reading Successful!\n");
	} else {
		fprintf(stdout, "Read Error\n");
	}
	return r;
}
