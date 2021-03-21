#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 

// 下面四个头文件是linux系统编程特有的 
#include <sys/stat.h> 
#include <sys/ioctl.h> 
#include <sys/mman.h> 
#include <fcntl.h> 
#include <linux/videodev2.h> // 操作摄像头设备 


#define WIDTH 640 			// 图片的宽度 
#define HEIGHT 480 			// 图片的高度 
#define FMT V4L2_PIX_FMT_YUYV 		// 图片格式 
#define COUNT 5 			// 缓冲区个数 

// int main(int argc, char **argv) { 
int main() { 
	unsigned char *datas[COUNT]; // 缓冲区数据地址 
	int ret, i; 
	int fd; 

	/* 第一步：打开摄像头设备文件 */ 
	fd = open("/dev/video0", O_RDWR); // 注意查看摄像头设备名 
	if (-1 == fd) { 
		perror("open /dev/video0"); 
		return -1; 
	} 

	/* 第二步：设置捕捉图片帧格式 */ 
	struct v4l2_format format; 
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 操作类型为获取图片 
	format.fmt.pix.width = WIDTH; // 图片的宽度 
	format.fmt.pix.height = HEIGHT; // 图片的高度 
	format.fmt.pix.pixelformat = FMT; // 图片格式 
	ret = ioctl(fd, VIDIOC_S_FMT, &format); // 进行设置(Set) 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_S_FMT"); 
		close(fd); 
		return -2; 
	} 

	/* 第三步：检查是否设置成功 */ 
	ret = ioctl(fd, VIDIOC_G_FMT, &format); // Get 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_G_FMT"); 
		close(fd); 
		return -3; 
	} 
	if (format.fmt.pix.pixelformat == FMT) { 
		printf("ioctl VIDIOC_S_FMT sucessful\n"); 
	} else { 
		printf("ioctl VIDIOC_S_FMT failed\n"); 
	} 

	/* 第四步：让摄像头驱动申请存放图像数据的缓冲区 */ 
	struct v4l2_requestbuffers reqbuf; 
	reqbuf.count = COUNT; // 缓冲区个数 
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 缓冲区类型 
	reqbuf.memory = V4L2_MEMORY_MMAP; // 缓冲区的用途：用于内存映射 
	ret = ioctl(fd, VIDIOC_REQBUFS, &reqbuf); 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_REQBUFS"); 
		close(fd); 
		return -4; 
	} 

	/* 第五步：查询每个缓冲区的信息，同时进行内存映射 */ 
	struct v4l2_buffer buff; 
	buff.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; 
	buff.memory = V4L2_MEMORY_MMAP; 
	for (i = 0; i < COUNT; i++) { 
		buff.index = i; 
		ret = ioctl(fd, VIDIOC_QUERYBUF, &buff); 
		if (-1 == ret) // 操作失败 
		{ 
			break; 
		} 

		/* 打印缓冲区的长度和偏移量 */ 
		printf("buf[%d]: len = %d offset: %d\n", i, buff.length, buff.m.offset); 
		/* 把每块缓冲区映射到当前进程来 */ 
		datas[i] = mmap(NULL, buff.length, PROT_READ, MAP_SHARED, fd, buff.m.offset); 
		if (MAP_FAILED == datas[i]) // 映射失败 
		{ 
			perror("mmap failed"); 
			return -5; 
		} 

		/* 把映射成功的缓冲区加入到摄像头驱动的图像数据采集队列里 */ 
		ret = ioctl(fd, VIDIOC_QBUF, &buff); // Queue 
		if (-1 == ret) { 
			perror("VIDIOC_QBUF"); 
			return -6; 
		} 
	} 

	/* 第六步：启动采集 */ 
	int on = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 设置启动标志位 
	ret = ioctl(fd, VIDIOC_STREAMON, &on); // 开启摄像头流 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_STREAMON"); 
		return -7; 
	} 

	/* 第七步：让已经采集好的数据缓冲退出队列 */ 
	ret = ioctl(fd, VIDIOC_DQBUF, &buff); // Dequeue 
	if (-1 == ret) { 
		perror("ioctl VIDIOC_DQUF"); 
		return -8; 
	} 

	/* 第八步：从退出队列的缓冲区中获取数据并保存到文件中 */ 
	FILE *fl; fl = fopen("./my.yuyv", "w"); 
	if (NULL == fl) { 
		fprintf(stderr, "open write file failed."); 
	} 
	fwrite(datas[buff.index], buff.bytesused, 1, fl); 
	fclose(fl); // 记得关闭已打开的文件 

	close(fd); // 记得关闭已打开的设备 

	return 0; 
}

