#ifndef __DEVICE_H
#define __DEVICE_H

struct corsair_device_info {
	/** device info */
	unsigned short vendor_id;
	unsigned short product_id;
	unsigned short device_id;
	char name[16];
	/** device endpoints */
	unsigned char read_endpoint;
	unsigned char write_endpoint;

	/** libusb device structures */
	struct libusb_device_handle *handle;
	libusb_context *context;
	int interface;

	/** device communication helper functions */
	int (*init)(struct libusb_device_handle*, unsigned char);
	int (*deinit)(struct libusb_device_handle*, unsigned char);
	int (*read)(struct libusb_device_handle*, unsigned char, unsigned char*, int);
	int (*write)(struct libusb_device_handle*, unsigned char, unsigned char*, int);
};
#endif

