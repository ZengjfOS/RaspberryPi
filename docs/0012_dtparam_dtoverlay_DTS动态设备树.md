# dtparam dtoverlay DTS动态设备树

分析dtparam/dtoverlay本质，为什么能够动态改变设备与驱动的match

## 参考文档

* [Device Trees, overlays, and parameters](https://www.raspberrypi.org/documentation/configuration/device-tree.md)

## 关闭i2c接口

* sudo raspi-config
  * i2c

## 命令打开I2C接口

* sudo dtparam -v i2c_arm=on
  ```
  DTOVERLAY[debug]: using platform 'bcm2711'
  DTOVERLAY[debug]: overlay map loaded
  run_cmd: which dtoverlay-pre >/dev/null 2>&1 && dtoverlay-pre
  run_cmd: dtc -I fs -O dtb -o '/tmp/.dtoverlays/base.dtb' /proc/device-tree 1>/dev/null 2>&1
  DTOVERLAY[debug]: loading file '/tmp/.dtoverlays/base.dtb'
  DTOVERLAY[debug]: found override i2c_arm
  DTOVERLAY[debug]:   override i2c_arm: string target 'status'
  DTOVERLAY[debug]: wrote 162 bytes to '/tmp/.dtoverlays/0_dtparam.dtbo'
  DTOVERLAY[debug]: wrote 174 bytes to '/sys/kernel/config/device-tree/overlays/0_dtparam/dtbo'
  run_cmd: which dtoverlay-post >/dev/null 2>&1 && dtoverlay-post
  ```
* cd /tmp/.dtoverlays/
* ls
  ```
  0_dtparam.dtbo  base.dtb
  ```
* sudo dtc -I dtb -O dts -o 0_dtparam.dts 0_dtparam.dtbo
* cat 0_dtparam.dts
  ```dts
  /dts-v1/;
  
  / {
  
      fragment-0 {
          target = < 0x32 >;
  
          __overlay__ {
              status = "okay";
          };
      };
  };
  ```
* sudo dtc -I dtb -O dts -o base.dts base.dtb
* base.dts
  ```
    * __symbols__
      * i2c1 = "/soc/i2c@7e804000";
      * i2c_arm = "/soc/i2c@7e804000";
    * soc
      * i2c@7e804000
        * phandle = < 0x32 >;
    * __overrides__
      * i2c1 = "\0\0\02status";
      * i2c_arm = "\0\0\02status";
  ```
  * 目前没有在设备树中找到`i2c_arm`这个字段内容，可能在一些配置中添加的

## dtparam dtoverlay

* ls -al /usr/bin/dtparam
  ```
  lrwxrwxrwx 1 root root 21 Jan  8 15:26 /usr/bin/dtparam -> /opt/vc/bin/dtoverlay
  ```
* ls -al /usr/bin/dtoverlay
  ```
  lrwxrwxrwx 1 root root 21 Jan  8 15:26 /usr/bin/dtoverlay -> /opt/vc/bin/dtoverlay
  ```

## dtparam源代码编译分析

* https://github.com/raspberrypi/userland
  * host_applications/linux/apps/dtoverlay
* ./buildme
  * build/raspberry/release/host_applications/linux/apps/dtoverlay/dtparam
* cd build/bin/
* ln -s dtoverlay dtparam
* ls -al dtparam
  ```
  lrwxrwxrwx 1 pi pi 9 Feb 15 00:24 dtparam -> dtoverlay
  ```
* sudo ./dtparam -v i2c_arm=on
  ```
  DTOVERLAY[debug]: using platform 'bcm2711'
  DTOVERLAY[debug]: overlay map loaded
  run_cmd: which dtoverlay-pre >/dev/null 2>&1 && dtoverlay-pre
  run_cmd: dtc -I fs -O dtb -o '/tmp/.dtoverlays/base.dtb' /proc/device-tree 1>/dev/null 2>&1
  DTOVERLAY[debug]: loading file '/tmp/.dtoverlays/base.dtb'
  DTOVERLAY[debug]: found override i2c_arm
  DTOVERLAY[debug]:   override i2c_arm: string target 'status'
  DTOVERLAY[debug]: wrote 162 bytes to '/tmp/.dtoverlays/0_dtparam.dtbo'
  DTOVERLAY[debug]: wrote 174 bytes to '/sys/kernel/config/device-tree/overlays/0_dtparam/dtbo'
  run_cmd: which dtoverlay-post >/dev/null 2>&1 && dtoverlay-post
  ```
  * `DTOVERLAY[debug]: found override i2c_arm`
* helpers/dtoverlay/dtoverlay.c
  ```cpp
  /* Returns a pointer to the override data and (through data_len) its length.
     On error, sets *data_len to be the error code. */
  const char *dtoverlay_find_override(DTBLOB_T *dtb, const char *override_name,
                                      int *data_len)
  {
     int overrides_off;
     const char *data;
     int len;
  
     // Find the table of overrides
     overrides_off = fdt_path_offset(dtb->fdt, "/__overrides__");
  
     if (overrides_off < 0)
     {
        dtoverlay_debug("/__overrides__ node not found");
        *data_len = overrides_off;
        return NULL;
     }
  
     // Locate the property
     data = fdt_getprop(dtb->fdt, overrides_off, override_name, &len);
     *data_len = len;
     if (data)
        dtoverlay_debug("found override %s", override_name);
     else
        dtoverlay_debug("/__overrides__ has no %s property", override_name);
  
     return data;
  }
  ```

## OF_OVERLAY

* [Device Tree overlays](https://github.com/torvalds/linux/blob/master/drivers/of/Kconfig#L85)
  ```
  config OF_OVERLAY
      bool "Device Tree overlays"
      select OF_DYNAMIC
      select OF_FLATTREE
      select OF_RESOLVE
      help
        Overlays are a method to dynamically modify part of the kernel's
        device tree with dynamically loaded data.
        While this option is selected automatically when needed, you can
        enable it manually to improve device tree unit test coverage.
  ```
* ls /sys/kernel/config/device-tree/overlays
* sudo dtparam -v i2c_arm=on
* ls /sys/kernel/config/device-tree/overlays
  ```
  0_dtparam
  ```
* ls /sys/kernel/config/device-tree/overlays/0_dtparam/
  ```
  dtbo  path  status
  ```

## 手动插入overlay

* 执行了`sudo dtparam -v i2c_arm=on`的基础上
  * cd /sys/kernel/config/device-tree/overlays
  * sudo rmdir 0_dtparam
  * cat /proc/device-tree/soc/i2c@7e804000/status
    ```
    disabled
    ```
  * sudo mkdir 0_dtparam
  * sudo su
  * cat /tmp/.dtoverlays/0_dtparam.dtbo > /sys/kernel/config/device-tree/overlays/0_dtparam/dtbo
  * cat /proc/device-tree/soc/i2c@7e804000/status
    ```
    okay
    ```
  * rmdir 0_dtparam
  * cat /proc/device-tree/soc/i2c@7e804000/status
    ```
    disabled
    ```
  * mount | grep config

