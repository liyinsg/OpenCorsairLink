int corsairlink_hid_write(struct libusb_device_handle *dev_handle,
 			unsigned char endpoint,
			unsigned char *data,
			int length);

int corsairlink_hid_read(struct libusb_device_handle *dev_handle,
			unsigned char endpoint,
			unsigned char *data,
			int length);
