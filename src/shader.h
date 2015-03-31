#pragma once

#include <iostream>
#include <fstream>
#include <string.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

class shader{

public:
  GLenum type; //Shader type
  std::string shaderPath;
  // GLchar shaderCode[5000];
  std::string shaderCode;

  GLuint shaderObject;

public:
  shader(const std::string shaderFullPath, GLenum shaderType);

};
