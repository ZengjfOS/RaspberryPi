#include <stdio.h> 
#include <unistd.h> 
#include <stdint.h>
#include <sys/types.h> 

// 下面四个头文件是linux系统编程特有的 
#include <sys/stat.h> 
#include <sys/ioctl.h> 
#include <fcntl.h> 
#include <linux/videodev2.h> // 操作摄像头设备 

uint8_t mask = 0xff;

// int main(int argc, char **argv) { 
int main() { 
	int ret, i; 
	int fd; 

	/* 打开摄像头设备 */ 
	fd = open("/dev/video0", O_RDWR); 						// 注意查看摄像头设备名 
	if (-1 == fd) { 
		perror("open /dev/video0"); 
		return -1; 
	} 

	/* 查询打开的设备是否属于摄像头：设备video不一定是摄像头*/ 
	struct v4l2_capability cap; 
	ret = ioctl(fd, VIDIOC_QUERYCAP, &cap); 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_QUERYCAP"); 
		close(fd); 
	} 
	if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) { 
		/* 如果为摄像头设备则打印摄像头驱动名字 */ 
		printf("Driver Name: %s\n", cap.driver); 
	} else { 
        printf( "Driver Caps:\n"
                "  Driver: \"%s\"\n"
                "  Card: \"%s\"\n"
                "  Bus: \"%s\"\n"
                "  Version: %d.%d\n"
                "  Capabilities: %08x\n",
                cap.driver,
                cap.card,
                cap.bus_info,
                (cap.version>>16)&&mask,
                (cap.version>>24)&&mask,
                cap.capabilities);

		printf("open file is not video\n"); 
		close(fd); 
		return -2; 
	} 
	/* 查询摄像头可捕捉的图片类型，VIDIOC_ENUM_FMT: 枚举摄像头帧格式 */ 
	struct v4l2_fmtdesc fmt; 
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; 					// 指定需要枚举的类型 
	for (i = 0; ; i++) // 有可能摄像头支持的图片格式不止一种 
	{ 
		fmt.index = i; 
		ret = ioctl(fd, VIDIOC_ENUM_FMT, &fmt); 
		if (-1 == ret) // 获取所有格式完成 
		{ 	
			break; 
		} 
		/* 打印摄像头图片格式 */ 
		printf("Picture Format: %s\n", fmt.description); 
		/* 查询该图像格式所支持的分辨率 */ 
		struct v4l2_frmsizeenum frmsize; frmsize.pixel_format = fmt.pixelformat; 
		for (i = 0; ; i++) //　该格式支持分辨率不止一种 
		{ 
			frmsize.index = i; 
			ret = ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize); 
			if (-1 == ret) 
			// 获取所有图片分辨率完成 
			{ 
				break; 
			} 
			/* 打印图片分辨率 */ 
			printf("width: %d height: %d\n", frmsize.discrete.width,frmsize.discrete.height); 
		} 
	} 
	close(fd); // 不要忘记关闭打开的设备 
	return 0; 
}

