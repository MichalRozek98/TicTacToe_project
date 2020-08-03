#include "Game.h"
#include "TCP.h"
#include "UDP.h"


int main(int argc, char** argv) {
  // Choose an arbitrary port for opening sockets
  const unsigned short port = 50001;

  // TCP, UDP or connected UDP ?
  char protocol;
  std::cout << "Do you want to use TCP (t) or UDP (u)? ";
  std::cin >> protocol;

  // Client or server ?
  char who;
  std::cout << "Do you want to be a server (s) or a client (c)? ";
  std::cin >> who;

  if (protocol == 't')
  {
    // Test the TCP protocol
    if (who == 's')
      runTcpServer(port);
    else
      runTcpClient(port);
  }
  else
  {
    // Test the unconnected UDP protocol
    if (who == 's')
      runUdpServer(port);
    else
      runUdpClient(port);
  }

  // Wait until the user presses 'enter' key
  std::cout << "Press enter to exit..." << std::endl;
  std::cin.ignore(10000, '\n');
  std::cin.ignore(10000, '\n');


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