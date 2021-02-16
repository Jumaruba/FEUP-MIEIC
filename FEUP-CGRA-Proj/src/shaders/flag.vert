 
#ifdef GL_ES
precision highp float;
#endif

attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec2 aTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

varying vec2 vTextureCoord;
uniform sampler2D defaultSampler;

uniform float time;
uniform float speed;
const float PI = 3.14159265;

//formula explanation ------------------------------------------
//wave = amplitude * (i + w*t) 
//w = frequency 
//INITIALPOSITION = sin(numberOfValleys * position * PI) 
//amplitude = Different for each point, since the final end of the flag has a higher amplitude 


void main() {
    vTextureCoord = aTextureCoord;
    vec3 offset = vec3 (0.0,0.0,0.0);
    vec3 offset2 = vec3(0.0,0.0,0.0);
	
	float valleys = 2.0; 		//two valleys are more realistic
    float initialPosition = sin(aTextureCoord.x * valleys * PI); 

    offset.z = 0.4 * sin(initialPosition + time * 0.1) * (aVertexPosition.x + 0.5);
    
    if(speed != 0.0)
    offset2.z =  0.2 * sin(initialPosition + speed * 100.0 * time * 0.1) * (aVertexPosition.x + 0.5);
 	
   gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition + offset2 +offset , 1.0);
} 
