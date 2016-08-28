#!/system/bin/sh

iface=wlan0

ifconfig $iface down
rmmod bcmdhd
insmod /system/lib/modules/bcmdhd.ko