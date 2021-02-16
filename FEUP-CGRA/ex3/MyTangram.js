class MyTangram extends CGFobject{
    constructor(scene){
        super(scene); 
        this.scene = scene;
        this.initBuffers();
        this.initMaterial();

    }
    initBuffers() {
        this.scene.diamond = new MyDiamond(this.scene);
        this.scene.triangle_A = new MyTriangleBig(this.scene);
        this.scene.triangle_B = new MyTriangleBig(this.scene);
        this.scene.paralelo = new MyParalelogram(this.scene);
        this.scene.triangle = new MyTriangle(this.scene);
        this.scene.triangle_c = new MyTriangleSmall(this.scene);
        this.scene.triangle_d = new MyTriangleSmall(this.scene);
    }

    initMaterial(){


        //triangle_A
        this.blue = new CGFappearance(this.scene);
        this.blue.setSpecular(1,1,1,1);
        this.blue.setDiffuse(0.2,0.6,1,1);
        this.blue.setShininess(10);
        this.blue.setAmbient(0.2,0.6,1,1);

        //triangle_B
        this.orange = new CGFappearance(this.scene);
        this.orange.setSpecular(1,1,1,1);
        this.orange.setDiffuse(1,0.55,0.1,1);
        this.orange.setShininess(10);
        this.orange.setAmbient(1,0.55,0.1,1);

        //paralelo
        this.yellow = new CGFappearance(this.scene);
        this.yellow.setSpecular(1,1,1,1);
        this.yellow.setDiffuse(1,1,0.2,1);
        this.yellow.setShininess(10);
        this.yellow.setAmbient(1,1,0.2,1);

        //triangle
        this.pink = new CGFappearance(this.scene);
        this.pink.setSpecular(1,1,1,1);
        this.pink.setDiffuse(1,0.5,1,1);
        this.pink.setShininess(10);
        this.pink.setAmbient(1,0.5,1,1);

        //triangle_c
        this.violet = new CGFappearance(this.scene);
        this.violet.setSpecular(1,1,1,1);
        this.violet.setDiffuse(0.5,0,1,1);
        this.violet.setShininess(10);
        this.violet.setAmbient(0.5,0,1,1);

        //triangle_d
        this.red = new CGFappearance(this.scene);
        this.red.setSpecular(1,1,1,1);
        this.red.setDiffuse(1,0,0,1);
        this.red.setAmbient(1,0,0,1);
        this.red.setShininess(10);


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
    display(){
        var diamTrans = [1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,2.5,0,1]; 

        // ---- BEGIN Primitive drawing section
        //diamond 
        this.scene.customMaterial.apply();
        this.scene.pushMatrix();
        this.scene.multMatrix(diamTrans);
        this.scene.scale(0.7,0.7,1);
        this.scene.diamond.display();
        this.scene.popMatrix();
        //triangle_A
        this.scene.pushMatrix();
        this.scene.translate(0,1.8,0);
        this.scene.rotate(Math.PI*3/4,0,0,1);
        this.blue.apply();
        this.scene.triangle_A.display();
        this.scene.popMatrix(); 
        //triangle_B
        this.scene.pushMatrix(); 
        this.scene.translate(0.5, -1,0);
        this.scene.rotate(-Math.PI/4,0,0,1);
        this.orange.apply();
        this.scene.triangle_B.display();
        this.scene.popMatrix();
        //Paralelogram
        this.scene.pushMatrix(); 
        this.scene.translate(1.2,-0.3,0); 
        this.scene.rotate(-Math.PI/2,0,0,1);
        this.scene.scale(1,-1,1);
        this.scene.scale(0.7,0.7,1);
        this.yellow.apply();
        this.scene.paralelo.display();
        this.scene.popMatrix();
        //triangle bottom
        this.scene.pushMatrix();
        this.scene.translate(0.5,-2.4,0);
        this.scene.rotate(Math.PI/2, 0,0,1);
        this.scene.scale(0.7,0.7,1);
        this.pink.apply();
        this.scene.triangle.display();
        this.scene.popMatrix();
        //small triangle 1 
        this.scene.pushMatrix();
        this.scene.translate(-1.4,0.4,0);
        this.scene.rotate(-Math.PI/4,0,0,1);
        this.violet.apply();
        this.scene.triangle_c.display();
        //small triangle 2
        this.scene.popMatrix();
        this.scene.pushMatrix(); 
        this.scene.translate(-2.1,1.1,0);
        this.scene.rotate(-Math.PI/4,0,0,1);
        this.red.apply();
        this.scene.triangle_d.display();

        this.scene.popMatrix();

    }
    updateBuffers(complexity){
        // reinitialize buffers
        this.initBuffers();
        this.initNormalVizBuffers();
    }


}