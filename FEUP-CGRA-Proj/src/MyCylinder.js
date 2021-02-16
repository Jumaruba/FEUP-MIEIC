class MyCylinder extends CGFobject{
    constructor(scene, slices){
        super(scene);
        this.scene = scene; 
        this.slices = Math.round(slices);           //Number of slices integer
        if (this.slices <= 2) this.slices = 3;      //Min number of slices to form a polygon
        this.initBuffers(); 
        
        
    }
    

    initBuffers(){
        this.angle = 2*Math.PI/this.slices;         
        this.texSlice = 1/this.slices;              //Size of the slice in s axis
        
        this.vertices = []; 
        this.indices = []; 
        this.texCoords = []; 
        this.normals = [];
        
        this.scene.pushMatrix(); 
        for (let i= 0; i < this.slices+1; i++){
            this.vertices.push(Math.cos(i*this.angle),1,Math.sin(this.angle*i));  
            this.normals.push(Math.cos(i*this.angle),0,Math.sin(this.angle*i));
            this.texCoords.push(i*this.texSlice, 0); 
            
            this.vertices.push(Math.cos(i*this.angle),0,Math.sin(this.angle*i));    
            this.normals.push(Math.cos(i*this.angle),0,Math.sin(this.angle*i));
            this.texCoords.push(i*this.texSlice, 1); 
            
            if (i !== 0){                
                this.indices.push((i-1)*2,i*2,i*2-1);
                this.indices.push(i*2, i*2+1, i*2-1);

            }
        }
        this.scene.popMatrix();
        this.primitiveType = this.scene.gl.TRIANGLES;
        this.initGLBuffers(); 
    }
    
    
    updateBuffers(slices){
        this.slices = Math.round(slices);  
        if (this.slices <= 2) this.slices = 3;  
        this.texSlices = 1/this.slices; 
        this.initBuffers();
        
    }
    
}
             
