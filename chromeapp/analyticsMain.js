var ws;
                ws = new WebSocket("ws://aether.xilabs.net:9002");
                ws.binaryType="arraybuffer";
              
            var a = new Analysis();
            
            ws.onmessage = function (e) {
                
                var dv = new DataView(e.data);
                var offset = 0;
                var object_type=dv.getUint32(offset, true);
                var xheader_length=dv.getUint32(offset+=4, true);
		var object_size=dv.getUint32(offset+=4, true);
		var object_count=dv.getUint32(offset+=4, true);
		var xheader=new Uint8Array(e.data,offset+=4, xheader_length);
                
                a.currentTime = new Date().getTime();
                if (a.iter == 0) {
                    a.lastTime = a.currentTime;
                }
                var d = new Date();
                a.currentGap = a.currentTime - a.lastTime;
                var thisSecond = Math.round(a.currentTime/1000);
                var lastSecond =Math.round(a.lastTime/1000);
                if (thisSecond == lastSecond) {
                    a.messagesThisSecond++;
                } else {
                    a.messagesPerSecond = a.messagesThisSecond;
                    a.messagesThisSecond = 0;
                }
                a.lastTime = a.currentTime;
                a.arrayOfGaps.push(a.currentGap);
                if (a.arrayOfGaps.length > 100) {
                    a.arrayOfGaps.splice(0,1);
                }
                a.averageMessageGap();
                a.iter++;
                a.getStandardDev();
                var bla = a.messagesPerSecond * a.averageGap;
                var header = "<div class='col1'>Gap</div><div class='col2'>Av G</div><div class='col3'>M/s</div><div class='col4'>S Dev</div><div class='col5'>Time</div><div style='clear: both;'>";
                var lala = "<div class='col1'>" + a.currentGap +  "</div><div class='col2'>" + a.averageGap + "</div><div class='col3'>" + a.messagesPerSecond + "</div><div class='col4'>" + a.standardDev + "</div><div class='col5'>" + d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds() + "</div><div class='col6'>" + object_type + " " + xheader_length + " " + object_size + " " + object_count + "</div><div style='clear: both;'>";
                a.messageArray.push(lala);
                if (a.messageArray.length > 30) {
                    a.messageArray.splice(0,1);
                }
                var tempMessageArray = a.messageArray.slice(0);
                tempMessageArray.push(header);
                tempMessageArray.reverse();
                var message = "";
                var i = 0;
                while (tempMessageArray[i]) {
                    
                    message = message + tempMessageArray[i];
                    i++;
                }
                
               $("#results").html(message);
                                
            }
                
            function Analysis() {
                this.iter = 0;
                this.currentGap = 0;
                this.currentTime = new Date();
                this.averageGap = 0;
                this.lastTime = 0;
                this.arrayOfGaps = new Array();
                this.standardDev = 0;
                this.messageArray = new Array();
                this.sum;
                this.messagesThisSecond = 0;
                this.messagesPerSecond = 0;
                this.standardDev;
                
                this.averageMessageGap = function() {
                    var sum = 0;
                    
                    for(var i=0; i<this.arrayOfGaps.length; i++){
                        
                        sum = this.arrayOfGaps[i] + sum;
                        
                    }
                    this.sum = sum;
                    
                    this.averageGap = Math.round(sum/this.arrayOfGaps.length);
                };
                this.getStandardDev = function() {
                    var sum = 0;
                    
                    for(var i=0; i<this.arrayOfGaps.length; i++){
                        
                        var stdVal = (this.arrayOfGaps[i] - this.averageGap)*(this.arrayOfGaps[i] - this.averageGap);
                        sum = stdVal + sum;
                        
                    }
                    this.standardDev = Math.round(Math.sqrt(sum/this.arrayOfGaps.length));
                };
            }