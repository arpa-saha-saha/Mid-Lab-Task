#include <GLUT/glut.h>
#include <iostream>
using namespace std;

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

//////////////////// DDA LINE ////////////////////
void DDA(int x1,int y1,int x2,int y2)
{
    float dx=x2-x1;
    float dy=y2-y1;

    int steps = abs(dx)>abs(dy)?abs(dx):abs(dy);

    float xinc = dx/steps;
    float yinc = dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps;i++)
    {
        putPixel(x,y);
        x+=xinc;
        y+=yinc;
    }
}

//////////////////// BRESENHAM LINE ////////////////////
void Bresenham(int x1,int y1,int x2,int y2)
{
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);

    int sx = (x1<x2)?1:-1;
    int sy = (y1<y2)?1:-1;

    int err = dx-dy;

    while(true)
    {
        putPixel(x1,y1);

        if(x1==x2 && y1==y2)
            break;

        int e2=2*err;

        if(e2>-dy)
        {
            err-=dy;
            x1+=sx;
        }

        if(e2<dx)
        {
            err+=dx;
            y1+=sy;
        }
    }
}

//////////////////// MIDPOINT CIRCLE ////////////////////
void drawCirclePoints(int xc,int yc,int x,int y)
{
    putPixel(xc+x,yc+y);
    putPixel(xc-x,yc+y);
    putPixel(xc+x,yc-y);
    putPixel(xc-x,yc-y);
    putPixel(xc+y,yc+x);
    putPixel(xc-y,yc+x);
    putPixel(xc+y,yc-x);
    putPixel(xc-y,yc-x);
}

void MidpointCircle(int xc,int yc,int r)
{
    int x=0;
    int y=r;
    int d=1-r;

    while(x<=y)
    {
        drawCirclePoints(xc,yc,x,y);

        if(d<0)
            d=d+2*x+3;
        else
        {
            d=d+2*(x-y)+5;
            y--;
        }
        x++;
    }
}

//////////////////// DRAW SCENE ////////////////////
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2);

    // Flag border (Bresenham)
    Bresenham(200,350,400,350);
    Bresenham(400,350,400,250);
    Bresenham(400,250,200,250);
    Bresenham(200,250,200,350);

    // Flag circle (Midpoint)
    MidpointCircle(290,300,40);

    // Flag pole (DDA)
    DDA(200,350,200,150);

    // Shaheed Minar base (Bresenham)
    Bresenham(450,200,650,200);
    Bresenham(650,200,650,220);
    Bresenham(650,220,450,220);
    Bresenham(450,220,450,200);

    // Pillars
    Bresenham(470,220,470,300);
    Bresenham(490,220,490,300);

    Bresenham(520,220,520,330);
    Bresenham(540,220,540,330);

    Bresenham(570,220,570,300);
    Bresenham(590,220,590,300);

    // Flowers (extra element)
    MidpointCircle(500,180,8);
    MidpointCircle(520,180,8);

    // Cloud (extra element)
    MidpointCircle(150,420,20);
    MidpointCircle(170,420,20);
    MidpointCircle(190,420,20);

    glFlush();
}

void init()
{
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,800,0,600);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(800,600);
    glutCreateWindow("Bangladesh Tribute Scene");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}