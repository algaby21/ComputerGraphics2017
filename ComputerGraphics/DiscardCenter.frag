#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

// Esto es la resolución de la ventana en pixeles
uniform vec2 Resolution;

void main(){
	// Es la posición del pixel en la ventana en un tango de [(0,0), (1,1)]
	vec2 p = gl_FragCoord.xy / Resolution;
	// Calculando un vector que van del pixel al centro de la ventana
	vec2 q = p - vec2(0.5f, 0.5f);
	// Si el vector que tiene una medida menor a 0.25, descartamos el pixel usando length
	if(length(q) < 0.25f)
		discard;

	FragColor = vec4(InterpolatedColor, 1.0f);

	//vec2 pixelPositionInWindow = gl_FragCoord.xy;
	//if( (pixelPositionInWindow[0] > sqrt(100*gl_FragCoord.x) && pixelPositionInWindow[0] < 300) && (pixelPositionInWindow[1] > 100 && pixelPositionInWindow[1] < 300) ){
		//discard;
	//}
	//float d = sqrt((pixelPositionInWindow[0]-resX/2)*(pixelPositionInWindow[0]-resX/2)+(pixelPositionInWindow[1]-resY/2)*(pixelPositionInWindow[1]-resY/2));
	//if(d<=resX/4){
		//discard;
	//}
}