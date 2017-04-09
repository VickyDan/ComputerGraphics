#include<gl/glut.h>
int iPointNum=0;
int x1=0,y1=0,x2=0,y2=0;
int winWidth=400,winHeight=300;
int count=0;//记录特殊键按下次数

void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void ChangeSize(int w,int h){
	winWidth=w;
	winHeight=h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	if(iPointNum>=1){
		glBegin(GL_LINES);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
		glEnd();
	}
	glutSwapBuffers();
}
/*
  鼠标实现
*/
void MousePlot(GLint button,GLint action,GLint xMouse,GLint yMouse){
	if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN){
		if(iPointNum==0||iPointNum==2){
			x1=xMouse;
			y1=winHeight-yMouse;
			iPointNum=1;
		}
		else{
			iPointNum=2;
			x2=xMouse;
			y2=winHeight-yMouse;
			glutPostRedisplay();
		}
	}
	if(button==GLUT_RIGHT_BUTTON&&action==GLUT_DOWN){
		iPointNum=0;
		glutPostRedisplay();
	}
}


void PassiveMouseMove(GLint xMouse,GLint yMouse){
	if(iPointNum==1){
		x2=xMouse;
		y2=winHeight-yMouse;
		glutPostRedisplay();
	}
}
/*
  键盘实现
*/
void Key(unsigned char key,int x,int y){
	switch(key){
	case 'p':
		if(iPointNum==0||iPointNum==2){
			x1=x;
			y1=winHeight-y;
			iPointNum=1;
			count=0;
		}
		else{
			iPointNum=2;
			x2=x;
			y2=winHeight-y;
			glutPostRedisplay();
		}
		break;
	default:break;
	}
}
//
void SpecialKey(GLint key,GLint x,GLint y){
	if(iPointNum==2){
		if(count==0){
		if(key==GLUT_KEY_UP){
			y2=winHeight-y1-10;
		}
		if(key==GLUT_KEY_DOWN){
			y2=winHeight-y1+10;
		}
		if(key==GLUT_KEY_LEFT){
			x2=x1-10;
		}
		if(key==GLUT_KEY_RIGHT){
			x2=x1+10;
		}
		}
		else{
			if(key==GLUT_KEY_UP){
			y2+=10;
		}
		if(key==GLUT_KEY_DOWN){
			y2-=10;
		}
		if(key==GLUT_KEY_LEFT){
			x2-=10;
		}
		if(key==GLUT_KEY_RIGHT){
			x2+=10;
		}
		}
		count++;
		glutPostRedisplay();
	}
}
int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,100);
	glutCreateWindow("橡皮筋技术");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	//glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	//glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}