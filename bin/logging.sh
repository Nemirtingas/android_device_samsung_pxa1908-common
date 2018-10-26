#!/system/bin/sh
sleep 2
ncount=`cat /NVM/ncount.txt`
echo "ncount is $ncount" > /dev/kmsg
cd /NVM
kname=kmsg.lpm.$ncount.log
lname=logcat.lpm.$ncount.log
rname=radio.lpm.$ncount.log
if [ -f $kname ]; then
	gzip $kname
fi
if [ -f $lname ]; then
	gzip $lname
fi
if [ -f $rname ]; then
	gzip $rname
fi
if [ $ncount == 9 ]; then
	ncount=0
fi

let ncount=ncount+1
echo "ncount is $ncount" > /dev/kmsg
kname=kmsg.lpm.$ncount.log
lname=logcat.lpm.$ncount.log
rname=radio.lpm.$ncount.log

time_stamp=`date`
echo $time_stamp > /NVM/$kname
cat /proc/kmsg >> /NVM/$kname &

echo $time_stamp > /NVN/$lname
logcat -v time >> /NVM/$lname &

#echo $time_stamp > /NVN/$rname
#logcat -v time -b radio >> /NVM/$rname &

echo $ncount > /NVM/ncount.txt
echo "ncount is $ncount" > /dev/kmsg
sync

