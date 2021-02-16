#ifdef GL_ES
precision highp float;
#endif

varying vec4 coords;
varying vec4 normal;

uniform int nSuppliesDelivered;
uniform float totalSupplies;

void main() {
    float boundary = -0.6 + ((1.2/float(totalSupplies)))*float(nSuppliesDelivered);

    if(coords.x > boundary){
        gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
    }
    else{
        gl_FragColor.rgb =  vec3(1.0 - (0.6 + coords.x / 0.6), 0.6 + coords.x / 0.6, 0);
        gl_FragColor.a = 1.0;
    }
}