#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

void DDA_lines(float x1, float y1, float x2, float y2);
int x11 = 100;
int y11 = 200;
int x22 = 300;
int y22 = 400; 
void plot(float x, float y){
glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();

}
void rect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	DDA_lines(x1, y1, x2, y2);
	DDA_lines(x2, y2, x3, y3);
	DDA_lines(x3, y3, x4, y4);
	DDA_lines(x4, y4, x1, y1);
	
}

void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0); 
    
   //co ordinate lines
	//DDA_lines(640, 240, 0, 240); //horizonal line
	//DDA_lines(320, 0, 320, 480); //vertical line


	rect(x11, y11, x22, y11, x22, y22, x11, y22);
	rect((x11 + x22)/2, y11, x22, (y11+y22)/2, (x11 + x22)/2, y22, x11, (y11+y22)/2);
	rect((3*x11 + x22)/4, (3*y11 + y22)/4, (x11 + 3*x22)/4, (3*y11 + y22)/4, (x11 + 3*x22)/4, (y11 + 3*y22)/4,(3*x11 + x22)/4, (y11 + 3*y22)/4);
	
    glEnd();
    glFlush();
}


void DDA_lines(float x1, float y1, float x2, float y2){
	
	float dy,dx,step,x,y,k,Xin,Yin;
	
	dx=x2-x1;
	dy=y2-y1;
	 
	if(abs(dx)> abs(dy)){
		step = abs(dx);
	}
	else
		step = abs(dy);
	 
	Xin = dx/step;
	Yin = dy/step;
	 
	x= x1;
	y=y1;
	
	 plot(x,y);
	for (k=1 ;k<=step;k++){
		x= x + Xin;
		y= y + Yin;
		 
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}
	
	glFlush();

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMainLoop();    
    return 0;
}
