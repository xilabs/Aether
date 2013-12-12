
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
	processParams(portal);
});

function processParams(portal) {
	
	var params = getParams();
	
	if (params["wsurl"]) {
	
		portal.updateCommLink(params["wsurl"], portal);
		
	}

}

function getParams() {
	
	var pKV = new Array();
	var url = window.location.toString();
	var urlArray = url.split("#");
	if (urlArray[1]) {
		var params = urlArray[1].split("&");
		
		var i = 0;
		while(params[i]) {
			var param = params[i].split("=");
			var key = param[0];
			var value = param[1];
			pKV[key] = value;
			i++;
		}
	}
	return pKV;
}