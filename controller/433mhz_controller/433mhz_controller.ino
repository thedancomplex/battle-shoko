#include "coms.h"

void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer
  coms_setup();
}

void loop() {
  if( get_message() == 0) Serial.println(s_msg.mode);
}
