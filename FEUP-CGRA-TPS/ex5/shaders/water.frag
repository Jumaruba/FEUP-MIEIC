#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;

uniform sampler2D waterMap;
uniform sampler2D waterTex;
uniform float timeFactor;

#define greyShader      0.4
#define MULT_FACTOR     0.01
void main() {

    vec4 color = texture2D(waterTex, vTextureCoord+timeFactor*(MULT_FACTOR,-MULT_FACTOR));        //move the color
    vec4 map = texture2D(waterMap, vec2(0.0,0.1)+vTextureCoord+timeFactor*(MULT_FACTOR,-MULT_FACTOR));

    //less intensity (grey) => that's how the map will "move"
    color=vec4(color.r-map.r+greyShader, color.g-map.g+greyShader, color.b-map.b+greyShader, 1.0);

    gl_FragColor = color;
}