#!/bin/sh

# build buildroot only for toolchain
./build.sh

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
echo $SCRIPTPATH

if [ $1 = "clean" ]; then

	echo "cleanning ... "
	make -C sw/rsender/ clean
	make -C sw/rreceiver/ clean
	make -C sw/tun/ clean

	exit 0
fi

make -C sw/rsender/ CROSS_COMPILE=${SCRIPTPATH}/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-
make -C sw/rreceiver/ CROSS_COMPILE=${SCRIPTPATH}/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-
make -C sw/tun/ CROSS_COMPILE=${SCRIPTPATH}/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-

cp ${SCRIPTPATH}/sw/rsender/rsender ${SCRIPTPATH}/base_external/rootfs_overlay/apps/

cp ${SCRIPTPATH}/sw/rreceiver/rrecv ${SCRIPTPATH}/base_external/rootfs_overlay/apps/

cp ${SCRIPTPATH}/sw/tun/tun_app ${SCRIPTPATH}/base_external/rootfs_overlay/apps/

./build.sh

