class MyBillboard extends CGFobject {
    constructor(scene) {
        super(scene);
        this.base = new MyPlane(this.scene, 20);
        this.baseB = new MyPlane(this.scene, 20);
        this.panel = new MyPlane(this.scene, 20);
        this.supLeft = new MyPlane(this.scene,20);
        this.supRight = new MyPlane(this.scene,20);
        this.supLeftB = new MyPlane(this.scene,20);
        this.supRightB = new MyPlane(this.scene,20);
        this.initShaders();
        this.initTextures();
    }

    initTextures() {

        this.billboardTexture = new CGFappearance(this.scene);
        this.billboardTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.billboardTexture.setDiffuse(0.9,0.9,0.9,1);
        this.billboardTexture.setSpecular(0,0,0,1);
        this.billboardTexture.setShininess(10.0);
        this.billboardTexture.loadTexture('images/plane.png');
        this.billboardTexture.setTextureWrap('REPEAT', 'REPEAT');
        this.supTexture = new CGFappearance(this.scene);
        this.supTexture.setAmbient(0.1,0.1,0.1,1);
        this.supTexture.setDiffuse(0.9,0.9,0.9,1);
        this.supTexture.setSpecular(0,0,0,1);
        this.supTexture.setShininess(10.0);
        this.supTexture.loadTexture('images/panel.jpeg');
        this.supTexture.setTextureWrap('REPEAT', 'REPEAT');

    }
    
    initShaders(){
        this.shader = new CGFshader(this.scene.gl, "shaders/billboard.vert", "shaders/billboard.frag");
        this.shader.setUniformsValues({nSuppliesDelivered: this.scene.nSuppliesDelivered});
        this.shader.setUniformsValues({totalSupplies: this.scene.totalSupplies});
    }
    update(t){
        this.shader.setUniformsValues({nSuppliesDelivered: this.scene.nSuppliesDelivered});
    }
    reset(){
        this.shader.setUniformsValues({nSuppliesDelivered: 0});
    }

    display(){
        this.scene.pushMatrix();
        this.scene.translate(-3,-7.5,-20);
        this.scene.translate(2,9,17);
        this.scene.rotate(-Math.PI/8.0,0,1,0);
        
        this.scene.pushMatrix();
        this.supTexture.apply();
        this.scene.translate(0,-1,-0.9);
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.scale(0.20,1,1);
        this.supLeft.display();
        this.scene.popMatrix();
        
        this.scene.pushMatrix();
        this.supTexture.apply();
        this.scene.translate(0,-1,0.9);
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.scale(0.20,1,1);
        this.supRight.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.supTexture.apply();
        this.scene.translate(0,-1,-0.9);
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.rotate(Math.PI,0,1,0);
        this.scene.scale(0.20,1,1);
        this.supLeftB.display();
        this.scene.popMatrix();
        
        this.scene.pushMatrix();
        this.supTexture.apply();
        this.scene.translate(0,-1,0.9);
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.rotate(Math.PI,0,1,0);
        this.scene.scale(0.20,1,1);
        this.supRightB.display();
        this.scene.popMatrix();
        
        this.scene.pushMatrix();
        this.billboardTexture.apply();
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.scale(2,1,1);
        this.base.display();
        this.scene.popMatrix();

        this.scene.pushMatrix(); 
        this.supTexture.apply();
        this.scene.rotate(-Math.PI/2.0,0,1,0);
        this.scene.scale(2,1,1);
        this.baseB.display();
        this.scene.popMatrix();

        this.scene.pushMatrix();
        this.scene.setActiveShader(this.shader);
        this.scene.scale(1.5,0.2,1);    
        this.scene.rotate(Math.PI/2.0,0,1,0);
        this.scene.translate(0,-1,0.01);
        this.panel.display(); 
        this.scene.popMatrix();
        
        this.scene.setActiveShader(this.scene.defaultShader);
        this.scene.popMatrix();
    }
}