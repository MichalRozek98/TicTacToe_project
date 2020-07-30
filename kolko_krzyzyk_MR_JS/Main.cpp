
// BadproG.com
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

/**
* glVertex2f(float x, float y).
* The point (0.0, 0.0) represents the middle of the window (not the top left corner).
* The "2f" suffix means 2 values of float type (x and y).
*/

#define PI 3.14159f
int winner_looser_matrix[3][3];
bool move = false;
bool if_somebody_wins = false;

void init(void)
{
  glClearColor(1, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  winner_looser_matrix[3][3] = { -1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 };
}

void DrawLines()
{
  glBegin(GL_LINES);
  glColor3f(0, 0, 0);

  glVertex2f(210, 30);
  glVertex2f(210, 570);
  glVertex2f(390, 30);
  glVertex2f(390, 570);

  glVertex2f(30, 210);
  glVertex2f(570, 210);
  glVertex2f(30, 390);
  glVertex2f(570, 390);

  glEnd();
}


void Draw_O(int x, int y, int z = 60, int a = 0)
{
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(a, 1, 0, 0);
  glutSolidTorus(60.0, 60.5, 16, 16);
  glPopMatrix();

}

void Draw_X(int x, int y)
{
  glBegin(GL_LINES);
  glColor3f(0, 0, 0);
  glVertex2f(x - 50, y - 50);
  glVertex2f(x + 50, y + 50);
  glVertex2f(x - 50, y + 50);
  glVertex2f(x + 50, y - 50);
  glEnd();
}

void X_or_O(int x, int y, int i, int j)
{
  if (!move)
  {
    Draw_X(x, y);
    winner_looser_matrix[i][j] = 2;
    move = true;
  }
  else
  {
    Draw_O(x, y);
    winner_looser_matrix[i][j] = 1;
    move = false;
  }
}

void WhoIsTheWinner()
{
  int iterator_x_w = 0;
  int iterator_o_w = 0;
  int iterator_x_k = 0;
  int iterator_o_k = 0;
  int iterator_x_b = 0;
  int iterator_o_b = 0;
  int iterator_x_s = 0;
  int iterator_o_s = 0;
  int iterator_move = 0;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (winner_looser_matrix[i][j] == 1) {
        ++iterator_o_w;
      }
      else if (winner_looser_matrix[i][j] == 2) {
        ++iterator_x_w;
      }
      if (winner_looser_matrix[j][i] == 1) {
        ++iterator_o_k;
      }
      else if (winner_looser_matrix[j][i] == 2) {
        ++iterator_x_k;
      }
      ++iterator_move;
    }
    if (winner_looser_matrix[i][i] == 1) {
      ++iterator_o_b;
    }
    else if (winner_looser_matrix[i][i] == 2) {
      ++iterator_x_b;
    }
    if (winner_looser_matrix[i][2 - i] == 1) {
      ++iterator_o_s;
    }
    else if (winner_looser_matrix[i][2 - i] == 2) {
      ++iterator_x_s;
    }

    if (iterator_o_w == 3 || iterator_o_k == 3 || iterator_o_b == 3 || iterator_o_s == 3)
    {
      MessageBox(NULL, "Wygra³ Pan O - ale zaskoczenie", "Info", MB_OK);// | MB_ICONEXCLAMATION);
      break;
    }
    else if (iterator_x_w == 3 || iterator_x_k == 3 || iterator_x_b == 3 || iterator_x_s == 3)
    {
      MessageBox(NULL, "Wygra³ Pan X - niemo¿liwe", "Info", MB_OK);// | MB_ICONEXCLAMATION);
      break;
    }

    iterator_o_w = 0;
    iterator_x_w = 0;
    iterator_x_k = 0;
    iterator_o_k = 0;
  }
}

bool check;
void mouse(int button, int state, int x, int y) {
  WhoIsTheWinner();

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    check = true;
    if (x > 40 && (600 - y) > 40 && x < 200 && (600 - y) < 200)
    {
      X_or_O(115, 115, 2, 0);
    }
    else if (x > 200 && (600 - y) > 40 && x < 400 && (600 - y) < 200)
    {
      X_or_O(300, 115, 2, 1);
    }
    else if (x > 400 && (600 - y) > 40 && x < 560 && (600 - y) < 200)
    {
      X_or_O(485, 115, 2, 2);
    }
    else if (x > 40 && (600 - y) > 200 && x < 200 && (600 - y) < 400)
    {
      X_or_O(115, 300, 1, 0);
    }
    else if (x > 200 && (600 - y) > 200 && x < 400 && (600 - y) < 400)
    {
      X_or_O(300, 300, 1, 1);
    }
    else if (x > 400 && (600 - y) > 200 && x < 560 && (600 - y) < 400)
    {
      X_or_O(485, 300, 1, 2);
    }
    else if (x > 40 && (600 - y) > 400 && x < 200 && (600 - y) < 560)
    {
      X_or_O(115, 485, 0, 0);
    }
    else if (x > 200 && (600 - y) > 400 && x < 400 && (600 - y) < 560)
    {
      X_or_O(300, 485, 0, 1);
    }
    else if (x > 400 && (600 - y) > 400 && x < 560 && (600 - y) < 560)
    {
      X_or_O(485, 485, 0, 2);
    }

    /*int x1 = 120;
    int y1 = 120;

    for (int i = 0; i < 3; ++i)
    {

      y1 = 120;
      for (int j = 0; j < 3; ++j)
      {
        y1 += 180;
        if (i % 3 == 0 && j % 3 == 0)
        {
          //x1 = 115; y1 = 115;
          Draw_X(x1,y1);
        }
        else if (i % 3 == 1 && j % 3 == 1)
        {
          //x1 = 300; y1 = 300;
          Draw_X(x1, y1);
        }
        else if (i % 3 == 2 && j % 3 == 2)
        {
          //x1 = 485; y1 = 485;
          Draw_X(x1, y1);
        }
      }
      x1 += 180;*/
  }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    glClearColor(1, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    check = false;
  }

  glutPostRedisplay();
}

void display(void)
{
  DrawLines();

  //glEnd();
  glFlush();

}

void resize(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}






int main(int argc, char** argv) {
  glutInit(&argc, argv);
  //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Game");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMainLoop();


  return 0;
}