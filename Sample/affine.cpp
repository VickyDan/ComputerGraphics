/*
*����εĶ�ά����任
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
void PolygonD(struct point p[],int poly){//���ƶ����
	glFrontFace(GL_CCW);//������ʱ�뷽��Ϊ����
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glBegin(GL_POLYGON);
	for(int i=0;i<poly;i++){
		glVertex2d(p[i].x,p[i].y);
	}
	glEnd();
}

void Translation(struct point p[],double x,double y,int poly){//ƽ�Ʊ任
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=p[i].x+x;
		p1[i].y=p[i].y+y;
	}
	PolygonD(p1,poly);
	delete(p1);
}

void Scaling(struct point p[],double x,double y,int poly){//�����任
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=p[i].x*x;
		p1[i].y=p[i].y*y;
	}
	PolygonD(p1,poly);
	delete(p1);
}

void Rotation(struct point p[],double angle,double x,double y,int poly){//��ת�任,�Ƶ�(x,y)��ת
	struct point *p1=new point[poly];
	for(int i=0;i<poly;i++){
		p1[i].x=(p[i].x-x)*cos(angle)-(p[i].y-y)*sin(angle)+x;
		p1[i].y=(p[i].x-x)*sin(angle)+(p[i].y-y)*cos(angle)+y;
	}
	PolygonD(p1,poly);
	delete(p1);
}
void Symmetry(struct point p[],int type,int poly){//�ԳƱ任��type=0(����x��Գ�)��type=1(����y��Գ�),type=2(����ԭ��Գ�);type=3(����y=x�Գ�),type=4(����y=-x�Գ�)
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
	gluOrtho2D(0.0f,20.0f,0.0f,20.0f);//����ͶӰ
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
	  glutCreateWindow("����任");
	  glutDisplayFunc(Display);
	  glutReshapeFunc(ChangeSize);
	  Initial();
	  glutMainLoop();
}