#!/bin/sh

ifconfig eth1 192.165.5.11
ifconfig eth0 0.0.0.0 promisc up

openvpn --mktun --dev tap0
ifconfig tap0 up
brctl addbr br0
brctl addif br0 eth0
brctl addif br0 tap0
ifconfig br0 up
