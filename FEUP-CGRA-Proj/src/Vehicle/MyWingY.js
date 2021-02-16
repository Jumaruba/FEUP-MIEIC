const VARIANCE = Math.PI / 144;
const MAX_ANGLE = Math.PI / 6;

class MyWingY extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();

        this.turnAngle = 0;
    }

    initBuffers() {
        this.triangle = new MyTriangle(this.scene, 6);

        //show at the both sides
        this.quad = new MyDiamond(this.scene, undefined, 1);
        this.quad2 = new MyDiamond(this.scene, undefined, 1);
    }

    display() {


        this.scene.pushMatrix();
        this.scene.rotate(this.turnAngle, 0, 1, 0);
        this.scene.scale(0.5, 0.8, 0.8);

        //triangle
        this.scene.pushMatrix();
        this.scene.rotate(-Math.PI / 2, 1, 0, 0);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.rotate(-Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.6, 0.6, 0.6);
        this.triangle.display();
        this.scene.popMatrix();


        //square
        this.scene.pushMatrix();
        this.scene.translate(0, 0, -Math.sqrt(3) / 2 + 0.05);
        this.scene.rotate(Math.PI / 4, 1, 0, 0);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.scale(0.43, 0.43, 0.43);
        this.quad.display();
        this.scene.rotate(Math.PI, 0, 1, 0);
        this.quad2.display();
        this.scene.popMatrix();

        this.scene.popMatrix();
    }


    //Animation functions 
    turn(alpha) {
        if (alpha < 0 && this.turnAngle - VARIANCE > -MAX_ANGLE) //pressed B                                 
            this.turnAngle = this.turnAngle - VARIANCE;

        else if (alpha > 0 && this.turnAngle + VARIANCE < MAX_ANGLE) //pressed A
            this.turnAngle = this.turnAngle + VARIANCE;

    }


    backToNormal() {
        if (this.turnAngle > 0) this.turnAngle -= VARIANCE;
        if (this.turnAngle < 0) this.turnAngle += VARIANCE;
    }
}
