function Portal(universe) {
    
    this.u = universe;
    this.v = new View();
    this.scene = new THREE.Scene();
    this.scene.fog = new THREE.FogExp2( 0xcccccc, 0.005);
    this.camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 ); 
    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setSize( window.innerWidth, window.innerHeight );
    this.renderer.setClearColor( this.scene.fog.color, 1 );
    this.i = 0;
    this.canvas = document.body.appendChild( this.renderer.domElement );
    this.canvas.id = "portal";
    this.camera.position.z = 50;
    this.happy;
    var directionalLight = new THREE.DirectionalLight(0xffffff);
    directionalLight.position.set(1, 1, 1).normalize();
    this.scene.add(directionalLight);
    
    var ambientLight = new THREE.AmbientLight(0x222222);

    ambientLight.position.set(-50,-50,-50).normalize();
    this.scene.add(ambientLight);
    
    
    this.populateView = function(n) {
        var moxels = this.u.moxels;
       
        var i = n;
        while(moxels[i]) {
            var moxel = moxels[i];
            
            var geometry = new THREE.SphereGeometry(moxel.radius,10,10); 
            var material = new THREE.MeshLambertMaterial({color: 'blue'}); 
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
        
        var n = 0;
        while (this.v.objects[n]) {
            this.v.objects[n].position.x = this.u.moxels[n].position[0];
            this.v.objects[n].position.y = this.u.moxels[n].position[1];
            this.v.objects[n].position.z = this.u.moxels[n].position[2];
            n++;
        }
       
    };
       
}

function View() {
    this.objects = new Array();
}