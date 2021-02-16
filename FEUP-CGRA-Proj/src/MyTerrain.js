class MyTerrain extends CGFobject {
	constructor(scene, nDiv) {
		super(scene);
		this.nDiv = nDiv;
		this.scene = scene;
		this.initBuffers();
		this.initTexture();
		this.initAppearence();
		this.initShader();
	}
	initTexture() {
		this.map = new CGFtexture(this.scene, "images/shader/nevadoMap.jpg");
		this.tex = new CGFtexture(this.scene, "images/shader/nevadoTex.png");
	}

	initShader() {
		this.shader = new CGFshader(
			this.scene.gl,
			"shaders/terrain.vert",
			"shaders/terrain.frag"
		);
		this.shader.setUniformsValues({ textureTerrain: 1 });
		this.shader.setUniformsValues({ heightTerrain: 2 });
	}
	initBuffers() {
		this.plane = new MyPlane(this.scene, this.nDiv);
	}

	initAppearence() {
		this.appearence = new CGFappearance(this.scene);
		this.appearence.setAmbient(1, 1, 1);
		this.appearence.setDiffuse(0.7, 0.7, 0.7);
		this.appearence.setShininess(7);
		this.appearence.setTexture(this.tex);
		this.appearence.setSpecular(0.7, 0.7, 0.7);
	}

	display() {
		this.scene.pushMatrix();
		this.scene.scale(50, 50, 8);
		this.appearence.apply();
		this.scene.setActiveShader(this.shader);
		this.tex.bind(1);
		this.map.bind(2);
		this.plane.display();
		this.scene.popMatrix();
	}
}
