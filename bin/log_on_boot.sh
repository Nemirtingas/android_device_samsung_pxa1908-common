#!/system/bin/sh
propvalue=`getprop persist.radio.bootlog.enable`

if [[ !$propvalue==null ]];then
    main_enabled=${propvalue:0:1}

    if [[ !$main_enabled==null && $main_enabled -eq 1 ]]
    then
        /system/bin/logcat -v threadtime -f /data/log/Mlog/main -n 5 -r 2048&
    fi
    radio_enabled=${propvalue:1:1}
    if [[ !$radio_enabled==null &&  $radio_enabled -eq 1 ]]
    then
        /system/bin/logcat -v threadtime -b radio -f /data/log/Mlog/radio -n 4 -r 4096&
    fi

    tcp_enabled=${propvalue:2:1}
    if [[ !$tcp_enabled==null &&  $tcp_enabled -eq 1 ]]
    then
        tcpdump -i any -p -C 50 -W 1 -o 2048 -w /data/log/Mlog/tcpdump.pcap &
    fi
fi
