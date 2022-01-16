#include "shader.h"


class marchingCube{
public:
    marchingCube();
    ~marchingCube();
  
    GLfloat * m_TriangleVertexArray;
    size_t m_size; 
    int m_faceCount;
};
