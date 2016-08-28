#!/usr/bin/bash
iface=wlan0

while true; do
	for i in 1 2 3 4 5 6 7 8 9 10 11 12 13; do
		iwconfig $iface channel $i
		sleep 0.5
	done
done