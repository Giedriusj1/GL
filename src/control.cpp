#include <cmath>
#include <iostream>
#include <stdlib.h>

#include "control.h"
#include "render.h"

#define ESCAPE_KEY 27

namespace controlspace {

double eyeX = 100;
double eyeY = 100;
double eyeZ = 100;

double objectX = 10;
double objectY = 10;
double objectZ = 10;

double rotationX = 0;
double rotationY = -3.14 / 2;

bool keys[255] = {0};
bool captureMouse = true;
const double pi = 3.14;

double mouseSensitivity = 0.001;
float speedScale = 0.001;

void updateCamera() {
  objectX = eyeX + cos(rotationX) * sin(rotationY);
  objectY = eyeY + cos(rotationY);
  objectZ = eyeZ + sin(rotationY) * sin(rotationX);
}

void mouseRotateCamera(int x, int y) {

  if (keys[(unsigned char)'m'])
    captureMouse = false; // else captureMouse = true;

  if (keys[(unsigned char)'n'])
    captureMouse = true; // else captureMouse = true;

  if (captureMouse) {
    double alphaX = x - window_width / 2;
    double alphaY = (window_height / 2) - y;

    rotationX -= alphaX * mouseSensitivity;
    rotationY -= alphaY * mouseSensitivity;

    // if(rotationY > -0.0001){rotationY = -0.0001;}
    // if(rotationY < -pi  ){rotationY = -pi;}

    // std::cout << rotationX << " " << rotationY << std::endl;
    // std::cout << win.width / 2 << " " << win.height / 2 << std::endl;
    // std::cout << "x : " << alphaX << " y: " << alphaY << std::endl;

    updateCamera();
  }
}

void keyPressed(unsigned char key, int mousePositionX, int mousePositionY) {
  keys[key] = true;

  // std::cout << "key pressed: " << (char) key << std::endl;

  switch (key) {
  case ESCAPE_KEY:
    exit(0);
    break;

  case 'm':
    captureMouse = false;
    break;

  case 'n':
    captureMouse = true;
    break;

  case '2':
    speedScale = speedScale * 2;
    break;

  case '1':
    speedScale = speedScale / 2;
    break;

  default:
    break;
  }
}

void keyReleased(unsigned char key, int mousePositionX, int mousePositionY) {
  keys[key] = false;
}

void checkKeyboard(double delta) {
  // delta = delta * cameraScale;

  // if (delta <0 || delta > 100) {delta = 0;}

  // delta = delta * 9;

  // eyeY = eyeY - 0.1 * delta;

  if (keys[(unsigned char)'w']) {

    eyeX += (cos(rotationX) * sin(rotationY)) * delta;
    eyeY += cos(rotationY) * delta;
    eyeZ += (sin(rotationX) * sin(rotationY)) * delta;
    updateCamera();
  }
  if (keys[(unsigned char)'s']) {

    eyeX -= (cos(rotationX) * sin(rotationY)) * delta;
    eyeY -= cos(rotationY) * delta;
    eyeZ -= (sin(rotationX) * sin(rotationY)) * delta;
    updateCamera();
  }
  if (keys[(unsigned char)'a']) {

    eyeX += cos(rotationX - (pi / 2)) * delta;
    eyeZ += sin(rotationX - (pi / 2)) * delta;
    updateCamera();
  }
  if (keys[(unsigned char)'d']) {

    eyeX -= cos(rotationX - (pi / 2)) * delta;
    eyeZ -= sin(rotationX - (pi / 2)) * delta;
    updateCamera();
  }

  if (keys[(unsigned char)' ']) {
    eyeY -= delta;
    updateCamera();
  }
}

void setCoordinates(float *eX, float *eY, float *eZ, float *oX, float *oY,
                    float *oZ, float timeDelta) {

  // std::cout << eyeX << " " << eyeY<< " " << eyeZ << std::endl;
  timeDelta = timeDelta * speedScale;
  // read from keyboard, calculate new coordinate values:
  checkKeyboard(timeDelta);

  // return new coordinate values:
  *eX = eyeX;
  *eY = eyeY;
  *eZ = eyeZ;

  *oX = objectX;
  *oY = objectY;
  *oZ = objectZ;
}
} // namespace controlspace
