#!/bin/bash

# # led pre config
# cd /sys/class/gpio
# echo 10 > export
# cd gpio10
# echo out > direction
# chmod 666 value

# button pre config
cd /sys/class/gpio
if [ ! -e gpio9 ];then
	echo 9 > export
	cd gpio9
	echo in > direction
	echo both > edge
fi
