

function Universe() {
    
    this.moxels = new Array();
    this.objectTypes = [1000];
    
    this.createMoxel = function(position, radius) {
        
        var moxel = new Moxel();
        moxel.position = position;
        moxel.radius = radius;
        this.moxels.push(moxel);
        return moxel;
        
    };
    
    this.updateUniverse = function() {
        
    };
     
}

function Moxel() {
    
    this.object_type_id = 1000;
    this.position;
    this.radius;
    this.happy = "hmm";
    
    this.to_string = function(){

		return "Moxel("+this.position[0]+","+this.position[1]+","+this.position[2]+")";
    };
    
    
}

