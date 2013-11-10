
// 315, 433MHz RF Sender Test

#include <VirtualWire.h>

const int PIN_RFSEND = 9;

void setup()
{
  vw_set_tx_pin(PIN_RFSEND);
  vw_set_ptt_inverted(true); 
  vw_setup(2000);  // Bits per sec
  
  Serial.begin(9600);
  Serial.println("ready");
}

void loop()
{
    const char *msg = "hello";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println( "send" );
    digitalWrite(13, false);
    delay(2000);
  
}

