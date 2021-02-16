attribute vec3 aVertexPosition;
attribute vec3 aVertexNormal;
attribute vec2 aTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

uniform sampler2D textureTerrain;
uniform sampler2D heightTerrain; 
varying vec2 vTextureCoord;
varying vec4 coord;


#define     MULT_FACTOR     0.5
void main() {
    vec3 offset = vec3(0.0,0.0,0.0);

    vTextureCoord = aTextureCoord;
    vec4 heightterrain = texture2D(heightTerrain, vTextureCoord);
    vec4 textureterrain = texture2D(textureTerrain, vTextureCoord);

    offset = aVertexNormal*MULT_FACTOR*heightterrain.b;


    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition+offset, 1.0);

}

