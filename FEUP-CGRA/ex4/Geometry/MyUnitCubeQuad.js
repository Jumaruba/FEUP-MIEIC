class MyUnitCubeQuad extends CGFobject{
    constructor(scene){
        super(scene);
        this.scene = scene;

        this.initBuffers();
        this.initMaterial()

    }
    initBuffers() {
        this.new_coords = [
            0,1,
            1,1,
            0,0,
            1,0
        ];
        this.quad1 = new MyDiamond(this.scene,this.new_coords);  //front
        this.quad2 = new MyDiamond(this.scene,this.new_coords);  //back
        this.quad3 = new MyDiamond(this.scene,this.new_coords);  //right
        this.quad4 = new MyDiamond(this.scene,this.new_coords);  //left
        this.quad5 = new MyDiamond(this.scene,this.new_coords);  //up
        this.quad6 = new MyDiamond(this.scene,this.new_coords);  //down
    }

    initMaterial(){
        this.texMineTop = new CGFtexture(this.scene, 'images/mineTop.png');
        this.texMineBottom = new CGFtexture(this.scene, 'images/mineBottom.png');
        this.texMineSide = new CGFtexture(this.scene, 'images/mineSide.png');
        this.mainApp = new CGFappearance(this.scene);
        this.mainApp.setDiffuse(1,1,1,1);
        this.mainApp.setAmbient(1,1,1,1);
        this.mainApp.setShininess(10);


    }


    display(){
        
        this.scene.pushMatrix();
        const sqrt = Math.sqrt(2)/2; 
        //quad1 -- front
        this.scene.pushMatrix();
        this.mainApp.setTexture(this.texMineSide);
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,0,sqrt); 
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad1.display();
        this.scene.popMatrix();

        //quad2 -- back
        this.scene.pushMatrix();
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,0,-sqrt);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad2.display();
        this.scene.popMatrix();

        //quad3 -- right
        this.scene.pushMatrix();
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(sqrt,0,0);
        this.scene.rotate(Math.PI/2, 0,1,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad3.display();
        this.scene.popMatrix(); 

        //quadr4 - left
        this.scene.pushMatrix();
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(-sqrt,0,0);
        this.scene.rotate(Math.PI/2,0,1,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad4.display();
        this.scene.popMatrix(); 

        //quad5 -- up
        this.scene.pushMatrix();
        this.mainApp.setTexture(this.texMineTop);
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,sqrt,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad5.display();
        this.scene.popMatrix();

        //quad6 -- down
        this.scene.pushMatrix();
        this.mainApp.setTexture(this.texMineBottom);
        this.mainApp.apply();
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(0,-sqrt,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad6.display();
        this.scene.popMatrix();

        this.scene.popMatrix();


    }
    
}