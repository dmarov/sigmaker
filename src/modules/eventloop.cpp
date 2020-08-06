#include "eventloop.h"
#include <GL/glut.h>
#include <iostream>

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void EventLoop::start(int argc, char **argv) {

    std::string window_name = "FPS";

    glutInit(&argc, argv);

    int screen_width = glutGet(GLUT_SCREEN_WIDTH);
    int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowSize(screen_width, screen_height);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    /* glClearDepth(1.0f); */
    /* glDepthFunc(GL_LEQUAL); */
    /* glShadeModel(GL_SMOOTH); */
    /* glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); */

    int window_id = glutCreateWindow(window_name.c_str());

    glutSetWindowTitle(window_name.c_str());
    glutSetIconTitle(window_name.c_str());
    /* glutFullScreen(); */
    /* glutSetCursor(GLUT_CURSOR_NONE); */
    glutDisplayFunc(&EventLoop::on_display);
    glutReshapeFunc(&EventLoop::on_reshape);
    glutKeyboardFunc(&EventLoop::on_keyboard);
    glutMouseFunc(&EventLoop::on_mouse);
    glutSpecialFunc(&EventLoop::on_special);

    glEnable(GL_DEPTH_TEST);

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.0);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);

    glutMainLoop();

}

void EventLoop::on_display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int i;

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }

    glutSwapBuffers();
}

void EventLoop::on_keyboard(unsigned char key, int x, int y) {

    std::cout << key << " " << x << " " << y <<std::endl;
}

void EventLoop::on_mouse(int button, int state, int x, int y) {

    std::cout << button << " " << state << " " << x << " " << y <<std::endl;
}

void EventLoop::on_special(int key, int x, int y) {

    std::cout << key << " " << x << " " << y <<std::endl;
}


void EventLoop::on_reshape(int width, int height) {

}
