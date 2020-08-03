#include "Game.h"


int main(int argc, char** argv) {
  sf::Thread* thread = 0;

  char who;
  std::cout << "Do you want to be a server (s) or a client (c) ? ";
  std::cin >> who;

  if (who == 's')
    Server();
  else
    Client();

  thread = new sf::Thread(&DoStuff);
  thread->launch();

  while (!quit)
  {
    GetInput();
  }

  if (thread)
  {
    thread->wait();
    delete thread;
  }

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