struct corsair_device_info {
	/** device info */
	unsigned short vendor_id;
	unsigned short product_id;
	unsigned short device_id;
	char *name[16];
	/** device endpoints */
	unsigned char read_endpoint;
	unsigned char write_endpoint;

	/** libusb device structures */
	struct libusb_device_handle *handle;
	libusb_context *context;
	int interface;

	/** device communication helper functions */
	// int (*read)(struct libusb_device_handle *dev_handle,
	// 	unsigned char endpoint,
	// 	unsigned char *data,
	// 	int length,
	// 	//int* transferred,
	// 	//unsigned int timeout
	// )
	int (*read)();
	int (*write)();
	// int (*write)(struct libusb_device_handle *dev_handle,
	// 	unsigned char endpoint,
	// 	unsigned char *data,
	// 	int length,
	// 	//int* transferred,
	// 	//unsigned int timeout
	// )
} corsairlink_devices[] = {
	{
		.vendor_id = 0x1b1c,
		.product_id = 0x0c04,
		.device_id = 0x3c, /** H100i */
		.name = "H100i",
		.read_endpoint = 0x01,
		.write_endpoint = LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
		.read = corsairlink_hid_read,
		.write = corsairlink_hid_write,
	},
	{}
};
