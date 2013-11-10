

// 315, 433MHz RF Sender Test

#include <VirtualWire.h>

const int PIN_RFSEND = 9;
const int PIN_DHT11 = A0;
const int PIN_LED = 7;

byte Temperature = 0;
byte Humdity = 0;

byte read_dht11_dat()
{
  byte i = 0;
  byte result=0;
  for(i=0; i< 8; i++)
  {
    while (!digitalRead(PIN_DHT11));
    delayMicroseconds(30);
    if (digitalRead(PIN_DHT11) != 0 )
      bitSet(result, 7-i);
    while (digitalRead(PIN_DHT11));
  }
  return result;
}

void Init_DHT11()
{
  pinMode(PIN_DHT11, OUTPUT);
  digitalWrite(PIN_DHT11, HIGH);  
}

boolean Sensing_DHT11()
{
 byte dht11_dat[5];   
  byte dht11_in;
  byte i;// start condition
       
  digitalWrite(PIN_DHT11, LOW);
  delay(18);
  digitalWrite(PIN_DHT11, HIGH);
  delayMicroseconds(1);
  pinMode(PIN_DHT11, INPUT);
  delayMicroseconds(40);     
   
  if (digitalRead(PIN_DHT11))
  {
    Serial.println("dht11 start condition 1 not met"); // wait for DHT response signal: LOW
    delay(1000);
    return false;
  }
  delayMicroseconds(80);
  if (!digitalRead(PIN_DHT11))
  {
    Serial.println("dht11 start condition 2 not met");  //wair for second response signal:HIGH
    return false;
  }
    
  delayMicroseconds(80);// now ready for data reception
  for (i=0; i<5; i++)
  {  dht11_dat[i] = read_dht11_dat();}  //recieved 40 bits data. Details are described in datasheet
    
  pinMode(PIN_DHT11, OUTPUT);
  digitalWrite(PIN_DHT11, HIGH);
  byte dht11_check_sum = dht11_dat[0]+dht11_dat[2];// check check_sum
  if(dht11_dat[4]!= dht11_check_sum)
  {
    Serial.println("DHT11 checksum error");
  }  
  
  Serial.print("Current humdity = ");
  Serial.print(dht11_dat[0], DEC);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(dht11_dat[2], DEC);
  Serial.println("C  ");
  
  Humdity = dht11_dat[0];
  Temperature = dht11_dat[2];  
  return true;
}
  
void setup()
{
  vw_set_tx_pin(PIN_RFSEND);
  vw_set_ptt_inverted(true); 
  vw_setup(1000);  // Bits per sec
  
  Init_DHT11();
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
  Serial.println("ready");
}

void loop()
{
 
  if (Sensing_DHT11())
  {
    digitalWrite(PIN_LED, HIGH);
    byte packet[ 3];
    packet[ 0] = 11; // header
    packet[ 1] = Humdity;
    packet[ 2] = Temperature;    
    vw_send((byte*)packet, sizeof(packet));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(PIN_LED, LOW);
  }

  delay(2000);  
}

