#!/system/bin/sh

iface=wlan0
opmode=512 #random value

svc wifi disable
rmmod bcmdhd
insmod /system/lib/modules/bcmdhd2.ko iface_name=$iface op_mode=$opmode
ifconfig $iface up