#!/system/bin/sh
if ! applypatch -c EMMC:/dev/block/platform/soc.2/by-name/RECOVERY:8925184:5806057c7d6aa5a824c47bfafc45e3bdc5fbca85; then
  applypatch -b /system/etc/recovery-resource.dat EMMC:/dev/block/platform/soc.2/by-name/KERNEL:7966720:5254a84a615c81380d065a7012c2dda4576d1fc0 EMMC:/dev/block/platform/soc.2/by-name/RECOVERY 5806057c7d6aa5a824c47bfafc45e3bdc5fbca85 8925184 5254a84a615c81380d065a7012c2dda4576d1fc0:/system/recovery-from-boot.p && log -t recovery "Installing new recovery image: succeeded" || log -t recovery "Installing new recovery image: failed"
else
  log -t recovery "Recovery image already installed"
fi
