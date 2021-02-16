class MyUnitCubeQuad extends CGFobject{
    constructor(scene){
        super(scene);
        this.scene = scene;
        this.textureMap();
        this.initBuffers();

    }
    textureMap(){
        this.left = [
            0,1/3,
            0,2/3,
            0.25,1/3,
            0.25,2/3
        ]; 
        
        this.front = [
            0.25,1/3,
            0.25,2/3,
            0.5,1/3,
            0.5,2/3
        ];
        
        this.right = [
            0.5,1/3,
            0.5,2/3,
            0.75,1/3,
            0.75,2/3
        ]; 
        
        this.back = [
            0.75,1/3,
            0.75,2/3,
            1,1/3,
            1,2/3
        ]; 
        
        this.down = [
            0.25,2/3,
            0.25,1,
            0.5,2/3,
            0.5,1
        ];
        
        this.up = [
            0.25,0,
            0.25,1/3,
            0.5,0,
            0.5,1/3
        ];
        
        
    }
    initBuffers() {
                
        this.quad1 = new MyDiamond(this.scene,this.front, this.newPos);     //front
        this.quad2 = new MyDiamond(this.scene,this.back, this.newPos);      //back
        this.quad3 = new MyDiamond(this.scene,this.left, this.newPos);      //left
        this.quad4 = new MyDiamond(this.scene,this.right, this.newPos);     //right
        this.quad5 = new MyDiamond(this.scene,this.up, this.newPos);        //up
        this.quad6 = new MyDiamond(this.scene,this.down, this.newPos);      //down
    }

    display(){
        
        const sqrt = Math.sqrt(2)/2; 
        const space = 0.0005;           //eliminate the white spaces in the cubemap 
        //quad1 -- front
        this.scene.pushMatrix();
    
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,0,sqrt-space);
        this.scene.rotate(Math.PI, 0,1,0); this.scene.rotate(-Math.PI/4, 0,0,1);
        this.quad1.display();
        this.scene.popMatrix();

        //quad2 -- back
        this.scene.pushMatrix();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,0,-sqrt+space);
        this.scene.rotate(-Math.PI/4, 0,0,1);
        this.quad2.display();
        this.scene.popMatrix();

        //quad3 -- left
        this.scene.pushMatrix();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(sqrt-space,0,0);
        this.scene.rotate(-Math.PI/2, 0,1,0);
        this.scene.rotate(-Math.PI/4, 0,0,1);
        this.quad3.display();
        this.scene.popMatrix(); 

        //quadr4 - right
        this.scene.pushMatrix();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(-sqrt+space,0,0);
        this.scene.rotate(Math.PI/2,0,1,0);
        this.scene.rotate(-Math.PI/4, 0,0,1);
        this.quad4.display();
        this.scene.popMatrix(); 

        //quad5 -- up
        this.scene.pushMatrix();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,sqrt-space,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(3*Math.PI/4, 0,0,1);
        this.quad5.display();
        this.scene.popMatrix();

        //quad6 -- down
        this.scene.pushMatrix();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,-sqrt+space,0);
        this.scene.rotate(-Math.PI/2, 1,0,0);
        this.scene.rotate(3*Math.PI/4, 0,0,1);
        this.quad6.display();
        this.scene.popMatrix();



    }

    
}