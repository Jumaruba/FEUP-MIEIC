/**
 * MyDiamond
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyDiamond extends CGFobject {
    constructor(scene, coords, newPos) {
        super(scene);
        if (newPos !== undefined)
            this.newPos = newPos;

        else this.newPos = 1;
        this.initBuffers(); 
        if (coords !== undefined)
            this.updateTexCoords(coords);


    }

    initBuffers() {
        this.vertices = [
            -this.newPos, 0, 0,	//0
            0, -this.newPos, 0,	//1
            0, this.newPos, 0,	//2
            this.newPos, 0, 0	//3
        ];

        this.indices = [
            0, 1, 2,
            1, 3, 2
        ];

        this.normals = [];

        for (let i = 0; i < 4; i++) this.normals.push(0, 0, 1);

        this.texCoords = [
            0, 0.5,
            0.25, 0.75,
            0.25, 0.25,
            0.5, 0.5
        ];
        
        this.primitiveType = this.scene.gl.TRIANGLES;

        this.initGLBuffers();
    }

    updateTexCoords(coords) {
        this.texCoords = [...coords];
        this.updateTexCoordsGLBuffers();
    }
    
}

