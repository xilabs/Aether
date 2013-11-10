
var u = new Universe();

 $(document).ready(function(){
				
    var portal = new Portal(u);
                
    var controls = new THREE.OrbitControls( portal.camera, portal.canvas );
  
    render = function() {
        requestAnimationFrame(render);
        controls.update();
        portal.updateView();
        portal.renderer.render(portal.scene, portal.camera);
    }
                
    render();
});