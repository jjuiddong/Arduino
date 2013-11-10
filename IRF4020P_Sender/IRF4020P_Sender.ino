
#include <SoftwareSerial.h>

const int PIN_RX = 2;
const int PIN_TX = 3;
const int PIN_LED = 11;

SoftwareSerial serial(PIN_RX, PIN_TX);
void setup()
{
  serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
//  digitalWrite(DATA_PIN, LOW);
//  delay( 3000 );
//  digitalWrite(DATA_PIN, HIGH);
//  delay( 1000 ); 
  
  serial.write( 123 );
  digitalWrite( PIN_LED, LOW );
  delay( 2000 );

  serial.write( 255 );
  digitalWrite( PIN_LED, HIGH );
  delay( 2000 );

}

