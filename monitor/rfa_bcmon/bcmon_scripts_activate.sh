#!/system/bin/sh
svc wifi disable
sleep 2
rmmod dhd 2&>/dev/null
insmod /system/lib/modules/dhd.ko iface_name=wlan0 firmware_path=$(ls /data/data/com.bcmon.bcmon/files/*.bin) nvram_path=/system/etc/wifi/nvram_net.txt 
export LD_LIBRARY_PATH=/data/data/com.bcmon.bcmon/files/libs:$LD_LIBRARY_PATH
export LD_PRELOAD=/data/data/com.bcmon.bcmon/files/libs/libfake_driver.so
cd /data/data/com.bcmon.bcmon/files/tools
./enable_bcmon 2&>/dev/null
echo "rfasuccess"
exit
