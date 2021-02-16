class MyQuad extends CGFobject{
    constructor(scene){
        super(scene); 

        this.scene = scene; 
        this.quad1 = new MyDiamond(scene); 
        this.quad2 = new MyDiamond(scene); 
        this.quad3 = new MyDiamond(scene); 
        this.quad4 = new MyDiamond(scene); 
        this.quad5 = new MyDiamond(scene); 
        this.quad6 = new MyDiamond(scene); 

        this.blue = new CGFappearance(this.scene);
        this.blue.setDiffuse(0, 0, 1);
        this.blue.loadTexture("./texture/red.png");
    }


    display(){
        

        this.blue.apply();
        const sqrt = Math.sqrt(2)/2; 
        //quad1 -- front
        this.scene.pushMatrix();
        this.scene.translate(0,0,sqrt); 
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad1.display();
        this.scene.popMatrix();

        //quad2 -- background
        this.scene.pushMatrix();
        this.scene.translate(0,0,-sqrt);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad2.display();
        this.scene.popMatrix();

        //quad3 -- right
        this.scene.pushMatrix();
        this.scene.translate(sqrt,0,0);
        this.scene.rotate(Math.PI/2, 0,1,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad3.display();
        this.scene.popMatrix(); 

        //quadr4 - left
        this.scene.pushMatrix(); 
        this.scene.translate(-sqrt,0,0);
        this.scene.rotate(Math.PI/2,0,1,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad4.display();
        this.scene.popMatrix(); 

        //quad5 -- up
        this.scene.pushMatrix();
        this.scene.translate(0,sqrt,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad5.display();
        this.scene.popMatrix();

        this.scene.pushMatrix(); 
        this.scene.translate(0,-sqrt,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad6.display();
        this.scene.popMatrix();
        


    }
    
}