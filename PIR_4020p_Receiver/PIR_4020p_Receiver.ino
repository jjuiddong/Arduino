
// humidity, temperature, infrared sensor 
// using irf4020p module
// Receiver

#include <SoftwareSerial.h>

const int PIN_LED = 7;
const int PIN_RFRECEIVE = A0;
const int PIN_RX = 2;
const int PIN_TX = 3;
SoftwareSerial serial(PIN_RX, PIN_TX);

void setup()
{
  Serial.begin(9600); 
  Serial.println("recv ready");
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW); // Flash a light to show received good message

  serial.begin(9600);
}

void loop()
{
  if (0 < serial.available()) // Non-blocking
  {
	int i;
        delay( 100 );

        // Message with a good checksum received, dump it.
        byte header = serial.read();
        if (12 != header)
        {
          Serial.println( "header does not match" );
          Serial.print( "header = " );
          Serial.println( header );
          serial.flush();
          return;
        }
        byte sensor = serial.read();
        
        // serial communicatione
        //Serial.write((byte)header);
        //Serial.write((byte)sensor);

	Serial.println("");
        Serial.print("sensor = ");
        Serial.print(sensor, DEC);
        Serial.println("  ");

        digitalWrite(PIN_LED, (sensor == 0)? LOW : HIGH); // Flash a light to show received good message
  }
}

