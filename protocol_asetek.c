#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include "lowlevel.h"
#include "device.h"

int corsairlink_asetek_change_led(struct corsair_device_info *dev,
			uint8_t Led_Red, uint8_t Led_Green, uint8_t Led_Blue,
			uint8_t Warning_Red, uint8_t Warning_Green, uint8_t Warning_Blue,
			uint8_t Warning_Temp, uint8_t Warning_Enable)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x10;
	commands[1] = Led_Red;
	commands[2] = Led_Green;
	commands[3] = Led_Blue;
	commands[4] = 0x00;
	commands[5] = 0xff;
	commands[6] = 0xff;
	commands[7] = Warning_Red;
	commands[8] = Warning_Green;
	commands[9] = Warning_Blue;
	commands[10] = Warning_Temp; // 0x37 = ??, 0x2d = ??
	commands[11] = 0x0a;
	commands[12] = 0x05;
	commands[13] = 0x01;
	commands[14] = 0x00;
	commands[15] = 0x00;
	commands[16] = Warning_Enable;
	commands[17] = 0x00;
	commands[19] = 0x01;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 19);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_fan_curve(struct corsair_device_info *dev,
			uint8_t temp1, uint8_t temp2, uint8_t temp3,
			uint8_t temp4, uint8_t temp5, uint8_t temp6
			uint8_t speed1, uint8_t speed2, uint8_t speed3,
			uint8_t speed4, uint8_t speed5, uint8_t speed6)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x11;
	commands[1] = 0x00;
	
	commands[2] = temp1;
	commands[3] = temp2;
	commands[4] = temp3;
	commands[5] = temp4;
	commands[6] = temp5;
	commands[7] = temp6;

	commands[8] = speed1;
	commands[9] = speed2;
	commands[10] = speed3;
	commands[11] = speed4;
	commands[12] = speed5;
	commands[13] = speed6;
	
	r = dev->write(dev->handle, dev->write_endpoint, commands, 14);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_22000000(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x22;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_14000000(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x14;
	commands[1] = 0x00;
	commands[2] = 0x00;
	commands[3] = 0x00;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 4);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_20(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x20;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 1);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_continue_transaction(struct corsair_device_info *dev)
{
	int r;
	int bytes_transferred;

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_OUT,
				0x02, 0x0001, 0x0000, "", 0, 0);

}

int corsairlink_asetek_start_transaction(struct corsair_device_info *dev)
{
	int r;
	int bytes_transferred;

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_IN,
				255, 0x370B, 0x0000, "", 1, 0);

	r = libusb_control_transfer(dev->handle,
				LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_DEVICE|LIBUSB_ENDPOINT_OUT,
				0x00, 0x0000, 0x0000, "", 0, 0);

}

int corsairlink_asetek_pump_mode_performance(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x42;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}

int corsairlink_asetek_pump_mode_quiet(struct corsair_device_info *dev)
{
	int r;
	unsigned char response[64];
	unsigned char commands[64] ;
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));
	commands[0] = 0x13;
	commands[1] = 0x28;

	r = dev->write(dev->handle, dev->write_endpoint, commands, 2);
	r = dev->read(dev->handle, dev->read_endpoint, response, 32);

	return r;
}
