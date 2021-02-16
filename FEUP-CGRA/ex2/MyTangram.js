class MyTangram extends CGFobject{
    constructor(scene){
        super(scene); 
        this.scene = scene;
        scene.diamond = new MyDiamond(scene); 
        scene.triangle_A = new MyTriangleBig(scene);
        scene.triangle_B = new MyTriangleBig(scene); 
        scene.paralelo = new MyParalelogram(scene);
        scene.triangle = new MyTriangle(scene);
        scene.triangle_c = new MyTriangleSmall(scene);
        scene.triangle_d = new MyTriangleSmall(scene);
        
        this.green = new CGFappearance(this.scene);
        this.green.setDiffuse(0,1,0.145,1);
        this.green.loadTexture("./texture/red.png");

        this.blue = new CGFappearance(this.scene);
        this.blue.setDiffuse(0,0,1,1);
        this.blue.loadTexture("./texture/red.png");

        this.orange = new CGFappearance(this.scene);
        this.orange.setDiffuse(1,0.647,0);
        this.orange.loadTexture("./texture/red.png");

        this.yellow = new CGFappearance(this.scene);
        this.yellow.setDiffuse(0.855,1,0);
        this.yellow.loadTexture("./texture/red.png");

        this.pink = new CGFappearance(this.scene);
        this.pink.setDiffuse(1, 0.702, .957);
        this.pink.loadTexture("./texture/red.png");

        this.ppink = new CGFappearance(this.scene);
        this.ppink.setDiffuse(1, .106, .871);
        this.ppink.loadTexture("./texture/red.png");

        this.red = new CGFappearance(this.scene);
        this.red.setDiffuse(1, 0, 0);
        this.red.loadTexture("./texture/red.png");

    }
    display(){
        var diamTrans = [1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,2.5,0,1]; 

        // ---- BEGIN Primitive drawing section
        //diamond 

        this.scene.pushMatrix();
        this.scene.multMatrix(diamTrans);
        this.scene.scale(0.7,0.7,1);
        this.green.apply();
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
        this.ppink.apply();
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
}