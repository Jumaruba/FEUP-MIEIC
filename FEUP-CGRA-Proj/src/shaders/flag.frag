#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;
uniform sampler2D defaultSampler;
void main() {
	vec4 color = texture2D(defaultSampler, vTextureCoord);
	gl_FragColor = color;
}