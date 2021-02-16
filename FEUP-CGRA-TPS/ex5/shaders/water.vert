attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec2 aTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

uniform sampler2D waterMap;
uniform sampler2D waterTex;
varying vec2 vTextureCoord;
varying vec4 coord;

uniform float timeFactor;

#define     MULT_FACTOR     0.03
void main() {
    vec3 offset = vec3(0.0,0.0,0.0);

    vTextureCoord = aTextureCoord;
    vec4 watermap = texture2D(waterMap, vec2(0.0, 0.1) + vTextureCoord+timeFactor*(MULT_FACTOR,MULT_FACTOR));
    vec4 watertex = texture2D(waterTex, vTextureCoord+timeFactor*(MULT_FACTOR,MULT_FACTOR));     //moving the color


    offset = aVertexNormal*MULT_FACTOR*watermap.b;


    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition+offset, 1.0);

}

