getmntdir - get mount directory (v0.1.1)
=========

## Build

        # cd getmntdir
        # make (or gmake)

## Usage

        # ./getmntdir /var/tmp /boot/vmlinuz /sys/bus/scsi/uevent
        /var/tmp -> /
        /boot/vmlinuz -> /boot
        /sys/bus/scsi/uevent -> /sys
