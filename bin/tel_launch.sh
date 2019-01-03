#!/system/bin/sh

#move NVM_ROOT_DIR to init.rc so other applications and services also use it.
#export  NVM_ROOT_DIR="/data/Linux/Marvell/NVM"

setprop marvell.ril.ppp.enabled 0
setprop log.tag.Mms V
setprop sys.usb.diagmodem 1

is_world_phone=`getprop ro.cmd.WORLD_PHONE`
if [ "$is_world_phone" == "true" ]
then
	auto_switch_option=`getprop persist.radio.auto.switch`
	if [ "$auto_switch_option" == "" ]
	then
		setprop persist.radio.auto.switch 0
	fi
fi

#backup log files
/system/bin/backup_log.sh

/system/bin/run_composite.sh;

