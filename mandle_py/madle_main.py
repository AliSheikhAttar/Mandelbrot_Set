from configparser import MAX_INTERPOLATION_DEPTH
from PIL import Image, ImageDraw
import math
max_iter = 88

def mandel(c):
    z=0
    i=0
    while abs(z) <=28 and i <max_iter:
        z =z*z +c
        i+=1
    return i


width, height = (1000,800)
cx, cy, zoom = -0.74384935657398, -0.13170134084746293 ,20
minx, maxx, miny, maxy = (cx-1.5, cx+1.5, cy-1, cy+1)
def zooming(zoom,maxx,minx,maxy,miny):
    for i in range(zoom):
        im = Image.new('HSV', (width, height), (0,0,0))
        draw = ImageDraw.Draw(im)   
        x_pixelunit = (maxx - minx) / width
        y_pixelunit = (maxy-miny) / height



        for x in range(width):
            for y in range(height):
                xx = minx +x*x_pixelunit
                yy = miny +y*y_pixelunit
                c = complex(xx, yy)
                iter = mandel(c)
                # print(iter/max_iter)
                color = 60*(int(100*(iter/max_iter))%6)
                sat = 100
                if iter < max_iter:
             
                    value = 88
                else:
          
                    value = 3

                draw.point([x, y], (color, sat, value))
        im.convert('RGB').save(f'yutput{i}.png', 'PNG')

        spanx = maxx - minx
        spany = maxy - miny

        minx = minx + spanx/4
        maxx = minx + spanx/2

        miny = miny + spany/4
        maxy = miny + spany/2
        # spanx = maxx - minx
        # spany = maxy - miny
        # minx = minx + spanx/6
        # maxx = minx + 2*spanx/3
        # miny = miny+spany/6
        # maxy = miny + 2*spany/3
        # maxx *= math.cos(math.pi/6)
        # minx *= math.cos(math.pi/6)
        # maxy *= math.cos(math.pi/6)
        # miny *= math.cos(math.pi/6)
    return minx,maxx,miny,maxy

def panning(iter_pan,maxx,minx,maxy,miny):
    for i in range(iter_pan):
        im = Image.new('HSV', (width, height), (0,0,0))
        draw = ImageDraw.Draw(im)   
        x_pixelunit = (maxx - minx) / width
        y_pixelunit = (maxy-miny) / height



        for x in range(width):
            for y in range(height):
                xx = minx +x*x_pixelunit + i*x_pixelunit*5
                yy = miny +y*y_pixelunit + i*y_pixelunit*5
                c = complex(xx, yy)
                iter = mandel(c)
                if iter < max_iter/2:
                    color = int(160*((iter/max_iter)*2))
                else :
                    color = int(160*((iter/max_iter)))
                sat = 100
                if iter < max_iter:
             
                    value = int((iter/max_iter)*100)
                else:
          
                    value = 100

                draw.point([x, y], (color, sat, value))
        im.convert('RGB').save(f'zutput{i}.png', 'PNG')


def rotating(max_deg,maxx,minx,maxy,miny):
    for i in range(0,max_deg):
        im = Image.new('HSV', (width, height), (0,0,0))
        draw = ImageDraw.Draw(im)   
        x_pixelunit = (maxx - minx) / width
        y_pixelunit = (maxy-miny) / height
        xx =1
        yy = 1

        for x in range(width):
            for y in range(height):
                xx = minx +x*x_pixelunit
                yy = miny +y*y_pixelunit
                r = (xx**2+yy**2)**0.5
                unit = (i/9)*math.pi

                if xx<0 and yy<0:
                    tetha = math.pi+math.atan(abs(yy)/abs(xx))
                elif xx<0 and yy>0:
                    tetha = math.pi - math.atan(abs(yy)/abs(xx))
                elif xx>0 and yy<0:
                    tetha = 2*math.pi-math.atan(abs(yy)/abs(xx))
                else:
                    tetha = math.atan(abs(yy)/abs(xx))

                xx = r*(math.cos(tetha+unit))
                yy = r*(math.sin(tetha+unit))

                c = complex(xx, yy)
                iter = mandel(c)
                if iter < max_iter/2:
                    color = 160*(int(6*iter/max_iter))
                else :
                    color = 160*int(6*(iter/max_iter))
                sat = 100
                if iter < max_iter:
             
                    value = int((iter/max_iter)*100)
                else:
          
                    value = 100

                draw.point([x, y], (color, sat, value))
        im.convert('RGB').save(f'zutput{i}.png', 'PNG')



zooming(zoom,maxx,minx,maxy,miny)
minx, maxx, miny, maxy = zooming(zoom,maxx,minx,maxy,miny)




# panx = 0
# pany = 0
# iter_pan = 10
# panning(iter_pan,maxx,minx,maxy,miny)
# max_deg = 10
# rotating(max_deg,maxx,minx,maxy,miny)