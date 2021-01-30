# USB OTG虚拟网卡

在有些场合，没有Wifi想登陆树莓派，使用USB虚拟网卡SSH登陆


* [一、树莓派启动配置](#一树莓派启动配置)
* [二、树莓派设置静态IP](#二树莓派设置静态IP)
* [三、PC USB网卡驱动](#三PC-USB网卡驱动)
* [四、PC设置静态IP](#四PC设置静态IP)


## 一、树莓派启动配置

* /boot/cmdline.txt
  * 第一行末尾添加：`modules-load=dwc2,g_ether dwc_otg.lpm_enable=1`
* /boot/config.txt
  * 文件最后添加行：`dtoverlay=dwc2`


## 二、树莓派设置静态IP

* /etc/dhcpcd.conf
  ```
  interface usb0
  static ip_address=192.168.137.2/24
  # static routers=192.168.137.1          # 禁用路由设定，否则会导致Wifi路由不能用
  static domain_name_servers=8.8.8.8
  ```


## 三、PC USB网卡驱动

* 驱动
  * [mod-duo-rndis.zip](refers/mod-duo-rndis.zip)
* Windows 10上使用OTG转网卡可能会出现识别到串口，需要换到上面的驱动：


## 四、PC设置静态IP

* 网卡管理可以看到usb网卡，设置网卡IP和树莓派IP在同一个网段；
  * 192.168.137.5
