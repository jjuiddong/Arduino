
const int DATA_PIN = 10;
const int SENSOR_PIN = 6;
const int SPEAKER_PIN = 5;
const int STATE_PIN = 4;
int State = 0; // 0 = normal state
               // 1 = error state
int oldMillis = 0;
int incMillis = 0;
boolean stateLED = true;

int SenderState = 0;  // 0=Low
                      // 1=High
int SenderMillis = 0;

float SpeakerTone = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);  
  pinMode(SENSOR_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(STATE_PIN, OUTPUT);

  digitalWrite(SPEAKER_PIN, LOW);
  digitalWrite(STATE_PIN, HIGH);
}

// type = 0 : cos
// type = 1 : sin
void WarningSound(int type)
{
    double val = 0.f;
    if (type == 0)
    {
      val = cos( SpeakerTone );
      analogWrite(SPEAKER_PIN, val * 255);
    }
    else
    {
      val = cos( SpeakerTone*8 );
      analogWrite(SPEAKER_PIN, val * 10);
    }
}

void WarningSoundOff()
{
  digitalWrite(SPEAKER_PIN, LOW);
}

void loop()
{
  const int elapse = millis() - oldMillis;
  incMillis += elapse;
  SenderMillis += elapse;
  oldMillis = millis();
  
   SpeakerTone += 0.1f;  

  int sensor = digitalRead(SENSOR_PIN);
  Serial.print( "sensor " );
  Serial.println( sensor );
  Serial.print( "RFSenderState " );
  Serial.println( State );
  Serial.print( "senderMillis " );  
  Serial.println( SenderMillis );
  
  if (incMillis > 1000)
  {
    //    stateLED = !stateLED;
    //    digitalWrite(STATE_PIN, stateLED? HIGH : LOW );
    //    incMillis = 0;   
  }

  if (sensor == 0) // sensor disconnect
  {
    digitalWrite(DATA_PIN, LOW);
    digitalWrite(SPEAKER_PIN, HIGH);
    State = 1; // error occure
  }
  
  if (State == 0)
  {
    if (SenderMillis < 2000)
    {
      SenderState = 0;
    }
    else
    {
      SenderState = 1;
    }
    
    if (SenderMillis > 4000)
      SenderMillis = 0;    
    digitalWrite(DATA_PIN, (SenderState==1)? HIGH : LOW);     
    
    if (SenderState == 0 && SenderMillis < 200)
    {
      WarningSound(1);
    }
    else
    {
      WarningSoundOff();
    }
  }
  else if (State == 1)
  {
    WarningSound(0);
//    SpeakerTone += 0.1f;
  //  double val = cos( SpeakerTone );
    //analogWrite(SPEAKER_PIN, val * 255);
  }
  
}

