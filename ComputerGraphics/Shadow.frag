#version 330

in vec3 InterpolatedColour;
in vec3 PixelPosition;
in vec3 InterpolatedNormal;
in vec2 InterpolatedTexCoord;
in vec4 PixelPositionLightSpace;

uniform vec3 LightPosition;
uniform vec3 LightColour;
uniform vec3 CameraPosition;
uniform sampler2D DiffuseTexture;
uniform sampler2D DiffuseTexture1;
uniform sampler2D ShadowMap;

out vec4 FragColor;

float IsPixelOccluded(vec4 fragPosLightSpace) {
	// Realizar la corrección de perspectiva. Coordenadas en rango [-1, 1] -> Normalized Device Space
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords* 0.5 + 0.5;
	// Transformar projCoords al rango [0, 1]. (projCoords * 0.5 + 0.5)
	// Muestrear el mapa de profundidad usando projCoords.xy como coordenadas de textura.
	// Con esto obtenemos la profundidad del pixel en el primer render (desde la luz).
	float closestDepth = texture2D(ShadowMap, projCoords.xy).r;
	// La profundidad del pixel desde la actual cámara (ya transformado) está en projCoords.z
	// Si la profundidad del render actual es mayor a closestDepth, regresar 1.0f
	// De lo contrario, regresar 0.0f
	float currentDepth = projCoords.z;
	float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;
}

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

	vec4 box = texture2D(DiffuseTexture, InterpolatedTexCoord);
    //vec4 pig = texture2D(DiffuseTexture1, InterpolatedTexCoord);
    //vec4 outColor = mix(box, pig, 0.4);

	float shadow = IsPixelOccluded(PixelPositionLightSpace);
	vec3 phong = (ambient + (1.0 - shadow) * (diffuse + specular));

	FragColor = box*vec4(phong, 1.0f);
}

// References
// https://open.gl/textures