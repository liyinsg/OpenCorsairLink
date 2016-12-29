/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2014  Sean Nelson <audiohacked@gmail.com>

 * OpenCorsairLink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.

 * OpenCorsairLink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OpenCorsairLink.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Proto.h"
#include "Link.h"
#include "Fan.h"

extern CorsairLink *cl;

int CorsairFan::SelectFan(int index) {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x04;
	commands[1] = cl->CommandId++;
	commands[2] = WriteOneByte;
	commands[3] = FAN_Select;
	commands[4] = index;

	cl->hid_wrapper(cl->handle, commands, 8);
	return commands[2];
}

int CorsairFan::CurrentFan() {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadOneByte;
	commands[3] = FAN_Select;

	cl->hid_wrapper(cl->handle, commands, 8);
	return commands[2];
}

int CorsairFan::GetFanCount() {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = WriteOneByte;
	commands[3] = FAN_Count;
	commands[4] = 0x00;

	cl->hid_wrapper(cl->handle, commands, 8);
	return commands[2];
}

int CorsairFan::GetFanMode() {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadOneByte;
	commands[3] = FAN_Mode;
	commands[4] = 0x00;

	cl->hid_wrapper(cl->handle, commands, 8);
	return commands[2];
}

int CorsairFan::SetFanMode(int mode) {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = WriteOneByte;
	commands[3] = FAN_Mode;
	commands[4] = mode;
	cl->hid_wrapper(cl->handle, commands, 8);
	return 0;
}

int CorsairFan::GetFanPWM() {
	//ReadOneByte
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadOneByte;
	commands[3] = FAN_FixedPWM;
	cl->hid_wrapper(cl->handle, commands, 8);
	return commands[2];
}

int CorsairFan::SetFanPWM(int pwm) {
	//WriteOneByte
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x04;
	commands[1] = cl->CommandId++;
	commands[2] = WriteOneByte;
	commands[3] = FAN_FixedPWM;
	commands[4] = pwm;
	cl->hid_wrapper(cl->handle, commands, 8);
	return 0;
}

int CorsairFan::GetFanRPM() {
	//ReadTwoBytes
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x04;
	commands[1] = cl->CommandId++;
	commands[2] = ReadTwoBytes;
	commands[3] = FAN_FixedRPM;
	commands[4] = 0x00;
	cl->hid_wrapper(cl->handle, commands, 8);
	int RPM = commands[3]<<8;
	RPM += commands[2];
	return RPM;
}

int CorsairFan::SetFanRPM(int rpm) {
	//WriteTwoBytes
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x05;
	commands[1] = cl->CommandId++;
	commands[2] = WriteTwoBytes;
	commands[3] = FAN_FixedRPM;
	commands[4] = rpm & 0x00ff;
	commands[5] = rpm>>8;
	cl->hid_wrapper(cl->handle, commands, 8);
	return 0;
}

int CorsairFan::GetExternalReport() {
	//ReadTwoBytes
	return -1;
}

int CorsairFan::SetExternalReport() {
	//WriteTwoBytes
	return -1;
}

int CorsairFan::GetCurrentRPM() {
	//ReadTwoBytes
	memset(commands, 0x00, sizeof(commands));	
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadTwoBytes;
	commands[3] = FAN_ReadRPM;
	cl->hid_wrapper(cl->handle, commands, 8);
	int RPM = commands[3]<<8;
	RPM += commands[2];
	return RPM;
}

int CorsairFan::GetMaxRPM() {
	//ReadTwoBytes
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadTwoBytes;
	commands[3] = FAN_MaxRecordedRPM;
	cl->hid_wrapper(cl->handle, commands, 8);
	int MaxRPM = commands[3]<<8;
	MaxRPM += commands[2];
	return MaxRPM;
}

int CorsairFan::GetFanUnderspeedThreshold() {
	//ReadTwoBytes
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x03;
	commands[1] = cl->CommandId++;
	commands[2] = ReadTwoBytes;
	commands[3] = FAN_UnderSpeedThreshold;
	cl->hid_wrapper(cl->handle, commands, 8);
	int threshold = commands[3]<<8;
	threshold += commands[2];
	return 0;
}

int CorsairFan::SetFanUnderspeedThreshold(int threshold) {
	//WriteTwoBytes
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x05;
	commands[1] = cl->CommandId++;
	commands[2] = WriteTwoBytes;
	commands[3] = FAN_UnderSpeedThreshold;
	commands[4] = threshold & 0x00FF;
	commands[5] = threshold >> 8;
	return 0;
}

int CorsairFan::GetRPMTable(int &rpm1, int &rpm2, int &rpm3, int &rpm4, int &rpm5) {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x0F;
	commands[1] = cl->CommandId++;
	commands[2] = ReadThreeBytes;
	commands[3] = FAN_RPMTable;
	commands[4] = 0x0A;
	cl->hid_wrapper(cl->handle, commands, 24);

	rpm1 = commands[4]<<8;
	rpm1 += commands[3];

	rpm2 = commands[6]<<8;
	rpm2 += commands[5];

	rpm3 = commands[8]<<8;
	rpm3 += commands[7];

	rpm4 = commands[10]<<8;
	rpm4 += commands[9];

	rpm5 = commands[12]<<8;
	rpm5 += commands[11];

	return 0;
}

int CorsairFan::SetRPMTable(int rpm1, int rpm2, int rpm3, int rpm4, int rpm5) {
	memset(commands, 0x00, sizeof(commands));	
	commands[0] = 0x0F;
	commands[1] = cl->CommandId++;
	commands[2] = WriteThreeBytes;
	commands[3] = FAN_RPMTable;
	commands[4] = 0x0A;

	commands[5] = rpm1 & 0x00FF;
	commands[6] = rpm1>>8;

	commands[7] = rpm2 & 0x00FF;
	commands[8] = rpm2>>8;

	commands[9] = rpm3 & 0x00FF;
	commands[10] = rpm3>>8;

	commands[11] = rpm4 & 0x00FF;
	commands[12] = rpm4>>8;

	commands[13] = rpm5 & 0x00FF;
	commands[14] = rpm5>>8;

	cl->hid_wrapper(cl->handle, commands, 24);

	return 0;
}

int CorsairFan::GetTemperatureTable(int &temp1, int &temp2, int &temp3, int &temp4, int &temp5) {
	memset(commands, 0x00, sizeof(commands));
	commands[0] = 0x0F;
	commands[1] = cl->CommandId++;
	commands[2] = ReadThreeBytes;
	commands[3] = FAN_TempTable;
	commands[4] = 0x0A;
	cl->hid_wrapper(cl->handle, commands, 24);

	temp1 = commands[4]<<8;
	temp1 += commands[3];

	temp2 = commands[6]<<8;
	temp2 += commands[5];

	temp3 = commands[8]<<8;
	temp3 += commands[7];

	temp4 = commands[10]<<8;
	temp4 += commands[9];

	temp5 = commands[12]<<8;
	temp5 += commands[11];

	return 0;
}

int CorsairFan::SetTemperatureTable(int temp1, int temp2, int temp3, int temp4, int temp5) {
	memset(commands, 0x00, sizeof(commands));	
	commands[0] = 0x0F;
	commands[1] = cl->CommandId++;
	commands[2] = WriteThreeBytes;
	commands[3] = FAN_TempTable;
	commands[4] = 0x0A;

	commands[5] = temp1 & 0x00FF;
	commands[6] = temp1>>8;

	commands[7] = temp2 & 0x00FF;
	commands[8] = temp2>>8;

	commands[9] = temp3 & 0x00FF;
	commands[10] = temp3>>8;

	commands[11] = temp4 & 0x00FF;
	commands[12] = temp4>>8;

	commands[13] = temp5 & 0x00FF;
	commands[14] = temp5>>8;

	cl->hid_wrapper(cl->handle, commands, 24);

	return 0;
}

void CorsairFan::PrintInfo(CorsairFanInfo fan) {
	fprintf(stdout, "%s:\n", fan.Name );
	fprintf(stdout, "\tMode: %s\n", GetFanModeString(fan.Mode) );
	fprintf(stdout, "\tRPM: %i\n", fan.RPM );
}

char* CorsairFan::GetFanModeString(int mode)
{
	char *modeString = NULL;
	switch(mode){
		case FixedPWM:
			asprintf(&modeString,"Fixed PWM");
			break;
		case FixedRPM:
			asprintf(&modeString, "Fixed RPM");
			break;
		case Default:
			asprintf(&modeString, "Default");
			break;
		case Quiet:
			asprintf(&modeString, "Quiet");
			break;
		case Balanced:
			asprintf(&modeString, "Balanced");
			break;
		case Performance:
			asprintf(&modeString, "Performance");
			break;
		case Custom:
			asprintf(&modeString, "Custom");
			break;
		default:
			asprintf(&modeString, "N/A (%02X)", mode );
			break;
	}
	return modeString;
}

int CorsairFan::ConnectedFans() {
	int fans = 0, i = 0, fanMode = 0;

	for (i = 0; i < 5; i++) {
		memset(commands,0x00,sizeof(commands));
		// Read fan Mode
		commands[0] = 0x07; // Length
		commands[1] = cl->CommandId++; // Command ID
		commands[2] = WriteOneByte; // Command Opcode
		commands[3] = FAN_Select; // Command data...
		commands[4] = i; // select fan
		commands[5] = cl->CommandId++; // Command ID
		commands[6] = ReadOneByte; // Command Opcode
		commands[7] = FAN_Mode; // Command data...

		int res = hid_write(cl->handle, commands, 11);
		if (res < 0) {
			fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
		}

		res = cl->hid_read_wrapper(cl->handle, commands);
		if (res < 0) {
			fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
		}
		fanMode = commands[4];

		if(fanMode != 0x03){
			fans++;
		}
	}

	return fans;
}

void CorsairFan::ReadFanInfo(int fanIndex, CorsairFanInfo *fan){
	int res = 0;

	if(fanIndex < 4){
		asprintf(&fan->Name, "Fan %i", fanIndex + 1);
	}
	else {
		asprintf(&fan->Name, "Pump");
	}

	memset(commands,0x00,sizeof(commands));
	// Read fan Mode
	commands[0] = 0x07; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = WriteOneByte; // Command Opcode
	commands[3] = FAN_Select; // Command data...
	commands[4] = fanIndex; // select fan
	commands[5] = cl->CommandId++; // Command ID
	commands[6] = ReadOneByte; // Command Opcode
	commands[7] = FAN_Mode; // Command data...
	
	res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to read() %s\n", (char*)hid_error(cl->handle) );
	}
	fan->Mode = commands[4] & 0x0E;

	memset(commands,0x00,sizeof(commands));
	// Read fan RPM
	commands[0] = 0x07; // Length
	commands[1] = cl->CommandId++; // Command ID
	commands[2] = WriteOneByte; // Command Opcode
	commands[3] = FAN_Select; // Command data...
	commands[4] = fanIndex; // select fan
	commands[5] = cl->CommandId++; // Command ID
	commands[6] = ReadTwoBytes; // Command Opcode
	commands[7] = FAN_ReadRPM; // Command data...

	res = hid_write(cl->handle, commands, 11);
	if (res < 0) {
		fprintf(stderr, "Error: Unable to write() %s\n", (char*)hid_error(cl->handle) );
	}

	res = cl->hid_read_wrapper(cl->handle, commands);
	//All data is little-endian.
	int rpm = commands[5] << 8;
	rpm += commands[4];

	fan->RPM = rpm;
}

int CorsairFan::SetFansInfo(int fanIndex, CorsairFanInfo fanInfo){
	memset(commands,0x00,sizeof(commands));

	if(fanInfo.Mode == FixedPWM || fanInfo.Mode == FixedRPM
		|| fanInfo.Mode == Default || fanInfo.Mode == Quiet
		|| fanInfo.Mode == Balanced	|| fanInfo.Mode == Performance
		|| fanInfo.Mode == Custom) {

		commands[0] = 0x0b; // Length
		commands[1] = cl->CommandId++; // Command ID
		commands[2] = WriteOneByte; // Command Opcode
		commands[3] = FAN_Select; // Command data...
		commands[4] = fanIndex; // select fan
		commands[5] = cl->CommandId++; // Command ID
		commands[6] = WriteOneByte; // Command Opcode
		commands[7] = FAN_Mode; // Command data...
		commands[8] = fanInfo.Mode;
		commands[9] = cl->CommandId++; // Command ID
		commands[10] = ReadOneByte; // Command Opcode
		commands[11] = FAN_Mode; // Command data...

		int res = hid_write(cl->handle, commands, 17);
		if (res < 0) {
			fprintf(stderr, "%s", (char*)hid_error(cl->handle) );
			return 1;
		}

		res = cl->hid_read_wrapper(cl->handle, commands);
		if (res < 0) {
			fprintf(stderr, "%s", (char*)hid_error(cl->handle) );
			return 1;
		}
		if(fanInfo.Mode != commands[6]){
			fprintf(stderr, "Cannot set fan mode.");
			return 1;
		}
	} else {
		fprintf(stderr, "Invalid fan mode." );
		return 1;
	}
	if(fanInfo.RPM != 0) {
		memset(commands,0x00,sizeof(commands));

		commands[0] = 0x0b; // Length
		commands[1] = cl->CommandId++; // Command ID
		commands[2] = WriteOneByte; // Command Opcode
		commands[3] = FAN_Select; // Command data...
		commands[4] = fanIndex; // select fan
		commands[5] = cl->CommandId++; // Command ID
		commands[6] = WriteTwoBytes; // Command Opcode
		commands[7] = FAN_FixedRPM; // Command data...
		commands[8] = fanInfo.RPM & 0x00FF;
		commands[9] = fanInfo.RPM >> 8;
		commands[10] = cl->CommandId++; // Command ID
		commands[11] = ReadTwoBytes; // Command Opcode
		commands[12] = FAN_ReadRPM; // Command data...

		int res = hid_write(cl->handle, commands, 18);
		if (res < 0) {
			fprintf(stderr, "%s", (char*)hid_error(cl->handle) );
			return 1;
		}

		res = cl->hid_read_wrapper(cl->handle, commands);
		if (res < 0) {
			fprintf(stderr, "%s", (char*)hid_error(cl->handle) );
			return 1;
		}
		//All data is little-endian.
		int rpm = commands[5] << 8;
		rpm += commands[4];
		if(fanInfo.RPM != rpm){
			fprintf(stderr, "Cannot set fan RPM.");
			return 1;
		}
	}

	return 0;
}

