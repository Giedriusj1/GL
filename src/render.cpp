#include "shaderManager.h"
#include "render.h"
#include "control.h"
#include "objectLoader.h"
#include "network/network.h"

#include <iostream>
#include <stdio.h>
#include <ctime>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/date_time.hpp>

#include "marchingCubesHelper.h"

using namespace renderspace;

const int window_width = 1000;
const int window_height = 1000;

float eyeX = 0;
float eyeY = 0;
float eyeZ = 0;

float objectX = 10;
float objectY = 10;
float objectZ = 10;

//THESE SHOULD GO SOMEWHERE ELSE:
long timeDelta = 0;
long startTime;
long lastFrameTime;

GLuint gVAO = 0;
GLuint gVBO = 0;

uint faceCount;

unsigned long delta;

shaderManager shader;



#include <queue>

std::queue<int> renderMessageQueue;
std::mutex renderMessageQueueMutex;

void readMessageIfExists(){


  if(renderMessageQueueMutex.try_lock()){


    int count = 0;
  while(!renderMessageQueue.empty()){
    
      
    std::cout << "msg from thread: "<< (int) renderMessageQueue.front() << ": " << count << std::endl;
    count++;
    renderMessageQueue.pop();


  }

    renderMessageQueueMutex.unlock();

  
}

  
}

// renderMessageQueue = new std::queue;

void loadShaders(){
  shader.attachShader("vertex-shader.glsl", GL_VERTEX_SHADER);
  shader.attachShader("fragment-shader.glsl", GL_FRAGMENT_SHADER);
  shader.linkShaders();

}

void loadData(){
  // objectLoader bike("desert_oasis.obj");
  // objectLoader bike("testmap1.obj");
  marchingCube cube;

  // make and bind the VAO
  glGenVertexArrays(1, &gVAO);
  glBindVertexArray(gVAO);

  // make and bind the VBO
  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);

  // Put the three triangle verticies into the VBO

  // glBufferData(GL_ARRAY_BUFFER, bike.m_size , bike.m_TriangleVertexArray, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, cube.m_size , cube.m_TriangleVertexArray, GL_STATIC_DRAW);

  glBindAttribLocation(shader.getProgram(), 1, "vnormal");

  GLint q  = glGetAttribLocation(shader.getProgram(), "vnormal");
  glEnableVertexAttribArray(q);
  
  glVertexAttribPointer(q, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  faceCount = cube.m_faceCount;
  // faceCount = bike.m_faceCount;

  // unbind the VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}

void renderspace::initialize(){
  network * net = new network();

  //glEnable(GL_DEPTH_TEST);

  // GLUT initialization;
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // Display Mode
  glutInitWindowSize(window_width, window_height);
  glutCreateWindow("");
  
  glutPassiveMotionFunc(controlspace::mouseRotateCamera);
  glutKeyboardFunc(controlspace::keyPressed);
  glutKeyboardUpFunc(controlspace::keyReleased);  

  glutDisplayFunc(renderspace::display);
  glutIdleFunc(renderspace::display);
   
  //glutReshapeFunc(resize);

  glEnable(GL_DEPTH_TEST);

  glDepthFunc(GL_LESS);
  glutSetCursor(GLUT_CURSOR_NONE);

  // initialise GLEW
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  

  if (GLEW_OK != err) 
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  else
    std::cout << "GLEW_VERSION: " << glewGetString(GLEW_VERSION) << std::endl;

  if (!glewIsSupported("GL_VERSION_3_3")) 
    std::cout << "Required GL version not supported" << std::endl;

  loadShaders();
  loadData();

  //Setting initial time for fps counter
  boost::posix_time::ptime timeD = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration duration(timeD.time_of_day());

  startTime = duration.total_milliseconds();



  glutMainLoop();

}

void renderspace::display(){
  //This is the main rendering loop
  readMessageIfExists();
  //counting time last frame took to draw
  boost::posix_time::ptime timeD = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration duration(timeD.time_of_day());

  timeDelta = duration.total_milliseconds() - lastFrameTime;
  lastFrameTime = duration.total_milliseconds();

  // Clear Screen and Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); 
  glLoadIdentity();
  
  glUseProgram(shader.getProgram());
  
  //Sets pointer position to the middle of the window, to prevent it from leaving window frame.
  glutWarpPointer(window_width  / 2, window_height / 2);

  controlspace::setCoordinates(&eyeX, &eyeY, &eyeZ, &objectX, &objectY, &objectZ,(float) timeDelta);
  glm::mat4 projection = glm::perspective<float>(50.0,
												 (float) (window_width / window_height ),
												 0.1, 40000.0);

  glm::mat4 camera = glm::lookAt(glm::vec3(eyeX,eyeY,eyeZ),
								 glm::vec3(objectX,objectY,objectZ), 
								 glm::vec3(0,1,0));

  glUseProgram(shader.getProgram());

  glBindVertexArray(gVAO);

  shader.setUniform("projectionMatrix", &projection);
  shader.setUniform("cameraMatrix", &camera);


  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  

  glDrawArrays(GL_TRIANGLES,0,3*faceCount);
  // glDrawArrays(GL_POINTS,0,3*faceCount);

  // glPointSize(4);

  // unbind the VAO
  glBindVertexArray(0);


  // unbind the program
  glUseProgram(0);

  glutSwapBuffers();
  glFinish();

}
