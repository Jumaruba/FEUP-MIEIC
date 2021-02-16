/**
 * MyScene
 * @constructor
 */

const POSY_VEHICLE = 5;                     //y position of the vehicle
const BODY_DIM = 0.7;                       //dimension of the body of the vehicle
class MyScene extends CGFscene {
    constructor() {
        super();
        this.actualTime = 0;
        this.timeBefore = 0;
        this.L_Pressed = false; 
        this.P_Pressed = false; 
    }

    init(application) {
        super.init(application);
        this.initCameras();
        this.initLights();
        this.QuadMaterial();                //setting the material of the quad
        this.CylinderMaterial();            //setting the cylinder Material

        this.accel = 0.001;                 //value of the acceleration
        this.angleChange = Math.PI / 30;    //angle of rotation 
        this.speedFactor = 1;
        this.scaleFactor = 1;


        //setting console variables -----------------------------
        this.nFaces = 5;
        this.nSuppliesDelivered = 0;
        this.totalSupplies = 5;
        this.displayAxis = false;
        this.displaySphere = false;
        this.displayCylinder = false;
        this.displaySkybox = true;
        this.automaticPilot = false;
        this.displayVehicle = true;
        this.displayTerrain = true;

        this.selectedTex = 0;
        this.selectedTexCylinder = -1;
        this.enableTexCylinder = false;


        //textures cubemap --------------------------------------
        this.texture1 = new CGFtexture(this, "images/cubemap/interstellarClouds.jpg");
        this.texture2 = new CGFtexture(this, "images/cubemap/stormyDays.jpg");
        this.texture3 = new CGFtexture(this, "images/cubemap/violentDays.jpg");
        this.texture4 = new CGFtexture(this, "images/cubemap/grimmNight.jpg");


        this.textures = [this.texture1, this.texture2, this.texture3, this.texture4];

        this.textureIds = {
            'interstellar': 0,
            'storm': 1,
            'violent': 2,
            'grimm': 3
        };

        //textures cylinder -------------------------------------
        this.textureCylinder1 = new CGFtexture(this, "images/earth.jpg");
        this.texturesCylinder = [this.textureCylinder1];
        this.texturesCylinderId = {
            "map": 0
        };

        //Background color --------------------------------------
        this.gl.clearColor(0.0, 0.0, 0.0, 1.0);

        this.gl.clearDepth(100.0);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.depthFunc(this.gl.LEQUAL);

        this.setUpdatePeriod(50);
        this.defaultApp(); //set the default appearence
        this.enableTextures(true);


        //Initialize scene objects ------------------------------
        this.axis = new CGFaxis(this);
        this.incompleteSphere = new MySphere(this, 16, 8);
        this.cylinder = new MyCylinder(this, 6);
        this.skyBox = new MyUnitCubeQuad(this);

        this.terrain = new MyTerrain(this, 20);
        this.vehicle = new MyVehicle(this);
        this.billboard = new MyBillboard(this);
        //this.flag = new MyFlag(this);

        this.supplies = [];
        this.initSupplies();

        //Initialize sphere material -------------------------------
        this.SphereMaterial = new CGFappearance(this);
        this.SphereMaterial.setAmbient(0.1, 0.1, 0.1, 1);
        this.SphereMaterial.setDiffuse(0.9, 0.9, 0.9, 1);
        this.SphereMaterial.setSpecular(0.1, 0.1, 0.1, 1);
        this.SphereMaterial.setShininess(10.0);
        this.SphereMaterial.loadTexture('images/earth.jpg');

        this.texture1 = new CGFtexture(this, 'images/earth.jpg');


    }

    QuadMaterial() {
        this.mainApp = new CGFappearance(this);
        this.mainApp.setDiffuse(1, 1, 1, 1);
        this.mainApp.setAmbient(1, 1, 1, 1);
        this.mainApp.setShininess(10);
    }

    CylinderMaterial() {
        this.cylinderApp = new CGFappearance(this);
        this.cylinderApp.setAmbient(0.7, 0.7, 0.7, 1);
        this.cylinderApp.setDiffuse(1, 1, 1, 1);
        this.cylinderApp.setShininess(7);
    }


    defaultApp() {
        this.defaultAppearence = new CGFappearance(this);
        this.defaultAppearence.setAmbient(0.2, 0.4, 0.8, 1.0);
        this.defaultAppearence.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.defaultAppearence.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.defaultAppearence.setShininess(10.0);

    }

    initSupplies() {
        for (var i = 0; i < this.totalSupplies; i++)
            this.supplies.push(new MySupply(this));
    }
    
    initLights() {
        this.lights[0].setPosition(15, 2, 5, 1);
        this.lights[0].setAmbient(0.7, 0.7, 0.7, 1);
        this.lights[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
        this.lights[0].setSpecular(1, 1, 1, 1.0);
        this.lights[0].enable();
        this.lights[0].update();
    }

    initCameras() {
        this.camera = new CGFcamera(0.4, 0.1, 500, vec3.fromValues(15, 15, 15), vec3.fromValues(0, 0, 0));
    }

    setDefaultAppearance() {
        this.setAmbient(0.2, 0.4, 0.8, 1.0);
        this.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.setShininess(10.0);
    }

    //update the texture inside the cubemap
    updateAppliedTex() {
        this.mainApp.setTexture(this.textures[this.selectedTex]);
    }

    updateAppliedTexCylinder() {
        this.cylinderApp.setTexture(this.texturesCylinder[this.selectedTexCylinder]);
    }
    
    update(t) {
        this.checkKeys();

        this.actualTime = t;
        this.vehicle.update(this.actualTime - this.timeBefore);
        this.vehicle.flag.update(t/100 % 1000);
        //update supplies 
        for (var i = 0; i < this.supplies.length; i++){
            this.supplies[i].update(this.actualTime - this.timeBefore);
        }
        this.billboard.update(this.actualTime - this.timeBefore);
        this.timeBefore = t;

    }

    checkKeys() {
        var text = "Keys pressed: ";
        var keysPressed = false;
        var AD_Pressed = false;

        

        if (this.gui.isKeyPressed("KeyW") && this.automaticPilot === false) {
            this.vehicle.accelerate(this.accel * this.speedFactor);
            text += " W ";
            keysPressed = true;
        }

        if (this.gui.isKeyPressed("KeyS") && this.automaticPilot === false) {
            this.vehicle.accelerate(-this.accel * this.speedFactor);
            text += " S ";
            keysPressed = true;
        }

        if (this.gui.isKeyPressed("KeyA") && this.automaticPilot === false) {
            this.vehicle.turn(this.angleChange);
            for (let i = 0; i < this.supplies.length; i++)
                this.supplies[i].turn(this.angleChange);
            text += " A ";
            keysPressed = true;
            AD_Pressed = true;
        }

        if (this.gui.isKeyPressed("KeyD") && this.automaticPilot === false) {
            this.vehicle.turn(-this.angleChange);
            for (let i = 0; i < this.supplies.length; i++)
                this.supplies[i].turn(this.angleChange);
            text += " D ";
            keysPressed = true;
            AD_Pressed = true;
        }


        if (this.gui.isKeyPressed("KeyR")) {
            this.vehicle.reset();
            text += " R ";
            this.supplies = [];
            this.initSupplies();
            this.nSuppliesDelivered = 0;
            keysPressed = true;
            this.automaticPilot = false;
        }

        if (this.gui.isKeyPressed("KeyP") && this.P_Pressed == false) {
            text += " P ";
            keysPressed = true;
            this.automaticPilot = !this.automaticPilot;
            this.vehicle.setAutomaticPilot();
            this.P_Pressed = true; 

        }

        if (!this.gui.isKeyPressed("KeyP")){
            this.P_Pressed = false; 
        }
        
        if (this.gui.isKeyPressed("KeyL") && this.L_Pressed == false) {
            
            this.realeaseSupply();
            text += " L ";
            keysPressed = true; 
            this.L_Pressed = true;

        }
        if (!this.gui.isKeyPressed("KeyL")){
            this.L_Pressed = false; 
        }

        if (AD_Pressed === false) {
            this.vehicle.backToNormal();
        }
        if (keysPressed)
            console.log(text);
            }

    realeaseSupply() {
        //if there's no more supplies to release in the array, add more 5 supplies
        if (this.nSuppliesDelivered == this.supplies.length) this.initSupplies();
        
        var pos = [...this.vehicle.getPos()];
        pos[1] += POSY_VEHICLE - BODY_DIM * this.scaleFactor;           //position in y considering the size of the vehicle and y position 
        
        this.supplies[this.nSuppliesDelivered++].drop(pos);
    }


    display() {

        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);


        this.updateProjectionMatrix();
        this.loadIdentity();

        this.applyViewMatrix();

        // Draw axis
        if (this.displayAxis)
            this.axis.display();

        // Textures 
        this.defaultAppearence.apply();
        this.setDefaultAppearance();
        this.billboard.display();
        //update objects 
        this.cylinder.updateBuffers(this.nFaces);

        // ---- BEGIN Primitive drawing section


        //cylinder ----------------------------------------------
        this.pushMatrix();
        if (this.displayCylinder) {
            //if it's suppose to display a texture 
            if (this.enableTexCylinder) {
                this.updateAppliedTexCylinder();
                this.cylinderApp.apply();
            }
            this.cylinder.display();
        }
        this.popMatrix();

        //cubemap -----------------------------------------------
        this.pushMatrix();
        if (this.displaySkybox) {
            this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_MAG_FILTER, this.gl.LINEAR);
            this.updateAppliedTex();
            this.mainApp.apply();
            this.scale(Math.sqrt(2) * 25, Math.sqrt(2) * 25, Math.sqrt(2) * 25);
            this.skyBox.display();
        }

        this.popMatrix();

        //sphere -----------------------------------------------
        this.SphereMaterial.apply();
        if (this.displaySphere)
            this.incompleteSphere.display();



        //vechile -----------------------------------------------
        if (this.displayVehicle) {
            this.pushMatrix();
            this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_MAG_FILTER, this.gl.LINEAR);
            this.translate(0, POSY_VEHICLE, 0);
            this.scale(this.scaleFactor, this.scaleFactor, this.scaleFactor);
            this.vehicle.display();
            //this.flag.display();
            this.popMatrix();

            //supplies ------------------------------------------
            for (var i = 0; i < this.supplies.length; i++)
                this.supplies[i].display();

        }


        //terrain ----------------------------------------------
        this.pushMatrix();
        this.rotate(-Math.PI / 2, 1, 0, 0);
        if (this.displayTerrain)
            this.terrain.display();

        this.popMatrix();
        this.setActiveShader(this.defaultShader);


        // ---- END Primitive drawing section
    }
    
}
