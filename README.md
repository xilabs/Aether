Project Aether
======

The Aether Engine represents the future of simulated reality.  As computers continue to improve in computational power, less corners need to be cut in pursuit of VR.  We believe that voxel based physics engines or "atom" engines might be next evolution in immersive gaming.

Definitions: 

- Aether Engine:  A realtime soft simulation of physical interactions between "atoms"
- Moxel:    Smallest unit of simulated matter
- Voxel:	Unit of space created for management convenence.  Voxels contain moxels.


### Engine Overview
																						} moxel 0
																	} voxel 0	->		} moxel ...
					} shared_ptr<Universe> 		universe 	->		} voxel ...			} moxel n
					}												} voxel n
	aether.cpp ->	} shared_ptr<Logger> 		logger
					}
					} shared_ptr<Configuration>	config
					}
					} shared_ptr<ServiceManager> service_manager

The aether engine program creates several globals (universe, config, etc) before daemonizing.  Generally speaking, each manager type item presents a ```run()``` method in which it creates any worker threads and then returns.  It shuts down when ```stop()``` is called.  So running the universe (for example) looks like this:

```cpp
new Universe();
run();		// spawns threads... does not block
/* ... */
stop();
```

The ```universe``` item runs the universe simulation and provides any needed visibility into the universe.  Similarly, all services are managed by the singleton global ```service_manager```.  (```/* TODO */``` the ```service_manager->run();``` call blocks instead of returning.)

Since ```service_manager``` and ```universe``` both run independently (threadwise), they enjoy almost complete decoupling.

All logging is handled using the thread safe singleton ```logger``` which provides ```logger->notice()```, ```logger->warning()```, and ```logger->err()``` calls. 

## Engine Simulation


## Engine Services

Services (running on the engine under the aforementioned global singleton ```service_manager``` allow us to communicate with the moxel universe.  Currently, only websockets are supported.


### Websocket notes - encoding schemes

For *binary data* coming across the websocket: we essentially ferry groups of objects across the wire.  Here is what an object group looks like:

C++ Type		|		JS Type			|		Bytes		|		Name			|		Description
----------------|-----------------------|-------------------|-----------------------|-----------------------
unsinged int	|	 Uint32				|		4			|	object_type_id		|	object type ID
unsigned int	|	 Uint32				|		4			|	xheader_length		|	length of extra header
unsinged int	|	 Uint32				|		4			|	object_size			|	size of 1 object (padded to dword boundary)
unsigned int	|	 Uint32				|		4			|	object_count		|	total number of objects in payload
unsigned char	|	ArrayBuffer			|					|	xheader				|	data specific to this type of message (padded to dword boundary)
unsigned char	|	ArrayBuffer			|					|	objects				|	objects

And here are the object types:

Object type ID	|	Object
----------------|-----------
1000			|	Moxel
1001			|	Banana
1002			|	Pear


** Note:  ** If you create one of these data structures, please pad your data to the nearest dword boundary!


Suppose we send a group of moxels to the client.   The message could be decoded in JS using something like the following:

```js

    /**
     * Moxel object
     *
     */
    function Moxel(){};
    Moxel.prototype.object_type_id=1000;
    Moxel.prototype.to_string=function(){

        return "Moxel("+this.x+","+this.y+","+this.z+")";
    };
    Moxel.prototype.from_arraybuffer=function(buff){
        
        var dv = new DataView(buff);
        this.x=dv.getFloat64(0,true);
        this.y=dv.getFloat64(8,true);
        this.z=dv.getFloat64(16,true);
    };

    /**
     * Read Aether data, convert to usable objects
     *
     * @param buff arraybuffer of incoming data
     * @retval an array of native objects of the appropriate type (moxel, etc)
     */
    function process_aether_data(buff){

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

        // Reconstitute objects
        if(object_type != Moxel.prototype.object_type_id) {

            throw "Unknown object type received";
        }
        offset+=xheader_length;
        for(var n=0; n<object_count; n++){

            var m=new Moxel();
            m.from_arraybuffer(buff.slice(offset, offset+=object_size));
            objects[n]=m;
        }
        return objects;
    };

```








