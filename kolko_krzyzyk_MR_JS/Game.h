#pragma once

#include <math.h>
#include <stdlib.h>
#include "DrawObjects.h"
#include <SFML/Network.hpp>
#include <iostream>
#include "TCP.h"

#define PI 3.14159f
int winner_looser_matrix[3][3];
bool move = false;
bool somebody_wins = false;
Draw* draw = new Draw();


void init(void)
{
  glClearColor(1, 1, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  move = false;
  somebody_wins = false;

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      winner_looser_matrix[i][j] = -1;
    }
  }
}


void X_or_O(int x, int y, int i, int j)
{
  if (!move)
  {
    if (winner_looser_matrix[i][j] == -1)
    {
      draw->Draw_X(x, y);
      winner_looser_matrix[i][j] = 2;
      move = true;
    }
  }
  else
  {
    if (winner_looser_matrix[i][j] == -1)
    {
      draw->Draw_O(x, y);
      winner_looser_matrix[i][j] = 1;
      move = false;
    }
  }
}

void SendTheMatrix()
{
  if (who == 's')
  {
    if (Socket_server.send(winner_looser_matrix, sizeof(winner_looser_matrix)) != sf::Socket::Done)
      return;
  }
  else
  {
    if (Socket_client.send(winner_looser_matrix, sizeof(winner_looser_matrix)) != sf::Socket::Done)
      return;
  }
}

void ReceiveTheMatix()
{
  int winner_looser_matrix_copy[3][3];// = winner_looser_matrix;
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      winner_looser_matrix_copy[i][j] = winner_looser_matrix[i][j];
    }
  }

  if (who == 's')
  {
    if (Socket_server.receive(winner_looser_matrix, sizeof(winner_looser_matrix), received_server) != sf::Socket::Done)
      return;
  }
  else
  {
    if (Socket_client.receive(winner_looser_matrix, sizeof(winner_looser_matrix), received_client) != sf::Socket::Done)
      return;
  }

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (winner_looser_matrix_copy[i][j] != winner_looser_matrix[i][j])
      {
        X_or_O(115,115,i,j);
      }
    }
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
  int if_empty_matrix = 0;

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
      draw->DrawString(GLUT_BITMAP_HELVETICA_18, "Mr. O wins", 430, 580);
      somebody_wins = true;
      break;
    }
    else if (iterator_x_w == 3 || iterator_x_k == 3 || iterator_x_b == 3 || iterator_x_s == 3)
    {
      draw->DrawString(GLUT_BITMAP_HELVETICA_18, "Mr. X wins", 430, 580);
      somebody_wins = true;
      break;
    }
    iterator_o_w = 0;
    iterator_x_w = 0;
    iterator_x_k = 0;
    iterator_o_k = 0;
  }

  if (!somebody_wins)
  {
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (winner_looser_matrix[i][j] == 1 || winner_looser_matrix[i][j] == 2)
        {
          ++if_empty_matrix;
        }
      }
    }

    if (if_empty_matrix == 9)
    {
      draw->DrawString(GLUT_BITMAP_HELVETICA_18, "Draw", 450, 580);
    }
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
      SendTheMatrix();
    }
    else if (x > 200 && (600 - y) > 40 && x < 400 && (600 - y) < 200)
    {
      X_or_O(300, 115, 2, 1);
      SendTheMatrix();
    }
    else if (x > 400 && (600 - y) > 40 && x < 560 && (600 - y) < 200)
    {
      X_or_O(485, 115, 2, 2);
      SendTheMatrix();
    }
    else if (x > 40 && (600 - y) > 200 && x < 200 && (600 - y) < 400)
    {
      X_or_O(115, 300, 1, 0);
      SendTheMatrix();
    }
    else if (x > 200 && (600 - y) > 200 && x < 400 && (600 - y) < 400)
    {
      X_or_O(300, 300, 1, 1);
      SendTheMatrix();
    }
    else if (x > 400 && (600 - y) > 200 && x < 560 && (600 - y) < 400)
    {
      X_or_O(485, 300, 1, 2);
      SendTheMatrix();
    }
    else if (x > 40 && (600 - y) > 400 && x < 200 && (600 - y) < 560)
    {
      X_or_O(115, 485, 0, 0);
      SendTheMatrix();
    }
    else if (x > 200 && (600 - y) > 400 && x < 400 && (600 - y) < 560)
    {
      X_or_O(300, 485, 0, 1);
      SendTheMatrix();
    }
    else if (x > 400 && (600 - y) > 400 && x < 560 && (600 - y) < 560)
    {
      X_or_O(485, 485, 0, 2);
      SendTheMatrix();
    }
    else if (x > 255 && (600 - y) > 580 && x < 345 && (600 - y) < 600)
    {
      init();
      glClearColor(1, 1, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT);
      check = false;
      /*if (who == 's')
      {

      }
      else
      {

      }
      */
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

  glutPostRedisplay();
}


void display(void)
{
  draw->DrawLines();
  ReceiveTheMatix();
  draw->DrawString(GLUT_BITMAP_HELVETICA_18, "Mr. X starts", 5, 580);
  draw->DrawString(GLUT_BITMAP_HELVETICA_18, "Play again", 258, 580);

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