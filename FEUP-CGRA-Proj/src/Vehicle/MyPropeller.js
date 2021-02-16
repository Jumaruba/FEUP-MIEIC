const PROP_FACTOR = 0.5;						//proportionality factor for the proppeler rotation
class MyProppeler extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
        this.proppelerAngle = Math.PI;
    }


    initBuffers() {
        this.proppeler = new MySphere(this.scene, 16, 8, [0.01, 0.01, 0.1]);
    }


    display() {
        this.scene.pushMatrix();
        this.scene.rotate(this.proppelerAngle, 0, 0, 1);            //animation 
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.proppeler.display();
        this.scene.popMatrix();
    }

    update(vel) {
        this.proppelerAngle += vel / PROP_FACTOR;
    }

}
