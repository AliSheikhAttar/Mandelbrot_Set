from PIL import Image, ImageDraw
max_iter = 60

def mandel(c):
    z=0
    i=0
    while abs(z) <=4 and i <max_iter:
        z =z*z +c
        i+=1
    return i




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
                color = int(360*(iter/max_iter))
                sat = 100
                if iter < max_iter:
                    value = 100
                else:
                    value = 0
                draw.point([x, y], (color, sat, value))
        im.convert('RGB').save(f'output{i}.png', 'PNG')
        spanx = maxx - minx
        spany = maxy - miny
        minx = minx + spanx/4
        maxx = minx + spanx/2
        miny = miny+spany/4
        maxy = miny + spany/2
def zooming1(zoom,zoomp,maxx,minx,maxy,miny):
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
                color = int(360*(iter/max_iter))
                sat = 100
                if iter < max_iter:
                    value = 100
                else:
                    value = 0
                draw.point([x, y], (color, sat, value))
        im.convert('RGB').save(f'output{i+zoomp}.png', 'PNG')
        spanx = maxx - minx
        spany = maxy - miny
        minx = minx + spanx/4
        maxx = minx + spanx/2
        miny = miny+spany/4
        maxy = miny + spany/2

    
width, height = (600,400)
cx, cy, zoom = -1.04, 0.34, 12
minx, maxx, miny, maxy = (cx-1.5, cx+1.5, cy-1.5, cy+1.5)
zooming(zoom,maxx,minx,maxy,miny)
cx, cy, zoom = -0.74, -0.12, 10
minx, maxx, miny, maxy = (cx-1.5, cx+1.5, cy-1.5, cy+1.5)
zooming1(10,zoom,maxx,minx,maxy,miny)