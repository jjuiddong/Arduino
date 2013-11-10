
#include <SoftwareSerial.h>
#include <VirtualWire.h>

const int PIN_RX = 2;
const int PIN_TX = 3;
const int PIN_LED = 12;
boolean isLED_On = false;

SoftwareSerial serial(PIN_RX, PIN_TX);
void setup()
{
  serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
 
}

void loop()
{
//  int data = analogRead(INPUT_PIN);
//  Serial.println( data );

    if (serial.available() > 0)
    {
      int data = serial.read();
//      Serial.println( data );
      digitalWrite(PIN_LED, (data==255)? HIGH : LOW);      
      isLED_On = !isLED_On;      
    }

}

