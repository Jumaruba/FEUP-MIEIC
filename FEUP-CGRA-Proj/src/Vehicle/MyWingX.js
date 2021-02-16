class MyWingX extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
    }

    initBuffers() {
        this.triangle = new MyTriangle(this.scene, 6);

        //show at both sides
        this.quad = new MyDiamond(this.scene);
        this.quad2 = new MyDiamond(this.scene);
    }


    display() {

        this.scene.pushMatrix();
        this.scene.scale(0.7, 0.8, 0.8);

        //triangle
        this.scene.pushMatrix();
        this.scene.rotate(-Math.PI, 1, 0, 0);
        this.scene.scale(0.6, 0.6, 0.6);
        this.triangle.display();
        this.scene.popMatrix();

        //square
        this.scene.pushMatrix();
        this.scene.translate(0, 0, -Math.sqrt(3) / 2 + 0.05);
        this.scene.rotate(Math.PI / 2, 0, 0, 1);
        this.scene.rotate(Math.PI / 4, 1, 0, 0);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.scale(0.43, 0.43, 0.43);
        this.quad.display();
        this.scene.rotate(Math.PI, 1, 0, 0);
        this.quad2.display();
        this.scene.popMatrix();

        this.scene.popMatrix();
    }


}
