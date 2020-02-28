#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<string.h>

int mat[20][3];
float trans[3][3],ans[20][3];
int dx,dy,pos,neg,X1,X2,Y1,Y2,sdx,sdy,tx,ty;             //pos=positive constant   neg=negitive constant  s=sign 
float X=90,Y=90;

typedef struct pixel
{
     GLubyte r;
     GLubyte g;
     GLubyte b;

}pixel;
pixel b_clr,f_clr;

void initialize()
{
	int Y=90;	
	for(int i=0;i<10;i+=2)
	{
		mat[i][0]=90;
		mat[i][1]=Y;
		mat[i][2]=1;
		
		mat[i+1][0]=210;
		mat[i+1][1]=Y;
		mat[i+1][2]=1;
		
		Y+=30;
	}
	
	int X=90;	
	for(int i=10;i<20;i+=2)
	{
		mat[i][0]=X;
		mat[i][1]=90;
		mat[i][2]=1;
		
		mat[i+1][0]=X;
		mat[i+1][1]=210;
		mat[i+1][2]=1;
		
		X+=30;
	}
	
	float root2 = 1/(sqrt(2));
	
	trans[0][0]=trans[0][1]=trans[1][1]=root2;
	trans[1][0]=-root2;
	trans[0][2]=trans[1][2]=0;
	
	tx=mat[0][0];
	ty=mat[0][1];
	
	trans[2][0]=((ty-tx)*root2) + tx;
	trans[2][1]=((-ty-tx)*root2) + ty;
	trans[2][2]=1;
	
	for(int i=0;i<20;i++)
	{
		
		for(int j=0;j<3;j++)
		{	
			ans[i][j]=0;
			
			for(int k=0;k<3;k++)
				ans[i][j] += mat[i][k]*trans[k][j];
		}
	}
	
	for(int i=0;i<20;i++)
		printf("%f %f %f \n",ans[i][0],ans[i][1],ans[i][2]);
	
}

int sign(int a,int b)
{
      if( (b-a)>0 )
            return 1;
      
      else if( (b-a)<0 )
            return -1;
}

void bresenham(int x1,int y1,int x2,int y2)
{
   dx=abs(x2-x1);
   dy=abs(y2-y1);   
            
   if(dy<=dx)
   {
      
      int x=x1,y=y1;
      
      sdx=sign(x1,x2);                            //assigning constants
      sdy=sign(y1,y2);
      
      pos=2*dy-2*dx;
      neg=2*dy;
      
      int p;     
      p=2*dy-dx;                          //p0
      
      glBegin(GL_POINTS);
      glVertex2d(x,y);
      
      for(int i=0;i<dx;i++)
      {
            if(p<0)
            {                          
                  x=x+sdx;                                                      
                  glVertex2d(x,y);                  
                  p=p+neg;      
            }
            
            else if(p>0)
            {
                  x=x+sdx;
                  y=y+sdy;                                  
                  glVertex2d(x,y);                  
                  p=p+pos;               
            }
      }
      
      glEnd();
	glFlush();
      
      
   }
   
   else if(dx<dy)
   {
      int x=x1,y=y1;
        
      sdy=sign(y1,y2);
      sdx=sign(x1,x2);
      pos=2*dx-2*dy;
      neg=2*dx;                     //assigning constants
      
      int p;     
      p=2*dx-dy;                          //p0
      
      glBegin(GL_POINTS);
      glVertex2d(x,y);
      
      for(int i=0;i<dy;i++)
      {
            if(p<0)
            {
                  y=y+sdy;                                  
                  glVertex2d(x,y);                  
                  p=p+neg;
                                                  
            }
            
            else if(p>0)
            {
                  y=y+sdy;
                  x=x+sdx;                  
                  glVertex2d(x,y);                  
                  p=p+pos;
             
            }
      }      
      glEnd();
	glFlush();
   }
}

void boundary_fill(float x,float y)
{
     pixel c;
     glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
     
     if((c.r!=b_clr.r || c.g!=b_clr.g || c.b!=b_clr.b) && (c.r!=f_clr.r || c.g!=f_clr.g || c.b!=f_clr.b))
     {
         
          glBegin(GL_POINTS);
          glVertex2d(x,y);
          glColor3ub(f_clr.r,f_clr.g,f_clr.b);
          glEnd();
          glFlush();
          boundary_fill(x,y+1);
          boundary_fill(x-1,y);
          boundary_fill(x,y-1);
          boundary_fill(x+1,y);
     }
     else return;
} 

void init()
{
	glClearColor(1.0,1.0,1.0,0);
	glColor3i(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	
}

void draw()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	
	int i;
	for(i=0;i<20;i+=2)
		bresenham(ans[i][0],ans[i][1],ans[i+1][0],ans[i+1][1]);
	
	float factor=60/(sqrt(2));
	float add=30/sqrt(2);
	Y=Y+add;
	
	boundary_fill(X,Y);
	
	for(int i=2;i<=6;i++)	
		boundary_fill(X,Y+i*add);
	
	Y=Y+factor;	
	boundary_fill(X+factor,Y);
	boundary_fill(X+factor,Y+factor);
	
	boundary_fill(X-factor,Y);
	boundary_fill(X-factor,Y+factor);
	
	glEnd();
      glFlush();
	
}

int main(int argc, char** argv)
{	
	
	initialize();
	
	b_clr.r=0;
    	b_clr.g=0;
        b_clr.b=0;
        
        f_clr.r=150;
	f_clr.g=150;
	f_clr.b=150;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Chess");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
	}
