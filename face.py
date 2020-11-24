#!/usr/bin/env python3

from flask import Flask, render_template, Response
import cv2

class VideoCamera(object):
    def __init__(self):
        # 通过opencv获取实时视频流
        self.video = cv2.VideoCapture(0) 
        self.classfier = cv2.CascadeClassifier("haarcascade_frontalface_alt.xml")
        self.color = (0, 255, 0)
    
    def __del__(self):
        self.video.release()
    
    def get_frame(self):
        success, image = self.video.read()

        num = 0
        grey = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  #将当前桢图像转换成灰度图像
        #人脸检测，1.2和2分别为图片缩放比例和需要检测的有效点数
        faceRects = self.classfier.detectMultiScale(grey, scaleFactor = 1.2, minNeighbors = 3, minSize = (32, 32))
        if len(faceRects) > 0:          #大于0则检测到人脸
            for faceRect in faceRects:  #单独框出每一张人脸
                num += 1
                x, y, w, h = faceRect

                #画出矩形框
                cv2.rectangle(image, (x - 10, y - 10), (x + w + 10, y + h + 10), self.color, 2)

                #显示当前捕捉到了多少人脸图片了，这样站在那里被拍摄时心里有个数，不用两眼一抹黑傻等着
                font = cv2.FONT_HERSHEY_SIMPLEX
                cv2.putText(image, 'num:%d' % (num), (x + 30, y + 30), font, 1, (255, 0, 255), 4)

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

