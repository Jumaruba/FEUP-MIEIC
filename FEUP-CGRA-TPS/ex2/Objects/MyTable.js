class MyTable extends CGFobject{
    constructor(scene){
        super(scene); 
        this.scene = scene; 
        scene.up = new MyQuad(scene); 
        scene.foot1 = new MyQuad(scene); 
        scene.foot2 = new MyQuad(scene); 
        scene.foot3 = new MyQuad(scene); 
        scene.foot4 = new MyQuad(scene); 
    }

    display(){
        
        var x = Math.sqrt(2)/2*4-Math.sqrt(2)/2*0.3;
        var z = Math.sqrt(2)-Math.sqrt(2)/2*0.3; 
        var y = -Math.sqrt(2)/2*2.5-Math.sqrt(2)/2*0.3;        

        //table
        this.scene.pushMatrix(); 
        this.scene.scale(4,0.3,2);
        this.scene.up.display(); 
        this.scene.popMatrix(); 

        
        this.scene.pushMatrix();
        this.scene.translate(x,y,z);
        this.scene.scale(0.3,2.5,0.3);
        this.scene.foot1.display();
        this.scene.popMatrix(); 

        this.scene.pushMatrix(); 
        this.scene.translate(x,y,-z); 
        this.scene.scale(0.3,2.5,0.3);       
        this.scene.foot2.display(); 
        this.scene.popMatrix(); 

        this.scene.pushMatrix();
        this.scene.translate(-x,y,z);
        this.scene.scale(0.3,2.5,0.3);
        this.scene.foot3.display();  
        this.scene.popMatrix(); 

        this.scene.pushMatrix();
        this.scene.translate(-x,y,-z); 
        this.scene.scale(0.3,2.5,0.3);
        this.scene.foot4.display();
        this.scene.popMatrix(); 
    }
}