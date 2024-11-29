#!/bin/bash

can=$1
baud=$2
password="7913cuffia"

echo "selected can: $can"
echo "set baud: $baud"

if [ $can == "vcan0" ]
then
	echo "configuring virtual can"
	echo $password | sudo -S modprobe vcan
	sudo ip link add dev $can type vcan
	sudo ip link set up $can
fi

if [ $can == "can0" ]
then
	echo "configuring can device"
	echo $password | sudo -S ip link set $can type can bitrate $baud
	sudo ip link set up $can
fi

echo "can configurations done"