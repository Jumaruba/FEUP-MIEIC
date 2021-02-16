class MyTangram extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
        this.initMaterial();

    }

    initBuffers() {
        this.triangle_d_coords = [
            0.5,0.75,
            0.5,0.5,
            0.25,0.75,
            0.75,0.75
        ];
        this.scene.diamond = new MyDiamond(this.scene);
        this.scene.triangle_A = new MyTriangleBig(this.scene);
        this.scene.triangle_B = new MyTriangleBig(this.scene);
        this.scene.paralelo = new MyParalelogram(this.scene);
        this.scene.triangle = new MyTriangle(this.scene);
        this.scene.triangle_c = new MyTriangleSmall(this.scene);
        this.scene.triangle_d = new MyTriangleSmall(this.scene, this.triangle_d_coords);

    }

    initMaterial() {

        this.tangramTex = new CGFtexture(this.scene, 'images/tangram.png');
        this.default = new CGFappearance(this.scene);
        this.default.setShininess(1);
        this.default.setAmbient(1,1,1,1);       //white light
        this.default.setDiffuse(1,1,1,1);
        this.default.setSpecular(1,1,1,1);
        this.default.setTexture(this.tangramTex);

    }

    enableNormalViz() {
        this.scene.paralelo.enableNormalViz();
        this.scene.diamond.enableNormalViz();
        this.scene.triangle_A.enableNormalViz();
        this.scene.triangle_B.enableNormalViz();
        this.scene.triangle.enableNormalViz();
        this.scene.triangle_c.enableNormalViz();
        this.scene.triangle_d.enableNormalViz();

    }

    disableNormalViz() {
        this.scene.paralelo.disableNormalViz();
        this.scene.diamond.disableNormalViz();
        this.scene.triangle_A.disableNormalViz();
        this.scene.triangle_B.disableNormalViz();
        this.scene.triangle.disableNormalViz();
        this.scene.triangle_c.disableNormalViz();
        this.scene.triangle_d.disableNormalViz();
    }

    display() {
        var diamTrans = [1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 2.5, 0, 1];

        var newBigTriangleCoords = [
            1,0.5,
            0.5,0.5,
            1,1,
            1,0
        ];

        // ---- BEGIN Primitive drawing section
        this.scene.pushMatrix();
        this.default.apply();
        //diamond
        this.scene.pushMatrix();
        this.scene.multMatrix(diamTrans);
        this.scene.scale(0.7, 0.7, 1);
        this.scene.diamond.display();
        this.scene.popMatrix();
        //triangle_A
        this.scene.pushMatrix();
        this.scene.translate(0, 1.8, 0);
        this.scene.rotate(Math.PI * 3 / 4, 0, 0, 1);
        this.scene.triangle_A.display();
        this.scene.popMatrix();
        //triangle_B
        this.scene.pushMatrix();
        this.scene.triangle_B.updateTexCoords(newBigTriangleCoords);
        this.scene.translate(0.5, -1, 0);
        this.scene.rotate(-Math.PI / 4, 0, 0, 1);
        this.scene.triangle_B.display();
        this.scene.popMatrix();
        //Paralelogram
        this.scene.pushMatrix();
        this.scene.translate(1.2, -0.3, 0);
        this.scene.rotate(-Math.PI / 2, 0, 0, 1);
        this.scene.scale(1, -1, 1);
        this.scene.scale(0.7, 0.7, 1);
        this.scene.paralelo.display();
        this.scene.popMatrix();
        //triangle bottom
        this.scene.pushMatrix();
        this.scene.translate(0.5, -2.4, 0);
        this.scene.rotate(Math.PI / 2, 0, 0, 1);
        this.scene.scale(0.7, 0.7, 1);
        this.scene.triangle.display();
        this.scene.popMatrix();
        //small triangle 1 
        this.scene.pushMatrix();
        this.scene.translate(-1.4, 0.4, 0);
        this.scene.rotate(-Math.PI / 4, 0, 0, 1);
        this.scene.triangle_c.display();
        this.scene.popMatrix();
        //small triangle 2

        this.scene.pushMatrix();
        this.scene.translate(-2.1, 1.1, 0);
        this.scene.rotate(-Math.PI / 4, 0, 0, 1);
        this.scene.triangle_d.display();

        this.scene.popMatrix();
        this.scene.popMatrix();

    }

    updateBuffers(complexity) {
        // reinitialize buffers
        this.initBuffers();
        this.initNormalVizBuffers();
    }



}