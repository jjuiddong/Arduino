
// HD-SEN0018 test

#include <SoftwareSerial.h>

const int PIN_SENSOR = 11;
const int PIN_STATE = 10;

const int PIN_RX = 2;
const int PIN_TX = 3;
SoftwareSerial serial(PIN_RX, PIN_TX);

void setup()
{
  Serial.begin(9600);
  serial.begin(9600);
}

void loop()
{
  static int oldSensor = -1;
  int sensor = digitalRead(PIN_SENSOR);
  if (sensor > 0)
  {
    if (oldSensor != sensor)
    {
      serial.write( (byte)12 );
      serial.write( (byte)1 );
      Serial.write( (byte)1 );
    }
  }
  else
  {
    if (oldSensor != sensor)
    {
      serial.write( (byte)12 );
      serial.write( (byte)0 );
      Serial.write( (byte)0 );
    }    
  }
  
  oldSensor = sensor;  
}

