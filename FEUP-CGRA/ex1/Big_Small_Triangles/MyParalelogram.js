class MyParalelogram extends CGFobject {
	constructor(scene) {
		super(scene);
		this.initBuffers();
	}

    initBuffers(){
        this.vertices = [0,0,0,     //0
                         1,1,0,     //1
                         2,0,0,     //2
                         3,1,0];    //3
        this.indices = [0,2,1,
                        2,3,1]; 

        this.primitiveType = this.scene.gl.TRIANGLES; 
        this.initGLBuffers(); 

    }
}