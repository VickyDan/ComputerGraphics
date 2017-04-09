/*
* 分别使用DAA算法、Bresenham和中点Bresenham算法扫描转换直线段
*/
#include<gl\glut.h>
#include<cmath>
void DAALine(int x0,int y0,int x1,int y1){//DAA算法扫描转换直线段
	int dx,dy,epsl,k;
	float x,y,xIncre,yIncre;
	dx=x1-x0;
	dy=y1-y0;
	x=x0;
	y=y0;
	if(abs(dx)>abs(dy)){
		epsl=abs(dx);
	}
	else{
		epsl=abs(dy);
	}
	xIncre=dx/(float)epsl;
	yIncre=dy/(float)epsl;
	for(k=0;k<=epsl;k++){

		glBegin(GL_POINTS);
		glVertex2i((int)(x+0.5),(int)(y+0.5));
		glEnd();
		x+=xIncre;
		y+=yIncre;
	}
}

void MidBresenhamLine(int x0,int y0,int x1,int y1){//中点Bresenham算法扫描转换直线段
	int dx,dy,d,UpIncre,DownIncre,x,y;
	dx=x1-x0;
	dy=y1-y0;
	d=dx-2*dy;
	x=x0;
	y=y0;
	UpIncre=2*dx-2*dy;
	DownIncre=-2*dy;
	while(x<=x1){
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		if(d<0){
			x=x+1;
			y=y+1;
			d+=UpIncre;
		}else{
			x=x+1;
			d+=DownIncre;
		}
	}
}

void BresenhamLine(int x0,int y0,int x1,int y1){//Bresenham算法扫描转换直线段
	int dx,dy,e,x,y;
	dx=x1-x0;
	dy=y1-y0;
	x=x0;
	y=y0;
	e=-dx;
	while(x<=x1){
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		x++;
		e=e+2*dy;
		if(e>0){
			y++;
			e=e-2*dx;
		}
	}
}

void CirclePoint(int x,int y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glVertex2i(y,x);
	glVertex2i(-y,x);
	glVertex2i(-x,y);
	glVertex2i(-x,-y);
	glVertex2i(-y,-x);
	glVertex2i(y,-x);
	glVertex2i(x,-y);
	glEnd();
}

void MidBresenhamCircle(int r){//中点Bresenham算法扫描转换圆
	int d,x,y;
	d=1-r;
	x=0;
	y=r;
	while(x<y){
		CirclePoint(x,y);
		x++;
		if(d<0){
			d=d+2*x+3;
		}else{
			d=d+2*(x-y)+5;
			y--;
		}
	}
}

void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void ChangeSize(int w,int h){
	glViewport(0,0,400,300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20.0f,20.0f,-15.0f,15.0f);
}
void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(5);
	//DAALine(0,0,8,6);
	//MidBresenhamLine(0,0,8,6);
	//BresenhamLine(0,0,8,6);
	MidBresenhamCircle(8);
	glutSwapBuffers();
}

int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	//glutCreateWindow("DAA算法扫描转换直线段");
	//glutCreateWindow("中点Bresenham算法扫描转换直线段");
	//glutCreateWindow("Bresenham算法扫描转换直线段");
	glutCreateWindow("中点Bresenham算法扫描转换圆");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	Initial();
	glutMainLoop();
	return 0;
}