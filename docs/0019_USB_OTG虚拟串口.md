# USB OTG虚拟串口

USB OTG虚拟串口，可用于学习串口通信

## 树莓派启动配置

* /boot/cmdline.txt
  * 第一行末尾添加：`modules-load=dwc2,g_serial dwc_otg.lpm_enable=1`
* /boot/config.txt
  * 文件最后添加行：`dtoverlay=dwc2`
* reboot

## 节点

* 树莓派：
  * /dev/ttyGS0
* PC
  * COM3

## 安装调试工具

* sudo apt-get install minicom
* minicom -s
  * 退出：ctrl + a, q, enter


## 参考C代码

https://github.com/ZengjfOS/UartRS
