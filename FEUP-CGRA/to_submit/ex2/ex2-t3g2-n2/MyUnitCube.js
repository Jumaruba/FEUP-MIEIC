class MyUnitCube extends CGFobject {
    constructor(scene){
        super(scene); 
        this.initBuffers(); 
    }
    initBuffers(){
        this.vertices = [-0.5,0.5,0.5,     //0
                         0.5,0.5,0.5,     //1
                         0.5,-0.5,0.5,    //2
                         -0.5,-0.5,0.5,    //3
                         0.5,0.5,-0.5,    //4
                         -0.5,0.5,-0.5,    //5
                         -0.5,-0.5,-0.5,   //6
                         0.5,-0.5,-0.5    //7   
                         ]; 
        this.indices= [0,3,1,
                       1,3,2,
                       4,1,2,
                       4,2,7,
                       4,0,1,
                       4,5,0,
                       0,5,6,
                       0,6,3,
                       2,3,6,
                       2,6,7,
                       5,4,7,
                       5,7,6]; 
        this.primitiveType = this.scene.gl.TRIANGLES; 
        this.initGLBuffers(); 
    }
}