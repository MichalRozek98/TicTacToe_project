#include "Game.h"


int main(int argc, char** argv) {
  
  
  std::cout << "Do you want to be a server (s) or a client (c)? ";
  std::cin >> who;

  if (who == 's')
    runTcpServer(port);
  else
  {
    runTcpClient(port);
  }
  // Wait until the user presses 'enter' key
  /*std::cout << "Press enter to exit..." << std::endl;
  std::cin.ignore(10000, '\n');
  std::cin.ignore(10000, '\n');*/


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
 

  //ReceiveTheMatix();
  return 0;
}