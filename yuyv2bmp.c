#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define WIDTH  640
#define HEIGHT 480
#define YUYV_FILE "./my.yuyv"
#define BMP_FILE  "./my.bmp"


typedef struct                       /**** BMP file header structure ****/
{
    unsigned short bftype;
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */

} BITMAPFILEHEADER;

typedef struct                       /**** BMP file info structure ****/
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

int yuv_to_rgb_pixel(int y, int u, int v)
{
    unsigned int pixel24 = 0;
    unsigned char *pixel = (unsigned char *)&pixel24;
    int r, g, b;
    // static long int ruv, guv, buv;

    r = 1.164*(y-16) + 1.159*(v-128);
    g = 1.164*(y-16) - 0.380*(u-128) - 0.813*(v-128);
    b = 1.164*(y-16) + 2.018*(u-128);

    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;

    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
    return pixel24;
}

int yuyv_to_rgb(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
    unsigned int in, out;
    int y0, u, y1, v;
    unsigned int pixel24;
    unsigned char *pixel = (unsigned char *)&pixel24;
    unsigned int size = width*height*2;

    for (in = 0, out = 0; in < size; in += 4, out += 6)
    {
      /*特殊说明，因bmp文件是以bgr顺序排列而不是rgb，故此u，v颠倒*/
        y0 = yuv[in+0];
        v  = yuv[in+1];//u  = yuv[in+1];
        y1 = yuv[in+2];
        u  = yuv[in+3];//v  = yuv[in+3];

        pixel24 = yuv_to_rgb_pixel(y0, u, v);
        rgb[out+0] = pixel[0];
        rgb[out+1] = pixel[1];
        rgb[out+2] = pixel[2];

        pixel24 = yuv_to_rgb_pixel(y1, u, v);
        rgb[out+3] = pixel[0];
        rgb[out+4] = pixel[1];
        rgb[out+5] = pixel[2];

    }
    return 0;
}

void SaveBmp(const char *filename,unsigned char *rgb,int width,int height)
{
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    bf.bftype = 0x4d42;
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    /*其中这两项为何减去2，是因为结构体对齐问题，sizeof(BITMAPFILEHEADER)并不是14，而是16*/
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+width*height*3-2;
    bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)-2;//0x36

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;//height
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = 0;
    bi.biSizeImage = width*height*3;
    bi.biXPelsPerMeter = 5000;
    bi.biYPelsPerMeter = 5000;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("file open failed\n");
        return;
    }
    /*这里不直接写fwrite(&bf,sizeof(bf),1,file);原因，
      因为结构体对齐原因，其实第一个bf.bftype并不是占用两个字节，而是4个字节，sizeof
      就是16了，显然不对，bmp固定文件头为14个字节。故按如下方式处理。
    */
    fwrite(&bf.bftype,2,1,file);
    fwrite((&bf.bftype)+2,12,1,file);
    fwrite(&bi,sizeof(bi),1, file);
    fwrite(rgb,width*height*3,1,file);
    fclose(file);
}

int main()
{
  /*声明数组，存储yuyv数据和rgb数据*/
  /*因已知格式为yuyv，640*480.这里就直接声明两个数组，分别为640*480*2 和 640*480*3大小*/
  unsigned char yuyv[WIDTH*HEIGHT*2],rgb[WIDTH*HEIGHT*3];
  /*打开yuyv文件并读取*/
  FILE *fd_yuv = fopen(YUYV_FILE,"r");
  if(fd_yuv == NULL){
    printf("open yuyv picture failed\n");
    return -1;
  }
  fread(yuyv,1,WIDTH*HEIGHT*2,fd_yuv);
  fclose(fd_yuv);
  /*yuyv转rgb格式*/
  yuyv_to_rgb(yuyv,rgb,WIDTH,HEIGHT);
  /*rgb转为bmp存储到文件*/
  SaveBmp(BMP_FILE,rgb,WIDTH,HEIGHT);
  return 0;
}
