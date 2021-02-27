# 利用AT24C02 EEPROM理解I2C通信

利用Overlay加载AT24C02 I2C驱动，通过i2c-tools获取数据

## overlay

* arch/arm/boot/dts/overlays/rpi-at24c02-overlay.dts
  ```dts
  // rpi-sense HAT
  /dts-v1/;
  /plugin/;
  
  / {
          compatible = "brcm,bcm2835";
  
          fragment@0 {
                  target = <&i2c1>;
                  __overlay__ {
                          #address-cells = <1>;
                          #size-cells = <0>;
                          status = "okay";
  
                          DebugHAT@50 {
                                  compatible = "atmel,24c02";
                                  reg = <0x50>;
                                  status = "okay";
                          };
                  };
          };
  };
  ```

## Makefile修改

```diff
diff --git a/arch/arm/boot/dts/overlays/Makefile b/arch/arm/boot/dts/overlays/Makefile
index ff269e097..56df92009 100644
--- a/arch/arm/boot/dts/overlays/Makefile
+++ b/arch/arm/boot/dts/overlays/Makefile
@@ -86,6 +86,7 @@ dtbo-$(CONFIG_ARCH_BCM2835) += \
        i2c4.dtbo \
        i2c5.dtbo \
        i2c6.dtbo \
+       rpi-at24c02.dtbo \
        i2s-gpio28-31.dtbo \
        ilitek251x.dtbo \
        imx219.dtbo \
diff --git a/drivers/i2c/busses/i2c-bcm2835.c b/drivers/i2c/busses/i2c-bcm2835.c
index 9f4f4964a..792f20ec2 100644
--- a/drivers/i2c/busses/i2c-bcm2835.c
+++ b/drivers/i2c/busses/i2c-bcm2835.c
@@ -517,6 +517,8 @@ static int bcm2835_i2c_probe(struct platform_device *pdev)
        struct clk *mclk;
        u32 bus_clk_rate;

+       dump_stack();
+
        i2c_dev = devm_kzalloc(&pdev->dev, sizeof(*i2c_dev), GFP_KERNEL);
        if (!i2c_dev)
                return -ENOMEM;
```

## 驱动

* drivers/misc/eeprom/at24.c
  ```
  dev_info(dev, "%u byte %s EEPROM, %s, %u bytes/write\n",
       byte_len, client->name,
       writable ? "writable" : "read-only", at24->write_max);
  ```

## 实践测试

* make -j4 dtbs
* sudo cp arch/arm/boot/dts/overlays/rpi-at24c02.dtbo /boot/overlays/
* dmesg -w
* sudo dtoverlay rpi-at24c02
  ```
  [   19.654568] broken atomic modeset userspace detected, disabling atomic
  [   65.553108] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /soc/i2c@7e804000/status
  [   65.562299] CPU: 1 PID: 786 Comm: systemd-udevd Tainted: G         C        5.4.83-v7l #1
  [   65.562306] Hardware name: BCM2711
  [   65.562309] Backtrace:
  [   65.562325] [<c020dfb0>] (dump_backtrace) from [<c020e330>] (show_stack+0x20/0x24)
  [   65.562331]  r7:ffffffff r6:00000000 r5:a0000013 r4:c129fab0
  [   65.562339] [<c020e310>] (show_stack) from [<c0a76c34>] (dump_stack+0xd8/0x11c)
  [   65.562351] [<c0a76b5c>] (dump_stack) from [<bf34b9b4>] (bcm2835_i2c_probe+0x34/0x388 [i2c_bcm2835])
  [   65.562357]  r10:00000000 r9:00000023 r8:c1204fc8 r7:d3fb1c00 r6:d3fb1c10 r5:00000000
  [   65.562360]  r4:d3fb1c10 r3:d3e0a79d
  [   65.562370] [<bf34b980>] (bcm2835_i2c_probe [i2c_bcm2835]) from [<c07969ec>] (platform_drv_probe+0x58/0xa8)
  [   65.562375]  r9:00000023 r8:bf34d014 r7:00000000 r6:bf34d014 r5:00000000 r4:d3fb1c10
  [   65.562382] [<c0796994>] (platform_drv_probe) from [<c07949c0>] (really_probe+0x1f0/0x354)
  [   65.562387]  r7:00000000 r6:c13616b4 r5:d3fb1c10 r4:c13616b0
  [   65.562393] [<c07947d0>] (really_probe) from [<c0794d1c>] (driver_probe_device+0x70/0x184)
  [   65.562398]  r10:c1204fc8 r9:d2bf7f30 r8:bf34d080 r7:c0795028 r6:bf34d014 r5:bf34d014
  [   65.562401]  r4:d3fb1c10 r3:00000000
  [   65.562408] [<c0794cac>] (driver_probe_device) from [<c0795020>] (device_driver_attach+0x68/0x70)
  [   65.562413]  r9:d2bf7f30 r8:bf34d080 r7:c0795028 r6:bf34d014 r5:00000000 r4:d3fb1c10
  [   65.562419] [<c0794fb8>] (device_driver_attach) from [<c0795090>] (__driver_attach+0x68/0xdc)
  [   65.562423]  r7:c0795028 r6:d3fb1c10 r5:bf34d014 r4:00000000
  [   65.562429] [<c0795028>] (__driver_attach) from [<c07929c8>] (bus_for_each_dev+0x84/0xc4)
  [   65.562434]  r7:c0795028 r6:bf34d014 r5:c1204fc8 r4:d2a42bb4
  [   65.562439] [<c0792944>] (bus_for_each_dev) from [<c0794218>] (driver_attach+0x2c/0x30)
  [   65.562444]  r7:00000000 r6:d2a42b00 r5:c12713b8 r4:bf34d014
  [   65.562450] [<c07941ec>] (driver_attach) from [<c0793c30>] (bus_add_driver+0x1c8/0x1e8)
  [   65.562456] [<c0793a68>] (bus_add_driver) from [<c079574c>] (driver_register+0x84/0x118)
  [   65.562461]  r7:00000000 r6:d38762c0 r5:bf0e9000 r4:bf34d014
  [   65.562467] [<c07956c8>] (driver_register) from [<c0796940>] (__platform_driver_register+0x50/0x58)
  [   65.562471]  r5:bf0e9000 r4:c1204fc8
  [   65.562481] [<c07968f0>] (__platform_driver_register) from [<bf0e9028>] (bcm2835_i2c_driver_init+0x28/0x1000 [i2c_bcm2835])
  [   65.562489] [<bf0e9000>] (bcm2835_i2c_driver_init [i2c_bcm2835]) from [<c02030c4>] (do_one_initcall+0x50/0x25c)
  [   65.562496] [<c0203074>] (do_one_initcall) from [<c02c28fc>] (do_init_module+0x70/0x264)
  [   65.562501]  r8:bf34d080 r7:d3876300 r6:d38762c0 r5:d3876d00 r4:bf34d080
  [   65.562507] [<c02c288c>] (do_init_module) from [<c02c4f58>] (load_module+0x236c/0x2670)
  [   65.562511]  r6:d38762c0 r5:00000002 r4:00000002
  [   65.562517] [<c02c2bec>] (load_module) from [<c02c54c0>] (sys_finit_module+0xd4/0xec)
  [   65.562522]  r10:0000017b r9:d2bf6000 r8:c02011c4 r7:00000006 r6:b6d808e0 r5:00000000
  [   65.562525]  r4:c1204fc8
  [   65.562530] [<c02c53ec>] (sys_finit_module) from [<c02011a4>] (__sys_trace_return+0x0/0x1c)
  [   65.562534] Exception stack(0xd2bf7fa8 to 0xd2bf7ff0)
  [   65.562539] 7fa0:                   5f669600 0142cbe8 00000006 b6d808e0 00000000 b6d813f4
  [   65.562544] 7fc0: 5f669600 0142cbe8 00000000 0000017b 01442958 0051e1dc 014442d0 00000000
  [   65.562548] 7fe0: becf4228 becf4218 b6d779d8 b6e67af0
  [   65.562552]  r7:0000017b r6:00000000 r5:0142cbe8 r4:5f669600
  [   65.619900] at24 1-0050: 256 byte 24c02 EEPROM, writable, 1 bytes/write
  ```
* lsmod | grep at24
  ```
  at24                   20480  0
  regmap_i2c             16384  1 at24
  ```
* cd /sys/kernel/config/device-tree/overlays
* 开机启动加载：
  * sudo vim /boot/config.txt
    ```
    [...省略]
    dtoverlay=rpi-at24c02
    ```

## 操作EEPROM

* sudo su
* ls -al /sys/bus/i2c/devices/1-0050
* echo zengjf > eeprom
* xxd -g 1 eeprom

## i2c-tools

* https://manpages.debian.org/unstable/i2c-tools/i2cdetect.8.en.html
* i2c-tools
  * i2cget -f -y 1 0x50 0x03
  * i2cset -f -y 1 0x50 0x03 0x01
  * i2cget -f -y 1 0x50 0x03
