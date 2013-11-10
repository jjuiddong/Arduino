
// 315, 433MHz RF Receiver Test

#include <VirtualWire.h>

const int PIN_RFRECEIVE = A1;

void setup()
{
  vw_set_rx_pin(PIN_RFRECEIVE);
  vw_set_ptt_inverted(true); 
  vw_setup(2000);  // Bits per sec
  vw_rx_start(); 
    
  Serial.begin(9600); 
  Serial.println( "ready");
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
	int i;

        digitalWrite(13, true); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
	    Serial.print(buf[i], HEX);
	    Serial.print(" ");
	}
	Serial.println("");
  }
}

