class MyParalelogram extends CGFobject {
	constructor(scene) {
		super(scene);
		this.initBuffers();
	}


    initBuffers(){
	    this.vertices = [];
	    for (var i = 0; i < 2; i++) this.vertices.push( 0,0,0,     //0
                                                        1,1,0,     //1
                                                        2,0,0,     //2
                                                        3,1,0);

        this.indices = [0,2,1,
                        2,3,1,
                        1,2,0,
                        1,3,2];

        this.normals = [];
        for (var i = 0; i < 8; i++){
            if (i >= 4) this.normals.push(0,0,-1);
            else this.normals.push(0,0,1);
        }

        this.primitiveType = this.scene.gl.TRIANGLES;

        this.initGLBuffers(); 

    }

}