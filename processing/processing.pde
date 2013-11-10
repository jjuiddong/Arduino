/*
 import processing.serial.*;
 
 Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 
 void setup () 
 {
   // set the window size:
   size(400, 300);
   
   // List all the available serial ports
   println(Serial.list());
   // I know that the first port in the serial list on my mac
   // is always my  Arduino, so I open Serial.list()[0].
   // Open whatever port is the one you're using.
   myPort = new Serial(this, Serial.list()[2], 9600);
   // don't generate a serialEvent() unless you get a newline character:
   myPort.bufferUntil('\n');
   // set inital background:
   background(0);
 }
 
 void draw () 
 {
   // everything happens in the serialEvent()
 }
 
 void serialEvent (Serial myPort) 
 {
   // get the ASCII string:
   String inString = myPort.readStringUntil('\n');
   
   if (inString != null) 
   {
     // trim off any whitespace:
     inString = trim(inString);
     // convert to an int and map to the screen height:
     float inByte = float(inString); 
     inByte = map(inByte, 0, 1023, 0, height);
     
     // draw the line:
     stroke(127,34,255);
     line(xPos, height, xPos, height - inByte);
     
     // at the edge of the screen, go back to the beginning:
     if (xPos >= width) 
     {
       xPos = 0;
       background(0); 
     } 
     else 
     {
       // increment the horizontal position:
       xPos++;
     }
   }
 }
 /**/
 
 
 import processing.serial.*; 
 
 float boxX;
 float boxY;
 int boxSize = 40;
 boolean mouseOverBox = false;
 
 Serial port; 
 
 void setup()  {
 size(300, 300);
 boxX = width/2.0;
 boxY = height/2.0;
 rectMode(RADIUS); 
 
 // List all the available serial ports in the output pane. 
 // You will need to choose the port that the Arduino board is 
 // connected to from this list. The first port in the list is 
 // port #0 and the third port in the list is port #2. 
 println(Serial.list()); 
 
 // Open the port that the Arduino board is connected to (in this case #0) 
 // Make sure to open the port at the same speed Arduino is using (9600bps) 
 port = new Serial(this, Serial.list()[2], 9600); 
 
 }
 
 void draw() 
 { 
   background(0);
   
   // Test if the cursor is over the box 
   if (mouseX > boxX-boxSize && mouseX < boxX+boxSize && 
       mouseY > boxY-boxSize && mouseY < boxY+boxSize) 
   {
     mouseOverBox = true;  
     // draw a line around the box and change its color:
     stroke(255); 
     fill(153);
     // send an 'H' to indicate mouse is over square:
     port.write('H');       
   } 
   else 
   {
     // return the box to it's inactive state:
     stroke(153);
     fill(153);
     // send an 'L' to turn the LED off: 
     port.write('L');      
     mouseOverBox = false;
   }
   
   // Draw the box
   rect(boxX, boxY, boxSize, boxSize);
 }
 
