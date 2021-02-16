/**
 * MyDiamond
 * @constructor
 * @param scene - Reference to MyScene object
 */

 class MyTriangle extends CGFobject{
    constructor(scene) {
		super(scene);
		this.initBuffers();
	}
     initBuffers(){
         this.vertices = [
            0,0,0,          //0
            -1,1,0,         //1
            -1,0,0,         //2
            -1,-1,0,        //3
            0,-1,0,         //4
            1,-1,0          //5
        ];

        this.indices = [
            0,1,2,
            0,2,3,
            0,3,4,
            0,4,5

        ]; 
        this.primitiveType = this.scene.gl.TRIANGLES;

		this.initGLBuffers();
     }
 }