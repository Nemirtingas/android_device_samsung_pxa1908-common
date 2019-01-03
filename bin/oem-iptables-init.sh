#!/system/bin/sh

/system/bin/iptables -A oem_fwd -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu



