#!/system/bin/sh

#su -c "echo /system/xbin/mdev > /proc/sys/kernel/hotplug"
su -c "mdev -s"

#cd /system/lib/modules
#for i in $(ls cpufreq_*) do;
#insmod $i
#done