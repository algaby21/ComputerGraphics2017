#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

int resX = 400;
int resY = 400;

void main(){
	FragColor = vec4(InterpolatedColor, 1.0f);
	vec2 pixelPositionInWindow = gl_FragCoord.xy;
	//if( (pixelPositionInWindow[0] > sqrt(100*gl_FragCoord.x) && pixelPositionInWindow[0] < 300) && (pixelPositionInWindow[1] > 100 && pixelPositionInWindow[1] < 300) ){
		//discard;
	//}
	float d = sqrt((pixelPositionInWindow[0]-resX/2)*(pixelPositionInWindow[0]-resX/2)+(pixelPositionInWindow[1]-resY/2)*(pixelPositionInWindow[1]-resY/2));
	if(d<=resX/4){
		discard;
	}
}