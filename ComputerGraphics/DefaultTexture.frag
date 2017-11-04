#version 330

in vec3 InterpolatedColour;
in vec3 PixelPosition;
in vec3 InterpolatedNormal;
in vec2 InterpolatedTexCoord;

uniform vec3 LightPosition;
uniform vec3 LightColour;
uniform vec3 CameraPosition;
uniform sampler2D DiffuseTexture;
uniform sampler2D DiffuseTexture1;

out vec4 FragColor;

void main(){
	// Ambient component
	vec3 ambient = 0.1f * LightColour;

	// Diffuse component
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 N = normalize(InterpolatedNormal);
	vec3 diffuse = max(dot(N, L), 0.0f)*LightColour;

	// Specular component
	vec3 R = reflect(-L, N);
	vec3 V = normalize(CameraPosition - PixelPosition);
	vec3 specular = 0.5f * pow(max(dot(V, R), 0.0f), 32.0f) * LightColour;
	
	vec3 phong = (ambient + specular + diffuse);

	vec4 box = texture2D(DiffuseTexture, InterpolatedTexCoord);
    vec4 pig = texture2D(DiffuseTexture1, InterpolatedTexCoord);
    vec4 outColor = mix(box, pig, 0.4);
	FragColor = outColor*vec4(phong, 1.0f);
}

// References
// https://open.gl/textures