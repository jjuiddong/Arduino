
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
  SoundInit();
}

void loop()
{
  SoundOn( 1  );
  
}

