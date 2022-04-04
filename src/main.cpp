// OpenGL libraries:
#include <GL/glew.h>
#include <GL/glut.h>

#include "render.h"

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  renderspace::initialize();
  return 0;
}
