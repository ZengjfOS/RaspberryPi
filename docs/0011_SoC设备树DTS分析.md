# SoC设备树DTS分析

怎么分析芯片设备树

## 配置bash环境变量

* tail ~/.bashrc
  ```
  # ...省略
  
  LINUX_SRC=/home/pi/zengjf/linux-rpi-5.4.y
  alias kernel="cd ${LINUX_SRC}"
  alias dts="cd ${LINUX_SRC}/arch/arm/boot/dts"
  ```
* 便于代码目录跳转

## SoC Datasheet

* [Raspberry Pi 4 B Datasheets](https://www.raspberrypi.org/documentation/hardware/raspberrypi/datasheets.md)
* [rpi_DATA_2711_1p0.pdf](refers/datasheet/rpi_DATA_2711_1p0.pdf)

# GPIO UART I2C DTS分析

* arch/arm/boot/dts/bcm2711-rpi-4-b.dts
  ```
  * arch/arm/boot/dts                             # dts目录
    * bcm2711-rpi-4-b.dts                         # 一般是产品的名字称，包含整个产品控制器的描述
      * #include "bcm2711.dtsi"                   # 一般是芯片的名称，包含基本芯片的控制器的基本描述
        * #include "bcm283x.dtsi"                 # 芯片是在原来芯片基础上设计的，继承原先的基础配置
          * gpio                                  # pin脚复用配置
          * uart0 ~ 1
          * i2c0if
          * i2c1
        * uart2 ~ 5
        * i2c3 ~ 6
  ```
* Chapter 3. BSC
  * i2c
* Chapter 5. General Purpose I/O (GPIO)
  * gpio
* Chapter 11. UART
  * uart

## DTS如何关联Driver

* arch/arm/boot/dts/bcm2711-rpi-4-b.dts
  ```
  * arch/arm/boot/dts                                               # dts目录
    * bcm2711-rpi-4-b.dts                                           # dts文件
        * i2c3: i2c@7e205600                                        # i2c3控制器
          * compatible = "brcm,bcm2711-i2c", "brcm,bcm2835-i2c";    # 控制器与驱动match字段
            * cd  drivers/i2c                                       # 查找i2c驱动目录
              * ack brcm,bcm2711-i2c                                # 查找match字段
                * busses/i2c-bcm2835.c                              # 驱动文件
                  * { .compatible = "brcm,bcm2711-i2c" },           # 驱动match字段
  ```
* of: Open Firmware

## Device Driver match

* 打印probe内核调用栈：
  ```diff
  diff --git a/drivers/i2c/busses/i2c-bcm2835.c b/drivers/i2c/busses/i2c-bcm2835.c
  index 9f4f496..792f20e 100644
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
* KERNEL=kernel7l
* make -j4 zImage modules dtbs
  ```
    CALL    scripts/atomic/check-atomics.sh
    CALL    scripts/checksyscalls.sh
    CHK     include/generated/compile.h
    CC [M]  drivers/i2c/busses/i2c-bcm2835.o
    Kernel: arch/arm/boot/Image is ready
    Building modules, stage 2.
    MODPOST 1626 modules
    Kernel: arch/arm/boot/zImage is ready
    CC [M]  drivers/i2c/busses/i2c-bcm2835.mod.o
    LD [M]  drivers/i2c/busses/i2c-bcm2835.ko
  ```
* uname -a
  ```
  Linux raspberrypi 5.4.83-v7l #1 SMP Wed Feb 10 09:33:55 GMT 2021 armv7l GNU/Linux
  ```
* sudo cp drivers/i2c/busses/i2c-bcm2835.ko /lib/modules/5.4.83-v7l/kernel/drivers/i2c/busses/i2c-bcm2835.ko
* sudo raspi-config
  * i2c
  * vim /boot/config.txt
    * dtparam=i2c_arm=on
* dmesg
  ```
  ...省略
  [  287.688821] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /soc/i2c@7e804000/status
  [  287.730053] CPU: 1 PID: 787 Comm: systemd-udevd Tainted: G         C        5.4.83-v7l #1
  [  287.730060] Hardware name: BCM2711
  [  287.730063] Backtrace:
  [  287.730080] [<c020dfb0>] (dump_backtrace) from [<c020e330>] (show_stack+0x20/0x24)
  [  287.730086]  r7:ffffffff r6:00000000 r5:a0000013 r4:c129fab0
  [  287.730095] [<c020e310>] (show_stack) from [<c0a76c34>] (dump_stack+0xd8/0x11c)
  [  287.730113] [<c0a76b5c>] (dump_stack) from [<bf36a9b4>] (bcm2835_i2c_probe+0x34/0x388 [i2c_bcm2835])
  [  287.730118]  r10:00000000 r9:00000023 r8:c1204fc8 r7:d6a05e00 r6:d6a05e10 r5:00000000
  [  287.730122]  r4:d6a05e10 r3:cbd15570
  [  287.730133] [<bf36a980>] (bcm2835_i2c_probe [i2c_bcm2835]) from [<c07969ec>] (platform_drv_probe+0x58/0xa8)
  [  287.730138]  r9:00000023 r8:bf36c014 r7:00000000 r6:bf36c014 r5:00000000 r4:d6a05e10
  [  287.730145] [<c0796994>] (platform_drv_probe) from [<c07949c0>] (really_probe+0x1f0/0x354)
  [  287.730150]  r7:00000000 r6:c13616b4 r5:d6a05e10 r4:c13616b0
  [  287.730156] [<c07947d0>] (really_probe) from [<c0794d1c>] (driver_probe_device+0x70/0x184)
  [  287.730161]  r10:c1204fc8 r9:d5a8ff30 r8:bf36c080 r7:c0795028 r6:bf36c014 r5:bf36c014
  [  287.730164]  r4:d6a05e10 r3:00000000
  [  287.730171] [<c0794cac>] (driver_probe_device) from [<c0795020>] (device_driver_attach+0x68/0x70)
  [  287.730176]  r9:d5a8ff30 r8:bf36c080 r7:c0795028 r6:bf36c014 r5:00000000 r4:d6a05e10
  [  287.730182] [<c0794fb8>] (device_driver_attach) from [<c0795090>] (__driver_attach+0x68/0xdc)
  [  287.730187]  r7:c0795028 r6:d6a05e10 r5:bf36c014 r4:00000000
  [  287.730193] [<c0795028>] (__driver_attach) from [<c07929c8>] (bus_for_each_dev+0x84/0xc4)
  [  287.730197]  r7:c0795028 r6:bf36c014 r5:c1204fc8 r4:d5943db4
  [  287.730203] [<c0792944>] (bus_for_each_dev) from [<c0794218>] (driver_attach+0x2c/0x30)
  [  287.730207]  r7:00000000 r6:d736ae80 r5:c12713b8 r4:bf36c014
  [  287.730214] [<c07941ec>] (driver_attach) from [<c0793c30>] (bus_add_driver+0x1c8/0x1e8)
  [  287.730220] [<c0793a68>] (bus_add_driver) from [<c079574c>] (driver_register+0x84/0x118)
  [  287.730224]  r7:00000000 r6:d60a2d00 r5:bf077000 r4:bf36c014
  [  287.730231] [<c07956c8>] (driver_register) from [<c0796940>] (__platform_driver_register+0x50/0x58)
  [  287.730234]  r5:bf077000 r4:c1204fc8
  [  287.730244] [<c07968f0>] (__platform_driver_register) from [<bf077028>] (bcm2835_i2c_driver_init+0x28/0x1000 [i2c_bcm2835])
  [  287.730252] [<bf077000>] (bcm2835_i2c_driver_init [i2c_bcm2835]) from [<c02030c4>] (do_one_initcall+0x50/0x25c)
  [  287.730260] [<c0203074>] (do_one_initcall) from [<c02c28fc>] (do_init_module+0x70/0x264)
  [  287.730265]  r8:bf36c080 r7:d60a2d40 r6:d60a2d00 r5:d60a2740 r4:bf36c080
  [  287.730271] [<c02c288c>] (do_init_module) from [<c02c4f58>] (load_module+0x236c/0x2670)
  [  287.730274]  r6:d60a2d00 r5:00000002 r4:00000002
  [  287.730280] [<c02c2bec>] (load_module) from [<c02c54c0>] (sys_finit_module+0xd4/0xec)
  [  287.730285]  r10:0000017b r9:d5a8e000 r8:c02011c4 r7:00000006 r6:b6e2f8e0 r5:00000000
  [  287.730288]  r4:c1204fc8
  [  287.730294] [<c02c53ec>] (sys_finit_module) from [<c02011a4>] (__sys_trace_return+0x0/0x1c)
  [  287.730298] Exception stack(0xd5a8ffa8 to 0xd5a8fff0)
  [  287.730303] ffa0:                   fdfcc000 00e13b90 00000006 b6e2f8e0 00000000 b6e303f4
  [  287.730308] ffc0: fdfcc000 00e13b90 00000000 0000017b 00e1ee40 0049b1dc 00e49ca0 00000000
  [  287.730312] ffe0: bebbd228 bebbd218 b6e269d8 b6f16af0
  [  287.730316]  r7:0000017b r6:00000000 r5:00e13b90 r4:fdfcc000
  ```
