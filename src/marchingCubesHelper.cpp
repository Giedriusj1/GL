#include "marchingCubesHelper.h"

#include "marchingCubes.h"
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <string>

static const int arrSize = 200;

bool dist(int ax, int ay, int az, int bx, int by, int bz) {

  float d = (float)sqrt(pow((float)ax - (float)bx, 2) +
                        pow((float)ay - (float)by, 2) +
                        pow((float)az - (float)bz, 2));

  return d < (float)20 ? true : false;
}

marchingCube::marchingCube() {

  bool scalMap[arrSize][arrSize][arrSize];

  srand(time(NULL));
  for (int x = 0; x < arrSize; x++) {
    for (int y = 0; y < arrSize; y++) {
      for (int z = 0; z < arrSize; z++) {
        // scalMap[x][y][z] = dist(x,y,z,50,50,50);
        int rand1 = rand() % 100 + 1;
        scalMap[x][y][z] = rand1 < 2 ? true : false;

        // scalMap[x][y][z] = false;
      }
    }
  }

  m_faceCount = 0;
  int arrIndex = 0;
  m_TriangleVertexArray = new GLfloat[arrSize * arrSize * arrSize * 90];

  // memset((GLfloat *) m_TriangleVertexArray, '0' ,
  // sizeof(m_TriangleVertexArray) * arrSize * arrSize * arrSize);
  m_size = sizeof(m_TriangleVertexArray) * arrSize * arrSize * arrSize;

  for (int x = 1; x < arrSize - 1; x++) {
    for (int y = 1; y < arrSize - 1; y++) {
      for (int z = 1; z < arrSize - 1; z++) {
        int cubeindex = 0;
        if (scalMap[x][y][z + 1] == true)
          cubeindex |= 1;
        if (scalMap[x + 1][y][z + 1] == true)
          cubeindex |= 2;
        if (scalMap[x + 1][y][z] == true)
          cubeindex |= 4;
        if (scalMap[x][y][z] == true)
          cubeindex |= 8;
        if (scalMap[x][y + 1][z + 1] == true)
          cubeindex |= 16;
        if (scalMap[x + 1][y + 1][z + 1] == true)
          cubeindex |= 32;
        if (scalMap[x + 1][y + 1][z] == true)
          cubeindex |= 64;
        if (scalMap[x][y + 1][z] == true)
          cubeindex |= 128;

        int tmp = cubeindex;
        int i = 0;

        while (triTable[tmp][i] != -1) {

          if (i % 3 == 0)
            m_faceCount++;

          switch (triTable[tmp][i]) {

          case 0:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 1;
            arrIndex++;
            break;

          case 1:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 0.5;
            arrIndex++;
            break;

          case 2:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z;
            arrIndex++;
            break;

          case 3:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 0.5;
            arrIndex++;
            break;

          case 4:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 1;
            arrIndex++;
            break;

          case 5:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 0.5;
            arrIndex++;
            break;

          case 6:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z;
            arrIndex++;
            break;

          case 7:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 0.5;
            arrIndex++;
            break;

          case 8:

            m_TriangleVertexArray[arrIndex] = (GLfloat)x;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 1;
            arrIndex++;
            break;

          case 9:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z + 1;
            arrIndex++;
            break;

          case 10:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x + 1;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z;
            arrIndex++;
            break;

          case 11:
            m_TriangleVertexArray[arrIndex] = (GLfloat)x;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)y + 0.5;
            arrIndex++;
            m_TriangleVertexArray[arrIndex] = (GLfloat)z;
            arrIndex++;
            break;

          default:
            break;
          }
          i++;
        }
      }
    }
  }
}

marchingCube::~marchingCube() { delete m_TriangleVertexArray; }
