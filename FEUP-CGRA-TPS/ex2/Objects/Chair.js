class Chair extends CGFobject{
    constructor(scene){
        super(scene); 
        
        this.scene = scene;
        scene.seat = new MyTable(scene); 
        scene.back = new MyQuad(scene); 
    }

    display(){
        var sizeTable = Math.sqrt(2)*0.3 + Math.sqrt(2)*2.5;
        var sizeChair = sizeTable*0.55;
        var y = sizeChair-sizeTable;
        this.scene.pushMatrix();
        this.scene.translate(0,y,0);
        this.scene.scale(0.2,0.55,0.5);
        this.scene.seat.display(); 
        this.scene.popMatrix(); 

        this.scene.pushMatrix(); 
        this.scene.translate(0, sizeChair - sizeTable + Math.sqrt(2)/2*1.17, 0.2*Math.sqrt(2)/2 - Math.sqrt(2)/2);
        this.scene.scale(0.8,1,0.2);
        this.scene.back.display();
        this.scene.popMatrix(); 
    }
}