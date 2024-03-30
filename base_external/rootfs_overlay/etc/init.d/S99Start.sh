#!/bin/sh

echo "Start ..."

ifconfig eth0 192.163.1.7

insmod /lib/modules/5.10.92-v7l/kernel/drivers/net/tun.ko
