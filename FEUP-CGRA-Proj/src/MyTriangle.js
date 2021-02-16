class MyTriangle extends CGFobject {
    constructor(scene, faces) {
        super(scene);
        this.faces = faces;
        this.initBuffers();
    }

    initBuffers() {

        this.angle = 360 / this.faces;
        this.l = Math.abs(Math.sin(Math.PI * this.angle / 2 / 180) * 2);        //side of the triangle
        this.h = Math.abs(Math.cos(Math.PI * this.angle / 2 / 180));          //high of the triangle

        this.vertices = [
            -this.l / 2, 0, this.h,         //0
            this.l / 2, 0, this.h,          //1
            0, 0, 0,                        //2
            -this.l / 2, 0, this.h,         //3
            this.l / 2, 0, this.h,          //4
            0, 0, 0                         //5
        ];
        this.texCoords = [
            1,1,
            0,0,
            0,1,
            0,0,
            1,1,
            1,0
        ]; 
        this.normals = [0,1,0,
                       0,1,0,
                       0,1,0,
                       0,-1,0,
                       0,-1,0,
                       0,-1,0]; 
        this.indices = [
            0, 1, 2,
            5, 4, 3
        ];
        this.primitiveType = this.scene.gl.TRIANGLES;

        this.initGLBuffers();
    }

}
