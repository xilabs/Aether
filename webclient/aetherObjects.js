

function Universe() {
    
    this.moxels = new Array();
    
    this.createMoxel = function(position, radius) {
        
        var moxel = new Moxel();
        moxel.position = position;
        moxel.radius = radius;
        this.moxels.push(moxel);
        return moxel;
        
    }
    
    this.updateUniverse = function() {
        
    }
     
}

function Moxel() {
    
    this.position;
    this.radius;
    this.happy = "hmm";
    
}