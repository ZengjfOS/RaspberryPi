# Debug串口

看内核启动log信息，当机器无法启动可以判定问题

## 开启串口登陆

* sudo raspi-config

## 开启内核log

* cat /boot/cmdline.txt
  ```
  console=serial0,115200 console=tty1 root=PARTUUID=d3269df4-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait quiet splash plymouth.ignore-serial-consoles modules-load=dwc2,g_ether dwc_otg.lpm_enable=1
  ```
* 修改第一个console：`console=ttyS0,115200`
* 移除第二个console：`console=tty1`
* 移除`quiet`字段
* cat /boot/cmdline.txt
  ```
  console=ttyS0,115200 root=PARTUUID=d3269df4-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait splash plymouth.ignore-serial-consoles modules-load=dwc2,g_ether dwc_otg.lpm_enable=1
  ```
