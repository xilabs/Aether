function Portal(universe) {
    
    this.u = universe;
    this.v = new View();
    this.scene = new THREE.Scene();
    this.camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 ); 
    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setSize( window.innerWidth, window.innerHeight );
    this.i = 0;
    this.canvas = document.body.appendChild( this.renderer.domElement );
    this.canvas.id = "portal";
    this.camera.position.z = 50;
    
    this.populateView = function() {
        var moxels = this.u.moxels;
       
        var i = 0;
        while(moxels[i]) {
            var moxel = moxels[i];
            
            var geometry = new THREE.SphereGeometry(moxel.radius,10,10); 
            var material = new THREE.MeshNormalMaterial( {} ); 
            var sphere = new THREE.Mesh( geometry, material );
            sphere.position.x = moxel.position[0];
            sphere.position.y = moxel.position[1];
            sphere.position.z = moxel.position[2];
            sphere.overdraw = true;
            this.scene.add( sphere );
            this.v.objects.push(sphere);
            
            i++;
        }
    };
    
    this.updateView = function() {
        this.v.objects[0].position.x = this.u.moxels[0].position[0];
        this.v.objects[0].position.y = this.u.moxels[0].position[1];
    };
       
}

function View() {
    this.objects = new Array();
}