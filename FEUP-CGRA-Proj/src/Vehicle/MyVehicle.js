class MyVehicle extends CGFobject {
    constructor(scene) {

        super(scene);
        this.scene = scene;

        this.initTextures();
        this.initPosition();
        this.initAssets();
        this.automaticPilot = false;
        this.centerCirc = [0, 0];
        this.theta = 0; 					//angle between the center of the circle and the vehicle 

    }

    initPosition() {
        this.xPos = 0;
        this.yPos = 0;
        this.zPos = 0;
        this.alpha = 0;
        this.vel = 0;
    }



    initAssets() {
        this.body = new MySphere(this.scene, 16, 8, [0.7, 0.7, 1]);

        this.passenger_floor = new MyPassengerFloor(this.scene);

        this.leftMotor = new MyMotor(this.scene);
        this.rightMotor = new MyMotor(this.scene);

        this.rightProppeler = new MyProppeler(this.scene);
        this.leftPropperler = new MyProppeler(this.scene);

        this.wingUp = new MyWingY(this.scene);
        this.wingDown = new MyWingY(this.scene);
        this.wingLeft = new MyWingX(this.scene);
        this.wingRight = new MyWingX(this.scene);
        this.flag = new MyFlag(this.scene);

    }

    initTextures() {
        this.VehicleMaterial = new CGFappearance(this.scene);
        this.VehicleMaterial.setAmbient(0.1, 0.1, 0.1, 1);
        this.VehicleMaterial.setDiffuse(0.9, 0.9, 0.9, 1);
        this.VehicleMaterial.setSpecular(0.1, 0.1, 0.1, 1);
        this.VehicleMaterial.setShininess(10.0);
        this.VehicleMaterial.loadTexture('images/Vehicle/body.jpg');

        this.PassengerMaterial = new CGFappearance(this.scene);
        this.PassengerMaterial.setAmbient(0.1, 0.1, 0.1, 1);
        this.PassengerMaterial.setDiffuse(0.9, 0.9, 0.9, 1);
        this.PassengerMaterial.setSpecular(0.1, 0.1, 0.1, 1);
        this.PassengerMaterial.setShininess(10.0);
        this.PassengerMaterial.loadTexture('images/Vehicle/passenger.jpg');

        this.WingMaterial = new CGFappearance(this.scene);
        this.WingMaterial.setAmbient(0.1, 0.1, 0.1, 1);
        this.WingMaterial.setDiffuse(0.9, 0.9, 0.9, 1);
        this.WingMaterial.setSpecular(0.1, 0.1, 0.1, 1);
        this.WingMaterial.setShininess(10.0);
        this.WingMaterial.loadTexture('images/Vehicle/wings.jpg');
    }

    display() {
        
        this.scene.pushMatrix();
        
    
        this.scene.defaultAppearence.apply();
        
		//applying the rotation and translation of the vehicle 
        this.scene.translate(this.xPos, this.yPos, this.zPos);
        this.scene.rotate(this.alpha, 0, 1, 0);
	
		//flag ---------------------------------------
        this.flag.display();
       
		//body ---------------------------------------
		this.VehicleMaterial.apply();

		this.body.display();
        this.scene.defaultAppearence.apply();
		
		//passenger floor ----------------------------
        this.PassengerMaterial.apply();
        this.passenger_floor.display();

        //motors---------------------------------------
        this.scene.pushMatrix();
        this.scene.translate(-0.1, -0.73, -0.3);
        this.leftMotor.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(0.1, -0.73, -0.3);
        this.rightMotor.display();
        this.scene.popMatrix();

        //proppelers------------------------------------
        this.scene.pushMatrix();
        this.scene.translate(-0.1, -0.73, -0.4);
        this.rightProppeler.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(0.1, -0.73, -0.4);
        this.leftPropperler.display();
        this.scene.popMatrix();

        //wings-----------------------------------------
        this.WingMaterial.apply();

        this.scene.pushMatrix();
        this.scene.translate(0, 0.4, -0.45);
        this.wingUp.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(0, -0.4, -0.45);
        this.wingDown.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(0.4, 0, -0.45);
        this.wingRight.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.translate(-0.4, 0, -0.45);
        this.wingLeft.display();
        this.scene.popMatrix();

        this.scene.defaultAppearence.apply();
        this.scene.popMatrix();


    }


    update(t) {
        if (this.automaticPilot) {
            var angle = Math.PI * 2 * (t * 0.001) / 5;
            this.turn(-angle);
        
            
            //get vector of the center->position 
            let vectorX = this.xPos - this.centerCirc[0];
            let vectorZ = this.zPos - this.centerCirc[1];
            
            //applying rotation matrix
            //  [cos(theta)  -sin(theta)] [vectorX]
            //  [sin(theta)   cos(theta)] [vectorY]
            let DeslocX = vectorX  * Math.cos(angle) - vectorZ *Math.sin(angle);
            let DeslocZ = vectorX * Math.sin(angle) + vectorZ *Math.cos(angle);
            
            //Moving a point from the center to the actualPosition 
            this.xPos = DeslocX + this.centerCirc[0];
            this.zPos = DeslocZ + this.centerCirc[1];
            
            //update parts - set number 4 just for convinience 
            this.rightProppeler.update(4);
            this.leftPropperler.update(4);
        } else {
            this.xPos += this.vel * Math.sin(this.alpha) * t * 0.01;
            this.zPos += this.vel * Math.cos(this.alpha) * t * 0.01;

            //update parts 
            this.rightProppeler.update(this.vel);
            this.leftPropperler.update(this.vel);

        }

    }

    turn(alpha) {
        this.alpha += alpha;

        this.wingDown.turn(alpha);
        this.wingUp.turn(alpha);
    }

    reset() {
        this.automaticPilot = false;
        this.initAssets();
        this.initPosition(0, 0, 0);

    }

    getPos() {
        return [this.xPos, this.yPos, this.zPos];
    }

    accelerate(acel) {
        this.vel += acel;
        this.flag.updateSpeed(this.vel);
    
    }

    setAutomaticPilot() {
        this.automaticPilot = !this.automaticPilot;

        this.theta = (this.alpha - Math.PI/2); 
        this.initialZ = this.zPos; 
        //calculating the center of the circle  [x,z]
        var x = Math.sin(this.theta);
        var z = Math.cos(this.theta);
        this.centerCirc = [this.xPos + x * 5, this.zPos + z * 5];
        console.log(this.centerCirc);

        //initial angle ===> cos = x.z/ (||x||.||z||) => cos = z => acos(z) = angle 
       


    }

    //get the wing to go back to its normal position 
    backToNormal() {
        this.wingDown.backToNormal();
        this.wingUp.backToNormal();
    }







}
