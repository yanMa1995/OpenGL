//#include <gl/glut.h>
//#include <cstdlib>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <fstream>
//#include <cstdio>
//using namespace std;
//
//float angle=10.0;        //��ת�Ƕ�
//int graph;
//
//struct coordinate
//{
//  float x,y,z;
//  coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
//};
//
//// ����ṹ�壬���Ա�ʾ�����λ����ı��Σ�����flag��ʾ
//struct face
//{
//    int facenum;
//    bool flag;
//    int faces[4];
//    face(int facen,int f1,int f2,int f3) : facenum(facen)
//    {
//      // ������
//      faces[0] = f1;
//      faces[1] = f2;
//      faces[2] = f3;
//      flag = false;
//    }
//    face(int facen,int f1,int f2,int f3,int f4) : facenum(facen)
//    {
//      // ���صĹ��캯��->�ı���
//      faces[0] = f1;
//      faces[1] = f2;
//      faces[2] = f3;
//      faces[3] = f4;
//      flag = true;
//    }
//};
//
//int objLoader(const char* filename)
//
//{
//  vector<string*> coord;                                                        // ����obj�ļ���ÿһ����Ϊһ���ַ���
//  vector<coordinate*> vertex;                                                   // �������� v
//  vector<face*> faces;                                                          // ���� f
//  vector<coordinate*> normals;                                                  // ����ķ������� vn
//
//  ifstream in(filename);                                                        // ���ļ�
//
//  if(!in)                                                                       // �ļ���ʧ��
//  {
//    cerr << "Cannot open " << filename << endl;
//    exit(1);
//  }
//
//  char buf[256];                                                                // ���ַ���
//
//  // ���ļ���ÿ�ж��� coord
//  while(!in.eof())
//  {
//    in.getline(buf,256);
//    coord.push_back(new string(buf));                                           // ��ȡ����һ���ַ���ѹ�� coord
//  }
//
//  // ���� coord ��ÿ��Ԫ�أ��ж���������
//  for(int i=0; i<coord.size(); i++)
//  {
//    if((*coord[i])[0] == '#')                                                   // �ַ�����ͷΪ "#"������
//      continue;
//    else if((*coord[i])[0] == 'v' && (*coord[i])[1] == ' ')                     // �����Ƕ�������
//    {
//      float tmpx,tmpy,tmpz;
//      sscanf_s(coord[i] -> c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);           // ��ȡ3��float�ͱ�����tmpx,tmpy,tmpz
//      vertex.push_back(new coordinate(tmpx, tmpy, tmpz));                       // �� tmpx,tmpy,tmpz�ӵ� vertex ����ĩβ
//    }
//    else if((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n')                     // �����Ǳ���ķ�������
//    {
//      float tmpx,tmpy,tmpz;
//      sscanf_s(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);            // ��ȡָ����ʽ�����ݵ�������
//      // c_str()��������һ��ָ������C�ַ�����ָ��, �����뱾string����ͬ.
//      // ����Ϊ����c���Լ��ݣ���c������û��string���ͣ��ʱ���ͨ��string�����ĳ�Ա����c_str()��string����ת����c�е��ַ�����ʽ��
//      normals.push_back(new coordinate(tmpx, tmpy, tmpz));
//    }
//    else if((*coord[i])[0] == 'f')                                              // �����Ǳ���
//    {
//      int a,b,c,d,e;
//			if(count(coord[i]->begin(),coord[i]->end(),' ')==3)	                      // ����face�������Σ���3�ո�
//			{
//		    sscanf_s(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
//				faces.push_back(new face(b,a,c,d));
//			}
//      else                                                                      // ����face���ı��Σ���4�ո�
//      {
//				sscanf_s(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
//				faces.push_back(new face(b,a,c,d,e));
//			}
//		}
//	}
//
//  // ���ÿ��Ԫ�صĸ���
//  cout<<"v: "<<vertex.size()<<endl;
//  cout<<"vn: "<<normals.size()<<endl;
//  cout<<"f: "<<faces.size()<<endl;
//
//  // ��ͼ
//	int num = 0;	                                                                // �б�id
//	num=glGenLists(1);	                                                          // ����һ�����ص��б�id
//	glNewList(num,GL_COMPILE);                                                    // ��ʾ�б���ԭ��
//
//	for(int i=0;i<faces.size();i++)
//	{
//		if(faces[i]->flag)	                                                        // �������ı��ξͻ��ı���
//		{
//			glBegin(GL_QUADS);
//				//basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
//				//I subtract 1 because the index start from 0 in C++
//				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
//				// ������
//				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
//				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
//				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
//				glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
//			glEnd();
//		}
//    else
//    {
//			glBegin(GL_TRIANGLES);
//				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
//				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
//				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
//				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
//			glEnd();
//		}
//	}
//	glEndList();
//
//	// �����ڴ�
//	for(int i=0;i<coord.size();i++)
//		delete coord[i];
//	for(int i=0;i<faces.size();i++)
//		delete faces[i];
//	for(int i=0;i<normals.size();i++)
//		delete normals[i];
//	for(int i=0;i<vertex.size();i++)
//		delete vertex[i];
//
//	return num;
//}
//
//void reshape(int w, int h)
//{
//  GLfloat nRange = 80.0f;
//  // Prevent a divide by zero
//  if(h == 0)
//    h = 1;
//
//  // Set Viewport to window dimensions
//  glViewport(0, 0, w, h);
//
//  // Reset coordinate system
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//
//  // Establish clipping volume (left, right, bottom, top, near, far)
//  if (w <= h)
//    glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
//  else
//    glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
//
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//}
//
//void key(unsigned char key, int x, int y)
//{
//    // ��ESC�˳�
//    if(key == 27)
//    {
//        cout<<"exit"<<endl;
//        exit(0);
//    }
//}
//
//void init()
//{
//  glClearColor(0.0,0.0,0.0,1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	// gluPerspective(45,640.0/480.0,1.0,500.0);
//	glMatrixMode(GL_MODELVIEW);
//	glEnable(GL_DEPTH_TEST);
//  graph = objLoader("test.obj");
//	glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
//  GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};                              // ������ɫΪ��ɫ
//  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);                                 // ��Դ�е�ɢ���ǿ��
//  glClearColor(1.0,1.0,1.0,0.0);                                                // ������ɫ
//}
//
//void display()
//{
//  angle += 0.01;
//  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//  glLoadIdentity();
//  float posLight0[]={-1.0,1.0,-2.0,1.0};                                        // ����λ��
//  glLightfv(GL_LIGHT0,GL_POSITION,posLight0);                                   // ָ����0�Ź�Դ��λ��      
//  cout << "14" << endl;// ���浱ǰ����
//  glScalef(10.0f, 10.0f, 10.0f);                                                // ����ģ��
//  glTranslatef(0.0,0.0,-5.0);
//  glRotatef(angle,0.0,0.0,1.0);
//	glCallList(graph);                                                            // ִ����ʾ�б�
//	glPopMatrix();                                                                // ����ջ���ľ���
//	glutSwapBuffers();     // ��������������ָ��
//}
//
//int main(int argc,char** argv)
//{
//  glutInit(&argc, argv);
//  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//  // ���ó���Ĵ��ڴ�С
//  GLint windowWidth = 800;
//  GLint windowHeight = 600;
//  glutInitWindowSize(windowWidth, windowHeight);
//  // ��ȡ��Ļ�Ŀ�͸�
//  GLint SCREEN_WIDTH=glutGet(GLUT_SCREEN_WIDTH);
//  GLint SCREEN_HEIGHT=glutGet(GLUT_SCREEN_HEIGHT);
//  glutInitWindowPosition((SCREEN_WIDTH-windowWidth)/2,(SCREEN_HEIGHT-windowHeight)/2);
//  glutCreateWindow("objLoader");
//  init();
//  glutKeyboardFunc(key);
//  glutDisplayFunc(display);
//  glutReshapeFunc(reshape);
//  glutMainLoop();
//	return 0;
//}
