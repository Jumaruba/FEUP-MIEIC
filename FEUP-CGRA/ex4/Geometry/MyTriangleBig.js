class MyTriangleBig extends CGFobject{
    constructor(scene){
        super(scene); 
        this.initBuffers(); 
    }

    initBuffers(){
        this.vertices = [0,0,0,
                        0,2,0,
                        -2,0,0,
                        2,0,0]; 
        this.indices = [0,1,2,
                        2,1,0]; 

        this.texCoords = [
            0.5,0,
            0.5,0.5,
            0.75,0,
            0,0
        ];
        this.primitiveType = this.scene.gl.TRIANGLES; 
        this.initGLBuffers(); 

    }

    updateTexCoords(coords){
        this.texCoords = [...coords];
        this.updateTexCoordsGLBuffers();
    }

}