const SupplyStates = {
        INACTIVE: 0, 
        FALLING: 1, 
        LANDED: 2
}; 

const SCALE = 0.2; 
class MySupply extends CGFobject{
    
	constructor(scene){
        super(scene);		
        this.Pos = [];              //will save the current position 
        this.initPos = [];             //will save the inital position
        this.alpha = 0;   

        this.scene = scene;
		this. state = SupplyStates.INACTIVE; 
        this.initBuffers();
        this.initMaterial(); 

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
        this.mainApp = new CGFappearance(this.scene);
        this.mainApp.setDiffuse(1,1,1,1);
        this.mainApp.setAmbient(1,1,1,1);
        this.mainApp.setShininess(10);
        this.mainApp.loadTexture('images/wood.jpg'); 
    }

    //SWITCH STATE FUNCTIONS ---------------------------------------

    //checks init the position of the box 
    drop (dropPosition){
        this.state = SupplyStates.FALLING; 
        this.Pos = [...dropPosition]; 
        this.initPos = [...dropPosition]; 
    } 
    
    //checks if the box is on land
    land(){
	if (this.Pos[1] <= 0) 
	    this.state = SupplyStates.LANDED; 

    }
    

    //DIPLAY FUNCTIONS -------------------------------------------- 

    //manage the display based on the state
    display(){
        if (this.state == SupplyStates.FALLING)
            this.displayFalling(); 
        if (this.state == SupplyStates.LANDED)
            this.displayOnLanded(); 
    }

    //displays the box falling 
    displayFalling(){
        this.scene.pushMatrix();
        this.scene.translate(this.Pos[0], this.Pos[1], this.Pos[2]); 
        this.scene.rotate(this.alpha, 0, 1, 0);
    
        this.scene.pushMatrix();
        const sqrt = Math.sqrt(2)/2; 
        this.mainApp.apply(); 
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.scale(SCALE, SCALE, SCALE);
        
        //quad1 -- front
        this.scene.pushMatrix();
        this.scene.translate(0,0,sqrt); 
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad1.display();
        this.scene.popMatrix();

        //quad2 -- back
        this.scene.pushMatrix();
        this.scene.translate(0,0,-sqrt);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.scene.rotate(Math.PI, 0, 1 ,0); 
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
        this.scene.rotate(3*Math.PI/2,0,1,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad4.display();
        this.scene.popMatrix(); 

        //quad5 -- up
        this.scene.pushMatrix();
        this.scene.translate(0,sqrt,0);
        this.scene.rotate(3*Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad5.display();
        this.scene.popMatrix();

        //quad6 -- down
        this.scene.pushMatrix();
        this.scene.translate(0,-sqrt,0);
        this.scene.rotate(Math.PI/2, 1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad6.display();
        this.scene.popMatrix();

        this.scene.popMatrix();


        this.scene.popMatrix() ;

        this.land(); 			//checks if the supply is landed
    } 

    //display the box when it's landed
    displayOnLanded() {        
    
        this.scene.pushMatrix();
        this.mainApp.apply(); 
        this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
        this.scene.translate(this.Pos[0], 0.1, this.Pos[2]); 
        this.scene.rotate(this.alpha, 0, 1, 0);
        this.scene.scale(SCALE, SCALE, SCALE);

        //quad 1 
        this.scene.pushMatrix();
        this.scene.translate(1,0.1,0);              
        this.scene.rotate(Math.PI/6, 0,1,0);      

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad1.display();
        this.scene.popMatrix();

        //quad 2 

        this.scene.pushMatrix();
        this.scene.translate(0.4,0.1,0.6);      
        this.scene.rotate(Math.PI/3, 0,1,0);    

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad2.display();
        this.scene.popMatrix();

        //quad 3

        this.scene.pushMatrix();
        this.scene.translate(-0.6,0.1, 0.6);      
        this.scene.rotate(Math.PI/4, 0,1,0);      

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad3.display();
        this.scene.popMatrix();

        //quad 4 

        this.scene.pushMatrix();
        this.scene.translate(-1,0.1,0);      
        this.scene.rotate(Math.PI/4, 0,1,0);   

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad4.display();
        this.scene.popMatrix();

        //quad 5 

        this.scene.pushMatrix();
        this.scene.translate(-0.8,0.1,-0.8);      
        this.scene.rotate(Math.PI/6, 0,1,0);      

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad5.display();
        this.scene.popMatrix();

        //quad 6

        this.scene.pushMatrix();
    
        this.scene.translate(0,0.1,-0.8);      
        this.scene.rotate(Math.PI/7, 0,1,0);     

        this.scene.rotate(-Math.PI/2,1,0,0);
        this.scene.rotate(Math.PI/4, 0,0,1);
        this.quad6.display();
        this.scene.popMatrix();

        this.scene.popMatrix();

    } 


    turn(alpha) {
        if (this.state == SupplyStates.INACTIVE)
            this.alpha += alpha;
    } 

    update(t){
        if (this.state == SupplyStates.FALLING)  {
            t = t*0.001;                                        //to seconds
            this.Pos[1] -=  this.initPos[1]/3 * t; 
        } 
    }
    
}
