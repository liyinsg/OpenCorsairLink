#include <libusb.h>
#include "lowlevel/asetek4.h"
#include "lowlevel/hid.h"
#include "device.h"

struct corsair_device_info corsairlink_devices[] = {
	{
		.vendor_id = 0x1b1c,
		.product_id = 0x0c04,
		.device_id = 0x3c, /** H100i */
		.name = "H100i",
		.read_endpoint = 0x01|LIBUSB_ENDPOINT_IN,
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

