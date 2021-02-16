/**
* MyScene
* @constructor
*/
class MyScene extends CGFscene {
    constructor() {
        super();
    }
    init(application) {
        super.init(application);
        this.initCameras();
        this.initLights();

        //Background color
        this.gl.clearColor(0.0, 0.0, 0.0, 1.0); // gl é o acesso a opengl 

        this.gl.clearDepth(100.0);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.depthFunc(this.gl.LEQUAL);

        //Initialize scene objects
        this.axis = new CGFaxis(this);
        this.tangram = new MyTangram(this);
        this.cube = new MyUnitCube(this);
        this.table = new MyTable(this); 
        this.quad = new MyQuad(this); 
        this.chair = new Chair(this);
        //Objects connected to MyInterface
        this.displayAxis = true; 
        this.displayTangram = false; 
        this.displayQuad1 = false; 
        this.displayQuad2 = false; 
        this.scaleFactor = 1;
    }
    initLights() {
        this.lights[0].setPosition(15, 2, 5, 1);
        this.lights[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
        this.lights[0].enable();
        this.lights[0].setVisible(true); 
        this.lights[0].update();
    }
    initCameras() {
        this.camera = new CGFcamera(0.4, 0.1, 500, vec3.fromValues(15, 15, 15), vec3.fromValues(0, 0, 0));
    }
    setDefaultAppearance() {
        this.setAmbient(1, 1, 1, 1.0);
        this.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.setShininess(0);
    }
    display() {
        // ---- BEGIN Background, camera and axis setup
        // Clear image and depth buffer everytime we update the scene
        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
        // Initialize Model-View matrix as identity (no transformation
        this.updateProjectionMatrix();
        this.loadIdentity();
        // Apply transformations corresponding to the camera position relative to the origin
        this.applyViewMatrix();
        
        // Draw axis
        if (this.displayAxis)
            this.axis.display();

        
        this.setDefaultAppearance();

        var sca = [this.scaleFactor, 0.0, 0.0, 0.0,
            0.0, this.scaleFactor, 0.0, 0.0,
            0.0, 0.0, this.scaleFactor, 0.0,
            0.0, 0.0, 0.0, 1.0];

        this.multMatrix(sca);

        // ---- BEGIN Primitive drawing section
        this.pushMatrix(); 
        this.translate(0.5,-0.5,0);
        if (this.displayTangram)
            this.tangram.display();
        //it was supposed to be z = -0.5, but in order to the cube don't cross
        //the tangram we used -0.51
        if (this.displayQuad1){
            this.translate(0,0,-0.51);
            this.cube.display();
            
        }
        this.popMatrix();
        
        if (this.displayQuad2){
            this.pushMatrix();
            this.translate(0.5,0,0);
            this.translate(0,0,-Math.sqrt(2)/2 - 0.01);
            this.quad.display();
            this.popMatrix();
        }
        
        this.table.display();
        this.pushMatrix();
        this.scale(1.5,1,1.5);
        this.translate(0,0,-1.5); 
        this.chair.display();
        this.popMatrix(); 
        // ---- END Primitive drawing section
        

    }


}