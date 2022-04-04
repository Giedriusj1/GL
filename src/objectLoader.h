#pragma once

#include <GL/gl.h>
#include <iostream>

class objectLoader {

public:
  objectLoader(const std::string objectName);
  ~objectLoader();

  GLfloat *getObjectVertexArray();
  size_t getObjectSize();

  int m_faceCount;
  GLfloat *m_TriangleVertexArray;
    
  size_t m_size;
};
