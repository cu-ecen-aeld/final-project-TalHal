#!/bin/sh
# Shared definitions for buildroot scripts

# The defconfig from the buildroot directory we use for qemu builds
RASPBERRYPI4_DEFCONFIG=configs/raspberrypi4_defconfig
# The place we store customizations to the qemu configuration
MODIFIED_RASPBERRYPI4_DEFCONFIG=base_external/configs/raspberrypi4_defconfig
# The defconfig from the buildroot directory we use for the project
AESD_DEFAULT_DEFCONFIG=${RASPBERRYPI4_DEFCONFIG}
AESD_MODIFIED_DEFCONFIG=${MODIFIED_RASPBERRYPI4_DEFCONFIG}
AESD_MODIFIED_DEFCONFIG_REL_BUILDROOT=../${AESD_MODIFIED_DEFCONFIG}
