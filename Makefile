CC ?= gcc
LDFLAGS ?= -L/usr/lib -L/usr/local/lib -lusb-1.0
CFLAGS ?= -I/usr/include/libusb-1.0 -I/usr/local/include/libusb-1.0
OBJS = corsairlink.o \
			device.o
OBJS_LL = lowlevel/asetek4.o \
			lowlevel/hid.o
OBJS_PROTO = protocol/asetek4/core.o \
			protocol/asetek4/fan.o \
			protocol/asetek4/led.o \
			protocol/asetek4/pump.o \
			protocol/hid/core.o \
			protocol/hid/fan.o \
			protocol/hid/led.o \
			protocol/hid/pump.o

default: all

all: corsairlink4.elf
	
corsairlink4.elf: $(OBJS_PROTO) $(OBJS_LL) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	$(RM) corsairlink4.elf $(OBJS) $(OBJS_LL) $(OBJS_PROTO)
