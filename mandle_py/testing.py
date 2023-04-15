from configparser import MAX_INTERPOLATION_DEPTH
from PIL import Image, ImageDraw
import math
max_iter = 60

def mandel(c):
    z=0
    i=0
    while abs(z) <=4 and i <max_iter:
        z =z*z +c
        i+=1
    return i


width, height = (600,400)
cx, cy, zoom = -0.8, 0.28,5
minx, maxx, miny, maxy = (cx-2, cx+2, cy-2, cy+2)

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
                    tetha = math.pi/2 + math.atan(abs(yy)/abs(xx))
                elif xx>0 and yy<0:
                    tetha = 1.5*math.pi+math.atan(abs(yy)/abs(xx))
                else:
                    tetha = math.atan(abs(yy)/abs(xx))

                xx = r*(math.cos(tetha))
                yy = r*(math.sin(tetha))

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



# zooming(zoom,maxx,minx,maxy,miny)
# minx, maxx, miny, maxy = zooming(zoom,maxx,minx,maxy,miny)




# panx = 0
# pany = 0
# iter_pan = 10
# panning(iter_pan,maxx,minx,maxy,miny)
max_deg = 10
rotating(max_deg,maxx,minx,maxy,miny)

# zooming(zoom,maxx,minx,maxy,miny)
# minx, maxx, miny, maxy = zooming(zoom,maxx,minx,maxy,miny)




# panx = 0
# pany = 0
# iter_pan = 10
# panning(iter_pan,maxx,minx,maxy,miny)
max_deg = 10
rotating(max_deg,maxx,minx,maxy,miny)