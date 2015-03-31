#version 130
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;
in vec4 vnormal;
out vec4 vvertex;



void main() {
    vvertex = vnormal;
    gl_Position = projectionMatrix * cameraMatrix  * vnormal;
}
