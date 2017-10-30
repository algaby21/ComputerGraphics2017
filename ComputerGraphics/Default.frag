#version 330

in vec3 InterpolatedColour;
in vec3 PixelPosition;
in vec3 InterpolatedNormal;

uniform vec3 LightPosition;
uniform vec3 LightColour;
uniform vec3 CameraPosition;

out vec4 FragColor;

void main(){
	vec3 ambient = 0.1f * LightColour;
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 diffuse = max(dot(InterpolatedNormal, L), 0.0f)*LightColour;
	vec3 R = reflect(-L, InterpolatedNormal);
	vec3 V = normalize(CameraPosition - PixelPosition);
	vec3 specular = 0.5f * pow(max(dot(V, R), 0.0f), 32.0f) * LightColour;
	vec3 phong = (ambient + specular + diffuse)*InterpolatedColour;
	FragColor = vec4(phong, 1.0f);
}