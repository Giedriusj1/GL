#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "shader.h"

namespace renderspace {
class shaderManager {
public:
  void attachShader(const std::string shaderName, GLenum shaderType);
  void linkShaders();
  GLuint getProgram();
  void setUniform(const GLchar *uniformName, glm::mat4 *matrix);

private:
  std::vector<shader *> shaderVector;
  unsigned int shaderCount = 0;
  GLuint programObject;
};
} // namespace renderspace
