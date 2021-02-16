class MyFlag extends CGFobject {
	constructor(scene) {
		super(scene);
		this.scene = scene;
		this.wire1 = new MyPlane(this.scene, 20);
		this.wire2 = new MyPlane(this.scene, 20);
		this.flag = new MyPlane(this.scene, 20);
        
        this.wire1Inv = new MyPlane(this.scene, 20);
		this.wire2Inv = new MyPlane(this.scene, 20);
		this.flagInv = new MyPlane(this.scene, 20);
		this.initBuffers();
		this.initShaders();
	}

	initBuffers() {
		this.flagTex = new CGFappearance(this.scene);
		this.flagTex.setAmbient(0.1, 0.1, 0.1, 1);
		this.flagTex.setDiffuse(0.9, 0.9, 0.9, 1);
		this.flagTex.setSpecular(0.0, 0.0, 0.0, 1);
		this.flagTex.setShininess(10.0);
		this.flagTex.loadTexture("images/flag.png");
	
		this.flagTex.setTextureWrap("CLAMP_TO_EDGE", "CLAMP_TO_EDGE");
		this.texture = new CGFtexture(this.scene, "images/flag.png");

		this.wireTex = new CGFappearance(this.scene);
		this.wireTex.setAmbient(0.1, 0.1, 0.1, 1);
		this.wireTex.setDiffuse(0.9, 0.9, 0.9, 1);
		this.wireTex.setSpecular(0, 0, 0, 1);
		this.wireTex.setShininess(10.0);
		this.wireTex.loadTexture("images/wire.jpg");
		this.wireTex.setTextureWrap("REPEAT", "REPEAT");
	}

	initShaders() {
		this.shader1 = new CGFshader(
			this.scene.gl,
			"shaders/flag.vert",
			"shaders/flag.frag"
		);
		this.shader1.setUniformsValues({ defaultSampler: 4 });
		this.shader1.setUniformsValues({ speed: 0 });
		this.shader1.setUniformsValues({ time: 0 });
        
        
        this.shader2 = new CGFshader(
			this.scene.gl,
			"shaders/flag2.vert",
			"shaders/flag.frag"
		);
        this.shader2.setUniformsValues({ defaultSampler: 4 });
		this.shader2.setUniformsValues({ speed: 0 });
		this.shader2.setUniformsValues({ time: 0 });
        
	}

	display() {
		//bind the texture
		this.texture.bind(4);

		//flag
		this.flagTex.apply();
		this.scene.setActiveShader(this.shader1);
		this.scene.pushMatrix();
		this.scene.translate(0, 0.1, -2.65);
		this.scene.scale(0.7, 1.0, 1.8);
		this.scene.rotate(Math.PI / 2, 0, 1, 0);
		this.flag.display();
		this.scene.popMatrix();
		this.scene.setActiveShader(this.scene.defaultShader);
		this.scene.defaultAppearence.apply();

		//wire1
		this.scene.pushMatrix();
		this.scene.translate(0, 0.15, 0.5);
		this.scene.scale(1, 0.025, 1.5);
		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI / 2, 0, 1, 0);
		this.wire1.display();
		this.scene.popMatrix();

		//wire2
		this.scene.pushMatrix();
		this.scene.translate(0, -0.15, 0.5);
		this.scene.scale(1, 0.025, 1.5);
		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI / 2, 0, 1, 0);
		this.wire2.display();
		this.scene.popMatrix();
        
        //inverted -------------------------------------
 		//Instead of invert the flag inside the vehicle we decided that the caracteristic of both sides is inherinted to the flag 

        //flag
        this.scene.setActiveShader(this.shader2);
		this.flagTex.apply();
		this.scene.pushMatrix();
		this.scene.translate(0, 0.1, -2.65);
		this.scene.scale(0.7, 1.0, 1.8);
		this.scene.rotate(-Math.PI/2, 0, 1, 0);
		this.flagInv.display();
		this.scene.popMatrix();
		this.scene.setActiveShader(this.scene.defaultShader);
		this.scene.defaultAppearence.apply();

		//wire1
		this.scene.pushMatrix();
		this.scene.translate(0, 0.15, 0.5);
		this.scene.scale(1, 0.025, 1.5);
		this.scene.translate(0, 0, -1);
		this.scene.rotate(-Math.PI / 2, 0, 1, 0);
		this.wire1Inv.display();
		this.scene.popMatrix();

		//wire2
		this.scene.pushMatrix();
		this.scene.translate(0, -0.15, 0.5);
		this.scene.scale(1, 0.025, 1.5);
		this.scene.translate(0, 0, -1);
		this.scene.rotate(-Math.PI / 2, 0, 1, 0);
		this.wire2Inv.display();
		this.scene.popMatrix();
	}

	update(t) {
		
		this.shader1.setUniformsValues({ time: t });
        this.shader2.setUniformsValues({ time: t });
        
	}

    updateSpeed(v){
        this.shader1.setUniformsValues({ speed: v });
        this.shader2.setUniformsValues({ speed: v });
    }
}
