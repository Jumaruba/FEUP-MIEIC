class MyTriangleSmall extends CGFobject{
    constructor(scene, coords){
        super(scene); 
        this.initBuffers();
        if (coords !== undefined) {
            this.texCoords = [...coords];
            this.updateTexCoordsGLBuffers();
        }
    }

    initBuffers(){
        this.vertices = [0,0,0,
                        0,1,0,
                        -1,0,0,
                        1,0,0];
        this.indices = [0,1,2,
                        2,1,0];

        this.normals = [];
        for (var i = 0; i < 3; i++) this.normals.push(0,0,1);

        //mapped to the blue
        this.texCoords = [
            0,0.25,
            0.25,0.25,
            0,0,
            0,0.5
        ];
        this.primitiveType = this.scene.gl.TRIANGLES; 
        this.initGLBuffers(); 

    }

}