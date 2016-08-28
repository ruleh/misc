#!/system/bin/sh

#cd /dev
#for tty in tty $(ls tty[0-9]) $(ls tty[0-9][0-9]); do
#for tty in tty1; do
#    su -c dmesg > $tty
#    su -c echo -n "\n" > /dev/console
#   done

#su -c script -f -c dmesg /dev/tty1
#su -c dmesg > /dev/tty1 &
#su -c logcat -d -C -b main -b system -b crash -v tag *:D > /dev/tty1

#for i in s u SPACE - c SPACE d m e s g ENTER; do
#    echo $i | su -c virt-key
#   done

echo "d m e s g" | su -c virt-key
echo "ENTER" | su -c virt-key