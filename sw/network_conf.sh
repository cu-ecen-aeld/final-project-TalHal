#!/bin/sh

ifconfig eth1 192.165.5.11
openvpn --mktun --dev tap0
ifconfig tap0 up
brctl addbr br0
brctl addif br0 eth1
brctl addif br0 tap0
ifconfig br0 up
