## Services

Services allow us to communicate with the moxel universe.  Currently, only websockets are supported


### Websocket notes - encoding schemes

For *binary data* coming across the websocket: we essentially ferry groups of objects across the wire.  Here is what an object group looks like:

C++ Type		|		JS Type			|		Bytes		|		Name			|		Description
unsinged int	|	 Uint32				|		4			|	object_type_id		|	object type ID
unsigned int	|	 Uint32				|		4			|	xheader_length		|	length of extra header
unsinged int	|	 Uint32				|		4			|	object_size			|	size of 1 object (padded to dword boundary)
unsigned int	|	 Uint32				|		4			|	object_count		|	total number of objects in payload
unsigned char	|	ArrayBuffer			|					|	xheader				|	data specific to this type of message (padded to dword boundary)
unsigned char	|	ArrayBuffer			|					|	objects				|	objects

And here are the object types:

Object type ID	|	Object
1000			|	Moxel
1001			|	Banana
1002			|	Pear


** Note:  ** If you create one of these data structures, please pad your data to the nearest dword boundary!


Suppose we send a group of moxels to the client.   The message could be decoded in JS using something like the following:

```js

// A Moxel might be defined like this:
function Moxel(){};
Moxel.prototype=object_type_id=1000;
Moxel.prototype.from_arraybuffer=function(buff){
	
	var _data=new Float64Array(buff);
	this.x=_data[0];
	this.y=_data[1];
	this.z=_data[2];
};


// Create socket
var ws = new WebSocket("ws://aether.xilabs.net:9002");
ws.binaryType="arraybuffer";
ws.onmessage = function (e) {

	// Read incoming data per Aether binary spec
    var dv = new DataView(e.data);
    var offset=0;

    // Header data
    var object_type=dv.getUint32(offset);
    var xheader_length=dv.getUint32(offset+=4);
    var object_size=dv.getUint32(offset+=4);
    var object_count=dv.getUint32(offset+=4);
    var xheader=new Uint8Array(e.data,offset+=4, xheader_length);
    var objects=[object_count];

    // Reconstitute objects
    if(object_type_id != Moxel.prototype.object_type_id) {

    	throw "Unknown object type received";
    }
    offset+=xheader_length;
    for(var n=0; n<object_count; n++){

    	var m=new Moxel();
    	m.from_arraybuffer(e.data.slice(offset, offset+=object_size));
    	objects[object_count]=m;
    }

    // Do something with the new moxels contained in objects[]
}


```








