class MyMotor extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
    }

    initBuffers() {
        this.body = new MySphere(this.scene, 16, 8, [1, 1, 1]);
    }


    display() {
        this.scene.pushMatrix();
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.04, 0.1, 0.04);
        this.body.display();
        this.scene.popMatrix();
    }

}
