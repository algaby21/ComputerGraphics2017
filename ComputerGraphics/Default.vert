#version 330

in vec3 VertexPosition;
in vec3 VertexColour;
in vec3 VertexNormal;

out vec3 InterpolatedColour;
out vec3 PixelPosition;
out vec3 InterpolatedNormal;

uniform mat4 mvpMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

void main(){
	InterpolatedColour = VertexColour;
	InterpolatedNormal = NormalMatrix * VertexNormal;
	PixelPosition = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}