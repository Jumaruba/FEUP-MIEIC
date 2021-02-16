#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;
uniform sampler2D uSampler;

void main() {

    vec4 color = texture2D(uSampler, vTextureCoord);
    color.rgb = vec3(color.r * 0.299 + color.g * 0.587 + color.b * 0.114);
    gl_FragColor = color;
}