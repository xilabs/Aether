function Portal(universe) {
    
    this.u = universe;
    this.v = new View();
    this.scene = new THREE.Scene();
	this.commLink = new CommLink(this);
    this.scene.fog = new THREE.FogExp2( 0xcccccc, 0.005);
    this.camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 ); 
    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setSize( window.innerWidth, window.innerHeight );
    this.renderer.setClearColor( this.scene.fog.color, 1 );
    this.i = 0;
    this.canvas = document.body.appendChild( this.renderer.domElement );
    this.canvas.id = "portal";
	this.cmd = new CmdModule(this);
    this.camera.position.z = 50;
    this.happy;
    this.projector = new THREE.Projector();
    this.PI2 = Math.PI * 2;
    this.particleMaterial = new THREE.SpriteCanvasMaterial( {
        color: 0x000000,
        program: function ( context ) {
			context.beginPath();
			context.arc( 0, 0, 1, 0, this.PI2, true );
			context.fill();
		}
    });
	
	
    
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
    
    this.onPortalClick = function(event) {
        
        var offset = $("#portal").offset();
        var relX = event.clientX - offset.left;
        var relY = event.clientY - offset.top;
        var pWidth = $("#portal").width();
        var pHeight = $("#portal").height();
        
        event.preventDefault();
        
        var vector = new THREE.Vector3( ( relX / pWidth ) * 2 - 1, - ( relY / pHeight ) * 2 + 1, 0.5 );
        
        this.projector.unprojectVector( vector, this.camera );

        var raycaster = new THREE.Raycaster( this.camera.position, vector.sub( this.camera.position ).normalize() );
        var intersects = raycaster.intersectObjects( this.v.objects );

        if ( intersects.length > 0 ) {

            intersects[ 0 ].object.material.color.setHex( Math.random() * 0xffffff );

        }
    };
	
	this.updateCommLink = function(url, portal) {
		portal.commLink.url = url;
		//u.moxels.splice(0);
		portal.commLink.init(portal.commLink);
	}
	
	this.init = function(portal) {
	
		$("#portal").click(function() {
			portal.onPortalClick(event);
		});
		
	};
    
	this.init(this);
}

function View() {
    this.objects = new Array();
}

function CmdModule(portal) {
	this.skeleton = "<div id='cmd'><form id='cmdForm'><input type='text' id='cmdLine' autocomplete='off'></form><div id='cmdResponse'></div></div>";
	this.cmdActive = false;
	this.responses = new Array();
	this.responsesLimit = 20;
	this.portal = portal;
	
	this.processCmd = function(cmd, cmdModule) {
		var parsedCmd = cmd.split(" ");
		var target = parsedCmd[0];
		var validTargets = ["/client", "/help"];
		
		if (validTargets.indexOf(target) != -1) {
			if (target == "/client") {
				cmdModule.processClientCmd(cmd, cmdModule);
			} else if (target == "/help") {
				cmdModule.updateResponse("Please use one of the following targets:<br>/client</br>/server", cmdModule);
			}
		} else {
			cmdModule.portal.commLink.sendMessage(cmd, cmdModule.portal.commLink);
		}
	};
	
	this.processClientCmd = function(cmd, cmdModule) {
		var parsedCmd = cmd.split(" ");
		var command = parsedCmd[1];
		var cmdValue = parsedCmd[2];
		var validCommands = ["wsurl", "help"];
		
		if (validCommands.indexOf(command) != -1) {
			if(command == validCommands[0]) {
				portal.updateCommLink(cmdValue, portal);
			} else if (command == validCommands[1]) {
				var commandString = "";
				var i=0;
				while (validCommands[i]) {
					commandString = validCommands[i] + "  " + commandString;
					i++;
				}
				cmdModule.updateResponse("Please use one of the following client commands: " + commandString, cmdModule);
			}
		} else {
			cmdModule.updateResponse("Not a valid client command.  Type \"/client help\" to see a list of available commands.", cmdModule);
		}
	}
	
	this.updateResponse = function(response, cmdModule) {
		cmdModule.responses.push(response);
		var rResponses = cmdModule.responses.slice(0);
		rResponses.reverse();
		var responseHTML = "";
		
		var i = 0;
		while (rResponses[i]) {
			responseHTML = responseHTML + "<div class='line'>" + rResponses[i] + "</div>";
			i++;
		}
		
		$("#cmdResponse").html(responseHTML);
		
		if (cmdModule.responses.length >= cmdModule.responsesLimit) {
			cmdModule.responses.splice(0,1);
		}
	}
	
	this.init = function(cmdModule) {
		$("body").prepend(this.skeleton);
		$("#cmd").width($("#portal").width());
		$("#cmdLine").width($("#portal").width() - 9);
		$(document).keypress(function(event) {
            if (event.which == 96) {
                if (!this.cmdActive) {
                    $("#cmd").show();
                    $("#cmdLine").focus();
                } else {
                    $("#cmdLine").blur();
                    $("#cmd").hide();
                }
				this.cmdActive = !this.cmdActive;
                return false;
            }
        });
        $("#cmdForm").submit(function(e) {
			e.preventDefault();
			//portal.getCommLink().send($("#cmdLine").val());
			if ($("#cmdLine").val() != "") {
				cmdModule.processCmd($("#cmdLine").val(), cmdModule);
			}
            $("#cmdLine").val("");
            return false;
        });
	}
	
	this.init(this);
}

function CommLink(portal) {
	this.url = "ws://aether.xilabs.net:9002";
	this.ws;

	this.from_arraybuffer = function(buff){
  
        var position = new Array;
    
        var dv = new DataView(buff);
                
        position[0] = dv.getFloat64(0,true);
        position[1] = dv.getFloat64(8,true);
        position[2] = dv.getFloat64(16,true);
                
        return position;
                 
    };
	
	this.process_aether_data = function(buff, commLink) {
                
		// Read incoming data per Aether binary spec
		var dv = new DataView(buff);
		var offset=0;

		// Header data
		var object_type=dv.getUint32(offset, true);
		var xheader_length=dv.getUint32(offset+=4, true);
		var object_size=dv.getUint32(offset+=4, true);
		var object_count=dv.getUint32(offset+=4, true);
		var xheader=new Uint8Array(buff,offset+=4, xheader_length);
		var objects=new Array(object_count);
                
		
                
		offset+=xheader_length;
                
		for(var n=0; n<object_count; n++){
                        
			var b = commLink.from_arraybuffer(buff.slice(offset, offset+=object_size));
                       
			objects[n]=b;       
                        
		}
                
		return objects;
	};
	
	this.sendMessage = function(message, commLink) {
		commLink.ws.send(message);
	};
	
	this.init = function(commLink) {
		
		if (commLink.ws) {
			commLink.ws.close();
			//commLink.ws = null;
		}
		commLink.ws = new WebSocket(commLink.url);
		commLink.ws.binaryType="arraybuffer";
		var happy = commLink;
		
		commLink.ws.onmessage = function(e) {
			//console.log();
			if (typeof e.data == "string") {
				portal.cmd.updateResponse(e.data, portal.cmd);
			} else {
				var objects = happy.process_aether_data(e.data, happy);
				
				if (e.data)
				
				if(u.moxels.length > objects.length) {
					
					//u.moxels.splice(0);
					
				}
				
				for(var n=0; n<objects.length; n++) {
					if (n < u.moxels.length) {
						u.moxels[n].position = objects[n];
					} else {
						u.createMoxel(objects[n], 5);
						portal.populateView(n);	
					}
				}
			}
		}
	};
        
	
	this.init(this);
}