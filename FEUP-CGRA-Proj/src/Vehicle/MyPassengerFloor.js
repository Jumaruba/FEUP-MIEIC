class MyPassengerFloor extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
    }

    initBuffers() {
        this.body = new MyCylinder(this.scene, 40);
        this.sphere1 = new MySphere(this.scene, 16, 8); //front sphere
        this.sphere2 = new MySphere(this.scene, 16, 8); //back sphere
    }

    display() {
        this.scene.pushMatrix();

        //body - cylinder 
        this.scene.pushMatrix();
        this.scene.translate(0, -0.7, -0.25);
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.1, 0.5, 0.1);
        this.body.display();
        this.scene.popMatrix();

        //sphere1 - front 
        this.scene.pushMatrix();
        this.scene.translate(0, -0.7, 0.25);
        this.scene.scale(0.1, 0.1, 0.1);
        this.sphere1.display();
        this.scene.popMatrix();

        //sphere2 - back
        this.scene.pushMatrix();
        this.scene.translate(0, -0.7, -0.25);
        this.scene.scale(0.1, 0.1, 0.1);
        this.sphere2.display();
        this.scene.popMatrix();

        this.scene.popMatrix();

    }


}
