
// LHI-878 sensor test
// S pin 47k ohm pull down
// D pin 10k ohm pull up

const int PIN_SENSOR = A1;
void setup()
{
  Serial.begin(9600);
  pinMode( PIN_SENSOR, INPUT);
}

void loop()
{
  int sensorData = analogRead(PIN_SENSOR);
  Serial.println( sensorData );
}


