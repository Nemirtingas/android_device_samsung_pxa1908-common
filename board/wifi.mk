# Wifi
# Enable Auto Channel Selection (For wifi Access Point hostapd)
#CONFIG_ACS                       := true
BOARD_WLAN_VENDOR                := MRVL
MRVL_WIRELESS_DAEMON_API         := true
BOARD_HAS_MRVL_WLAN              := true
BOARD_HOSTAPD_DRIVER             := NL80211
BOARD_WPA_SUPPLICANT_DRIVER      := NL80211
BOARD_WLAN_DEVICE                := mrvl
BOARD_HOSTAPD_PRIVATE_LIB        := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_$(BOARD_WLAN_DEVICE)
WPA_SUPPLICANT_VERSION           := VER_0_8_X
WIFI_DRIVER_FW_PATH_STA          := "/system/etc/firmware/mrvl/sd8777_uapsta.bin"
WIFI_DRIVER_FW_PATH_AP           := "/system/etc/firmware/mrvl/sd8777_uapsta.bin"
WIFI_DRIVER_FW_PATH_P2P          := "/system/etc/firmware/mrvl/sd8777_uapsta.bin"
WIFI_DRIVER_FW_PATH_PARAM        := "/dev/null"
WIFI_DRIVER_NVRAM_PATH_PARAM     := "/sys/module/dhd/parameters/nvram_path"
WIFI_DRIVER_NVRAM_PATH_CONF      := "/system/etc/wifi/nvram_net.txt"
