#include<glut.h>  
  
void myDisplay(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT);     //�����ɫ  
    glRectf(-0.5f,-0.5f,0.5f,0.5f);    //��һ������  
    glFlush();   //��ǰ�����������ִ�ж������ڻ���������fflush(stdout)��������  
}  
  
int main(int argc,char* argv[])  
{  
    glutInit(&argc,argv);    //��ʼ��glut,������ã����������仰����  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //������ʾ��ʽ��RGB�������塣��Ȼ����GLUT_INDEX������ɫ GLUT_DOUBLE˫���� 
    glutInitWindowPosition(100,100);   //λ��  
    glutInitWindowSize(400,400);//���ڴ�С  
    glutCreateWindow("��һ��OpenGL����");  //�������ڣ����ñ���  
    glutDisplayFunc(&myDisplay);  // �����ƴ���ʱ����myDisplay����Cocos2d-xˢ֡Draw�еĲ���  
	glutIdleFunc(&myDisplay);
    glutMainLoop();  //��Ϣѭ��  
    return 0;  
} 