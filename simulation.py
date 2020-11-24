#!/usr/bin/env python3

from flask import Flask, render_template, Response
import cv2
import numpy as np
import time

class VideoCamera(object):
    def __init__(self):
        self.color = 0
    
    def __del__(self):
        self.video.release()
    
    def get_frame(self):

        # 生成200 x 200的图片
        image = np.zeros((200, 200, 3), np.uint8)
        # 填充颜色
        image.fill(self.color)

        # 更新下次颜色
        self.color += 2
        if self.color > 255:
            self.color = 0

        # 每秒钟更新10次
        time.sleep(0.1)

        # 因为opencv读取的图片并非jpeg格式，因此要用motion JPEG模式需要先将图片转码成jpg格式图片
        ret, jpeg = cv2.imencode('.jpg', image)
        return jpeg.tobytes()

app = Flask(__name__)

@app.route('/')  # 主页
def index():
    # jinja2模板，具体格式保存在index.html文件中
    return render_template('index.html')

def gen(camera):

    while True:
        frame = camera.get_frame()

        #使用generator函数输出视频流， 每次请求输出的content类型是image/jpeg
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')

@app.route('/video_feed')  # 这个地址返回视频流响应
def video_feed():
    return Response(gen(VideoCamera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')   

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, port=5000)  

