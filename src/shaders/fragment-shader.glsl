#version 130
in vec4 vertex;
in vec4 normal;
in vec4 vvertex;
uniform float time;
out vec4 finalColor;


void main() {

        finalColor =  abs(normalize(vvertex));
	//finalColor = vec4(1,1,1,1);
}
