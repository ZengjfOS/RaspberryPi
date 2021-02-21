# IoT网页GPIO控制LED

通过Python3 Flask作为HTTP服务端，控制GPIO

## 参考文档

* [0009_USB摄像头搭建IP网络摄像头.md](0009_USB摄像头搭建IP网络摄像头.md)
* [0014_动态设备树GPIO控制LED.md](0014_动态设备树GPIO控制LED.md)
* [0015_用户空间控制GPIO.md](0015_用户空间控制GPIO.md)

## 原理图  

![0014_GPIO_LED_Power_OFF.png](images/0014_GPIO_LED_Power_OFF.png)

## 源代码

* https://github.com/LowLevelOfLogic/RaspberryPi/tree/IP_Camera
  * ledMonitor.py

## 实践操作

* cd /sys/class/gpio/
* echo 10 > export
* cd gpio10
* echo out > direction
* python3 ledMonitor.py
* http://192.168.3.3:5000/
