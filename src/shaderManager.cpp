#include "shaderManager.h"

using namespace renderspace;
//shaderManager implementation begin here

void shaderManager::attachShader(const std::string shaderName, GLenum shaderType){

  //Resolving full path to the shader file
  char resolved_path[200]; 
  realpath("src/shaders/", resolved_path); 
  
  std::string shaderFullPath; 
  shaderFullPath =  resolved_path + (std::string) "/" + shaderName;

  //  std::cout << shaderFullPath << std::endl;
  shader * s = new shader(shaderFullPath, shaderType);
  shaderVector.push_back(s);
  shaderCount ++;
  //  std::cout << shaderCount ;
}

void shaderManager::linkShaders(){

  programObject = glCreateProgram();

  std::cout << "glCreateProgram: " << glGetError() << std::endl;

  for(int i=0; i< shaderCount; i++){
    glAttachShader(programObject, shaderVector[i]->shaderObject);
    std::cout << "glAttachShader" << "[" << i <<"]: " << glGetError() << std::endl;
  }


  glLinkProgram(programObject);
  std::cout << "glLinkProgram: " << glGetError() << std::endl;


  GLint status = GL_FALSE;
  // glGetBooleanv(GL_LINK_STATUS, &s);



  glGetShaderiv(programObject, GL_LINK_STATUS, &status);
  std::cout << "glGetShaderiv: " << glGetError() << std::endl;

  if (status == GL_FALSE)
    {
      std::cout << "failed to link";
    }
  else
    {
    std::cout << "jeee";
    }
  
  // std::cout << (status ? "Program linked!" : "Program could not be linked") << std::endl;

}

GLuint shaderManager::getProgram(){

  return programObject;
}

void shaderManager::setUniform(const GLchar* uniformName, glm::mat4 * matrix){

  GLint loc = glGetUniformLocation(programObject, uniformName);
  if (loc != -1)
    {
      glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(*matrix));
    }


}
