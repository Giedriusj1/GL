#include "objectLoader.h"

#include <stdio.h>

#include "objLoader/objLoader.h"
#include <GL/gl.h>
#include <iostream>
#include <stdlib.h>

objectLoader::objectLoader(const std::string objectName)
    : m_faceCount(0), m_TriangleVertexArray(NULL) {

  objLoader *objData = new objLoader();

  // Resolving full path to the shader file
  char resolved_path[200];
  realpath("objects/", resolved_path);

  // std::string shaderFullPath;
  std::string objectFullPath = resolved_path + (std::string) "/" + objectName;
  std::cout << "resolved path: " << objectFullPath << std::endl;

  char *ptr = (char *)objectFullPath.c_str();
  objData->load(ptr);

  printf("%s", ptr);

  // sprintf(path, "%s", ResourcePath("models/test.obj"));

  m_faceCount = objData->faceCount;

  std::cout << "m_faceCount" << m_faceCount << std::endl;

  m_TriangleVertexArray = new GLfloat[3 * 3 * m_faceCount];

  int arrIndex = 0;
  for (int i = 0; i < objData->faceCount; i++) {
    obj_face *o = objData->faceList[i];
    // printf(" face ");
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++) {
        {
          m_TriangleVertexArray[arrIndex] =
              (objData->vertexList[o->vertex_index[j]])->e[k];
          arrIndex++;
        }
      }
  }

  m_size = arrIndex * sizeof(GLfloat);

  std::cout << "arr length:" << arrIndex * 3 << std::endl;
}

objectLoader::~objectLoader() { delete m_TriangleVertexArray; }
