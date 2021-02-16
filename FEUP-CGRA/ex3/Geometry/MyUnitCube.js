class MyUnitCube extends CGFobject {
    constructor(scene){
        super(scene); 
        this.initBuffers(); 
    }
    initBuffers(){
        this.vertices = [
            //front face (z axis positive)
            -0.5,0.5,0.5,       //0
            -0.5,-0.5,0.5,      //1
            0.5,-0.5,0.5,       //2
            0.5,0.5,0.5,        //3

            //back face (z axis negative)
            -0.5,0.5,-0.5,      //4
            0.5,0.5,-0.5,       //5
            0.5,-0.5,-0.5,      //6
            -0.5,-0.5,-0.5,     //7

            //up face (y axis positive)
            0.5,0.5,-0.5,       //8
            -0.5,0.5,-0.5,      //9
            -0.5,0.5,0.5,       //10
            0.5,0.5,0.5,        //11

            //down face (y axis negative)
            -0.5,-0.5,-0.5,     //12
            0.5,-0.5,-0.5,      //13
            0.5,-0.5,0.5,       //14
            -0.5,-0.5,0.5,      //15

            //right face (x axis positive)
            0.5,0.5,-0.5,       //16
            0.5,0.5,0.5,        //17
            0.5,-0.5,0.5,       //18
            0.5,-0.5,-0.5,      //19

            //left face (x axis negative)
            -0.5,0.5,-0.5,      //20
            -0.5,-0.5,-0.5,     //21
            -0.5,-0.5,0.5,      //22
            -0.5,0.5,0.5        //23


        ];

        this.indices = [

            //front face (z axis positive)
            0,1,2,
            2,3,0,
            //back face (z axis negative)
            4,5,6,
            6,7,4,
            //up face (y axis positive)
            8,9,10,
            10,11,8,
            //down face (y axis negative)
            12,13,14,
            14,15,12,
            //right face (x axis positive)
            16,17,18,
            18,19,16,
            //left face (x axis negative)
            20,21,22,
            22,23,20


        ];

        this.normals = [
            //front face (z axis positive)
            0,0,1,
            0,0,1,
            0,0,1,
            0,0,1,
            //back face (z axis negative)
            0,0,-1,
            0,0,-1,
            0,0,-1,
            0,0,-1,
            //up face (y axis positive)
            0,1,0,
            0,1,0,
            0,1,0,
            0,1,0,
            //down face (y axis negative)
            0,-1,0,
            0,-1,0,
            0,-1,0,
            0,-1,0,
            //right face (x axis positive)
            1,0,0,
            1,0,0,
            1,0,0,
            1,0,0,
            //left face (x axis negative)
            -1,0,0,
            -1,0,0,
            -1,0,0,
            -1,0,0

        ];


        this.primitiveType = this.scene.gl.TRIANGLES; 
        this.initGLBuffers(); 
    }
}