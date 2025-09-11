#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
int x_start,y_start,x_end,y_end;
void myinit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    gluOrtho2D(0,640,0,480);


}
void drawpixel(int x,int y)
{

    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void display(int x_start,int y_start,int x_end,int y_end)
{
    int dx,dy,steps;
    int x_inc,y_inc,x,y;

    dx=x_end-x_start;
    dy=y_end-y_start;

    if(abs(dx)>abs(dy))
    {

        steps=abs(dx);
    }else{
        steps=abs(dy);
    }
    x_inc=dx/steps;
    y_inc=dy/steps;

    x=x_start;
    y=y_start;

    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1,1,1);
    //drawpixel(round(x),round(y));

     for(int k=0;k<steps;k++)
     {
         drawpixel(round(x),round(y));

         x+=x_inc;
         y+=y_inc;


     }
     //

}
void mydisplay()
{

    display(x_start,y_start,x_end,y_end);
    glFlush();
}
int main(int argc,char** argv)
{
    printf("enter the x1,y1,enter the x2,y2");
    scanf("%d %d %d %d",&x_start,&y_start,&x_end,&y_end);


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(100,100);
    glutInitWindowPosition(30,30);
    myinit();
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;


}
