#!/system/bin/sh

setprop sys.telephony.default.loglevel 8
chown system:root /sys/class/power_supply/battery/capacity
chmod 0664 /sys/class/power_supply/battery/capacity

MODULE_DIR=/lib/modules
insmod $MODULE_DIR/msocketk.ko
insmod $MODULE_DIR/cploaddev.ko
#echo 1 > /sys/devices/system/cpu/cpu0/cp
insmod $MODULE_DIR/seh.ko

#This pcm_master argument have to set before cploader startup
pcm_master=`getprop persist.radio.pcmmaster`
if [ "$pcm_master" != "0" ]
then
	pcm_master="1"
fi
echo $pcm_master > /sys/module/audiostub/parameters/pcm_master

ssipc_enable=`getprop ro.cmd.ssipc_enable`
multisim=`getprop persist.radio.multisim.config`
#Below slice will set ssipc channels property and run channels.
if [ "$ssipc_enable" = "true" ]; then
	if [ "$multisim" = "dsds" ]; then
		echo 1 > sys/devices/virtual/ssipc_misc/umts_boot0/ssipc_dsds
	fi
	echo 1 > sys/devices/virtual/ssipc_misc/umts_boot0/ssipc_ch_enable
fi

# load cp and mrd image and release cp
/system/bin/cploader

ret="$?"
case "$ret" in
	    "-1")
		rmmod seh
		rmmod cploaddev
		rmmod msocketk
		exit
       ;;
	    "1")
		rmmod seh
		rmmod cploaddev
		rmmod msocketk
		start nvm-aponly
		start diag-aponly
		insmod $MODULE_DIR/citty.ko
		start atcmdsrv-aponly
		exit
       ;;
       *)
       ;;
esac


insmod $MODULE_DIR/citty.ko
insmod $MODULE_DIR/cci_datastub.ko
insmod $MODULE_DIR/ccinetdev.ko
insmod $MODULE_DIR/gs_modem.ko
insmod $MODULE_DIR/cidatattydev.ko
insmod $MODULE_DIR/audiostub.ko pcm_master=$pcm_master

setprop sys.tools.enable 1

sync

/system/bin/eeh -M yes &
/system/bin/nvm -A &
/system/bin/diag &
if [ "$ssipc_enable" != "true" ]; then
	/system/bin/atcmdsrv &
else
	/system/bin/at_router &
fi
