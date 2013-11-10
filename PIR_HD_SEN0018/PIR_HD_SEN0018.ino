// HD-SEN0018 test

const int PIN_SENSOR = 11;
const int PIN_STATE = 10;

//----------------------------------------------------------------
// Sound Library
const int PIN_SOUND = 9;
void SoundInit()
{
  pinMode(PIN_SOUND, OUTPUT);  
  digitalWrite(PIN_SOUND, LOW);  
}

// type = 0 : cos
// type = 1 : sin
void SoundOn(int type)
{
  static float SpeakerTone = 0.f;
  SpeakerTone += 0.01f;
  
    double val = 0.f;
    if (type == 0)
    {
      val = cos( SpeakerTone );
      analogWrite(PIN_SOUND, val * 255);
    }
    else
    {
      val = cos( SpeakerTone*8 );
      analogWrite(PIN_SOUND, val * 255);
    }
    
    if( SpeakerTone > 3.1415f)
      SpeakerTone = 0.f;
    
}
void SoundOff()
{
  digitalWrite(PIN_SOUND, LOW);
}
//----------------------------------------------------------------


void setup()
{
  //SoundInit();
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_STATE, OUTPUT);
  digitalWrite(PIN_STATE, LOW);
}

void loop()
{
  const int sensor = digitalRead(PIN_SENSOR);
  if (sensor > 0)
  {
    //SoundOn(1);
    Serial.write( (byte)1 );
//    Serial.println( " 1 " );
    digitalWrite(PIN_STATE, HIGH);
  }
  else
  {
    //SoundOff();
    Serial.write( (byte)0 );
//    Serial.println( " 0 " );
    digitalWrite(PIN_STATE, LOW);    
  }
}

