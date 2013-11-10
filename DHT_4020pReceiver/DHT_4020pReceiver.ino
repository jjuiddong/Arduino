
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

//       digitalWrite(PIN_LED, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
        int header = serial.read();
        if (11 != header)
        {
          Serial.println( "header does not match" );
          Serial.print( "header = " );
          Serial.println( header );
          Serial.flush();
          return;
        }
        int humidity = serial.read();
        int temperature = serial.read();
        int irsensor = serial.read();
        
        // serial communicatione
        Serial.write((byte)header);
        Serial.write((byte)humidity);
        Serial.write((byte)temperature);
        Serial.write((byte)irsensor);

	Serial.println("");
        Serial.print("recv humdity = ");
        Serial.print(humidity, DEC);
        Serial.print("%  ");
        Serial.print("temperature = ");
        Serial.print(temperature, DEC);
        Serial.print("C  ");
        Serial.print("ir sensor = ");
        Serial.print(irsensor, DEC);
        Serial.println("  ");

//        digitalWrite(PIN_LED, LOW);
  }
}

