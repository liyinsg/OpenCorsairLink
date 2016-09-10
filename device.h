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
} corsairlink_devices[] = {
	{
		.vendor_id = 0x1b1c,
		.product_id = 0x0c04,
		.device_id = 0x3c, /** H100i */
		.name = "H100i",
		.read_endpoint = 0x01,
		.write_endpoint = LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
		.handle = NULL,
		.context = NULL,
		.init = corsairlink_hid_init,
		.deinit = corsairlink_hid_deinit,
		.read = corsairlink_hid_read,
		.write = corsairlink_hid_write,
	},
	{
		.vendor_id = 0x1b1c,
		.product_id = 0x0c09,
		.device_id = 0x00,
		.name = "H100i V2",
		.read_endpoint = 0x02|LIBUSB_ENDPOINT_IN,
		.write_endpoint = 0x02|LIBUSB_ENDPOINT_OUT,
		.handle = NULL,
		.context = NULL,
		.init = corsairlink_asetek_init,
		.deinit = corsairlink_asetek_deinit,
		.read = corsairlink_asetek_read,
		.write = corsairlink_asetek_write,
	}
};
