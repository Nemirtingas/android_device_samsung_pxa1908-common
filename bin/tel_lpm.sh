#!/system/bin/sh
# echo "@@@@ LPM Logging start" > /dev/kmsg
# /system/bin/logging.sh &
sleep 2

# load cp and mrd image and release cp
#echo "@@@@ CP Loading start" > /dev/kmsg
#/system/bin/cploader > /dev/kmsg

#echo "@@@@ CP Loading finish with $?" > /dev/kmsg

echo "@@@@ fb0 control is " > /dev/kmsg
cat /sys/class/graphics/fb0/device/power/control > /dev/kmsg

echo "@@@@ disp control is " > /dev/kmsg
cat /sys/bus/platform/drivers/mmp-disp/mmp-disp/power/control > /dev/kmsg
echo "@@@@ set lcd control to auto" > /dev/kmsg
echo auto > /sys/class/graphics/fb0/device/power/control
#echo "@@@@ set disp control to auto" > /dev/kmsg
# echo auto > /sys/bus/platform/drivers/mmp-disp/mmp-disp/power/control

