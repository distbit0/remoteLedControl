import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
import cv2

picName = "LEDPic.jpg"
fromEmail = "a@b.c"

import tornado.ioloop
import tornado.web

class googleVerify(tornado.web.RequestHandler):
    def get(self):
        self.write(open("google68ee9615074f8719.html").read())

class home(tornado.web.RequestHandler):
    def get(self):
        self.write(open("html.html").read())

class css(tornado.web.RequestHandler):
    def get(self):
        self.set_header("Content-Type", "text/css")
        self.write(open("css.css").read())
        
class js(tornado.web.RequestHandler):
    def get(self):
        self.write(open("js.js").read())

class LEDPicSender(tornado.web.RequestHandler):
    def get(self):
        failed = False
        toEmail = self.get_argument("email")
        if toEmail and "@" in toEmail and "." in toEmail:
            
            camera_port = 0
            camera = cv2.VideoCapture(camera_port)
            return_value, image = camera.read()
            cv2.imwrite(picName, image)
            del(camera)  # so that others can use the camera as soon as possible 
      
            msg = MIMEMultipart()
            msg['Subject'] = 'Picture of LED'
            msg['From'] = fromEmail
            msg["To"] = toEmail
            msg.attach(MIMEText("Picture of LED is attached"))
            image = MIMEImage(open(picName, 'rb').read(), name=picName)
            msg.attach(image)
            try:
                emailObject = smtplib.SMTP_SSL("smtp.gmail.com", 465)
                emailObject.login(fromEmail, "pswd")
                emailObject.sendmail(fromEmail, toEmail, msg.as_string())
                emailObject.quit()
            except:
                failed = True
        else:
            failed = True
        if not failed:
            self.write("Sent")
        else:
            self.write("Failed")    


if __name__ == "__main__":
    app = tornado.web.Application([
        (r"/sendpic", LEDPicSender), (r"/", home), (r"/css.css", css), (r"/js.js", js), (r"/google68ee9615074f8719.html", googleVerify),
    ])
    app.listen(80)
    tornado.ioloop.IOLoop.current().start()


