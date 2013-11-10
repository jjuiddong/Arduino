import processing.core.*; 
import processing.data.*; 
import processing.opengl.*; 

import processing.serial.*; 
import processing.serial.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class processing extends PApplet {

/*
 
 
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
 
 
  
 
 float boxX;
 float boxY;
 int boxSize = 40;
 boolean mouseOverBox = false;
 
 Serial port; 
 
 public void setup()  {
 size(300, 300);
 boxX = width/2.0f;
 boxY = height/2.0f;
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
 
 public void draw() 
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
 
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
