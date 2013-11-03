
<html>
  <head>
    <title>WebGL Demo</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link rel="stylesheet" href="webgl.css" type="text/css">
    <script src="sylvester.js" type="text/javascript"></script>
    <script src="glUtils.js" type="text/javascript"></script>
    <script src="webgl.js" type="text/javascript"></script>

    <!-- Fragment shader program -->

    <script id="shader-fs" type="x-shader/x-fragment">
    	varying lowp vec4 vColor;
    	
      void main(void) {
        gl_FragColor = vColor;
      }
    </script>
    
    <!-- Vertex shader program -->
    
    <script id="shader-vs" type="x-shader/x-vertex">
      attribute vec3 aVertexPosition;
      attribute vec4 aVertexColor;
    
      uniform mat4 uMVMatrix;
      uniform mat4 uPMatrix;
      
			varying lowp vec4 vColor;
    
      void main(void) {
        gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
        vColor = aVertexColor;
      }
    </script>
  </head>
  
  <body onload="start()">
    <canvas id="glcanvas" width="640" height="480">
      Your browser doesn't appear to support the HTML5 <code>&lt;canvas&gt;</code> element.
    </canvas>
  </body>
</html>