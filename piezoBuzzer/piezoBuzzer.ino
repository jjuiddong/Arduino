
const int OUT_PIN = 9;

void setup()
{
  pinMode(OUT_PIN, OUTPUT);
  
  Serial.begin(9600);
}

float g_x = 0;
void loop()
{
  g_x += 0.01f;
  double y = cos( g_x );
  int vol = y*128 + 128; 
  Serial.println( vol );
  
  analogWrite(OUT_PIN, vol);
//digitalWrite(OUT_PIN, HIGH);
}

