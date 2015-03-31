#include "shader.h"


shader::shader(const std::string shaderFullPath, GLenum shaderType){
  //shader
  //TODO: what if file doesn't exist?

  shaderPath = shaderFullPath;
  type = shaderType;

  std::cout << "opening: " << shaderPath << std::endl;
    
  std::ifstream file;
  file.open(shaderFullPath,std::ifstream::in); //opens file for reading


  // unsigned long pos=file.tellg();
  // file.seekg(0,std::ifstream::end);
  // unsigned long len = file.tellg();
  // file.seekg(std::ifstream::beg);

  // std::string contents;
  file.seekg(0, std::ios::end);
  shaderCode.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&shaderCode[0], shaderCode.size());
  file.close();

  std::cout << "length :" << shaderCode.size() << std::endl;

  // int i = 0;

  // file.read(&shaderCode[0], len);
  // std::cout << file;

  // while(file.good())
  //   {
  //     shaderCode[i] = file.get();
  //     if (!file.eof())
  // 	i++;     
  //   }
  // shaderCode[i] = 0;
  // i++;

  std::cout << shaderCode;

  shaderObject = glCreateShader(type);

  std::cout << "glCreateShader: " << glGetError() << std::endl;

  const GLchar * code = shaderCode.c_str();

  // int * len2 = new int[1];
  // len2[0] = shaderCode.size(); //sizeof(shaderCode);

  glShaderSource(shaderObject, 1, (const GLchar**)&code, NULL); 

    
  std::cout << "glShaderSource: " << glGetError() << std::endl;


  glCompileShader(shaderObject);

  std::cout << "glcompileshader: " << glGetError() << std::endl;


  //throws exception if compile error occurred
  GLint status;
  glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);

  std::cout << "glGetShaderiv: " << glGetError() << std::endl;


  if (status == GL_FALSE) {
    std::string msg("Compile failure in shader:\n");
        

    GLint infoLogLength;


    glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* strInfoLog = new char[infoLogLength + 1];
    glGetShaderInfoLog(shaderObject, infoLogLength, NULL, strInfoLog);
    msg += strInfoLog;
    delete[] strInfoLog;
        
    //glDeleteShader(_object); _object = 0;
    std::cout << msg << std::endl;
  } else {
    std::cout << "All OK!" << std::endl << std::endl;
  }

};
