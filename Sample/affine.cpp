/*
*多边形的二维仿射变换
*
*/
#include<iostream>
#include<gl\glut.h>
#include<cmath>
using namespace std;
struct point{
	double x;
	double y;
};
void PolygonD(struct point p[],int poly){//绘制多边形
	glFrontFace(GL_CCW);//设置逆时针方向为正面
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glBegin(GL_POLYGON);
	for(int i=0;i<poly;i++){
		glVertex2d(p[i].x,p[i].y);
	}
	glEnd();
}

void Translation(struct point p[],double x,double y,int poly){//平移变换
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=p[i].x+x;
		p1[i].y=p[i].y+y;
	}
	PolygonD(p1,poly);
	delete(p1);
}

void Scaling(struct point p[],double x,double y,int poly){//比例变换
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=p[i].x*x;
		p1[i].y=p[i].y*y;
	}
	PolygonD(p1,poly);
	delete(p1);
}

void Rotation(struct point p[],double angle,double x,double y,int poly){//旋转变换,绕点(x,y)旋转
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=(p[i].x-x)*cos(angle)-(p[i].y-y)*sin(angle)+x;
		p1[i].y=(p[i].x-x)*sin(angle)+(p[i].y-y)*cos(angle)+y;
	}
	PolygonD(p1,poly);
	delete(p1);
}
void Symmetry(struct point p[],int type,int poly){//对称变换；type=0(关于x轴对称)，type=1(关于y轴对称),type=2(关于原点对称);type=3(关于y=x对称),type=4(关于y=-x对称)
	struct point *p1=new point[poly];
	switch(type){
	case 0:
		for(int i=0;i<poly;i++){
			p1[i].x=p[i].x;
			p1[i].y=-p[i].y;
	}
		break;
	case 1:
		for(int i=0;i<poly;i++){
			p1[i].x=-p[i].x;
			p1[i].y=p[i].y;
	}
		break;
	case 2:
		for(int i=0;i<poly;i++){
	    p1[i].x=-p[i].x;
		p1[i].y=-p[i].y;
	}
		break;
	case 3:
		for(int i=0;i<poly;i++){
		p1[i].x=p[i].y;
		p1[i].y=p[i].x;
	}
		break;
	case 4:
		for(int i=0;i<poly;i++){
		p1[i].x=-p[i].y;
		p1[i].y=-p[i].x;
	}
		break;
	}
	PolygonD(p1,poly);
	delete(p1);
}
void Dislocation(struct point p[],int x,int y,int poly){
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=p[i].x+y*p[i].y;
		p1[i].y=x*p[i].x+p[i].y;
	}
	PolygonD(p1,poly);
	delete(p1);
}
void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void ChangeSize(int w,int h){
	glViewport(0,0,400,400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f,20.0f,0.0f,20.0f);//设置投影
}

void Display(){
	struct point p[4]={{4,1},{7,3},{7,7},{1,4}};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	
	PolygonD(p,4);
	//Translation(p,5,0,4);
	//Scaling(p,2,2,4);
	//Rotation(p,90,5,4,4);
	//Symmetry(p,2,4);
	//Dislocation(p,0,4,4);
	glutSwapBuffers();
}

int main(int argc,char *argv[]){
	  glutInit(&argc,argv);
	  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	  glutInitWindowSize(400,300);
	  glutInitWindowPosition(100,100);
	  glutCreateWindow("仿射变换");
	  glutDisplayFunc(Display);
	  glutReshapeFunc(ChangeSize);
	  Initial();
	  glutMainLoop();
}