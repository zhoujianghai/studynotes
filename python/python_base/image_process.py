#!/usr/local/bin/python

import Image

def resize_img(path):
    img = Image.open(path)
    (x,y) = img.size
    print x,y
    new_x = x / 2
    new_y = y * new_x / x
    #Image.ANTIALIAS:反锯齿，提高图像画质
    out = img.resize((new_x,new_y),Image.ANTIALIAS)
    out.save(path)


if __name__ == '__main__':
    path = '/home/zhoujh/1.jpg'
    resize_img(path)
