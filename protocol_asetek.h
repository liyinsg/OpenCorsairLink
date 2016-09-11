/** copyright 2016 by Sean Nelson */
#ifndef _PROTOCOL_ASETEK_H
#define _PROTOCOL_ASETEK_H

int corsairlink_asetek_change_led(struct corsair_device_info *dev, unsigned char RR, unsigned char GG, unsigned char BB);
int corsairlink_asetek_22000000(struct corsair_device_info *dev);
int corsairlink_asetek_14000000(struct corsair_device_info *dev);
int corsairlink_asetek_20(struct corsair_device_info *dev);
int corsairlink_asetek_continue_transaction(struct corsair_device_info *dev);
int corsairlink_asetek_start_transaction(struct corsair_device_info *dev);
int corsairlink_asetek_pump_mode_performance(struct corsair_device_info *dev);
int corsairlink_asetek_pump_mode_quiet(struct corsair_device_info *dev);
#endif 
