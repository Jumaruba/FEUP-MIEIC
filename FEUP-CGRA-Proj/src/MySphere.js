class MySphere extends CGFobject {
    /* ro - size of the p*/
    constructor(scene, slices, stacks, ro) {
        super(scene);
        this.latDivs = stacks * 2;
        this.longDivs = slices;

        if (ro !== undefined) {
            this.xRo = ro[0];
            this.yRo = ro[1];
            this.zRo = ro[2];
        } else {
            this.xRo = this.yRo = this.zRo = 1;
        }


        this.initBuffers();
    }


    initBuffers() {
        this.vertices = [];
        this.indices = [];
        this.normals = [];
        this.texCoords = [];
        this.buffer = [];

        var phi = 0;
        var theta = 0;

        var phiInc = Math.PI / this.latDivs;
        var thetaInc = (2 * Math.PI) / this.longDivs;
        var latVertices = this.longDivs + 1;


        for (var latitude = 0; latitude <= this.latDivs; latitude++) {
            var sinPhi = Math.sin(phi);
            var cosPhi = Math.cos(phi);

            theta = 0;
            for (var longitude = 0; longitude <= this.longDivs; longitude++) {

                //--- Vertices coordinates
                var x = Math.cos(theta) * sinPhi * this.xRo;
                var y = cosPhi * this.yRo;
                var z = Math.sin(-theta) * sinPhi * this.zRo;


                this.vertices.push(x, y, z);

                //--- Indices
                var current = latitude * latVertices + longitude;
                if (latitude < this.latDivs && longitude < this.longDivs) {
                    var next = current + latVertices;


                    this.indices.push(current + 1, current, next);
                    this.indices.push(current + 1, next, next + 1);
                }


                this.normals.push(x, y, z);
                theta += thetaInc;

                //--- Texture Coordinates
                this.texCoords.push(longitude / this.longDivs, latitude / this.latDivs);

            }
            phi += phiInc;
        }


        this.primitiveType = this.scene.gl.TRIANGLES;
        this.initGLBuffers();
    }


}
