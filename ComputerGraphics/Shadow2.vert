#version 330

in vec3 VertexPosition;
in vec3 VertexColour;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec3 InterpolatedColour;
out vec3 PixelPosition;
out vec3 InterpolatedNormal;
out vec2 InterpolatedTexCoord;
out vec4 PixelPositionLightSpace;

uniform mat4 mvpMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 LightVPMatrix;

void main(){
	InterpolatedColour = VertexColour;
	InterpolatedNormal = NormalMatrix * VertexNormal;
	InterpolatedTexCoord = VertexTexCoord;
	PixelPosition = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
	PixelPositionLightSpace = LightVPMatrix * vec4(PixelPosition, 1.0);
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}