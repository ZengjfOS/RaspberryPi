all: 
	gcc getCameraInfo.c -o getCameraInfo
	gcc getyuyv.c -o getyuyv
	gcc yuyv2bmp.c -o yuyv2bmp
	gcc getjpg.c -o getjpg

clean:
	rm getyuyv yuyv2bmp getjpg getCameraInfo

test:
	./getCameraInfo
	./getyuyv
	./yuyv2bmp
